#include "../utils/Nodes.h"
#include "House.h"
#ifndef STREET_H
#define STREET_H

#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;

class Street {
	string name;
	int id;
	House* housesHead = nullptr;
public:
	Street* nextStreet = nullptr;
	Street(string name, int id) {
		this->name = name;
		this->id = id;
	}
	void addHouse(House& house) {
		House* newHouse = new House(house);
		if (housesHead == nullptr) {
			housesHead = newHouse;
		}
		else {
			House* current = housesHead;
			while (current->nextHouse != nullptr) {
				current = current->nextHouse;
			}
			current->nextHouse = newHouse;
		}
	}
	void removeHouse(int houseNum) {
		if (housesHead == nullptr) {
			return;
		}
		if (housesHead->getHouseNum() == houseNum) {
			House* toDelete = housesHead;
			housesHead = housesHead->nextHouse;
			delete toDelete;
			return;
		}
		House* current = housesHead;
		while (current->nextHouse != nullptr && current->nextHouse->getHouseNum() != houseNum) {
			current = current->nextHouse;
		}
		if (current->nextHouse != nullptr) {
			House* toDelete = current->nextHouse;
			current->nextHouse = current->nextHouse->nextHouse;
			delete toDelete;
		}
	}

	void addCitizenToHouse(int houseNum, Citizen& c1) {
		House* current = housesHead;
		while (current) {
			if (current->getHouseNum() == houseNum) {
				current->addMember(nullptr, c1); // Assuming nullptr as parent for simplicity
				return;
			}
			current = current->nextHouse;
		}
	}

	bool searchHouse(int houseNum) {
		House* current = housesHead;
		while (current) {
			if (current->getHouseNum() == houseNum) {
				return true;
			}
			current = current->nextHouse;
		}
		return false;
	}

	bool searchCitizenInHouse(int houseNum, string cnic) {
		House* current = housesHead;
		while (current) {
			if (current->getHouseNum() == houseNum) {
				return current->searchCitizen(cnic);
			}
			current = current->nextHouse;
		}
		return false;
	}
	int getID() const {
		return id;
	}
};

#endif 