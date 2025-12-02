#include "../utils/Nodes.h"
#include "RouteStack.h"
#include "BusStop.h"
#include "BusRoute.h"
/////
//// todo use curr STOP ID IDK WHERE
//////
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
	//pointer for linking in hash tables
	
public:
	Bus* next = nullptr;
	// --- Basic Getters ---
	string getID() const { return busID; }
	string getRoute() const { return busRouteID; }
	int getPassengers() const { return currPassengers; }
	int getCapacity() const { return capacity; }
	RouteStack* getStack() const { return busRouteHistory; }
	 // --Setters--
	void setcurrStopID(int stopID) { currStopID = stopID; }

	Bus(string busId="", string currRoute= "", int stopID = 0, int cap = 0,  bool ammv = true, bool dir = true)
	{
		busRouteHistory = new RouteStack();
		busID = busId;
		busRouteID = currRoute;
		capacity = cap;
		isMoving = ammv;
		direction = dir;
		currPassengers = 0;
		currStopID = stopID;
	}
	void changeState()
	{
		isMoving = !isMoving;
	}
	void changeDIr() 
	{
		direction = !direction;
	}
	void AddPassengers() 
	{
		int toAdd = rand() % (capacity - currPassengers + 1);
		currPassengers += toAdd;
		cout << toAdd << " passengers boarded the bus " << busID << ". Current passengers: " << currPassengers << endl;
	}
	void RemovePassengers()
	{
		// Exit if no passengers to prevent crashes.
		if (currPassengers <= 0)
		{
			return;
		}

		int maxToRemove = currPassengers / 2;
		int toRemove;

		if (maxToRemove == 0)
		{
			toRemove = 0;
		}
		else
		{
			toRemove = rand() % maxToRemove;
		}

		currPassengers -= toRemove;
		cout << toRemove << " passengers alighted from the bus " << busID << ". Current passengers: " << currPassengers << endl;
	}

	void simulateMovement(BusRoute* route) 
	{
		BusStop* head = route->getStartingStop();
		
		// Find current stop in the route
		BusStop* curr = head;
		BusStop* currentStop = nullptr;
		
		// Find the stop where bus is currently located
		while (curr) {
			if (curr->getStopID() == currStopID) {
				currentStop = curr;
				break;
			}
			curr = curr->nextStop;
		}
		
		if (!currentStop) {
			cout << "Bus " << busID << " is not on a valid stop!" << endl;
			return;
		}
		
		// Check if bus can move to next stop
		if (currentStop->nextStop != nullptr) {
			// Normal movement - move to next stop
			currentStop = currentStop->nextStop;
			currStopID = currentStop->getStopID();
			
			RemovePassengers();
			AddPassengers();
			busRouteHistory->push(currentStop->getStopName());
			cout << "Bus " << busID << " moved to stop " << currentStop->getStopName() << " (ID: " << currStopID << ")." << endl;
		}
		else {
			// Reached end of route - reverse the route in the BusRoute object
			cout << "Bus " << busID << " has reached the end of the route. Reversing route direction." << endl;
			
			// Reverse the route in the BusRoute object itself
			route->reverseRoute();
			
			// Now find the bus's current position in the reversed route and move to next
			head = route->getStartingStop(); // Get new head after reversal
			curr = head;
			while (curr) {
				if (curr->getStopID() == currStopID) {
					// Bus found in reversed route, move to next stop if possible
					if (curr->nextStop) {
						curr = curr->nextStop;
						currStopID = curr->getStopID();
						RemovePassengers();
						AddPassengers();
						busRouteHistory->push(curr->getStopName());
						cout << "Bus " << busID << " moved to stop " << curr->getStopName() << " (ID: " << currStopID << ") in reversed route." << endl;
					}
					break;
				}
				curr = curr->nextStop;
			}
		}
	}
};

#endif