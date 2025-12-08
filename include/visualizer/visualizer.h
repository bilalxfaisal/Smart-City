#include "SFML/Graphics.hpp"
#include "../utils/Nodes.h"
#include <string>



///
/// How to set this up:
/// 1. set up the grid by calling initializeIslamabadSectorGrid() once at program start.
/// 2. set up the visualizer object.
/// 3. set up the SFML window and font.
/// 4. set up the location head and sector pop head in the visualizer.
/// 5. set the min and max population in the visualizer.
/// 6. in the main loop, call visualizer.run() with the window and font.
/// 7. it will do the rest itself/
///
/// Instructions to use:
/// left click will zoom in on a sector
/// right click will zoom out
/// press 'H' to toggle heatmap mode
/// press 'Enter' to exit heatmap mode
/// 


// Struct to hold sector info
struct SectorBounds {
    std::string name = "";
    float topLeftX = 0.0;
    float topLeftY = 0.0;
};

// Fixed array — no STL containers used beyond std::string
const int TOTAL_SECTORS = 56; // 7 rows (D-J) × 8 cols (5-12)
static SectorBounds ISLAMABAD_SECTORS[TOTAL_SECTORS];

// Initialize the grid once (call this in your Visualizer constructor or main)
void initializeIslamabadSectorGrid() {
    const int ROWS = 7;          // D (0) to J (6)
    const int COLS = 8;          // 5 (0) to 12 (7)
    const int SECTOR_SIZE = 90;
    const int START_X = 80;
    const int START_Y = 50;

    int index = 0;
    for (int r = 0; r < ROWS; ++r) {
        char rowLetter = 'D' + r;
        for (int c = 0; c < COLS; ++c) {
            int colNumber = 5 + c;
            std::string name = std::string(1, rowLetter) + "-" + std::to_string(colNumber);

            ISLAMABAD_SECTORS[index].name = name;
            ISLAMABAD_SECTORS[index].topLeftX = START_X + c * SECTOR_SIZE;
            ISLAMABAD_SECTORS[index].topLeftY = START_Y + r * SECTOR_SIZE;
            ++index;
        }
    }
}

// Lookup function: returns true if found, and fills out bounds
bool getSectorTopLeft(const std::string& sectorName, float& outX, float& outY) {
    for (int i = 0; i < TOTAL_SECTORS; ++i) {
        if (ISLAMABAD_SECTORS[i].name == sectorName) {
            outX = ISLAMABAD_SECTORS[i].topLeftX;
            outY = ISLAMABAD_SECTORS[i].topLeftY;
            return true;
        }
    }
    return false; // not found
}


class Visualizer {
private:
    static const int ROWS = 7;          // D to J
    static const int COLS = 8;          // 5 to 12
    static const int SECTOR_SIZE = 90;
    static const int START_X = 80;
    static const int START_Y = 50;
    static const int WINDOW_WIDTH = 900;
    static const int WINDOW_HEIGHT = 700;
    static const int ZOOMED_AREA_SIZE = 600;

    bool isZoomedIn = false;
	bool HeatMapMode = false;
    int zoomedRow = -1;
    int zoomedCol = -1;

    Location* location; // head of all Locations
	SectorPopNode* sectorPopHead; // head of sector population list
	int minPop = INT_MAX;
	int maxPop = INT_MIN;

    char getRowLetter(int r) const { return static_cast<char>('D' + r); }
    int getColNumber(int c) const { return 5 + c; }

    std::string getSectorName(int r, int c) const {
        return std::string(1, getRowLetter(r)) + "-" + std::to_string(getColNumber(c));
    }

    // Helper to get sector bounds
    void getSectorBounds(int row, int col, float& left, float& top, float& right, float& bottom) const {
        left = START_X + col * SECTOR_SIZE;
        top = START_Y + row * SECTOR_SIZE;
        right = left + SECTOR_SIZE;
        bottom = top + SECTOR_SIZE;
    }

    // Check if a location is within a sector
    bool isInSector(Location* loc, int row, int col) const {
        float left, top, right, bottom;
        getSectorBounds(row, col, left, top, right, bottom);
        return loc->x >= left && loc->x <= right && loc->y >= top && loc->y <= bottom;
    }

public:
    Visualizer() {
        location = nullptr;
    }

    ~Visualizer() {
        // Cleanup handled elsewhere
    }

    void drawGrid(sf::RenderWindow& window) {
        // Vertical lines
        for (int c = 0; c <= COLS; ++c) {
            float x = START_X + c * SECTOR_SIZE;
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, START_Y)),
                sf::Vertex(sf::Vector2f(x, START_Y + ROWS * SECTOR_SIZE))
            };
            window.draw(line, 2, sf::Lines);
        }

        // Horizontal lines
        for (int r = 0; r <= ROWS; ++r) {
            float y = START_Y + r * SECTOR_SIZE;
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(START_X, y)),
                sf::Vertex(sf::Vector2f(START_X + COLS * SECTOR_SIZE, y))
            };
            window.draw(line, 2, sf::Lines);
        }

        // Corner dots (intersections)
        sf::CircleShape dot(4);
        dot.setFillColor(sf::Color::Green);
        for (int r = 0; r <= ROWS; ++r) {
            for (int c = 0; c <= COLS; ++c) {
                dot.setPosition(
                    START_X + c * SECTOR_SIZE - 4,
                    START_Y + r * SECTOR_SIZE - 4
                );
                window.draw(dot);
            }
        }
    }

    void drawLabels(sf::RenderWindow& window, const sf::Font& font) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::White);

        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                text.setString(getSectorName(r, c));
                text.setPosition(
                    START_X + c * SECTOR_SIZE + 5,
                    START_Y + r * SECTOR_SIZE + (SECTOR_SIZE - 20) / 2
                );
                window.draw(text);
            }
        }
    }

    void displayNode(sf::RenderWindow& window, Location* loc) const {
        sf::CircleShape circle(4);

        // Different colors for different types
        if (loc->type == "Intersection") {
            circle.setFillColor(sf::Color::Green);
        }
        else {
            const sf::Color orange(255, 165, 0);
            circle.setFillColor(orange);
        }

        circle.setOrigin(4, 4);
        circle.setPosition(static_cast<float>(loc->x), static_cast<float>(loc->y));
        window.draw(circle);
    }

    void displayEdges(sf::RenderWindow& window, Location* loc) const {
        sf::Vertex EdgeLine[2];
        EdgeLine[0].position = sf::Vector2f(static_cast<float>(loc->x), static_cast<float>(loc->y));
        EdgeLine[0].color = sf::Color(220, 220, 220);

        Edge* dest = loc->adjList;
        while (dest) {
            EdgeLine[1].position = sf::Vector2f(
                static_cast<float>(dest->destination->x),
                static_cast<float>(dest->destination->y)
            );
            EdgeLine[1].color = sf::Color(220, 220, 220);
            window.draw(EdgeLine, 2, sf::Lines);
            dest = dest->nextEdge;
        }
    }

    void showAllLocations(sf::RenderWindow& window) const {
        Location* curr = location;
        while (curr) {
            displayEdges(window, curr);
            curr = curr->next;
        }

        // Draw nodes on top of edges
        curr = location;
        while (curr) {
            displayNode(window, curr);
            curr = curr->next;
        }
    }

    void setLocationHead(Location* head) {
        location = head;
    }

    void removeLocationHead() {
        location = nullptr;
	}

    void setSectorPopHead(SectorPopNode* head) {
        sectorPopHead = head;
	}
    void setMinMaxPop(int minP, int maxP) {
        minPop = minP;
        maxPop = maxP;
	}

    Location* getLocationHead() const {
        return location;
    }

    void run() {
        // Create SFML window
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Islamabad Sector Visualizer");
        window.setFramerateLimit(60);

        // Load font
        sf::Font font;
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            if (!font.loadFromFile("arial.ttf")) {
                return; // Can't run without font
            }
        }

        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            bool hasEvent = false;

            while (window.pollEvent(event)) {
                hasEvent = true;
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Handle zoom in/out
                handleInput(event);
            }

            // Draw frame
            if(!HeatMapMode){
                draw(window, font);
            }
            else {
                // HeatMapMode drawing logic here
                window.clear(sf::Color::Black);
				drawHeatMap(window, font);
            }
            window.display();
        }
    }

    void handleInput(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && !isZoomedIn && !HeatMapMode) {
                int clickX = event.mouseButton.x;
                int clickY = event.mouseButton.y;
                int col = (clickX - START_X) / SECTOR_SIZE;
                int row = (clickY - START_Y) / SECTOR_SIZE;
                if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                    zoomedRow = row;
                    zoomedCol = col;
                    isZoomedIn = true;
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right && isZoomedIn) {
                isZoomedIn = false;
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::H && !isZoomedIn && !HeatMapMode) {
                HeatMapMode = true;
            }
            else if (event.key.code == sf::Keyboard::Enter && HeatMapMode) {
                HeatMapMode = false;
            }
        }
    }

    void draw(sf::RenderWindow& window, const sf::Font& font) {
        window.clear(sf::Color::Black);

        if (isZoomedIn) {
            // ===== ZOOMED VIEW USING sf::View =====

            // Calculate center of the clicked sector
            float sectorCenterX = START_X + zoomedCol * SECTOR_SIZE + SECTOR_SIZE / 2.0f;
            float sectorCenterY = START_Y + zoomedRow * SECTOR_SIZE + SECTOR_SIZE / 2.0f;

            // Create a view centered on the sector
            sf::View zoomedView;
            zoomedView.setCenter(sectorCenterX, sectorCenterY);

            // Set view size to show just the sector (with a bit of padding)
            float viewWidth = SECTOR_SIZE * 1.1f;  // 10% padding
            float viewHeight = SECTOR_SIZE * 1.1f;
            zoomedView.setSize(viewWidth, viewHeight);

            // Set viewport to fill the window
            zoomedView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

            // Apply the view
            window.setView(zoomedView);

            // Get sector bounds for filtering
            float origLeft, origTop, origRight, origBottom;
            getSectorBounds(zoomedRow, zoomedCol, origLeft, origTop, origRight, origBottom);

            // Draw sector boundary box
            sf::RectangleShape boundary(sf::Vector2f(SECTOR_SIZE, SECTOR_SIZE));
            boundary.setPosition(origLeft, origTop);
            boundary.setFillColor(sf::Color::Transparent);
            boundary.setOutlineColor(sf::Color::White);
            boundary.setOutlineThickness(1);
            window.draw(boundary);

            // Draw edges (only within this sector)
            Location* curr = location;
            while (curr) {
                if (isInSector(curr, zoomedRow, zoomedCol)) {
                    Edge* edge = curr->adjList;
                    while (edge) {
                        Location* dest = edge->destination;
                        if (isInSector(dest, zoomedRow, zoomedCol)) {
                            sf::Vertex line[] = {
                                sf::Vertex(sf::Vector2f(curr->x, curr->y), sf::Color(200, 200, 200)),
                                sf::Vertex(sf::Vector2f(dest->x, dest->y), sf::Color(200, 200, 200))
                            };
                            window.draw(line, 2, sf::Lines);
                        }
                        edge = edge->nextEdge;
                    }
                }
                curr = curr->next;
            }

            // Draw nodes (only within this sector)
            curr = location;
            while (curr) {
                if (isInSector(curr, zoomedRow, zoomedCol)) {
                    sf::CircleShape circle(2); // Size relative to world coordinates
                    circle.setOrigin(2, 2);

                    if (curr->type == "Intersection") {
                        circle.setFillColor(sf::Color::Green);
                    }
                    else {
                        circle.setFillColor(sf::Color(255, 165, 0));
                    }

                    circle.setPosition(curr->x, curr->y);
                    window.draw(circle);

                    // Draw location name
                    sf::Text nameText;
                    nameText.setFont(font);
                    nameText.setString(curr->name);
                    nameText.setCharacterSize(8); // Smaller for world coordinates
                    nameText.setFillColor(sf::Color::White);
                    nameText.setPosition(curr->x + 3, curr->y - 4);
                    window.draw(nameText);
                }
                curr = curr->next;
            }

            // Reset to default view for UI elements
            window.setView(window.getDefaultView());

            // Draw UI elements in screen space
            sf::Text label;
            label.setFont(font);
            label.setString("Sector: " + getSectorName(zoomedRow, zoomedCol));
            label.setCharacterSize(28);
            label.setFillColor(sf::Color::White);
            label.setPosition(20, 10);
            window.draw(label);

            sf::Text instruction;
            instruction.setFont(font);
            instruction.setString("Right-click to zoom out");
            instruction.setCharacterSize(14);
            instruction.setFillColor(sf::Color(180, 180, 180));
            instruction.setPosition(20, WINDOW_HEIGHT - 40);
            window.draw(instruction);
        }
        else {
            // ===== FULL VIEW =====
            // Use default view
            window.setView(window.getDefaultView());

            drawGrid(window);
            drawLabels(window, font);
            showAllLocations(window);

            // Instructions
            sf::Text instruction;
            instruction.setFont(font);
            instruction.setString("Left-click a sector to zoom in");
            instruction.setCharacterSize(14);
            instruction.setFillColor(sf::Color(180, 180, 180));
            instruction.setPosition(START_X, WINDOW_HEIGHT - 40);
            window.draw(instruction);
        }
    }


    void drawHeatMap(sf::RenderWindow& window, sf::Font& font) {
		drawGrid(window);
		drawLabels(window, font);
		// TO DO: Implement heat map drawing logic here
        SectorPopNode* head = sectorPopHead;
        int min = minPop;
		int max = maxPop;
		while (head) {
			float topLeftX, topLeftY;
            if (getSectorTopLeft(head->sectorName, topLeftX, topLeftY)) {
					// this will output 0.0 to 1.0
                    float intensity = static_cast<float>(head->population - min) / (max - min);
					sf::Color redColor = sf::Color(255, 0, 0, intensity * 255);
					sf::RectangleShape rectangle(sf::Vector2f(SECTOR_SIZE, SECTOR_SIZE));
					rectangle.setPosition(topLeftX, topLeftY);
					rectangle.setFillColor(redColor);
					window.draw(rectangle);

            }
            else {
                // Sector name not found
				// no need to do anything here for now
            }
			head = head->next;
        }
        
	}
};