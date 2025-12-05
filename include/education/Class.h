#include "../utils/Nodes.h"
#include "../education/Student.h"
#include <iostream>
#ifndef CLASS_H
#define CLASS_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Class
{
public:
	std::string classID;
	std::string className;
	Student* Bacha;
	Class* nextSibling;

	Class(string name = " ", string id = " ")
	{
		classID = id;
		className = name;
		Bacha = nullptr;
		nextSibling = nullptr;
	}

	//void switchStudentPlaces(Student*, Student*);
	//void switchStudentPlaces(int, int);
	bool isClassEmpty();
	string getClassID();
	string getClassName();
	Student* searchStudentByID(string ID);
	Student* searchStudentByName(string name);
	int getStudentCount();
	void printStudentsInClass();
	bool deleteStudentbyID(string studentID);
	bool deleteStudentByName(string name);
	bool addStudent(const Student& stu);
	void display();
};


bool Class::isClassEmpty()
{
	return Bacha == nullptr;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
string Class::getClassID() { return classID; }
string Class::getClassName() { return className; }
Student* Class::searchStudentByID(string ID)
{
	Student* temp = Bacha;
	while (temp != nullptr)
	{
		if (temp->getStudentID() == ID)
		{
			return temp;
		}
		temp = temp->next;
	}
	return nullptr; // not found
}
Student* Class::searchStudentByName(string name)
{
	Student* temp = Bacha;
	while (temp != nullptr)
	{
		if (temp->getStudentName() == name)
		{
			return temp;
		}
		temp = temp->next;
	}
	return nullptr; // not found
}
int Class::getStudentCount()
{
	int count = 0;
	Student* temp = Bacha;
	while (temp != nullptr)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
void Class::printStudentsInClass()
{
	Student* temp = Bacha;
	while (temp != nullptr)
	{
		temp->printStudentDetails();
		temp = temp->next;
	}
}
//void Class::switchStudentPlaces(Student* st1, Student* st2)
//{
//	string tempID = st1->studentID;
//	string tempName = st1->name;
//	int tempAge = st1->age;
//	st1->name = st2->name;
//	st1->age = st2->age;
//	st2->name = tempName;
//	st2->age = tempAge;
//	// the IDs remain the same only the students are switched
//}
//void Class::switchStudentPlaces(int studentID1, int studentID2)
//{
//	Student* student1 = searchStudentByID(studentID1);
//	Student* student2 = searchStudentByID(studentID2);
//	if (student1 != nullptr && student2 != nullptr)
//	{
//		switchStudentPlaces(student1, student2);
//	}
//}
bool Class::deleteStudentbyID(string studentID)
{
	Student* temp = Bacha;
	Student* prev = nullptr;
	while (temp != nullptr && temp->studentID != studentID)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == nullptr) 
	{
		cout << "Student with ID " << studentID << " not found in class " << className << endl;
		return false; // Student not found
	}
	if (prev == nullptr)
	{
		Bacha = temp->next; // Deleting the first student
	}
	else
	{
		prev->next = temp->next; // Bypass the deleted student
	}
	delete temp; // Free memory
	return true;
}
bool Class::deleteStudentByName(string name)
{
	Student* temp = Bacha;
	Student* prev = nullptr;

	while (temp != nullptr)
	{
		if (temp->name == name)
		{
			// Found the student -> delete and return true
			if (prev == nullptr)
				Bacha = temp->next;  // deleting head
			else
				prev->next = temp->next;

			delete temp;
			return true;  // deletion successful
		}

		prev = temp;
		temp = temp->next;
	}

	cout << "Student with name " << name << " not found in class " << className << endl;
	return false; // no student found
}



bool Class::addStudent(const Student& stu)
{
	Student* toAdd = new Student(stu);
	if (Bacha == nullptr)
	{
		Bacha = toAdd;
		return true;
	}
	else
	{
		toAdd->next = Bacha;
		Bacha = toAdd;
		return true;
	}

}

void Class::display()
{
	Student* temp = Bacha;
	while (temp)
	{
		cout << "Student ID: " << temp->studentID << ", Name: " << temp->name << ", Age: " << temp->age << endl;
		temp = temp->next;
	}
}

#endif