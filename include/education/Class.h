#include "../utils/Nodes.h"
#inlcude "../education/Student.h"
#include <iostream>
#ifndef CLASS_H
#define CLASS_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool Class::isClassEmpty()
{
	return firstStudent == nullptr;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
string Class::getClassID() { return classID; }
string Class::getClassName() { return className; }
Student* Class::searchStudentByID(int ID)
{
	Student* temp = firstStudent;
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
Student* Class::searchStudentByName()
{
	Student* temp = firstStudent;
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
	Student* temp = firstStudent;
	while (temp != nullptr)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
void Class::printStudentsInClass()
{
	Student* temp = firstStudent;
	while (temp != nullptr)
	{
		temp->printStudentDetails();
		temp = temp->next;
	}
}
void Class::switchStudentPlaces(Student* st1, Student* st2)
{
	int tempID = st1->studentID;
	string tempName = st1->name;
	int tempAge = st1->age;
	st1->name = st2->name;
	st1->age = st2->age;
	st2->name = tempName;
	st2->age = tempAge;
	// the IDs remain the same only the students are switched
}
void Class::switchStudentPlaces(int studentID1, int studentID2)
{
	Student* student1 = searchStudentByID(studentID1);
	Student* student2 = searchStudentByID(studentID2);
	if (student1 != nullptr && student2 != nullptr)
	{
		switchStudentPlaces(student1, student2);
	}
void Class::deleteStudentbyID(int studentID)
{
	Student* temp = firstStudent;
	Student* prev = nullptr;
	while (temp != nullptr && temp->studentID != studentID)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == nullptr) return; // Student not found
	if (prev == nullptr)
	{
		firstStudent = temp->next; // Deleting the first student
	}
	else
	{
		prev->next = temp->next; // Bypass the deleted student
	}
	delete temp; // Free memory
}
void Class::deleteStudentByName(string name)
{
	Student* temp = firstStudent;
	Student* prev = nullptr;

	while (temp != nullptr)
	{
		if (temp->name == name)
		{
			Student* toDelete = temp;

			if (prev == nullptr)
				firstStudent = temp->next;  // deleting head
			else
				prev->next = temp->next;

			temp = temp->next;
			delete toDelete;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}
