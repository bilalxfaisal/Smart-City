// include/utils/Nodes.h
#ifndef NODES_H
#define NODES_H

#include <string>
using std::string;
  //String Keys
    inline int Polynomial_Rolling_Hash_V1(string& str)
    {
        const int p = 31;
        const int m = 1e9 + 9;
        int hash_value = 0;
        int p_pow = 1;
        for (char c : str) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return static_cast<int>(hash_value);
    }
    inline int Polynomial_Rolling_Hash_V2(string& str)
    {
        const int p = 53;
        const int m = 1e9 + 9;
        int hash_value = 0;
        int p_pow = 1;
        for (char c : str) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return static_cast<int>(hash_value);
    }
    inline int DJB2_Hash(string& str)
    {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + c;
        }
        return static_cast<int>(hash);
    }

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
	int subjectCount; // current number of subjects
    int totalSubjets; // size of the array of strings, initial size set to 10
    Department* Bacha;

    Faculty* FacultyHead;

    School* nextSibling; // n ary trees

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
    void addFaculty();
};


#endif