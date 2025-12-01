#include "../utils/Nodes.h"
#include "RouteStack.h"
#include "BusStop.h"

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

	Bus(string busId="", int currRoute=0, int cap=0, bool ammv=true, bool dir=true) 
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
	void AddPassengers() 
	{
		int toAdd = rand() % (capacity - currPassengers + 1);
		currPassengers += toAdd;
		cout << toAdd << " passengers boarded the bus " << busID << ". Current passengers: " << currPassengers << endl;
	}
	void RemovePassengers() 
	{	
		int maxToRemove = currPassengers/2;
		int toRemove = rand() % (maxToRemove);
		currPassengers -= toRemove;
		cout << toRemove << " passengers alighted from the bus " << busID << ". Current passengers: " << currPassengers << endl;
	}

	void simulateMovement(BusStop* head) 
	{
		// move one stop forward or backward based on direction
		BusStop* curr = head;
		while(curr){
			if (curr->getStopID() == currStopID) {
				if (direction) {
					if (curr->nextStop == nullptr) {
						cout<<"Bus "<<busID<<" has reached the end of the route and will reverse direction."<<endl;
						direction = !direction;
						RemovePassengers();
						AddPassengers();
						busRouteHistory->push(curr->getStopName());
						break;
					}
					// basically an else case in disguise
					curr = curr->nextStop;
					currStopID = curr->getStopID();
				}
				else {
					if (curr->nextStop == nullptr) {
						cout << "Bus " << busID << " has reached the end of the route and will reverse direction." << endl;
						direction = !direction;
						RemovePassengers();
						AddPassengers();
						busRouteHistory->push(curr->getStopName());
						break;
					}
					curr = curr->prevStop;
					currStopID = curr->getStopID();
				}
				// removing must be done first i suppose :D
				RemovePassengers();
				AddPassengers();
				busRouteHistory->push(curr->getStopName());
				break;
			}
			curr = curr->nextStop;
		}
	}
};

#endif