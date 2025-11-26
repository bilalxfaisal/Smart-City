#include "../utils/Nodes.h"
#include <iostream>
#ifndef EDUCATIONSYSTEM_H
#define EDUCATIONSYSTEM_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

// TODO: make hashfunction, implement maxheap, add required pointers to school class, make heapify
class EducationSystem
{
	int hashTableSize;
	int noOfSchools;
	int heapSize;
	int heapCapacity;
	School* schools; // n-ary tree for schools
	School** schoolHashTable; // hash table for quick access to schools by ID
	School** heapArr; // max heap for schools based on rating, array structure

protected:
	void resizeHeap();
public:
	EducationSystem(int nSchools, int hashSize)
		: noOfSchools(nSchools), hashTableSize(hashSize), heapSize(0) {

		schools = nullptr;
		schoolHashTable = new School * [hashSize](); // initializes to nullptr

		// Pre-allocate heap for max N schools (no need to resize later)
		heapCapacity = nSchools;
		heapArr = new School * [heapCapacity]; // array of pointers
	}

	// THIS METHOD SHALL AND SHALL ONLY GET A SCHOOL OBJECT WHICH HAS NO KIDS
	// ADDING KIDS MUST BE DONE SEPARATELY
	void addSchool(School& newSchool) {
		School* toAdd = new School(newSchool);

		// getting index using the hashFunction
		int index = Polynomial_Rolling_Hash_V1(newSchool.schoolID);
		
		// checking for collisions
		if (schoolHashTable[index] != NULL) {
			// perform chaining, adding to head of L. List
			toAdd->nextSibling = schoolHashTable[index];
			schoolHashTable[index] = toAdd;
		}
		else {
			schoolHashTable[index] = toAdd;
		}

		// now add to the school general tree
		if (schools == nullptr) {
			schools = toAdd;
		}
		else {
			// adding to head cuz more easier
			toAdd->nextSibling = schools;
			schools = toAdd;
		}

		// Now for MaxHeap
		if (heapSize < heapCapacity) {
			heapArr[heapSize] = toAdd;
			heapify();
			heapSize++;
		}

	}
};

#endif