#include "../utils/Nodes.h"
#include "RouteStack.h"
#include <ctime>
#include <cstdlib>
#ifndef BUS_H
#define BUS_H

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Bus {
	int currStopID;
	string busRouteID;
	string busID;
	int capacity;
	int currPassengers;
	bool isMoving;
	bool direction;
	RouteStack* busRouteHistory;
public:
	// --- Basic Getters ---
	string getID() const { return busID; }
	string getRoute() const { return busRouteID; }
	int getPassengers() const { return currPassengers; }
	int getCapacity() const { return capacity; }

	Bus(string busId="", int currRoute, int cap, bool ammv, bool dir) 
	{
		busRouteHistory = new RouteStack();
		busID = busId;
		busRouteID = currRoute;
		capacity = cap;
		isMoving = ammv;
		direction = dir;
	}
	void changeState()
	{
		isMoving = !isMoving;
	}
	void changeDIr() 
	{
		direction = !direction;
	}
	void AddPassengers(BusStop* stop) 
	{
		busRouteHistory->push(stop->getName());
		int toAdd = rand() % (capacity - currPassengers + 1);
		currPassengers += toAdd;
		cout << toAdd << " passengers boarded the bus " << busID << ". Current passengers: " << currPassengers << endl;
	}
	void RemovePassengers(BusStop* stop) 
	{
		busRouteHistory->push(stop->getName());
		int toRemove = rand() % (currPassengers + 1);
		currPassengers -= toRemove;
		cout << toRemove << " passengers alighted from the bus " << busID << ". Current passengers: " << currPassengers << endl;
	}
};

#endif