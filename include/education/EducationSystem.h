#include "../utils/Nodes.h"
#include "../utils/LocationManager.h"
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

	Location* schoolLocationHead = nullptr;

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
	// Add to EducationSystem class public section:

	void connectSchoolsSubgraph() {
		cout << "\n[INFO] Connecting schools subgraph...\n";

		if (!schoolLocationHead) {
			cout << "[WARNING] No schools to connect.\n";
			return;
		}

		int connectedCount = 0;
		Location* current = schoolLocationHead;

		while (current) {
			// Connect each school to nearby schools (within 200 units)
			Location* other = schoolLocationHead;
			while (other) {
				if (current != other) {
					float dist = sqrt(
						pow(other->x - current->x, 2) +
						pow(other->y - current->y, 2)
					);

					// Connect if within reasonable distance
					if (dist < 200.0f && dist > 0) {
						// Check if edge already exists
						bool edgeExists = false;
						Edge* e = current->adjList;
						while (e) {
							if (e->destination == other) {
								edgeExists = true;
								break;
							}
							e = e->nextEdge;
						}

						if (!edgeExists) {
							// Add bidirectional edge
							Edge* newEdge1 = new Edge(dist, other);
							newEdge1->nextEdge = current->adjList;
							current->adjList = newEdge1;

							Edge* newEdge2 = new Edge(dist, current);
							newEdge2->nextEdge = other->adjList;
							other->adjList = newEdge2;

							connectedCount++;
						}
					}
				}
				other = other->next;
			}
			current = current->next;
		}

		cout << "[SUCCESS] Connected " << connectedCount << " school pairs.\n";
	}

	// Find shortest path between two schools
	PathNode* findShortestPathBetweenSchools(string schoolID1, string schoolID2) {
		// Find schools by ID
		School* school1 = nullptr;
		School* school2 = nullptr;

		int idx1 = Polynomial_Rolling_Hash_V1(schoolID1) % totalSchools;
		int idx2 = Polynomial_Rolling_Hash_V1(schoolID2) % totalSchools;

		School* temp = schoolHashTable[idx1];
		while (temp && temp->schoolID != schoolID1) {
			temp = temp->nextSibling;
		}
		school1 = temp;

		temp = schoolHashTable[idx2];
		while (temp && temp->schoolID != schoolID2) {
			temp = temp->nextSibling;
		}
		school2 = temp;

		if (!school1 || !school2) {
			cout << "[ERROR] One or both schools not found.\n";
			return nullptr;
		}

		// Use Dijkstra on school locations
		Location* start = &(school1->getSchoolLocation());
		Location* end = &(school2->getSchoolLocation());

		// Reset graph
		Location* loc = schoolLocationHead;
		while (loc) {
			loc->minDist = std::numeric_limits<float>::max();
			loc->visited = false;
			loc->parent = nullptr;
			loc = loc->next;
		}

		// Dijkstra's algorithm
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
			cout << "[ERROR] No path found between schools.\n";
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

	//RESIZING TEM
	void resizeSchoolHashTable() {
		int newSize = totalSchools * 2;
		School** newTable = new School * [newSize];
		for (int i = 0; i < newSize; i++)
			newTable[i] = nullptr;
		// Rehash all schools
		for (int i = 0; i < totalSchools; i++) {
			School* curr = schoolHashTable[i];
			while (curr) {
				School* next = curr->nextSibling;
				int index = Polynomial_Rolling_Hash_V1(curr->schoolID) % newSize;
				curr->nextSibling = newTable[index];
				newTable[index] = curr;
				curr = next;
			}
		}
		delete[] schoolHashTable;
		schoolHashTable = newTable;
		totalSchools = newSize;
	}
	// THIS METHOD SHALL AND SHALL ONLY GET A SCHOOL OBJECT WHICH HAS NO KIDS
	// ADDING KIDS MUST BE DONE SEPARATELY
	void addSchool(School& newSchool)
    {
		if (currSchools >= totalSchools) {
			resizeSchoolHashTable();
		}
		School* toAdd = new School(newSchool);

		// add location to location linked list for graph
		addSchoolLocation(toAdd->getSchoolLocation());

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

	void display() {
		cout << "\n=== Education System ===" << endl;
		cout << "Total Schools: " << currSchools << endl;
		cout << "\nDisplaying all schools in the Education System:" << endl;
		cout << "==============================================" << endl;

		School* temp = schools;
		int count = 0;
		while (temp) {
			count++;
			cout << "\nSchool #" << count << ":" << endl;
			cout << "School ID: " << temp->schoolID
				<< ", Name: " << temp->schoolName
				<< ", Rating: " << temp->rating
				<< ", Sector: " << temp->sector
				<< ", Campus: " << temp->campusNo << endl;
			cout << "Location: (" << temp->schoolLocation.x
				<< ", " << temp->schoolLocation.y << ")" << endl;
			cout << "-------------------------------------------" << endl;
			temp = temp->nextSibling;
		}

		if (count == 0) {
			cout << "No schools found in the system." << endl;
		}
		cout << "==============================================" << endl;
	}
	void displayStudentsInClass(const string& schoolId, const string& deptId, const string& classId) 
	{
		School* toDisplayFrom = nullptr;
		int index = Polynomial_Rolling_Hash_V1(schoolId);
		index = index % totalSchools;
		toDisplayFrom = schoolHashTable[index];
		if (toDisplayFrom == nullptr) 
		{
			cout << "School with ID " << schoolId << " not found." << endl;
			return; // school not found
		}
		else {
			 toDisplayFrom->displayStudentsInClass(classId, deptId);
			 return;
		}
		cout << "Could not display students in class " << classId << " in department " << deptId << " of school " << schoolId << endl;
		return;
	}
	void displayStudentsInSchool(const string& schoolId) 
	{
		School* toDisplayFrom = nullptr;
		int index = Polynomial_Rolling_Hash_V1(schoolId);
		index = index % totalSchools;
		toDisplayFrom = schoolHashTable[index];
		if (toDisplayFrom == nullptr) 
		{
			cout << "School with ID " << schoolId << " not found." << endl;
			return; // school not found
		}
		else {
			 toDisplayFrom->display();
			 return;
		}
		cout << "Could not display students in school " << schoolId << endl;
		return;
	}
	bool removeStudentByID(const string& schoolId, const string& deptId, const string& classId, const string& studentID) 
	{
		School* toRemoveFrom = nullptr;
		int index = Polynomial_Rolling_Hash_V1(schoolId);
		index = index % totalSchools;
		toRemoveFrom = schoolHashTable[index];
		if (toRemoveFrom == nullptr) {
			cout << "School with ID " << schoolId << " not found." << endl;
			return false; // school not found
		}
		else {
			 return toRemoveFrom->removeStudentByID(classId, deptId, studentID);
		}
		cout << "Could not remove student with ID " << studentID << " from class " << classId << " in department " << deptId << " of school " << schoolId << endl;
		return false;
	}
	bool removeStudentByName(const string& schoolId, const string& deptId, const string& classId, const string& studentName)
	{
		School* toRemoveFrom = nullptr;
		int index = Polynomial_Rolling_Hash_V1(schoolId);
		index = index % totalSchools;
		toRemoveFrom = schoolHashTable[index];
		if (toRemoveFrom == nullptr) 
		{
			cout << "School with ID " << schoolId << " not found." << endl;
			return false; // school not found
		}
		else {
			return toRemoveFrom->removeStudentByName(classId, deptId, studentName);
		}
		cout << "Could not remove student with name " << studentName << " from class " << classId << " in department " << deptId << " of school " << schoolId << endl;
		return false;
	}
	bool addFaculty(string& destSchool, Faculty& f1) 
	{
		School* toAdd = nullptr;
		int index = Polynomial_Rolling_Hash_V1(destSchool);
		index = index % totalSchools;
		toAdd = schoolHashTable[index];
		if (toAdd == nullptr) 
		{
			cout << "School with ID " << destSchool << " not found." << endl;
			return false;
		}
		else {
			return toAdd->addFaculty(f1);
		}
		cout << "Could not add faculty to school with ID " << destSchool << endl;
		return false;
	}
	bool addSubject(string& destSchool, const string& subjectName) 
	{
		School* toAdd = nullptr;
		int index = Polynomial_Rolling_Hash_V1(destSchool);
		index = index % totalSchools;
		toAdd = schoolHashTable[index];
		if (toAdd == nullptr) 
		{
			cout << "School with ID " << destSchool << " not found." << endl;
			return false;
		}
		else {
			toAdd->addSubject(subjectName);
			return true;
		}
		cout << "Could not add subject to school with ID " << destSchool << endl;
		return false;
	}
	bool removeFacultyByName(const string& schoolId, const string& facName) 
	{
		School* toRemoveFrom = nullptr;
		int index = Polynomial_Rolling_Hash_V1(schoolId);
		index = index % totalSchools;
		toRemoveFrom = schoolHashTable[index];
		if (toRemoveFrom == nullptr) {
			cout << "School with ID " << schoolId << " not found." << endl;
			return false; // school not found
		}
		else {
			 return toRemoveFrom->removeFacultyByName(facName);
		}
		cout << "Could not remove faculty member with name " << facName << " from school " << schoolId << endl;
		return false;
	}

	void addSchoolLocation(Location& loc)
	{
		// Check for duplicates
		Location* temp = schoolLocationHead;
		while (temp) {
			if (temp == &loc) return; // Already exists
			temp = temp->next;
		}
		
		loc.next = schoolLocationHead;
		schoolLocationHead = &loc;
	}

	void removeSchoolLocation(Location& loc)
	{
		if (!schoolLocationHead) return;
		
		if (schoolLocationHead == &loc) {
			schoolLocationHead = schoolLocationHead->next;
			loc.next = nullptr;
			return;
		}
		
		Location* temp = schoolLocationHead;
		while (temp->next) {
			if (temp->next == &loc) {
				temp->next = loc.next;
				loc.next = nullptr;
				return;
			}
			temp = temp->next;
		}
	}

	Location* getSchoolLocationsHead()
	{
		return schoolLocationHead;
	}
};

#endif