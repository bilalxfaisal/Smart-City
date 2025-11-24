#pragma once
#include <iostream>
#include <string>
using namespace std;
namespace HashFuncs
{
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
}

//Hash maps for education sector
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

class Teacher
{
public:
    string teacherID;
    string name;
    string specialization;

    Teacher* next;

    Teacher(string id = "", string nam = "", string spec = "")
    {
        teacherID = id;
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

    string* subjects;
    int subjectCount;

    Department* deptHead;

    Teacher* teacherHead;

    School* next;

    School()
    {
        subjects = nullptr;
        subjectCount = 0;

        deptHead = nullptr;
        teacherHead = nullptr;

        next = nullptr;
    }
};

