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
	BusRoute(string rName, int rID, int stopsCount) {
		routeName = rName;
		routeID = rID;
		busStopsCount = stopsCount;
		startingStop = NULL;
	}


	void addStop_AFTR(BusStop& toAdd, string AfterStop) 
	{
		//BASE CASE
		if (startingStop == nullptr)
		{
			BusStop* newStop = new BusStop(toAdd);
			startingStop = newStop;
			busStopsCount = 1;
			return;
		}
		BusStop* newStop = new BusStop(toAdd);
		BusStop* curr = startingStop;
		while (curr) {
			if (curr->getStopName() == AfterStop) {
				if (curr->nextStop) {
					curr->nextStop->prevStop = newStop;
					newStop->nextStop = curr->nextStop;
					newStop->prevStop = curr;
					curr->nextStop = newStop;
					busStopsCount++;
					return;
				}
				else {
					curr->nextStop = newStop;
					newStop->prevStop = curr;
					busStopsCount++;
					return;
				}
			}
		}
	}

	void addStop_B4(BusStop& toAdd, string beforeStop)
	{
		// CASE 1: route is empty
		if (startingStop == nullptr)
		{
			BusStop* newStop = new BusStop(toAdd);
			startingStop = newStop;
			busStopsCount = 1;
			return;
		}
		BusStop* newStop = new BusStop(toAdd);
		BusStop* curr = startingStop;

		if (startingStop->getStopName() == beforeStop) {
			newStop->nextStop = startingStop;
			startingStop->prevStop = newStop;
			startingStop = newStop;
			busStopsCount++;
			return;
		}
		while (curr) {
			if (curr->getStopName() == beforeStop) {
				curr->prevStop->nextStop = newStop;
				newStop->prevStop = curr->prevStop;
				newStop->nextStop = curr;
				curr->prevStop = newStop;
				busStopsCount++;
				return;
			}
		}
	}

	void removeStop(string stopName) {
		BusStop* curr = startingStop;
		while (curr) {
			if (curr->getStopName() == stopName) {
				if (curr->prevStop) {
					curr->prevStop->nextStop = curr->nextStop;
				}
				else {
					startingStop = curr->nextStop;
				}
				if (curr->nextStop) {
					curr->nextStop->prevStop = curr->prevStop;
				}
				delete curr;
				busStopsCount--;
				return;
			}
			curr = curr->nextStop;
		}
	}

	BusStop* getStartingStop() {
		return startingStop;
	}
	//GETTER
	string getRouteName() const {
		return routeName;
	}

};


#endif