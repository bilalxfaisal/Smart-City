#include "../utils/Nodes.h"
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
// using namespace std::chrono;

// todo: giraph banana hai
class TransportSystem
{
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
	TransportSystem(int compSize = 20, int routeSize = 20)
	{
		companyTableSize = compSize;
		routesTableSize = routeSize;

		companyHashTable = new TransportCompany * [companyTableSize];
		routeHashTable = new BusRoute * [routesTableSize];

		for (int i = 0; i < companyTableSize; i++)
			companyHashTable[i] = nullptr;

		for (int i = 0; i < routesTableSize; i++)
			routeHashTable[i] = nullptr;

		currCompanies = 0;
		currRoutes = 0;
		busStopsCount = 0;
	}

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
		string nameget = br.getRouteName();
		int index = Polynomial_Rolling_Hash_V1(nameget);
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
		for (int i = 0; i < companyTableSize; i++) 
		{
			currCompany = companyHashTable[i];
			// function in TransportCompany to simulate all buses
			if (currCompany) 
			{
				for (int i = 0; i < currCompany->busTableSize; i++)
				{
					Bus* BusPtr = currCompany->busHashTable[i];
					while (BusPtr) 
					{
						// find the route for this bus
						int routeIndex = Polynomial_Rolling_Hash_V1(BusPtr->getRoute());
						routeIndex = routeIndex % routesTableSize;
						BusRoute* routePtr = routeHashTable[routeIndex];
						while (routePtr && routePtr->getRouteName() != BusPtr->getRoute()) 
						{
							routePtr = routePtr->nextRoute;
						}
						if (routePtr) 
						{
							currCompany->simulateBusMovement(BusPtr, routePtr);
						}
						BusPtr = BusPtr->next;
					}
				}
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

	void displayRoutes(string compName) {
		int index = Polynomial_Rolling_Hash_V1(compName);
		index = index % companyTableSize;
		TransportCompany* currCompany = companyHashTable[index];

		if (currCompany) {
			int tableSize = currCompany->busTableSize;
			for (int i = 0; i < tableSize; i++) {
				Bus* currBus = currCompany->busHashTable[i];
				if (currBus) {
					string currBusStop = currBus->getRoute();
					int routeIndex = Polynomial_Rolling_Hash_V1(currBusStop);
					routeIndex = routeIndex % routesTableSize;
					if (routeHashTable[routeIndex]) {
						BusRoute* currRoute = routeHashTable[routeIndex];
						cout << "Showing route for Bus: " << currBus->getID();
						currRoute->DisplayRoute();
					}
				}
			}
		}
	}

	void displayBusHistory(string& company, string& busID) {
		int companyIndex = Polynomial_Rolling_Hash_V1(company);
		companyIndex %= companyTableSize;

		TransportCompany* comp = companyHashTable[companyIndex];
		if (comp) {
			int busIndex = Polynomial_Rolling_Hash_V1(busID);
			busIndex %= comp->busTableSize;
			Bus* busToDisplay = comp->busHashTable[busIndex];
			if (busToDisplay) {
				RouteStack* history = busToDisplay->getStack();
				while (!history->isEmpty()) {
					string his = history->top();
					cout << his << " ";
					history->pop();
				}
			}
		}
	}

	BusRoute** getRouteHashTable() {
		return routeHashTable;
	}

	// for bus consstructor so to initialize the starting stop of the bus to the first stop of the route
	int getStartingBusStopID(string& routeName) {
		int index = Polynomial_Rolling_Hash_V1(routeName);
		index = index % routesTableSize;
		BusRoute* currRoute = routeHashTable[index];
		while (currRoute) {
			if (currRoute->getRouteName() == routeName) {
				BusStop* startStop = currRoute->getStartingStop();
				if (startStop) {
					return startStop->getStopID();
				}
			}
			currRoute = currRoute->nextRoute;
		}
		return -1; // not found
	}
};

#endif