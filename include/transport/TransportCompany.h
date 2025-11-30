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
struct BusNode {
	Bus* bus;
	BusNode* next;

	BusNode(Bus* b = nullptr)
	{
		bus = b;
		next = nullptr;
	}
};
class TransportCompany {
public:
    string name;
    int busNo;
    BusNode* MyBusses;             // HEAD of linked list
    TransportCompany* nextCompany;

    TransportCompany(string s = "", int n = 0)
    {
        name = s;
        busNo = n;
        MyBusses = nullptr;
        nextCompany = nullptr;
    }


    void AddBus(Bus* newBus)
    {
        if (!newBus) {
            cout << "Cannot add null bus.\n";
            return;
        }

        BusNode* node = new BusNode(newBus);

        if (MyBusses == nullptr) {
            MyBusses = node;
            return;
        }


        BusNode* temp = MyBusses;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
    }

    void DisplayBuses()
    {
        cout << "Company: " << name << "\n";
        cout << "Total buses: " << busNo << "\n";

        BusNode* temp = MyBusses;

        if (!temp) {
            cout << "No buses registered.\n\n";
            return;
        }

        while (temp != nullptr)
        {
            Bus* b = temp->bus;
            cout << " - Bus ID: " << b->getID()
                << " | Route: " << b->getRoute()
                << " | Passengers: " << b->getPassengers()
                << "/" << b->getCapacity()
                << endl;

            temp = temp->next;
        }
        cout << endl;
    }
};

#endif
