#ifndef POPULATIONSYSTEM_H
#define POPULATIONSYSTEM_H

#include "Sector.h"
#include "Citizen.h"
#include <string>
using std::string;
using std::cout;
using std::endl;

class PopulationSystem
{
private:
    Sector** sectorMap;
    int sectorCap = 10;
    int sectorCount = 0;

    Citizen** citizenMap;
    int citizenCap = 10;
    int citizenCount = 0;
    int maxPopulationPerSector = 0;
    int minPopulationPerSector = 0;
    void display() const {
        cout << "=== Population System ===" << endl;
        cout << "Total Sectors: " << sectorCount << endl;

        for (int i = 0; i < sectorCount; i++) {
            if (sectorMap[i] != nullptr) {
                sectorMap[i]->display(); // Display each sector
                cout << endl;
            }
        }
        cout << "==========================" << endl;
    }
	Location* houseHead = nullptr; // Head of the house location list

    int hashStr(const string& s, int mod) const
    {
        long long h = Polynomial_Rolling_Hash_V1(s);
        if (h < 0) h = -h;
        return h % mod;
    }

    void resizeSectors()
    {
        int newCap = sectorCap * 2;
        Sector** nm = new Sector * [newCap];
        for (int i = 0; i < newCap; i++) nm[i] = nullptr;

        for (int i = 0; i < sectorCap; i++)
        {
            Sector* cur = sectorMap[i];
            while (cur)
            {
                Sector* nxt = cur->nextSector;
                int idx = hashStr(cur->getName(), newCap);
                cur->nextSector = nm[idx];
                nm[idx] = cur;
                cur = nxt;
            }
        }

        delete[] sectorMap;
        sectorMap = nm;
        sectorCap = newCap;
    }

    void resizeCitizens()
    {
        int newCap = citizenCap * 2;
        Citizen** nm = new Citizen * [newCap];
        for (int i = 0; i < newCap; i++) nm[i] = nullptr;

        for (int i = 0; i < citizenCap; i++)
        {
            Citizen* cur = citizenMap[i];
            while (cur)
            {
                Citizen* nxt = cur->nextCitizen;
                int idx = hashStr(cur->getCNIC(), newCap);
                cur->nextCitizen = nm[idx];
                nm[idx] = cur;
                cur = nxt;
            }
        }

        delete[] citizenMap;
        citizenMap = nm;
        citizenCap = newCap;
    }

    Sector* findSector(const string& name)
    {
        int idx = hashStr(name, sectorCap);
        Sector* cur = sectorMap[idx];
        while (cur)
        {
            if (cur->getName() == name) return cur;
            cur = cur->nextSector;
        }
        return nullptr;
    }


    void addHouseLocationToList(const Location& loc) {
        // Check for duplicate (same x,y)
        for (Location* temp = houseHead; temp; temp = temp->next) {
            if (temp->x == loc.x && temp->y == loc.y) {
                return; // already exists
            }
        }
        // Create new node on heap
        Location* newNode = new Location(loc);
        newNode->next = houseHead;
        houseHead = newNode;
    }

    // Remove house location from visualization list
    void removeHouseLocationFromList(const Location& loc) {
        if (!houseHead) return;

        if (houseHead->x == loc.x && houseHead->y == loc.y) {
            Location* toDelete = houseHead;
            houseHead = houseHead->next;
            delete toDelete;
            return;
        }

        Location* curr = houseHead;
        while (curr->next) {
            if (curr->next->x == loc.x && curr->next->y == loc.y) {
                Location* toDelete = curr->next;
                curr->next = curr->next->next;
                delete toDelete;
                return;
            }
            curr = curr->next;
        }
    }

public:
    PopulationSystem()
    {
        sectorMap = new Sector * [sectorCap];
        citizenMap = new Citizen * [citizenCap];
        for (int i = 0; i < sectorCap; i++) 
        {
            sectorMap[i] = nullptr;
        }
        for (int i = 0; i < citizenCap; i++) 
        {
            citizenMap[i] = nullptr;
        }
    }

    void addSector(Sector& s)
    {
        if (sectorCount * 2 >= sectorCap) resizeSectors();

        Sector* ns = new Sector(s);
        int idx = hashStr(s.getName(), sectorCap);
        ns->nextSector = sectorMap[idx];
        sectorMap[idx] = ns;
        sectorCount++;
    }

    void addStreet(Street& st, string sectorName)
    {
        Sector* s = findSector(sectorName);
        if (!s) return;
        s->addStreet(st);
    }

    void addHouse(House& h, string sectorName, int streetID)
    {
        Sector* s = findSector(sectorName);
        if (!s) return;

        // Add house location to visualization list
        addHouseLocationToList(h.getHouseLocation());

        s->addHouseToStreet(streetID, h);
    }

    void addCitizen(Citizen& c, string sectorName, int streetID, int houseNum)
    {
        if (citizenCount * 2 >= citizenCap) resizeCitizens();

        int idx = hashStr(c.getCNIC(), citizenCap);
        c.nextCitizen = citizenMap[idx];
        citizenMap[idx] = &c;
        citizenCount++;

        Sector* s = findSector(sectorName);
        if (!s) return;
        s->addCitizenToHouseInStreet(streetID, houseNum, c);
    }

    void searchIndividual(const string& cnic)
    {
        int idx = hashStr(cnic, citizenCap);
        Citizen* cur = citizenMap[idx];

        while (cur)
        {
            if (cur->getCNIC() == cnic)
            {
                cur->displayCitizenInfo();
                return;
            }
            cur = cur->nextCitizen;
        }

        cout << "Citizen not found\n";
    }

    void reportAgeDistribution()
    {
        int Kids = 0, Adults = 0, Old = 0;
        for (int i = 0; i < citizenCap; i++)
        {
            Citizen* cur = citizenMap[i];
            while (cur)
            {
                int a = cur->getAge();
                if (a < 18) Kids++;
                else if (a < 65) Adults++;
                else Old++;
                cur = cur->nextCitizen;
            }
        }

        cout << "Children: " << Kids << endl;
        cout << "Adults: " << Adults << endl;
        cout << "Seniors: " << Old << endl;
    }
    // Add to PopulationSystem class public section:

    void connectHousesSubgraph() {
        cout << "\n[INFO] Connecting houses subgraph...\n";

        if (!houseHead) {
            cout << "[WARNING] No houses to connect.\n";
            return;
        }

        int connectedCount = 0;
        Location* h1 = houseHead;

        while (h1) {
            Location* h2 = houseHead;
            while (h2) {
                if (h1 != h2) {
                    float dist = sqrt(
                        pow(h2->x - h1->x, 2) +
                        pow(h2->y - h1->y, 2)
                    );

                    // Connect houses within 100 units (neighbors)
                    if (dist < 100.0f && dist > 0) {
                        bool edgeExists = false;
                        Edge* e = h1->adjList;
                        while (e) {
                            if (e->destination == h2) {
                                edgeExists = true;
                                break;
                            }
                            e = e->nextEdge;
                        }

                        if (!edgeExists) {
                            Edge* newEdge1 = new Edge(dist, h2);
                            newEdge1->nextEdge = h1->adjList;
                            h1->adjList = newEdge1;

                            Edge* newEdge2 = new Edge(dist, h1);
                            newEdge2->nextEdge = h2->adjList;
                            h2->adjList = newEdge2;

                            connectedCount++;
                        }
                    }
                }
                h2 = h2->next;
            }
            h1 = h1->next;
        }

        cout << "[SUCCESS] Connected " << connectedCount << " house pairs.\n";
    }

    // Find shortest path between two houses in same sector
    PathNode* findPathBetweenHouses(string sectorName, int street1, int house1, int street2, int house2) {
        // Find sector
        int idx = hashStr(sectorName, sectorCap);
        Sector* sec = sectorMap[idx];

        while (sec && sec->getName() != sectorName) {
            sec = sec->nextSector;
        }

        if (!sec) {
            cout << "[ERROR] Sector not found.\n";
            return nullptr;
        }

        // Find houses
        House* h1 = sec->findHouse(street1, house1);
        House* h2 = sec->findHouse(street2, house2);

        if (!h1 || !h2) {
            cout << "[ERROR] One or both houses not found.\n";
            return nullptr;
        }

        Location* start = &(h1->getHouseLocation());
        Location* end = &(h2->getHouseLocation());

        // Reset graph
        Location* loc = houseHead;
        while (loc) {
            loc->minDist = std::numeric_limits<float>::max();
            loc->visited = false;
            loc->parent = nullptr;
            loc = loc->next;
        }

        // Dijkstra
        MinHeap pq(1000);
        start->minDist = 0;
        pq.push(start, 0);

        while (!pq.isEmpty()) {
            Location* u = pq.extractMin();
            if (u == end) break;
            if (u->visited) continue;
            u->visited = true;

            Edge* e = u->adjList;
            while (e) {
                Location* v = e->destination;
                float weight = e->weight;
                if (!v->visited && u->minDist + weight < v->minDist) {
                    v->minDist = u->minDist + weight;
                    v->parent = u;
                    pq.push(v, v->minDist);
                }
                e = e->nextEdge;
            }
        }

        if (end->minDist == std::numeric_limits<float>::max()) {
            cout << "[ERROR] No path found between houses.\n";
            return nullptr;
        }

        // Build path
        PathNode* pathHead = nullptr;
        Location* crawler = end;
        while (crawler) {
            PathNode* newNode = new PathNode(crawler);
            newNode->next = pathHead;
            pathHead = newNode;
            crawler = crawler->parent;
        }

        return pathHead;
    }

    void reportOccupationSummary()
    {
        struct Occ { string occ; int count; };
        Occ* arr = new Occ[citizenCap];
        int used = 0;

        for (int i = 0; i < citizenCap; i++)
        {
            Citizen* cur = citizenMap[i];
            while (cur)
            {
                string o = cur->getOccupation();
                bool found = false;

                for (int j = 0; j < used; j++)
                {
                    if (arr[j].occ == o)
                    {
                        arr[j].count++;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    arr[used].occ = o;
                    arr[used].count = 1;
                    used++;
                }

                cur = cur->nextCitizen;
            }
        }

        for (int i = 0; i < used; i++)
            cout << arr[i].occ << ": " << arr[i].count << endl;

        delete[] arr;
    }

    void reportPopulationDensity()
    {
        if (sectorCount == 0)
        {
            cout << "Density N/A\n";
            return;
        }
        double d = (double)citizenCount / sectorCount;
        cout << "Population density: " << d << endl;
    }

    void printSystem()
    {
        cout << "=== Population System ===\n";
        for (int i = 0; i < sectorCap; i++)
        {
            Sector* s = sectorMap[i];
            while (s)
            {
                s->printSector();
                cout << "\n";
                s = s->nextSector;
            }
        }
    }
    void displayMembersOfHouse(string sectorName, int streetID, int houseNum)
    {
        Sector* s = findSector(sectorName);
        if (!s) 
        {
            cout << "Sector not found\n";
            return;
		}
		s->printHouseInStreet(streetID, houseNum);
    }
    void displayHousesInStreet(string sectorName, int streetID)
    {
        Sector* s = findSector(sectorName);
        if (!s)
        {
            cout << "Sector not found\n";
            return;
        }
        s->printStreetHouses(streetID);
    }
    void GetMinMaxPop()
    {
        if (sectorCount == 0)
        {
            minPopulationPerSector = 0;
            maxPopulationPerSector = 0;
            return;
        }

        int minPop = INT_MAX;  // Start with maximum possible value
        int maxPop = INT_MIN;  // Start with minimum possible value

        for (int i = 0; i < sectorCap; i++)
        {
            Sector* sec = sectorMap[i];

            while (sec != nullptr)
            {
                int pop = sec->calculatePopulation();

                if (pop < minPop) minPop = pop;
                if (pop > maxPop) maxPop = pop;

                sec = sec->nextSector;
            }
        }

        minPopulationPerSector = minPop;
        maxPopulationPerSector = maxPop;
    }

    // Returns a linked list of SectorPopNode for heatmap visualization
    SectorPopNode* getSectorPopulationList()
    {
        SectorPopNode* head = nullptr;
        SectorPopNode* tail = nullptr;

        for (int i = 0; i < sectorCap; i++)
        {
            Sector* sec = sectorMap[i];
            while (sec != nullptr)
            {
                int pop = sec->calculatePopulation();
                SectorPopNode* newNode = new SectorPopNode(sec->getName(), pop);

                if (head == nullptr)
                {
                    head = tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    tail = newNode;
                }

                sec = sec->nextSector;
            }
        }

        return head;
    }

    int getMinPopulation() const { return minPopulationPerSector; }
    int getMaxPopulation() const { return maxPopulationPerSector; }
    Location* getHouseLocationHead() const {
        return houseHead;
    }

};

#endif
