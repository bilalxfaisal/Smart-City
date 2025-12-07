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
