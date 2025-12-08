#ifndef HOUSE_H
#define HOUSE_H

#include "Family.h"
#include <string>
using std::string;

class House
{
private:
   
    int houseNum;
    int streetNum;
    string sector;
    Location houseLocation;

public:
    House* nextHouse = nullptr;
    Family family;
    House(int h=0, int s=0, string sec="")
        : houseNum(h), streetNum(s), sector(sec)
    {
    }

    House(const House& other)
        : family(),
        houseNum(other.houseNum),
        streetNum(other.streetNum),
        sector(other.sector),
        nextHouse(nullptr)
    {
    }
    Location& getHouseLocation() 
    {
        return houseLocation;
    }
    void addMember(Citizen& c)
    {
        family.insertMember(c);
    }

    bool searchCitizen(const string& cnic) const
    {
        return family.containsCitizen(cnic);
    }

    int getHouseNum() const { return houseNum; }
    int getStreetNum() const { return streetNum; }
    string getSector()  const { return sector; }
    void printHouse() const
    {
        cout << "House " << houseNum << " : \n";
        family.display();
    }
    void display() const {
        cout << "House Number: " << houseNum
            << ", Street Number: " << streetNum
            << ", Sector: " << sector
            << ", Location: ";
        houseLocation.display(); // Assuming Location has a display method

        cout << "Residents:" << endl;
        Citizen* residentsHead = family.getCitizenHead();
        if (residentsHead) {
            Citizen* current = residentsHead;
            while (current) {
                current->displayCitizenInfo(); // Display each citizen
                current = current->nextSibling; // Move to next resident
            }
        }
        else {
            cout << "No residents." << endl;
        }
    }
};


#endif
