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
	bool addFaculty(const Faculty& fac);
	bool addClassToDepartment(const string& deptID, const Class& cls);

	bool AddStudent(string classId, Student student);
	bool addDepartment(string deptId);
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

bool School::addFaculty(const Faculty& fac) 
{
	// assuming that the faculty head variable is actually an n-ary pwease
	Faculty* toAdd = new Faculty(fac);
	if (FacultyHead == nullptr)
	{
		FacultyHead = toAdd;
		return true;
	}
	else {
		// adding to head for ease cuz why not meri jaan why not
		toAdd->next = FacultyHead;
		FacultyHead = toAdd;
	}
	return true;
}
bool School::addClassToDepartment(const string& deptID, const Class& cls) {
	Department* temp = Bacha;
	while (temp) {
		if (temp->deptID == deptID) {
			temp->addClass(cls);
			return true;
		}
		temp = temp->nextSibling;
		cout << "Added a class to department " << deptID << endl;
	}
	return false;

}
bool School::AddStudent(string classId, Student student) {
	Department* temp = Bacha;
	while (temp) {
		Class* cls = temp->findClassByID(classId);
		if (cls) {
			cls->addStudent(student);
			return true;
		}
		temp = temp->nextSibling;
	}
	return false;
}
bool School::addDepartment(string deptId) {
	Department* toADD = new Department();
	toADD->deptID = deptId;
	if (Bacha == nullptr) {
		Bacha = toADD;
		return true;
	}
	else {
		toADD->nextSibling = Bacha;
		Bacha = toADD;
		return true;
	}
	return false;
}

#endif