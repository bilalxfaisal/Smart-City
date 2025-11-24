#pragma once
#include <string>

class Student
{
public:
    std::string studentID;
    std::string name;
    int age;

    Student* next; 

    Student()
    {
        next = nullptr;
    }
};

class Class
{
public:
    std::string classID;
    std::string className;

    
    Student* studentHead;

    Class* next;   

    Class()
    {
        studentHead = nullptr;
        next = nullptr;
    }
};

class Department
{
public:
    std::string deptID;
    std::string deptName;

    
    Class* classHead;

    Department* next;   

    Department()
    {
        classHead = nullptr;
        next = nullptr;
    }
};

class School
{
public:
    std::string schoolID;
    std::string schoolName;
    std::string sector;

    // linked list of departments
    Department* deptHead;

    School* next; // for hashing schools in an array with chaining

    School()
    {
        deptHead = nullptr;
        next = nullptr;
    }
};
