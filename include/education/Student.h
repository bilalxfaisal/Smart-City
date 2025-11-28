#include "../utils/Nodes.h"
#include <iostream>
#ifndef STUDENT_H
#define STUDENT_H
using std::cout;
using std::cin;
using std::endl;
using std::string;
//Linked List of students.
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




string Student::getStudentID() { return studentID; }
string Student::getStudentName() { return name; }
void Student::printStudentDetails()
{
	cout << "ID: " << studentID << " | ";
	cout << "Name: " << name << " | ";
	cout << "Age: " << age << endl;
}
void insertStudent(Student* head, string id, string name, int age) 
{
    Student* newStudent = new Student(id, name, age);
    newStudent->next = head;
    head = newStudent;

}
void deleteStudent(Student** head_ref, string key) 
{
    //DELETE HEAD
    Student* temp = *head_ref, * prev = nullptr;
    if (temp != nullptr && temp->studentID == key) 
    {
        *head_ref = temp->next; 
        delete temp;            
        return;
    }
	//DELETE OTHER THAN HEAD
    while (temp != nullptr && temp->studentID != key) 
    {
        prev = temp;
        temp = temp->next;
    }
	// If key was not present in linked list
    if (temp == nullptr)
    {
        return;
    }
    prev->next = temp->next;
    delete temp; 
}
void printStudents(Student* node) 
{
    while (node != nullptr) 
    {
        node->printStudentDetails();
        node = node->next;
    }
}
//Linked List of Faculty
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
    void InsertFaculty(Faculty** head_ref, string id, string name, string spec) 
    {
        Faculty* newFaculty = new Faculty(id, name, spec);
        newFaculty->next = *head_ref;
        *head_ref = newFaculty;
	}
    void deleteFaculty(Faculty** head_ref, string key) 
    {
        Faculty* temp = *head_ref, * prev = nullptr;
        if (temp != nullptr && temp->FacultyID == key) 
        {
            *head_ref = temp->next; 
            delete temp;            
            return;
        }
        while (temp != nullptr && temp->FacultyID != key) 
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            return;
        }
        prev->next = temp->next;
        delete temp; 
	}
    void printFaculties(Faculty* node) 
    {
        while (node != nullptr) 
        {
            cout << "Faculty ID: " << node->FacultyID << " | ";
            cout << "Name: " << node->name << " | ";
            cout << "Specialization: " << node->specialization << endl;
            node = node->next;
        }
	}
};




#endif