#include "../utils/Nodes.h"
#include <iostream>
#ifndef STUDENT_H
#define STUDENT_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

int Student::getStudentID() { return studentID; }
string Student::getStudentName() { return name; }
void Student::printStudentDetails()
{
	cout << "ID: " << studentID << " | ";
	cout << "Name: " << name << " | ";
	cout << "Age: " << age << endl;
}
#endif