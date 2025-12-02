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
	
public:
	BusRoute* nextRoute; // pointer to the next bus route in the system
	
	BusRoute(string rName, int rID, int stopsCount) 
	{
		routeName = rName;
		routeID = rID;
		busStopsCount = stopsCount;
		startingStop = nullptr;
		nextRoute = nullptr;
	}

	bool addStop_AFTR(BusStop& toAdd, string AfterStop) 
	{
		//BASE CASE
		if (startingStop == nullptr)
		{
			BusStop* newStop = new BusStop(toAdd);
			startingStop = newStop;
			busStopsCount = 1;
			return true;
		}
		
		BusStop* newStop = new BusStop(toAdd);
		BusStop* curr = startingStop;
		
		while (curr) {
			if (curr->getStopName() == AfterStop) {
				// Insert after this stop
				newStop->nextStop = curr->nextStop;
				curr->nextStop = newStop;
				busStopsCount++;
				return true;
			}
			curr = curr->nextStop;
		}
		return false;
	}

	bool addStop_B4(BusStop& toAdd, string beforeStop)
	{
		// CASE 1: route is empty
		if (startingStop == nullptr)
		{
			BusStop* newStop = new BusStop(toAdd);
			startingStop = newStop;
			busStopsCount = 1;
			return true;
		}
		
		BusStop* newStop = new BusStop(toAdd);
		
		// CASE 2: insert before the first stop
		if (startingStop->getStopName() == beforeStop) {
			newStop->nextStop = startingStop;
			startingStop = newStop;
			busStopsCount++;
			return true;
		}
		
		// CASE 3: find the stop before the target and insert after it
		BusStop* curr = startingStop;
		while (curr->nextStop) {
			if (curr->nextStop->getStopName() == beforeStop) {
				newStop->nextStop = curr->nextStop;
				curr->nextStop = newStop;
				busStopsCount++;
				return true;
			}
			curr = curr->nextStop;
		}
		return false;
	}

	void removeStop(string stopName) {
		if (!startingStop) return;
		
		// If removing the first stop
		if (startingStop->getStopName() == stopName) {
			BusStop* toDelete = startingStop;
			startingStop = startingStop->nextStop;
			delete toDelete;
			busStopsCount--;
			return;
		}
		
		// Find the stop before the one to remove
		BusStop* curr = startingStop;
		while (curr->nextStop) {
			if (curr->nextStop->getStopName() == stopName) {
				BusStop* toDelete = curr->nextStop;
				curr->nextStop = curr->nextStop->nextStop;
				delete toDelete;
				busStopsCount--;
				return;
			}
			curr = curr->nextStop;
		}
	}

	// Reverse the entire route (singly linked list reversal)
	void reverseRoute() {
		BusStop* prev = nullptr;
		BusStop* current = startingStop;
		BusStop* next = nullptr;
		
		while (current != nullptr) {
			next = current->nextStop;
			current->nextStop = prev;
			prev = current;
			current = next;
		}
		
		startingStop = prev;
	}

	// Find a specific stop by ID
	BusStop* findStopByID(int stopID) {
		BusStop* curr = startingStop;
		while (curr != nullptr) {
			if (curr->getStopID() == stopID) {
				return curr;
			}
			curr = curr->nextStop;
		}
		return nullptr;
	}

	BusStop* getStartingStop() {
		return startingStop;
	}

	string getRouteName() const {
		return routeName;
	}

	void DisplayRoute() {
		BusStop* curr = startingStop;
		cout << "Bus Route: " << routeName << " (ID: " << routeID << ")\n";
		cout << "Stops in Route:\n";
		while (curr) {
			cout << " - " << curr->getStopName() << " (ID: " << curr->getStopID() << ")\n";
			curr = curr->nextStop;
		}
	}
};

#endif