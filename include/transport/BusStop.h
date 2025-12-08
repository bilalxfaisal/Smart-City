#include "../utils/Nodes.h"
//#include "Bus.h"
#ifndef BUSSTOP_H
#define BUSSTOP_H

using std::string;
using std::cout;
using std::cin;
using std::endl;

class BusStop {
	string stopName; // name of the bus stop
	static int counter; 
	int stopID; // unique ID of the bus stop
	Location stopLocation; // location of the bus stop
	int currBuses; // number of buses currently at the stop
	int totalSize; // size of the array
	Bus** busesAtStop; // dynamic array of pointers to buses currently at the stop
	string stopSector; // sector of the bus stop
public:
	BusStop* nextStop; // pointer to the next bus stop in the route
	// Removed prevStop - using singly linked list only

public:
	BusStop(string name, string sector) {
		stopName = name;
		stopSector = sector;
		currBuses = 0;
		totalSize = 10;
		busesAtStop = new Bus * [totalSize];
		nextStop = nullptr;
		counter++;
		stopID = counter;
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

	//DEEP COPY CONSTRUCTOR
	BusStop(const BusStop& other) {
		stopName = other.stopName;
		stopID = other.stopID;
		stopLocation = other.stopLocation;
		currBuses = other.currBuses;
		totalSize = other.totalSize;
		busesAtStop = new Bus * [totalSize];
		for (int i = 0; i < currBuses; i++) {
			busesAtStop[i] = other.busesAtStop[i];
		}
		nextStop = nullptr;
	}

	//GETTERS
	int getCurrBuses() const {
		return currBuses;
	}
	int getStopID() {
		return stopID;
	}
	string getStopName() const {
		return stopName;
	}
	Location& getLocation() {
		return stopLocation;
	}
	// 1. Default Constructor (REQUIRED)
	BusStop() {
		stopName = "";
		currBuses = 0;
		totalSize = 10;
		busesAtStop = new Bus * [totalSize];
		nextStop = nullptr;
		counter++;
		stopID = counter;
	}
	void Display() 
	{
		cout << "Stop Name: " << stopName << " " << " Stop Id " << stopID << endl;
	}
	// 2. Setter for loading data
	void setStopDetails(string name, float lat, float lon) {
		stopName = name;
		stopLocation.x = lat;
		stopLocation.y = lon;
	}

	string getStopSector() const {
		return stopSector;
	}
};

int BusStop::counter = 0;
#endif