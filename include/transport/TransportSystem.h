#include "BusStop.h"
#include "Bus.h"
#include "BusRoute.h"
#include "TransportCompany.h"
#include <iostream>
#ifndef TRANSPORTSYSTEM_H
#define TRANSPORTSYSTEM_H

using std::string;
using std::cout;
using std::cin;
using std::endl;

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

	void addBusToTransportCompany()
	{

	}
};

#endif