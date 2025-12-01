#include "BusStop.h"
#include "Bus.h"
#include "BusRoute.h"
#include "TransportCompany.h"
#include <iostream>
#include <chrono> // in case of time delays addition
#ifndef TRANSPORTSYSTEM_H
#define TRANSPORTSYSTEM_H

using std::string;
using std::cout;
using std::cin;
using std::endl;
using namespace std::chrono;

// todo: giraph banana hai
class TransportSystem {
	// kaam kaam "bus" ka kaam
	// jinnah
	int busStopsCount;// for giraffe

	int currRoutes;
	int routesTableSize;
	BusRoute** routeHashTable; // hashtable of routes string based
	

	
	int currCompanies;
	int companyTableSize;
	TransportCompany** companyHashTable; // hashtable of transport companies string based by name
public:
	
	void addTransportCompany(TransportCompany& t1) 
	{
		TransportCompany* toAdd = new TransportCompany(t1);
		int index = Polynomial_Rolling_Hash_V1(t1.name);
		index = index % companyTableSize;
		if (companyHashTable[index] == nullptr) {
			companyHashTable[index] = toAdd;
		}
		else {
			// collision handling via linked List
			toAdd->nextCompany = companyHashTable[index];
			companyHashTable[index] = toAdd;
			// done
		}
	}

	void addBusRoute(BusRoute& br) {
		BusRoute* toAdd = new BusRoute(br);
		int index = Polynomial_Rolling_Hash_V1(br.getRouteName());
		index = index % routesTableSize;
		if (routeHashTable[index] == nullptr) {
			routeHashTable[index] = toAdd;
		}
		else {
			// collision handling via linked List
			toAdd->nextRoute = routeHashTable[index];
			routeHashTable[index] = toAdd;
			// done
		}
	}

	void addBusToTransportCompany(Bus& b1, string& companyName)
	{
		Bus* toAdd = new Bus(b1);
		int index = Polynomial_Rolling_Hash_V1(companyName);
		index = index % companyTableSize;
		TransportCompany* curr = companyHashTable[index];
		while (curr) {
			if (curr->name == companyName) {
				curr->addBus(*toAdd);
				return;
			}
			curr = curr->nextCompany;
		}
	}

	// add time delays I guess
	void simulateBusMovement() {
		TransportCompany* currCompany = nullptr;
		for (int i = 0; i < companyTableSize; i++) {
			currCompany = companyHashTable[i];
			// function in TransportCompany to simulate all buses
			if (currCompany) {
				currCompany->simulateBusMovement();
			}
		}
	}


	// the fnc must only display the companies name and the fnc it calls is 
	void displayCompanyStatus(string companyName) {
		TransportCompany* currCompany = nullptr;
		int index = Polynomial_Rolling_Hash_V1(companyName);
		index = index % companyTableSize;
		currCompany = companyHashTable[index];
		if (currCompany) {
			cout << "Transport Company: " << companyName << endl;
			currCompany->display();
		}
		else {
			cout << "Company not found." << endl;
		}
	}
};

#endif