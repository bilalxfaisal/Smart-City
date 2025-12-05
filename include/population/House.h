#ifndef HOUSE_H
#define HOUSE_H

#include "Family.h"
#include <string>
using std::string;

class House
{
private:
    Family family;
    int houseNum;
    int streetNum;
    string sector;

public:
    House* nextHouse = nullptr;

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
        cout << "House " << houseNum << "\n";
        family.printFamily();
    }

};

#endif
