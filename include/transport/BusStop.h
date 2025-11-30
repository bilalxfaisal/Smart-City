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

public:
	string getName() const {
		return stopName;
	}

	BusStop(string name, int x, int y) {
		stopName = name;
		stopLocation.x = x;
		stopLocation.y = y;
		currBuses = 0;
		totalSize = 10;
		busesAtStop = new Bus * [totalSize];
	}

	void addBus(Bus* toAdd) {
		if (currBuses == totalSize) {
			totalSize *= 2;
			Bus** newArray = new Bus * [totalSize];
			for (int i = 0; i < currBuses; i++) {
				newArray[i] = busesAtStop[i];
			}
			delete[] busesAtStop;
			busesAtStop = newArray;
		}
		busesAtStop[currBuses] = toAdd;
		currBuses++;
	}
	//GETTERS
	int getCurrBuses() const {
		return currBuses;
	}
	string getStopName() const {
		return stopName;
	}
	Location getLocation() const {
		return stopLocation;
	}

};

#endif