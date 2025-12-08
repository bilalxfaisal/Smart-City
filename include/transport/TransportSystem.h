#include "../utils/Nodes.h"
#include "../utils/LocationManager.h"
#include "BusStop.h"
#include "Bus.h"
#include "BusRoute.h"
#include "TransportCompany.h"
#include <iostream>
#include <chrono> // in case of time delays addition
#ifndef TRANSPORTSYSTEM_H
#define TRANSPORTSYSTEM_H

using std::string;
using std::cout;
using std::cin;
using std::endl;
// using namespace std::chrono;

// todo: giraph banana hai
class TransportSystem
{
	// kaam kaam "bus" ka kaam
	// jinnah
	int busStopsCount;// for giraffe

	int currRoutes;
	int routesTableSize;
	BusRoute** routeHashTable; // hashtable of routes string based
	
	Location* headBusStopsList = nullptr; // linked list of all bus stops in the system
	
	int currCompanies;
	int companyTableSize;
	TransportCompany** companyHashTable; // hashtable of transport companies string based by name

	// Helper: Add bus stop location to linked list (with duplicate check)
	void addBusStopLocationToList(Location& busStopLocation) {
		Location* temp = headBusStopsList;
		while (temp) {
			if (temp == &busStopLocation) return;
			temp = temp->next;
		}
		busStopLocation.next = headBusStopsList;
		headBusStopsList = &busStopLocation;
		busStopsCount++;
	}

	// Helper: Remove bus stop location from linked list
	void removeBusStopLocationFromList(Location& busStopLocation) {
		if (!headBusStopsList) return;
		if (headBusStopsList == &busStopLocation) {
			headBusStopsList = headBusStopsList->next;
			busStopLocation.next = nullptr;
			busStopsCount--;
			return;
		}
		Location* temp = headBusStopsList;
		while (temp->next) {
			if (temp->next == &busStopLocation) {
				temp->next = busStopLocation.next;
				busStopLocation.next = nullptr;
				busStopsCount--;
				return;
			}
			temp = temp->next;
		}
	}

public:
	TransportSystem(int compSize = 20, int routeSize = 20)
	{
		companyTableSize = compSize;
		routesTableSize = routeSize;

		companyHashTable = new TransportCompany * [companyTableSize];
		routeHashTable = new BusRoute * [routesTableSize];

		for (int i = 0; i < companyTableSize; i++)
			companyHashTable[i] = nullptr;

		for (int i = 0; i < routesTableSize; i++)
			routeHashTable[i] = nullptr;

		currCompanies = 0;
		currRoutes = 0;
		busStopsCount = 0;
		headBusStopsList = nullptr;
	}
	void resizeTransportCompTable() {
		int newSize = companyTableSize * 2;
		TransportCompany** newTable = new TransportCompany * [newSize];
		for (int i = 0; i < newSize; i++)
			newTable[i] = nullptr;

		// Rehash all companies
		for (int i = 0; i < companyTableSize; i++) {
			TransportCompany* curr = companyHashTable[i];
			while (curr) {
				TransportCompany* next = curr->nextCompany;
				int index = Polynomial_Rolling_Hash_V1(curr->name) % newSize;
				curr->nextCompany = newTable[index];
				newTable[index] = curr;
				curr = next;
			}
		}

		delete[] companyHashTable;
		companyHashTable = newTable;
		companyTableSize = newSize;
	}
	void addTransportCompany(TransportCompany& t1)
	{
		if (currCompanies == companyTableSize)
		{
			resizeTransportCompTable();
		}
		TransportCompany* toAdd = new TransportCompany(t1);
		int index = Polynomial_Rolling_Hash_V1(t1.name);
		index = index % companyTableSize;
		if (companyHashTable[index] == nullptr) {
			companyHashTable[index] = toAdd;
		}
		else {
			// collision handling via linked List
			toAdd->nextCompany = companyHashTable[index];
			companyHashTable[index] = toAdd;
			// done
		}
	}
	void resizeRoutesTable() {
		int newSize = routesTableSize * 2;
		BusRoute** newTable = new BusRoute * [newSize];
		for (int i = 0; i < newSize; i++)
			newTable[i] = nullptr;
		// Rehash all routes
		for (int i = 0; i < routesTableSize; i++) {
			BusRoute* curr = routeHashTable[i];
			while (curr) {
				BusRoute* next = curr->nextRoute;
				int index = Polynomial_Rolling_Hash_V1(curr->getRouteName()) % newSize;
				curr->nextRoute = newTable[index];
				newTable[index] = curr;
				curr = next;
			}
		}
		delete[] routeHashTable;
		routeHashTable = newTable;
		routesTableSize = newSize;
	}
	void addBusRoute(BusRoute& br) 
	{
		if (currRoutes == routesTableSize)
		{
			resizeRoutesTable();
		}
		BusRoute* toAdd = new BusRoute(br);
		string nameget = br.getRouteName();
		int index = Polynomial_Rolling_Hash_V1(nameget);
		index = index % routesTableSize;
		if (routeHashTable[index] == nullptr) {
			routeHashTable[index] = toAdd;
		}
		else {
			// collision handling via linked List
			toAdd->nextRoute = routeHashTable[index];
			routeHashTable[index] = toAdd;
			// done
		}

		// Add all bus stops from this route to the location linked list
		BusStop* currentStop = toAdd->getStartingStop();
		while (currentStop) {
			addBusStopLocationToList(currentStop->getLocation());
			currentStop = currentStop->nextStop;
		}
	}

	void addBusToTransportCompany(Bus& b1, string& companyName)
	{
		Bus* toAdd = new Bus(b1);
		int index = Polynomial_Rolling_Hash_V1(companyName);
		index = index % companyTableSize;
		TransportCompany* curr = companyHashTable[index];
		while (curr) {
			if (curr->name == companyName) {
				curr->addBus(*toAdd);
				return;
			}
			curr = curr->nextCompany;
		}
	}

	// add time delays I guess
	void simulateBusMovement() {
		TransportCompany* currCompany = nullptr;
		for (int i = 0; i < companyTableSize; i++) 
		{
			currCompany = companyHashTable[i];
			// function in TransportCompany to simulate all buses
			if (currCompany) 
			{
				for (int i = 0; i < currCompany->busTableSize; i++)
				{
					Bus* BusPtr = currCompany->busHashTable[i];
					while (BusPtr) 
					{
						// find the route for this bus
						int routeIndex = Polynomial_Rolling_Hash_V1(BusPtr->getRoute());
						routeIndex = routeIndex % routesTableSize;
						BusRoute* routePtr = routeHashTable[routeIndex];
						while (routePtr && routePtr->getRouteName() != BusPtr->getRoute()) 
						{
							routePtr = routePtr->nextRoute;
						}
						if (routePtr) 
						{
							currCompany->simulateBusMovement(BusPtr, routePtr);
						}
						BusPtr = BusPtr->next;
					}
				}
			}
		}
	}


	// the fnc must only display the companies name and the fnc it calls is 
	void displayCompanyStatus(string companyName) {
		TransportCompany* currCompany = nullptr;
		int index = Polynomial_Rolling_Hash_V1(companyName);
		index = index % companyTableSize;
		currCompany = companyHashTable[index];
		if (currCompany) {
			cout << "Transport Company: " << companyName << endl;
			currCompany->display();
		}
		else {
			cout << "Company not found." << endl;
		}
	}

	void displayRoutes(string compName) {
		int index = Polynomial_Rolling_Hash_V1(compName);
		index = index % companyTableSize;
		TransportCompany* currCompany = companyHashTable[index];

		if (currCompany) {
			int tableSize = currCompany->busTableSize;
			for (int i = 0; i < tableSize; i++) {
				Bus* currBus = currCompany->busHashTable[i];
				if (currBus) {
					string currBusStop = currBus->getRoute();
					int routeIndex = Polynomial_Rolling_Hash_V1(currBusStop);
					routeIndex = routeIndex % routesTableSize;
					if (routeHashTable[routeIndex]) {
						BusRoute* currRoute = routeHashTable[routeIndex];
						cout << "Showing route for Bus: " << currBus->getID();
						currRoute->DisplayRoute();
					}
				}
			}
		}
	}

	void displayBusHistory(string& company, string& busID) {
		int companyIndex = Polynomial_Rolling_Hash_V1(company);
		companyIndex %= companyTableSize;

		TransportCompany* comp = companyHashTable[companyIndex];
		if (comp) {
			int busIndex = Polynomial_Rolling_Hash_V1(busID);
			busIndex %= comp->busTableSize;
			Bus* busToDisplay = comp->busHashTable[busIndex];
			if (busToDisplay) {
				RouteStack* history = busToDisplay->getStack();
				while (!history->isEmpty()) {
					string his = history->top();
					cout << his << " ";
					history->pop();
				}
			}
		}
	}
	// Add to TransportSystem class public section:

	void connectBusStopsSubgraph() {
		cout << "\n[INFO] Connecting bus stops subgraph...\n";

		if (!headBusStopsList) {
			cout << "[WARNING] No bus stops to connect.\n";
			return;
		}

		int connectedCount = 0;
		Location* bs1 = headBusStopsList;

		while (bs1) {
			Location* bs2 = headBusStopsList;
			while (bs2) {
				if (bs1 != bs2) {
					float dist = sqrt(
						pow(bs2->x - bs1->x, 2) +
						pow(bs2->y - bs1->y, 2)
					);

					// Connect bus stops within 150 units
					if (dist < 150.0f && dist > 0) {
						bool edgeExists = false;
						Edge* e = bs1->adjList;
						while (e) {
							if (e->destination == bs2) {
								edgeExists = true;
								break;
							}
							e = e->nextEdge;
						}

						if (!edgeExists) {
							Edge* newEdge1 = new Edge(dist, bs2);
							newEdge1->nextEdge = bs1->adjList;
							bs1->adjList = newEdge1;

							Edge* newEdge2 = new Edge(dist, bs1);
							newEdge2->nextEdge = bs2->adjList;
							bs2->adjList = newEdge2;

							connectedCount++;
						}
					}
				}
				bs2 = bs2->next;
			}
			bs1 = bs1->next;
		}

		cout << "[SUCCESS] Connected " << connectedCount << " bus stop pairs.\n";
	}

	// Find shortest path along a bus route
	PathNode* findShortestPathOnRoute(string routeName, string startStopName, string endStopName) {
		// Find route
		int idx = Polynomial_Rolling_Hash_V1(routeName) % routesTableSize;
		BusRoute* route = routeHashTable[idx];

		while (route && route->getRouteName() != routeName) {
			route = route->nextRoute;
		}

		if (!route) {
			cout << "[ERROR] Route not found.\n";
			return nullptr;
		}

		// Find start and end stops in route
		BusStop* startStop = nullptr;
		BusStop* endStop = nullptr;

		BusStop* temp = route->getStartingStop();
		while (temp) {
			if (temp->getStopName() == startStopName) {
				startStop = temp;
			}
			if (temp->getStopName() == endStopName) {
				endStop = temp;
			}
			temp = temp->nextStop;
		}

		if (!startStop || !endStop) {
			cout << "[ERROR] One or both stops not found on route.\n";
			return nullptr;
		}

		Location* start = &(startStop->getLocation());
		Location* end = &(endStop->getLocation());

		// Reset graph
		Location* loc = headBusStopsList;
		while (loc) {
			loc->minDist = std::numeric_limits<float>::max();
			loc->visited = false;
			loc->parent = nullptr;
			loc = loc->next;
		}

		// Dijkstra
		MinHeap pq(1000);
		start->minDist = 0;
		pq.push(start, 0);

		while (!pq.isEmpty()) {
			Location* u = pq.extractMin();
			if (u == end) break;
			if (u->visited) continue;
			u->visited = true;

			Edge* e = u->adjList;
			while (e) {
				Location* v = e->destination;
				float weight = e->weight;
				if (!v->visited && u->minDist + weight < v->minDist) {
					v->minDist = u->minDist + weight;
					v->parent = u;
					pq.push(v, v->minDist);
				}
				e = e->nextEdge;
			}
		}

		if (end->minDist == std::numeric_limits<float>::max()) {
			cout << "[ERROR] No path found between stops.\n";
			return nullptr;
		}

		// Build path
		PathNode* pathHead = nullptr;
		Location* crawler = end;
		while (crawler) {
			PathNode* newNode = new PathNode(crawler);
			newNode->next = pathHead;
			pathHead = newNode;
			crawler = crawler->parent;
		}

		return pathHead;
	}

	BusRoute** getRouteHashTable() {
		return routeHashTable;
	}

	// for bus consstructor so to initialize the starting stop of the bus to the first stop of the route
	int getStartingBusStopID(string& routeName) {
		int index = Polynomial_Rolling_Hash_V1(routeName);
		index = index % routesTableSize;
		BusRoute* currRoute = routeHashTable[index];
		while (currRoute) {
			if (currRoute->getRouteName() == routeName) {
				BusStop* startStop = currRoute->getStartingStop();
				if (startStop) {
					return startStop->getStopID();
				}
			}
			currRoute = currRoute->nextRoute;
		}
		return -1; // not found
	}

	// Getter for bus stop location head (for visualization)
	Location* getBusStopLocationHead() const { return headBusStopsList; }

	// Get total bus stops count
	int getBusStopsCount() const { return busStopsCount; }
};

#endif