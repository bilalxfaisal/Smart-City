#pragma once
#include "../utils/Nodes.h"
#include "Bus.h"
#include <iostream>
#ifndef TRANSPORTCOMPANY_H
#define TRANSPORTCOMPANY_H


using std::string;
using std::cout;
using std::cin;
using std::endl;

class TransportCompany {
public:
    string name;
    int busNo;

    TransportCompany* nextCompany;
    int currBuses;
    int busTableSize;
    Bus** busHashTable; // hashtable of buses string based

    TransportCompany(string s = "", int n = 0)
    {
        name = s;
        busNo = n;
        nextCompany = nullptr;
        currBuses = 0;
        busTableSize = 10;
        busHashTable = new Bus * [busTableSize];
        for (int i = 0; i < busTableSize; i++) {
            busHashTable[i] = nullptr;
        }
    }

    void addBus(Bus& b1)
    {
        Bus* toAdd = new Bus(b1);
        int index = Polynomial_Rolling_Hash_V2(b1.getID());
        index = index % busTableSize;
        if (busHashTable[index] == nullptr) {
            busHashTable[index] = toAdd;
        }
        else {
            // collision handling via linked List
			toAdd->next = busHashTable[index];
            busHashTable[index] = toAdd;

        }
        currBuses++;
	}
    void display()
    {
		cout << "Transport Company: " << name << ", Buses Number: " << currBuses<< endl;
        for (int i = 0; i < busTableSize; i++) {
            Bus* curr = busHashTable[i];
            while (curr) {
                cout << "  Bus ID: " << curr->getID() << ", Route: " << curr->getRoute() << ", Passengers: " << curr->getPassengers() << "/" << curr->getCapacity() << endl;
                curr = curr->next;
            }
		}
    }
    void DiscontineBus(string busID)
    {
        int index = Polynomial_Rolling_Hash_V2(busID);
        index = index % busTableSize;
        Bus* curr = busHashTable[index];
        Bus* prev = nullptr;
        while (curr) {
            if (curr->getID() == busID) {
                if (prev == nullptr) {
                    busHashTable[index] = curr->next;
                }
                else {
                    prev->next = curr->next;
                }
                delete curr;
                currBuses--;
                cout << "Bus " << busID << " discontinued from company " << name << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Bus " << busID << " not found in company " << name << endl;
	}
    void simulateBusMovement(Bus* BusToMove, BusRoute* movementRoute)
    {
		//Find the bus in the hash table
        int index = Polynomial_Rolling_Hash_V2(BusToMove->getID());
        index = index % busTableSize;
        Bus* curr = busHashTable[index];
        while (curr) {
            if (curr->getID() == BusToMove->getID()) {
                // Simulate movement
                curr->simulateMovement(movementRoute->getStartingStop());
                return;
            }
            curr = curr->next;
        }
		cout << "Bus " << BusToMove->getID() << " not found in company " << name << endl;
    }



};

#endif
