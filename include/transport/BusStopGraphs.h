#pragma once
#include "../utils/Nodes.h"
#include "BusStop.h"
#ifndef BUSSTOPGRAPHS_H
#define BUSSTOPGRAPHS_H
using std::string;
using std::cout;
using std::cin;

struct StopEdge
{
	BusStop* points_to = nullptr;
	float weight;
	//Ajacency list
	StopEdge* next = nullptr;
	StopEdge(BusStop* n = nullptr, float wt=0)
	{
		points_to = n;
		weight = wt;
	}
};
struct VertexStop
{
	BusStop* Meh = nullptr;
	StopEdge* AdjacencyList = nullptr;

	VertexStop(BusStop* bs=nullptr) 
	{
		Meh = bs;
	}
};
class graphStops
{
private:
	VertexStop* vertices = nullptr;
	int capacity = 0;
	int count_stops = 0;

public:
	graphStops(int n = 5) 
	{
		if (n < 0)
		{
			n = 5;
		}
		capacity = n;
		vertices = new VertexStop[n];
	}
	void addStop(BusStop* toAdd) 
	{
		if (count_stops == capacity)
		{
			Resize();
		}
		vertices[count_stops].Meh = toAdd;
		count_stops++;
	}
	void Resize()
	{
		int newCapacity = capacity * 2;
		VertexStop* newArray = new VertexStop[newCapacity];
		for (int i = 0; i < count_stops; i++)
		{
			newArray[i] = vertices[i];
		}
		delete[] vertices;
		vertices = newArray;
		capacity = newCapacity;

	}
	void addEdge(BusStop* from, BusStop* to, float weight)
	{
		//find from index
		int fromIndex = -1;
		for (int i = 0; i < count_stops; i++)
		{
			// Assuming BusStop has a method getName() to identify it
			if (vertices[i].Meh->getStopName() == from->getName())
			{
				fromIndex = i;
				break;
			}
		}
		int toIndex = -1;
		for (int i = 0; i < count_stops; i++)
		{
			if (vertices[i].Meh->getStopName() == to->getName())
			{
				toIndex = i;
				break;
			}
		}
		if (fromIndex == -1 || toIndex == -1)
		{
			cout << "From or To BusStop not found in graph." << endl;
			return;
		}
		// Create new edge
		StopEdge* newEdge = new StopEdge(to, weight);
		// Insert at the beginning of the adjacency list
		newEdge->next = vertices[fromIndex].AdjacencyList;
		vertices[fromIndex].AdjacencyList = newEdge;

	}
	void removeEdge(BusStop* from, BusStop* to)
	{
		int fromIndex = -1;
		for (int i = 0; i < count_stops; i++)
		{
			if (vertices[i].Meh->getStopName() == from->getName())
			{
				fromIndex = i;
				break;
			}
		}
		int toIndex = -1;
		for (int i = 0; i < count_stops; i++)
		{
			if (vertices[i].Meh->getStopName() == to->getName())
			{
				toIndex = i;
				break;
			}
		}
		if (fromIndex == -1 || toIndex == -1)
		{
			cout << "From or To BusStop not found in graph." << endl;
			return;
		}
		// Remove edge from fromIndex to toIndex
		StopEdge* current = vertices[fromIndex].AdjacencyList;
		StopEdge* prev = nullptr;
		while (current != nullptr)
		{
			if (current->points_to == to)
			{
				if (prev == nullptr)
				{
					vertices[fromIndex].AdjacencyList = current->next;
				}
				else
				{
					prev->next = current->next;
				}
				delete current;
				return;
			}
			prev = current;
			current = current->next;
		}
		cout << "Edge not found." << endl;
	}
	void UpdateWeight(BusStop* from, BusStop* to, float newWeight)
	{
		int fromIndex = -1;
		for (int i = 0; i < count_stops; i++)
		{
			if (vertices[i].Meh->getStopName() == from->getName())
			{
				fromIndex = i;
				break;
			}
		}
		int toIndex = -1;
		for (int i = 0; i < count_stops; i++)
		{
			if (vertices[i].Meh->getStopName() == to->getName())
			{
				toIndex = i;
				break;
			}
		}
		if (fromIndex == -1 || toIndex == -1)
		{
			cout << "From or To BusStop not found in graph." << endl;
			return;
		}
		StopEdge* current = vertices[fromIndex].AdjacencyList;
		while (current != nullptr)
		{
			if (current->points_to == to)
			{
				current->weight = newWeight;
				return;
			}
			current = current->next;
		}
		cout << "Edge not found." << endl;
	}
};


#endif  BUSSTOPGRAPHS_H