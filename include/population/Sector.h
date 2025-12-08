#ifndef SECTOR_H
#define SECTOR_H

#include "Street.h"
#include "../utils/Nodes.h"
#include <string>
using std::string;

class Sector
{
private:
    string name;
    int tableSize = 10;
    Street** streets;
    int streetCount = 0;

    Location topLeft;
    int rowID;
    int colID;
    int size; // size of the sector (assuming square sectors for simplicity)
    int streetTableSize;
    string* importantLocations;
    int impLocCap = 10;
    int impLocCount = 0;

    //For heat map
    int PopulationCount;
    

    int hashInt(int k) const
    {
        if (k < 0) k = -k;
        return k % tableSize;
    }

    void resize()
    {
        int newSize = tableSize * 2;
        Street** nm = new Street * [newSize];
        for (int i = 0; i < newSize; i++) nm[i] = nullptr;

        for (int i = 0; i < tableSize; i++)
        {
            Street* s = streets[i];
            while (s)
            {
                Street* nx = s->nextStreet;
                int idx = s->getID() % newSize;
                s->nextStreet = nm[idx];
                nm[idx] = s;
                s = nx;
            }
        }

        delete[] streets;
        streets = nm;
        tableSize = newSize;
    }
    void impLocArrayResize()
    {
        impLocCap *= 2;
        string* newLocArr = new string[impLocCap];
        for (int i = 0; i < impLocCount; i++)
        {
            newLocArr[i] = importantLocations[i];
        }
        delete[] importantLocations;
        importantLocations = newLocArr;
    }
public:
    //FOR CHAINING IN HASH FUNC
    Sector* nextSector = nullptr;

    Sector(string n) : name(n)
    {
        streets = new Street * [tableSize];
        for (int i = 0; i < tableSize; i++)
            streets[i] = nullptr;
        importantLocations = new string[impLocCap];


    }
    Sector() = default;
    void addImpLoc(string& newS)
    {
        if (impLocCount >= impLocCap)
        {
            impLocArrayResize();
        }
        importantLocations[impLocCount] = newS;
        impLocCount++;
    }
    bool searchLoc(string& strin)
    {
        for (int i = 0; i < impLocCount; i++)
        {
            if (importantLocations[i] == strin)
            {
                return true;
            }

        }
        return false;
    }
    string getName() const { return name; }

    void addStreet(Street& st)
    {
        if (streetCount * 2 >= tableSize)
            resize();

        Street* ns = new Street(st);
        int idx = hashInt(ns->getID());
        ns->nextStreet = streets[idx];
        streets[idx] = ns;
        streetCount++;
    }

    void addHouseToStreet(int sid, House& h)
    {
        int idx = hashInt(sid);
        Street* cur = streets[idx];
        while (cur)
        {
            if (cur->getID() == sid)
            {
                cur->addHouse(h);
                return;
            }
            cur = cur->nextStreet;
        }
    }

    void addCitizenToHouseInStreet(int sid, int hnum, Citizen& c)
    {
        int idx = hashInt(sid);
        Street* cur = streets[idx];
        while (cur)
        {
            if (cur->getID() == sid)
            {
                cur->addCitizenToHouse(hnum, c);
                return;
            }
            cur = cur->nextStreet;
        }
    }
    void printSector() const
    {
        cout << "Sector: " << name << "\n";
        for (int i = 0; i < tableSize; i++)
        {
            Street* s = streets[i];
            while (s)
            {
                s->printStreet();
                s = s->nextStreet;
            }
        }
        cout << "Street not found\n";
	}
    void display() const {
        cout << "Sector Name: " << name << endl;
        cout << "Streets:" << endl;

        for (int i = 0; i < streetCount; i++) {
            if (streets[i] != nullptr) {
                streets[i]->display(); // Display each street
            }
        }
    }
	void setName(const string& n) { name = n; }
	void setTopLeft(int x, int y) { topLeft = Location(x, y); }
    Location getTopLeft() const { return topLeft; }
    int calculatePopulation() 
    {
        PopulationCount = 0;
        for (int i = 0; i < streetTableSize; i++) 
        {
            Street* s = streets[i];
            while (s) 
            {
                PopulationCount += s->calculateStreetPopulation();
                s = s->nextStreet;
            }
        }
        return PopulationCount;
    }
    void printStreetHouses(int streetId) 
    {
        int idx = hashInt(streetId);

            Street* s = streets[idx];
            while (s)
            {
                s->printStreet();
                s = s->nextStreet;
            }
        
    }
    void printHouseInStreet(int street, int houseNum) 
    {
        int idx = hashInt(street);

        Street* s = streets[idx];
        House* h = s->getHouseHead();
        while (h)
        {
            if (h->getHouseNum() == houseNum) 
            {
                h->printHouse();
                return;

            }
            h = h->nextHouse;
        }
        cout << "House Or Street Not found. \n";
    }

};
#endif
