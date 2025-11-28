#include "../utils/Nodes.h"
#include "Department.h"
#include <iostream>

#ifndef School_H
#define School_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

class School
{
public:
	string schoolID;
	string schoolName;
	string sector;
	float rating;
	int campusNo;
	string* subjects;
	int subjectCount;     // current number of subjects
	int totalSubjets;     // size of the array of strings, initial size set to 10
	Department* Bacha;
	Faculty* FacultyHead;
	School* nextSibling;  // n-ary trees

	School()
	{
		subjects = nullptr;
		subjectCount = 0;
		totalSubjets = 10; // initial size
		rating = 0.0f;
		Bacha = nullptr;
		FacultyHead = nullptr;
		campusNo = 0;
		nextSibling = nullptr;
	}

	School(string ID, string name, string sector, int campus);
	void addSubject(const string& subject);
	void addFaculty(const Faculty& fac);
	bool addClassToDepartment(Department& dept, const Class& cls);
};


School::School(string ID, string name, string sector, int campus) {
	schoolID = ID;
	schoolName = name;
	this->sector = sector;
	campusNo = campus;
	subjects = nullptr;
	subjectCount = 0;
	totalSubjets = 10; // initial size
	subjects = new string[totalSubjets]();
	rating = 0.0f;
	Bacha = nullptr;
	FacultyHead = nullptr;
	nextSibling = nullptr;
}

void School::addSubject(const string& sub) {
	if (subjectCount >= totalSubjets) {
		// need to resize
		int newSize = totalSubjets * 2;
		string* newSubjects = new string[newSize]();
		// copy old subjects
		for(int i = 0; i < subjectCount; i++) {
			newSubjects[i] = subjects[i];
		}
		// delete old array
		delete[] subjects;
		subjects = newSubjects;
		totalSubjets = newSize;
	}
	else {
		// enough space
		subjects[subjectCount] = sub;
	}
}

void School::addFaculty(const Faculty& fac) {
	// assuming that the faculty head variable is actually an n-ary pwease
	Faculty* toAdd = new Faculty(fac);
	if (FacultyHead == nullptr) {
		FacultyHead = toAdd;
	}
	else {
		// adding to head for ease cuz why not meri jaan why not
		toAdd->next = FacultyHead;
		FacultyHead = toAdd;
	}
}
bool School::addClassToDepartment(Department& dept, const Class& cls) {
	// find the department in the school
	Department* temp = Bacha;
	while (temp) {
		if (temp->deptID == dept.deptID) {
			// found the department, add class
			temp->addClass(cls);
			return true;
		}
		temp = temp->nextSibling;
	}
	return false; // department not found
}

#endif