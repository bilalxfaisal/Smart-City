#ifndef  HOUSE_H
#define HOUSE_H
#include "../utils/Nodes.h"
#include "Family.h"
class House 
{
private:
	Family* family;
	int houseNum;
	int streetNum;
	string sector;
public:
	//HASH TABLE OF HOUSES BASED ON ADDRESS
	House* nextHouse = nullptr;

	House(int hn, int sn, string sec) 
	{
		family = new Family;
		houseNum = hn;
		streetNum = sn;
		sector = sec;

	}
	void addMember(Citizen* parent, Citizen* newMember)
	{
		family->insertMember(parent, newMember);
		
	}
	void removeMember(Citizen* parent, Citizen* toRemove)
	{
		family->removeMember(parent, toRemove);
	}

};
#endif // ! HOUSE_H
