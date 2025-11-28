#include "../utils/Nodes.h"
#include "BusStop.h"

#ifndef BUSROUTE_H
#define BUSROUTE_H

using std::string;
using std::cout;
using std::cin;
using std::endl;

class BusRoute {
	string routeName; // name of the bus route
	int routeID;
	int busStopsCount; // number of bus stops in the route
	BusStop* startingStop; // pointer to the starting bus stop
};


#endif