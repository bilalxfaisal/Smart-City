// include/utils/Nodes.h
#ifndef NODES_H
#define NODES_H

#include <string>
using std::string;

// ==================== FORWARD DECLARATIONS ====================

// Transport entities
class BusStop;
class Bus;
class TransportCompany;

// Education entities
class Student;
class Class;
class Department;
class School;
class Faculty; // yes needed; 25/11/25 11:58 AM

// Medical entities
class Doctor;
class Patient;
class Medicine;
class Pharmacy;
class Hospital;

// Commercial entities
class Product;
class Mall;
class Store;

// Population entities
class Citizen;
class Family;
class House;
class Street;
class Sector;

// Facility entities
class PublicFacility;
class Mosque;
class Park;
class Library;
// idk what else is called a public facility
// me is stupid

// ==================== NODE STRUCTURES ====================
// the rest of the node structures would go here...

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

};


class Class
{
public:
    std::string classID;
    std::string className;


    Student* Bacha;

    Class* nextSibling;

    Class()
    {
        Bacha = nullptr;
        nextSibling = nullptr;
    }
};

class Department
{
public:
    std::string deptID;
    std::string deptName;


    Class* Bacha;

    Department* nextSibling;

    Department()
    {
        Bacha = nullptr;
        nextSibling = nullptr;
    }
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

class School
{
public:
    string schoolID;
    string schoolName;
    string sector;
    float rating;
    int campusNo;

    string* subjects;
    int subjectCount;

    Department* Bacha;

    Faculty* FacultyHead;

    School* nextSibling; // n ary trees

    School()
    {
        subjects = nullptr;
        subjectCount = 0;

        Bacha = nullptr;
        FacultyHead = nullptr;

        nextSibling = nullptr;
    }
};


#endif