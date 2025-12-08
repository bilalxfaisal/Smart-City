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

struct PathNode {
    Location* loc;
    PathNode* next;
    PathNode(Location* l) : loc(l), next(nullptr) {}
};

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
    static const int SECTOR_SIZE = 90;
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

    void addEdgeRaw(Location* from, Location* to, float weight)
    {
        if (!from || !to) return;

        Edge* newEdge = new Edge(weight, to);
        newEdge->nextEdge = from->adjList;
        from->adjList = newEdge;
    }

    void addEdge(Location* nodeA, Location* nodeB) {
        if (!nodeA || !nodeB || nodeA == nodeB) return;

        float dist = sqrt(pow(nodeB->x - nodeA->x, 2) + pow(nodeB->y - nodeA->y, 2));
        float randomFactor = 1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float finalWeight = dist * randomFactor;

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

    string resolveSectorName(string inputName) {
        int dX, dY;
        if (getSectorBounds(inputName, dX, dY)) {
            return inputName;
        }

        string matchArray[100];
        int matchCount = 0;

        for (int i = 0; i < sectorCount; i++) {
            if (sectors[i]->searchLoc(inputName)) {
                if (matchCount < 100) {
                    matchArray[matchCount] = sectors[i]->getName();
                    matchCount++;
                }
            }
        }

        if (matchCount == 0) return "";

        int randIdx = rand() % matchCount;
        return matchArray[randIdx];
    }

    float calculateEuclideanDistance(Location* a, Location* b) {
        return sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
    }

public:
    locationManager()
    {
        cityLocationHead = nullptr;
        srand(time(0));

        buildRoadNetwork(true);
        initializeSectors();

        addTagToSector("F-8", "BlueArea");
        addTagToSector("F-8", "Centaurus");
        addTagToSector("G-8", "BlueArea");
        addTagToSector("G-8", "PIMS Hospital");
        addTagToSector("E-8", "Faisal Mosque");
        addTagToSector("F-9", "Lake View");
    }

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

    void addTagToSector(string sectorName, string tag)
    {
        for (int i = 0; i < sectorCount; i++) {
            if (sectors[i]->getName() == sectorName)
            {
                sectors[i]->addImpLoc(tag);
                return;
            }
        }
    }

    void buildRoadNetwork(bool allowDiagonals)
    {
        for (char row = 'D'; row <= 'J'; row++)
        {
            for (int col = 5; col <= 12; col++)
            {
                int rIdx = row - 'D';
                int cIdx = col - 5;

                int currX = 80 + cIdx * SECTOR_SIZE;
                int currY = 50 + rIdx * SECTOR_SIZE;

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

    void addTemporaryEdge(Location* start, Location* end)
    {
        if (!start || !end || start == end) return;

        float dist = calculateEuclideanDistance(start, end);
        addEdgeRaw(start, end, dist);
        addEdgeRaw(end, start, dist);
    }

    void removeTemporaryEdge(Location* start, Location* end) {
        if (!start || !end) return;

        Edge* prev = nullptr;
        Edge* curr = start->adjList;
        while (curr) {
            if (curr->destination == end) {
                if (prev) {
                    prev->nextEdge = curr->nextEdge;
                }
                else {
                    start->adjList = curr->nextEdge;
                }
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->nextEdge;
        }

        prev = nullptr;
        curr = end->adjList;
        while (curr) {
            if (curr->destination == start) {
                if (prev) {
                    prev->nextEdge = curr->nextEdge;
                }
                else {
                    end->adjList = curr->nextEdge;
                }
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->nextEdge;
        }
    }

    PathNode* findShortestPath(Location* start, Location* end, bool emergencyMode = false, Location** pathLocationHead = nullptr) {
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

                if (emergencyMode) {
                    weight = weight / 1.67f;
                }

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
            return nullptr;
        }

        // Build PathNode linked list (for displaying route)
        PathNode* pathHead = nullptr;
        Location* crawler = end;
        while (crawler != nullptr) {
            PathNode* newNode = new PathNode(crawler);
            newNode->next = pathHead;
            pathHead = newNode;
            crawler = crawler->parent;
        }

        // Build Location* linked list with edges for visualization (only if pointer provided)
        if (pathLocationHead != nullptr) {
            Location* pathLocHead = nullptr;
            Location* pathLocationTail = nullptr;

            PathNode* current = pathHead;
            while (current) {
                // Create a copy of the location
                Location* locCopy = new Location(
                    current->loc->x,
                    current->loc->y,
                    current->loc->name,
                    current->loc->type
                );

                // Copy ALL edges from the original location (including connections to sector corners)
                Edge* originalEdge = current->loc->adjList;
                while (originalEdge) {
                    // Create a copy of the original location's edge destination
                    Location* destCopy = new Location(
                        originalEdge->destination->x,
                        originalEdge->destination->y,
                        originalEdge->destination->name,
                        originalEdge->destination->type
                    );
                    
                    // Add edge from locCopy to destCopy
                    Edge* edgeCopy = new Edge(originalEdge->weight, destCopy);
                    edgeCopy->nextEdge = locCopy->adjList;
                    locCopy->adjList = edgeCopy;
                    
                    originalEdge = originalEdge->nextEdge;
                }

                // Add to linked list
                if (!pathLocHead) {
                    pathLocHead = locCopy;
                    pathLocationTail = locCopy;
                } else {
                    pathLocationTail->next = locCopy;
                    pathLocationTail = locCopy;
                }

                current = current->next;
            }

            *pathLocationHead = pathLocHead;
        }

        return pathHead;
    }

    void addPathEdgesToVisualization(PathNode* path)
    {
        if (!path) return;

        PathNode* current = path;
        while (current && current->next) {
            Location* from = current->loc;
            Location* to = current->next->loc;

            bool edgeExists = false;
            Edge* e = from->adjList;
            while (e) {
                if (e->destination == to) {
                    edgeExists = true;
                    break;
                }
                e = e->nextEdge;
            }

            if (!edgeExists) {
                addTemporaryEdge(from, to);
            }

            current = current->next;
        }
    }

    void removePathEdgesFromVisualization(PathNode* path) {
        if (!path) return;

        PathNode* current = path;
        while (current && current->next) {
            Location* from = current->loc;
            Location* to = current->next->loc;
            removeTemporaryEdge(from, to);
            current = current->next;
        }
    }

    bool getSectorBounds(string& sector, int& secX, int& secY)
    {
        if (sector.length() < 3) return false;

        char rowChar = sector[0];
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

    void addToCityGrid(string name, string sectorOrTag, string type, Location& toSet) {
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

            finalX = 80 + SectorStartX + offsetX;
            finalY = 50 + SectorStartY + offsetY;

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
        toSet = *newLocation;
        newLocation->next = cityLocationHead;
        cityLocationHead = newLocation;

        int cornersX[4] = {
            80 + SectorStartX,
            80 + SectorStartX + SECTOR_SIZE,
            80 + SectorStartX,
            80 + SectorStartX + SECTOR_SIZE
        };
        int cornersY[4] = {
            50 + SectorStartY,
            50 + SectorStartY,
            50 + SectorStartY + SECTOR_SIZE,
            50 + SectorStartY + SECTOR_SIZE
        };

        for (int i = 0; i < 4; i++)
        {
            Location* cornerNode = getOrCreateNode(cornersX[i], cornersY[i], "Intersection");
            addEdge(newLocation, cornerNode);
        }

        cout << "Added " << name << " at (" << finalX << "," << finalY << ") in " << resolvedSector << "\n";
    }

    Location* getHead()
    {
        return cityLocationHead;
    }

    Location* getAllLocations() const
    {
        return cityLocationHead;
    }

    Location* findLocationByName(const string& locationName) {
        Location* temp = cityLocationHead;
        while (temp) {
            string tempName = temp->name;
            string searchName = locationName;

            for (size_t i = 0; i < tempName.length(); i++) {
                if (tempName[i] >= 'A' && tempName[i] <= 'Z') {
                    tempName[i] = tempName[i] + 32;
                }
            }
            for (size_t i = 0; i < searchName.length(); i++) {
                if (searchName[i] >= 'A' && searchName[i] <= 'Z') {
                    searchName[i] = searchName[i] + 32;
                }
            }

            if (tempName.find(searchName) != string::npos) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void searchLocations(const string& searchTerm) {
        cout << "\n=== Search Results for: '" << searchTerm << "' ===\n";

        Location* temp = cityLocationHead;
        int count = 0;

        while (temp) {
            string tempName = temp->name;
            string search = searchTerm;

            for (size_t i = 0; i < tempName.length(); i++) {
                if (tempName[i] >= 'A' && tempName[i] <= 'Z') {
                    tempName[i] = tempName[i] + 32;
                }
            }
            for (size_t i = 0; i < search.length(); i++) {
                if (search[i] >= 'A' && search[i] <= 'Z') {
                    search[i] = search[i] + 32;
                }
            }

            if (tempName.find(search) != string::npos) {
                count++;
                cout << count << ". " << temp->name
                    << " [" << temp->type << "] "
                    << "at (" << temp->x << ", " << temp->y << ")\n";
            }
            temp = temp->next;
        }

        if (count == 0) {
            cout << "No locations found matching '" << searchTerm << "'.\n";
        }
        else {
            cout << "\nTotal: " << count << " location(s) found.\n";
        }
    }

    Location* findNearestLocationType(int x, int y, const string& type) {
        Location* nearest = nullptr;
        float minDist = std::numeric_limits<float>::max();

        Location* temp = cityLocationHead;
        while (temp) {
            if (temp->type == type) {
                float dist = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));
                if (dist < minDist) {
                    minDist = dist;
                    nearest = temp;
                }
            }
            temp = temp->next;
        }
        return nearest;
    }

    Location* findNearestIntersection(int x, int y) {
        Location* nearest = nullptr;
        float minDist = std::numeric_limits<float>::max();

        Location* temp = cityLocationHead;
        while (temp) {
            if (temp->type == "Intersection") {
                float dist = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));
                if (dist < minDist) {
                    minDist = dist;
                    nearest = temp;
                }
            }
            temp = temp->next;
        }
        return nearest;
    }

    void connectLocationToGrid(Location* loc) {
        if (!loc) return;

        Location* intersections[4] = { nullptr, nullptr, nullptr, nullptr };
        float distances[4] = {
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max()
        };

        Location* temp = cityLocationHead;
        while (temp) {
            if (temp->type == "Intersection") {
                float dist = sqrt(pow(temp->x - loc->x, 2) + pow(temp->y - loc->y, 2));

                for (int i = 0; i < 4; i++) {
                    if (dist < distances[i]) {
                        for (int j = 3; j > i; j--) {
                            distances[j] = distances[j - 1];
                            intersections[j] = intersections[j - 1];
                        }
                        distances[i] = dist;
                        intersections[i] = temp;
                        break;
                    }
                }
            }
            temp = temp->next;
        }

        for (int i = 0; i < 4; i++) {
            if (intersections[i]) {
                addEdge(loc, intersections[i]);
            }
        }
    }

    // NEW FUNCTION: Create visualization copy of location list with all edges
    Location* createVisualizationCopy(Location* originalHead) {
        if (!originalHead) return nullptr;

        Location* vizHead = nullptr;
        Location* vizTail = nullptr;

        // First pass: Copy all locations
        Location* original = originalHead;
        while (original) {
            Location* locCopy = new Location(
                original->x,
                original->y,
                original->name,
                original->type
            );

            // Copy ALL edges from the original location
            Edge* originalEdge = original->adjList;
            while (originalEdge) {
                // Create a copy of the destination
                Location* destCopy = new Location(
                    originalEdge->destination->x,
                    originalEdge->destination->y,
                    originalEdge->destination->name,
                    originalEdge->destination->type
                );

                // Add edge from locCopy to destCopy
                Edge* edgeCopy = new Edge(originalEdge->weight, destCopy);
                edgeCopy->nextEdge = locCopy->adjList;
                locCopy->adjList = edgeCopy;

                originalEdge = originalEdge->nextEdge;
            }

            // Add to visualization list
            if (!vizHead) {
                vizHead = locCopy;
                vizTail = locCopy;
            } else {
                vizTail->next = locCopy;
                vizTail = locCopy;
            }

            original = original->next;
        }

        return vizHead;
    }

    // Cleanup function for visualization copy
    void cleanupVisualizationCopy(Location* vizHead) {
        while (vizHead) {
            Location* temp = vizHead;
            vizHead = vizHead->next;

            // Clean up edges
            Edge* edge = temp->adjList;
            while (edge) {
                Edge* nextEdge = edge->nextEdge;
                // Delete the destination location copy
                delete edge->destination;
                delete edge;
                edge = nextEdge;
            }

            delete temp;
        }
    }
};

#endif
