#ifndef LOCATION_MANAGER
#define LOCATION_MANAGER

#include "../utils/Nodes.h"
#include "../population/Sector.h" 
#include <iostream>
#include <string>
#include <cmath>   
#include <cstdlib> 
#include <limits>  

using std::string;
using std::cout;
using std::to_string;
using std::stoi;

// Simple struct to return the path as a Linked List
struct PathNode {
    Location* loc;
    PathNode* next;
    PathNode(Location* l) : loc(l), next(nullptr) {}
};

// A simple Min-Heap for Dijkstra
class MinHeap
{
private:
    struct HeapNode
    {
        Location* loc;
        float dist;
    };
    HeapNode* array;
    int capacity;
    int size;

public:
    MinHeap(int cap)
    {
        capacity = cap;
        size = 0;
        array = new HeapNode[cap];
    }
    ~MinHeap() { delete[] array; }

    bool isEmpty() { return size == 0; }

    void push(Location* loc, float dist) {
        if (size == capacity) return;
        int i = size++;
        array[i] = { loc, dist };

        while (i > 0 && array[(i - 1) / 2].dist > array[i].dist) {
            std::swap(array[i], array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    Location* extractMin() {
        if (size == 0) return nullptr;
        Location* minLoc = array[0].loc;

        array[0] = array[--size];
        int i = 0;
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size && array[left].dist < array[smallest].dist) smallest = left;
            if (right < size && array[right].dist < array[smallest].dist) smallest = right;

            if (smallest == i) break;
            std::swap(array[i], array[smallest]);
            i = smallest;
        }
        return minLoc;
    }
};

class locationManager
{
private:
    static const int SECTOR_SIZE = 70;
    Location* cityLocationHead = nullptr;


    Sector* sectors[100];
    int sectorCount = 0;

    Location* findLocationAt(int x, int y)
    {
        Location* temp = cityLocationHead;
        while (temp) {
            if (temp->x == x && temp->y == y)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    Location* getOrCreateNode(int x, int y, string type)
    {
        Location* existing = findLocationAt(x, y);
        if (existing) 
        {
            return existing;
        }

        string name = "Corner_" + to_string(x) + "_" + to_string(y);
        Location* newNode = new Location(x, y, name, type);
        newNode->next = cityLocationHead;
        cityLocationHead = newNode;
        return newNode;
    }

    // HELPER: Adds raw edge to adjacency list
    void addEdgeRaw(Location* from, Location* to, float weight)
    {
        if (!from || !to) return;

        Edge* newEdge = new Edge(weight, to);
        newEdge->nextEdge = from->adjList;
        from->adjList = newEdge;
    }

    // MAIN: Adds Undirected Edge (Same weight both ways)
    void addEdge(Location* nodeA, Location* nodeB) {
        if (!nodeA || !nodeB || nodeA == nodeB) return;

        // 1. Calculate Distance
        float dist = sqrt(pow(nodeB->x - nodeA->x, 2) + pow(nodeB->y - nodeA->y, 2));

        // 2. Calculate Random Factor ONCE (1.0 to 2.0)
        float randomFactor = 1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float finalWeight = dist * randomFactor;

        // 3. Add symmetric edges (A->B and B->A)
        addEdgeRaw(nodeA, nodeB, finalWeight);
        addEdgeRaw(nodeB, nodeA, finalWeight);
    }

    void resetGraph()
    {
        Location* temp = cityLocationHead;
        while (temp)
        {
            temp->minDist = std::numeric_limits<float>::max();
            temp->visited = false;
            temp->parent = nullptr;
            temp = temp->next;
        }
    }


    // ---------------------------------------------------------
    string resolveSectorName(string inputName) {
        // 1. First, check if it's already a valid coordinate (e.g., "F-8")
        int dX, dY;
        if (getSectorBounds(inputName, dX, dY)) {
            return inputName;
        }

        // 2. If not, search all sectors for this tag
        string matchArray[100];
        int matchCount = 0;

        for (int i = 0; i < sectorCount; i++) {
            // Pass inputName to searchLoc (Sector.h)
            if (sectors[i]->searchLoc(inputName)) {
                if (matchCount < 100) {
                    matchArray[matchCount] = sectors[i]->getName();
                    matchCount++;
                }
            }
        }

        if (matchCount == 0) return ""; // Not found

        // 3. Pick a random sector from the matches
        int randIdx = rand() % matchCount;
        return matchArray[randIdx];
    }

public:
    locationManager() {
        cityLocationHead = nullptr;
        srand(time(0));

        // 1. Build Road Network
        buildRoadNetwork(true);

        // 2. Initialize Sector Objects (D-5 to J-12)
        initializeSectors();

        // 3. DEMO: Add "BlueArea" tag to F-8 and G-8 for testing
        addTagToSector("F-8", "BlueArea");
        addTagToSector("G-8", "BlueArea");
    }

    // Initialize the Sector objects so we can store tags in them
    void initializeSectors() {
        for (char row = 'D'; row <= 'J'; row++) {
            for (int col = 5; col <= 12; col++) {
                string secName = string(1, row) + "-" + to_string(col);
                if (sectorCount < 100) {
                    sectors[sectorCount] = new Sector(secName);
                    sectorCount++;
                }
            }
        }
        cout << "Initialized " << sectorCount << " Sectors.\n";
    }

    // Helper to manually add tags to sectors
    void addTagToSector(string sectorName, string tag)
    {
        for (int i = 0; i < sectorCount; i++) {
            if (sectors[i]->getName() == sectorName)
            {
                sectors[i]->addImpLoc(tag);
                return;
            }
        }
        // Silent fail or cout if preferred
    }

    void buildRoadNetwork(bool allowDiagonals)
    {
        for (char row = 'D'; row <= 'J'; row++)
        {
            for (int col = 5; col <= 12; col++)
            {
                int rIdx = row - 'D';
                int cIdx = col - 5;
                int currX = cIdx * SECTOR_SIZE;
                int currY = rIdx * SECTOR_SIZE;

                Location* current = getOrCreateNode(currX, currY, "Intersection");

                if (col < 12) {
                    Location* right = getOrCreateNode(currX + SECTOR_SIZE, currY, "Intersection");
                    addEdge(current, right);
                }
                if (row < 'J') {
                    Location* down = getOrCreateNode(currX, currY + SECTOR_SIZE, "Intersection");
                    addEdge(current, down);
                }
                if (allowDiagonals) {
                    if (col < 12 && row < 'J') {
                        Location* diagDR = getOrCreateNode(currX + SECTOR_SIZE, currY + SECTOR_SIZE, "Intersection");
                        addEdge(current, diagDR);
                    }
                    if (col > 5 && row < 'J') {
                        Location* diagDL = getOrCreateNode(currX - SECTOR_SIZE, currY + SECTOR_SIZE, "Intersection");
                        addEdge(current, diagDL);
                    }
                }
            }
        }
        cout << "Road Network Generated (Diagonals: " << (allowDiagonals ? "ON" : "OFF") << ")\n";
    }

    PathNode* findShortestPath(Location* start, Location* end) {
        if (!start || !end) return nullptr;
        resetGraph();

        MinHeap pq(5000);
        start->minDist = 0;
        pq.push(start, 0);

        while (!pq.isEmpty())
        {
            Location* u = pq.extractMin();
            if (u == end) break;
            if (u->visited) continue;
            u->visited = true;

            Edge* e = u->adjList;
            while (e)
            {
                Location* v = e->destination;
                float weight = e->weight;
                if (!v->visited && u->minDist + weight < v->minDist)
                {
                    v->minDist = u->minDist + weight;
                    v->parent = u;
                    pq.push(v, v->minDist);
                }
                e = e->nextEdge;
            }
        }

        if (end->minDist == std::numeric_limits<float>::max()) {
            cout << "No path found!\n";
            return nullptr;
        }

        PathNode* pathHead = nullptr;
        Location* crawler = end;
        while (crawler != nullptr) {
            PathNode* newNode = new PathNode(crawler);
            newNode->next = pathHead;
            pathHead = newNode;
            crawler = crawler->parent;
        }
        return pathHead;
    }

    // ---------------------------------------------------------
    // Utils
    // ---------------------------------------------------------
    bool getSectorBounds(string& sector, int& secX, int& secY)
    {
        if (sector.length() < 3) return false;

        char rowChar = sector[0];
        // Handle lowercase
        if (rowChar >= 'a' && rowChar <= 'z') {
            rowChar = rowChar - 32;
        }

        size_t hyphenPos = sector.find('-');
        if (hyphenPos == string::npos) return false;

        string colStr = sector.substr(hyphenPos + 1);
        int colNum;
        try { colNum = stoi(colStr); }
        catch (...) { return false; }

        if (rowChar < 'D' || rowChar > 'J') return false;
        if (colNum < 5 || colNum > 12) return false;

        int rowIdx = rowChar - 'D';
        int colIdx = colNum - 5;
        secX = colIdx * SECTOR_SIZE;
        secY = rowIdx * SECTOR_SIZE;
        return true;
    }

    bool isOccupied(int searchX, int searchY)
    {
        Location* temp = cityLocationHead;
        while (temp) {
            if (temp->x == searchX && temp->y == searchY) return true;
            temp = temp->next;
        }
        return false;
    }

    // ---------------------------------------------------------
    // addToCityGrid 
    // ---------------------------------------------------------
    void addToCityGrid(string name, string sectorOrTag, string type) {

        // 1. Resolve the input string. 
        // If it's "BlueArea", it randomly picks a sector that has that tag.
        string resolvedSector = resolveSectorName(sectorOrTag);

        if (resolvedSector == "") {
            cout << "Error: Sector or Area '" << sectorOrTag << "' not found.\n";
            return;
        }

        int SectorStartX = 0, SectorStartY = 0;
        if (!getSectorBounds(resolvedSector, SectorStartX, SectorStartY))
        {
            cout << "Invalid Sector Bounds: " << resolvedSector << "\n";
            return;
        }

        int finalX = 0, finalY = 0;
        bool locationFoundFree = false;
        int tries = 0;

        while (tries < 71 && !locationFoundFree)
        {
            int offsetX = 1 + (rand() % (SECTOR_SIZE - 2));
            int offsetY = 1 + (rand() % (SECTOR_SIZE - 2));
            finalX = SectorStartX + offsetX;
            finalY = SectorStartY + offsetY;

            if (!isOccupied(finalX, finalY))
            {
                locationFoundFree = true;
            }
            tries++;
        }

        if (!locationFoundFree)
        {
            cout << "Sector " << resolvedSector << " is too crowded.\n";
            return;
        }

        Location* newLocation = new Location(finalX, finalY, name, type);
        newLocation->next = cityLocationHead;
        cityLocationHead = newLocation;

        // Connect to the 4 corners
        int cornersX[4] = { SectorStartX, SectorStartX + SECTOR_SIZE, SectorStartX, SectorStartX + SECTOR_SIZE };
        int cornersY[4] = { SectorStartY, SectorStartY, SectorStartY + SECTOR_SIZE, SectorStartY + SECTOR_SIZE };

        for (int i = 0; i < 4; i++)
        {
            Location* cornerNode = getOrCreateNode(cornersX[i], cornersY[i], "Intersection");
            addEdge(newLocation, cornerNode);
        }

        cout << "Added " << name << " at (" << finalX << "," << finalY << ") in " << resolvedSector << " (Input: " << sectorOrTag << ")\n";
    }

    Location* getHead()
    {
        return cityLocationHead;
    }
};

#endif // !LOCATION_MANAGER
