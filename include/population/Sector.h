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
        for (int i = 0; i < tableSize; i++) streets[i] = nullptr;
    }
    Sector() = default;

        }
        return false;
    }
    string getName() const { return name; }
    Street* getStreetByID(int id)
    {
        int idx = hashInt(id);
        Street* cur = streets[idx];
        while (cur)
        {
            if (cur->getID() == id)
                return cur;
            cur = cur->nextStreet;
        }
        return nullptr;
	}
    int hashInt(int k) const
    {
        if (k < 0) k = -k;
        return k % tableSize;
    }

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
    }
    void printHouseInStreet(int streetID, int houseNum) 
    {
        Street* cur = getStreetByID(streetID);
        if (!cur) 
        {
            cout << "Street not found\n";
            return;
        }
        cur->printHouse(houseNum);
    }

    void printStreetHouses(int streetID) 
    {
        Street* cur = getStreetByID(streetID);
        if (cur)
        {
            cur->printStreet();
            return;
        }
        cout << "Street not found\n";
	}

	void setName(const string& n) { name = n; }
};
#endif
