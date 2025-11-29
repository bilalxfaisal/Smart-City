#include "../utils/Nodes.h"
#include "Bus.h"
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
	int totalSize; // size of the array
	Bus** busesAtStop; // dynamic array of pointers to buses currently at the stop
public:
	BusStop* nextStop; // pointer to the next bus stop in the route
	BusStop* prevStop; // pointer to the previous bus stop in the route
	
	BusStop(string name, int ID, int x, int y) {
		name = stopName;
		stopID = ID;
		stopLocation.x = x;
		stopLocation.y = y;
		currBuses = 0;
		nextStop = nullptr;
		prevStop = nullptr;
		totalSize = 10;
		busesAtStop = new Bus*[totalSize];
	}

	int getStopID() {
		return stopID;
	}
	string getStopName() {
		return stopName;
	}

	void addBusAtStop(Bus& toAdd) {
		Bus* newBus = new Bus(toAdd);
		int index = Polynomial_Rolling_Hash_V1(newBus->busID) % totalSize;
		busesAtStop[index] = newBus;
	}
};

#endif