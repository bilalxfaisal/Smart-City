#include "../utils/Nodes.h"
#include "School.h"
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
	// heap array size
	int heapSize;
	// heap array capacity
	int heapCapacity;

	int currSchools; // current number of schools stored in the array
	int totalSchools; // current capacity of the array
	School* schools; // n-ary tree for schools
	School** schoolHashTable; // hash table for quick access to schools by ID
	School** heapArr; // max heap for schools based on rating, array structure

protected:
	void resizeHeap() {
		School** newArr = new School * [heapCapacity * 2];
		for (int i = 0; i < heapSize; i++) {
			newArr[i] = heapArr[i];
		}
		delete[] heapArr;
		heapArr = newArr;
		heapCapacity *= 2;
	}
public:
	EducationSystem(int nSchools) : currSchools(0), totalSchools(nSchools), 
	heapSize(0), heapCapacity(nSchools) {

		schools = nullptr; // cuz n-ary so linkedlist
		schoolHashTable = new School * [nSchools](); // initializes to nullptr

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
		index = index % totalSchools;		
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
			heapSize++;
			heapifyUp(heapSize - 1);  // Heapify up from the newly added element
		}
		else {
			resizeHeap();
			heapArr[heapSize] = toAdd;
			heapSize++;
			heapifyUp(heapSize - 1);  // Heapify up from the newly
		}

	}
	
	// Heapify up : maintains max - heap property after insertion
	// CONSIDERING NO DELETION HAPPENS
	void heapifyUp(int index) {
		while (index > 0) {
			int parent = (index - 1) / 2;

			// If current node's rating is greater than parent's, swap
			if (heapArr[index]->rating > heapArr[parent]->rating) {
				School* temp = heapArr[index];
				heapArr[index] = heapArr[parent];
				heapArr[parent] = temp;

				index = parent;
			}
			else {
				break;  // Heap property satisfied
			}
		}
	}

	School* getMaxRatedSchool() {
		return (heapSize > 0) ? heapArr[0] : nullptr;
	}

	// takes in School ID, Department Name, Classroom Name
	// will be using the 
	bool addStudent(Student& st1, string& destSchool, string& destDepartment, string& destClassroom) {
		School* toAdd = nullptr;
		int index = Polynomial_Rolling_Hash_V1(destSchool);
		index = index % totalSchools;

		toAdd = schoolHashTable[index];
		if (toAdd == nullptr) {
			return false; // school not found
		}
		else {
			 return toAdd->AddStudent(destClassroom, destDepartment, st1);
		}
		return false;
	}

	// takes in School ID and adds Department to it
	bool addDepartment(string& destSchool, Department& dp1) {
		School* toAdd = nullptr;
		int index = Polynomial_Rolling_Hash_V1(destSchool);
		index = index % totalSchools;

		toAdd = schoolHashTable[index];
		if (toAdd == nullptr) {
			return false;
		}
		else {
			return toAdd->addDepartment(dp1);
		}
		return false;
	}

	// takes in School ID as a string, Department ID as a string and adds the class to it
	bool addClass(string& destSchool, string& destDepartment, Class& c1) {
		School* toAdd = nullptr;
		int index = Polynomial_Rolling_Hash_V1(destSchool);
		index = index % totalSchools;

		toAdd = schoolHashTable[index];
		if (toAdd == nullptr) {
			return false;
		}
		else {
			return toAdd->addClassToDepartment(destDepartment, c1);
		}
		return false;
	}

	bool addFaculty(string& destSchool, Faculty& f1) {
		School* toAdd = nullptr;
		int index = Polynomial_Rolling_Hash_V1(destSchool);
		index = index % totalSchools;

		toAdd = schoolHashTable[index];
		if (toAdd == nullptr) {
			return false;
		}
		else {
			return toAdd->addFaculty(f1);
		}
		return false;
	}

	void display() {
		School* temp = schools;
		cout << "Displaying all schools in the Education System:" << endl;
		while (temp) {
			cout << "School ID: " << temp->schoolID << ", Name: " << temp->schoolName << ", Rating: " << temp->rating << endl;
			temp->display();
			temp = temp->nextSibling;
		}
	}
};

#endif