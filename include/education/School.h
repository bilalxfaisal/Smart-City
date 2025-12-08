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
	Faculty* FacultyHead; // n-ary tree of faculties
	School* nextSibling;  // n-ary trees
	Location schoolLocation;



	School(string ID, string name, string sector, int campus);
	void addSubject(const string& subject);
	bool addFaculty(const Faculty& fac);
	bool addClassToDepartment(const string& deptID, const Class& cls);
	bool removeStudentByName(const string& classId, const string& deptId, const string& studentId);
	bool removeStudentByID(const string& classId, const string& deptId, const string& studentId);
	bool removeFacultyByName(const string& facName);

	bool AddStudent(string classId, string deptId, Student student);
	bool addDepartment(Department& dept);
	void display();
	void displayStudentsInClass(string, string);

	string getSchoolName() const {
		return schoolName;
	}
	string getSchoolSector() const {
		return sector;
	}
	Location& getSchoolLocation() 
	{
		return schoolLocation;
	}
	void display() const {
		cout << "School ID: " << schoolID
			<< ", Name: " << schoolName
			<< ", Sector: " << sector
			<< ", Rating: " << rating
			<< ", Campus No: " << campusNo << endl;

		Department* temp = Bacha;
		while (temp) {
			temp->display();  // Display department details
			temp = temp->nextSibling;  // Move to next department
		}
	}
	// Default Constructor
	School()
	{
		subjectCount = 0;
		totalSubjets = 10;
		subjects = new string[totalSubjets](); // <--- ALLOCATE MEMORY HERE
		rating = 0.0f;
		Bacha = nullptr;
		FacultyHead = nullptr;
		campusNo = 0;
		nextSibling = nullptr;
	}


	void setSchoolDetails(string id, string n, string sec, float r) {
		schoolID = id;
		schoolName = n;
		sector = sec;
		rating = r;
	}

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
	// 1. Check if we need to resize
	if (subjectCount >= totalSubjets) {
		int newSize = totalSubjets * 2;
		string* newSubjects = new string[newSize]();

		// Copy old subjects
		for (int i = 0; i < subjectCount; i++) {
			newSubjects[i] = subjects[i];
		}

		delete[] subjects;
		subjects = newSubjects;
		totalSubjets = newSize;
	}

	// 2. Add the new subject
	subjects[subjectCount] = sub;

	// 3. CRITICAL STEP: Increment the counter!
	subjectCount++;
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
	else 
	{
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
	}
	return false;

}
bool School::AddStudent(string classId,string deptId, Student student)
{

	Department* temp = Bacha;
	while (temp) 
	{
		if (temp->deptID == deptId) {
			break;
		}
		temp = temp->nextSibling;
	}
	while (temp) 
	{
		Class* cls = temp->findClassByID(classId);
		if (cls) {
			cls->addStudent(student);
			return true;
		}
		temp = temp->nextSibling;
	}
	return false;
}
bool School::addDepartment(Department& dept) 
{
	Department* toADD = new Department(dept);
	if (Bacha == nullptr) 
	{
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

void School::display() 
{
	Department* temp = Bacha;
	while (temp) {
		cout << "Department ID: " << temp->deptID << " | ";
		cout << "Department Name: " << temp->deptName << endl;
		temp->display();
		temp = temp->nextSibling;
	}
}
void School::displayStudentsInClass(string classId, string deptId)
{
	Department* temp = Bacha;
	while (temp) 
	{
		if (temp->deptID == deptId) {
			break;
		}
		temp = temp->nextSibling;
	}
	while (temp) 
	{
		Class* cls = temp->findClassByID(classId);
		if (cls) {
			cls->printStudentsInClass();
			return;
		}
		temp = temp->nextSibling;
	}
	cout << "Could not find class " << classId << " in department " << deptId << endl;
	return;
}
bool School::removeStudentByName(const string& classId, const string& deptId, const string& studentName) 
{
	Department* temp = Bacha;
	while (temp) 
	{
		if (temp->deptID == deptId) {
			break;
		}
		temp = temp->nextSibling;
	}
	while (temp) 
	{
		Class* cls = temp->findClassByID(classId);
		if (cls) {
			return cls->deleteStudentByName(studentName);
		}
		temp = temp->nextSibling;
	}
	cout << "Could not find student " << studentName << " in class " << classId << " of department " << deptId << endl;
	return false;
}

bool School::removeStudentByID(const string& classId, const string& deptId, const string& studentId)
{
	Department* temp = Bacha;
	while (temp)
	{
		if (temp->deptID == deptId) {
			break;
		}
		temp = temp->nextSibling;
	}
	while (temp)
	{
		Class* cls = temp->findClassByID(classId);
		if (cls) {
			return cls->deleteStudentbyID(studentId);
		}
		temp = temp->nextSibling;
	}
	cout << "Could not find student with ID " << studentId << " in class " << classId << " of department " << deptId << endl;
	return false;
}
bool School::removeFacultyByName(const string& facName) 
{
	Faculty* temp = FacultyHead;
	Faculty* prev = nullptr;
	while (temp != nullptr) 
	{
		if (temp->name == facName) 
		{
			// Found the faculty -> delete and return true
			if (prev == nullptr)
				FacultyHead = temp->next;  // deleting head
			else
				prev->next = temp->next;
			delete temp;
			return true;  // deletion successful
		}
		prev = temp;
		temp = temp->next;
	}
	cout << "Faculty with name " << facName << " not found in School " << schoolName << endl;
	return false; // no faculty found
}

#endif