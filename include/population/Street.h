#ifndef STREET_H
#define STREET_H

#include "House.h"
#include <string>
using std::string;

class Street
{
private:
    int id;
    string name;
    House* housesHead = nullptr;

public:
    Street* nextStreet = nullptr;

    Street(string n, int i) : 
        name(n), id(i) {}

    void addHouse(House& h)
    {
        House* nh = new House(h);
        if (!housesHead)
        {
            housesHead = nh;
            return;
        }
        House* cur = housesHead;
        while (cur->nextHouse)
            cur = cur->nextHouse;
        cur->nextHouse = nh;
    }

    void addCitizenToHouse(int hnum, Citizen& c)
    {
        House* cur = housesHead;
        while (cur)
        {
            if (cur->getHouseNum() == hnum)
            {
                cur->addMember(c);
                return;
            }
            cur = cur->nextHouse;
        }
    }

    bool searchInHouse(int hnum, const string& cnic)
    {
        House* cur = housesHead;
        while (cur)
        {
            if (cur->getHouseNum() == hnum)
            {
                return cur->searchCitizen(cnic);
            }
            cur = cur->nextHouse;
        }
        return false;
    }

    int getID() const { return id; }
    void printStreet() const
    {
        cout << "  Street ID: " << id << "\n";
        House* cur = housesHead;
        while (cur)
        {
            cout << "    House " << cur->getHouseNum() << "\n";
            cur->printHouse();
            cur = cur->nextHouse;
        }
    }
    void printHouse(int houseNum) const
    {
        House* cur = housesHead;
        while (cur)
        {
            if (cur->getHouseNum() == houseNum)
            {
                cout << "   House " << cur->getHouseNum() << ": \n";
                cur->printHouse();
                return;
            }
            cur = cur->nextHouse;
        }
        cout << "House " << houseNum << " not found on this street.\n";
	}
    int calculateStreetPopulation() 
    {
        int total = 0;
        House* temp = housesHead;
        while (temp) 
        {
            total += temp->family.calculateMemberNum();
            temp = temp->nextHouse;
        }
        return total;
    }
    House* getHouseHead() 
    {
        return housesHead;
    }
    void display() const 
    {
        cout << "Street ID: " << id
            << ", Name: " << name << endl;

        cout << "Houses:" << endl;
        House* current = housesHead;
        while (current) {
            current->display(); // Display each house
            current = current->nextHouse; // Move to next house
        }
    }
};

#endif
