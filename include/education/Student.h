#include "../utils/Nodes.h"
#include <iostream>
#ifndef STUDENT_H
#define STUDENT_H
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Student
{
public:
    std::string studentID;
    std::string name;
    int age;
    Student* next;

    Student(string id = "", string nam = "", int ag = 0)
    {
        studentID = id;
        name = nam;
        age = ag;
        next = nullptr;
    }

    string getStudentID();
    string getStudentName();
    void printStudentDetails();
};


class Faculty
{
public:
    string FacultyID;
    string name;
    string specialization;
    Faculty* next;

    Faculty(string id = "", string nam = "", string spec = "")
    {
        FacultyID = id;
        name = nam;
        specialization = spec;
        next = nullptr;
    }
};

string Student::getStudentID() { return studentID; }
string Student::getStudentName() { return name; }
void Student::printStudentDetails()
{
	cout << "ID: " << studentID << " | ";
	cout << "Name: " << name << " | ";
	cout << "Age: " << age << endl;
}


#endif