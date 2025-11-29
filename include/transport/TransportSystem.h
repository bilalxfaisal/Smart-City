#include "BusStop.h"
#include "Bus.h"
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
	
	int currBuses;
	int busTableSize;
	Bus** busHashTable; // hashtable of buses string based
	
	int currCompanies;
	int companyTableSize;
	TransportCompany** companyHashTable; // hashtable of transport companies string based by name
public:
	
	void addTransportCompany(TransportCompany& t1) {
		TransportCompany* toAdd = new TransportCompany(t1);
		int index = Polynomial_Rolling_Hash_V1(t1.name);
		index = index % companyTableSize;
		if (companyHashTable[index] == nullptr) {

		}
	}
};

#endif