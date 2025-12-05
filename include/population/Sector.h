#ifndef SECTOR_H
#define SECTOR_H

#include "Street.h"
#include "../utils/Nodes.h"
#include <string>
using std::string;

<<<<<<< Updated upstream
class Sector
{
private:
    string name;
    int tableSize = 10;
    Street** streets;
    int streetCount = 0;

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

=======
class Sector 
{
	Location topLeft;
	string name;
	int rowID;
	int colID;
	int size; // size of the sector (assuming square sectors for simplicity)
	Street** streets; 
	int streetCount;
	int streetTableSize;
>>>>>>> Stashed changes
public:
    //FOR CHAINING IN HASH FUNC
    Sector* nextSector=nullptr;

    Sector(string n) : name(n)
    {
        streets = new Street * [tableSize];
        for (int i = 0; i < tableSize; i++) streets[i] = nullptr;
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
    }

};

#endif
