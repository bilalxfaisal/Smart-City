#include "SFML/Graphics.hpp"
#include "../utils/Nodes.h"
#include "../population/Sector.h"


/// <summary>
/// id = 0  for universal node
/// </summary>




class Visualizer {
private:
    static const int ROWS = 7;
    static const int COLS = 8;
    static const int SECTOR_SIZE = 90;
    static const int START_X = 80;
    static const int START_Y = 50;

    Sector** sectors;

    // head of all Locations
    Location* location;

    char getRowLetter(int r) const { return 'D' + r; }
    int getColNumber(int c) const { return 5 + c; }

    std::string getSectorName(int r, int c) const {
        std::string name = std::string(1, getRowLetter(r)) + "-" + std::to_string(getColNumber(c));
        return name;
    }

public:
    Visualizer() {
        sectors = new Sector * [ROWS];
        for (int r = 0; r < ROWS; ++r) {
            sectors[r] = new Sector[COLS];
            for (int c = 0; c < COLS; ++c) {
                sectors[r][c].setName(getSectorName(r, c));
            }
        }
        location = nullptr;
    }

    ~Visualizer() {
        for (int r = 0; r < ROWS; ++r) delete[] sectors[r];
        delete[] sectors;
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

        // Corner dots at intersections
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
                text.setString(sectors[r][c].getName());
                text.setPosition(
                    START_X + c * SECTOR_SIZE + 5,
                    START_Y + r * SECTOR_SIZE + (SECTOR_SIZE - 20) / 2
                );
                window.draw(text);
            }
        }
    }

    void draw(sf::RenderWindow& window, const sf::Font& font) {
        drawGrid(window);
        drawLabels(window, font);
    }

    void addLocationHead(Location& loc) {
        Location* newLoc = new Location(loc);
    }

    void deleteLocationHead() {
        location = nullptr;
    }

    void showAllLocations(sf::RenderWindow& window) const {
        Location* curr = location;
        while (curr)
        {
            displayNode(window, curr);
            displayEdges(window, curr);
        }
    }
    void displayNode(sf::RenderWindow& window, Location* loc) const {
        sf::CircleShape circle(4);
        const sf::Color orange(255, 165, 0);
        if (loc->ID == 1) circle.setFillColor(sf::Color::Red);
        else if (loc->ID == 2) circle.setFillColor(sf::Color::Blue);
        else if (loc->ID == 3) circle.setFillColor(sf::Color::Yellow);
        else if (loc->ID == 4) circle.setFillColor(sf::Color::Cyan);
        else if (loc->ID == 5) circle.setFillColor(sf::Color::Magenta);
        else circle.setFillColor(orange);

        circle.setOrigin(4, 4);
        circle.setPosition(static_cast<float>(loc->x), static_cast<float>(loc->y));
        window.draw(circle);
    }

    void displayEdges(sf::RenderWindow& window, Location* loc) const {
		sf::Vertex EdgeLine[2];
		EdgeLine[0].position = sf::Vector2f(float(loc->x), float(loc->y));
		Edge* dest = loc->adjList;
        while (dest) {
            EdgeLine[1].position = sf::Vector2f(float(dest->destination->x), float(dest->destination->y));
            window.draw(EdgeLine, 2, sf::Lines);
			dest = dest->nextEdge;
        }
    }
};