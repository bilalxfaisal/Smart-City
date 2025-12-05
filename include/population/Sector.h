#include "../utils/Nodes.h"
#include "Street.h"
#ifndef SECTOR_H
#define SECTOR_H

#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;

class Sector {
	Location topLeft;
	string name;
	int rowID;
	int colID;
	int size; // size of the sector (assuming square sectors for simplicity)
	Street** streets; 
	int streetCount;
	int streetTableSize;
public:
	Sector(Location loc, string name, int row, int col, int size) {
		topLeft = loc;
		this->name = name;
		rowID = row;
		colID = col;
		this->size = size;
		streetCount = 0;
		streetTableSize = 100; // initial size
		streets = new Street * [streetTableSize]();
	}

	void addStreet(Street& street) {

		int index = Polynomial_Rolling_Hash_V3(street.getID());
		index = index % streetTableSize;

		Street* current = streets[index];
		Street* toAdd = new Street(street);
		if (current == nullptr) {
			streets[index] = toAdd;
			streetCount++;
		}
		else {
			toAdd->nextStreet = current;
			streets[index] = toAdd;
			streetCount++;
		}
	}

	void addHouseToStreet(int streetID, House& house) {
		int index = Polynomial_Rolling_Hash_V3(streetID);
		index = index % streetTableSize;
		Street* current = streets[index];
		while (current) {
			if (current->getID() == streetID) {
				current->addHouse(house);
				return;
			}
			current = current->nextStreet;
		}
	}

	void addCitizenToHouseInStreet(int streetID, int houseNum, Citizen& c1) {
		int index = Polynomial_Rolling_Hash_V3(streetID);
		index = index % streetTableSize;
		Street* current = streets[index];
		while (current) {
			if (current->getID() == streetID) {
				current->addCitizenToHouse(houseNum, c1);
				return;
			}
			current = current->nextStreet;
		}
	}
};

#endif