#include "../utils/Nodes.h"
#ifndef BUS_H
#define BUS_H

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Bus {
	int currStopID; // can be name too // ID of the vertex where the bus is currently located
	int busRouteID; //  
	// cuz doubly linked list
	// int routeIndex; // index of the route in the graph's route prolly a array of strings of routes
	string busID;  // cuz number plates are usually alphanumeric
	int capacity;
	int currPassengers;
	bool isMoving;
	bool direction; // true for forward, false for backward
};




#endif