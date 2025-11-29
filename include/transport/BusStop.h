#include "../utils/Nodes.h"
#ifndef BUSSTOP_H
#define BUSSTOP_H


using std::string;
using std::cout;
using std::cin;
using std::endl;

class BusStop {
	string stopName; // name of the bus stop
	int stopID; 
	Location stopLocation; // location of the bus stop
	int currBuses; // number of buses currently at the stop
	Bus** busesAtStop; // dynamic array of pointers to buses currently at the stop
	BusStop* nextStop; // pointer to the next bus stop in the route
	BusStop* prevStop; // pointer to the previous bus stop in the route

public:
	string getName() const {
		return stopName;
	}
};

#endif