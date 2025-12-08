#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "../utils/Nodes.h"
#include "../education/Class.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Department
{
public:
    std::string deptID;
    std::string deptName;
    Class* Bacha;
    Department* nextSibling;

    Department(string name = " ", string id = " ")
        : deptID(id), deptName(name), Bacha(nullptr), nextSibling(nullptr) {
    }

    ~Department() {
        while (Bacha) {
            Class* temp = Bacha;
            Bacha = Bacha->nextSibling;
            delete temp;
        }
    }

    void addClass(Class cls1) {
        Class* toADD = new Class(cls1);
        if (Bacha == nullptr) {
            Bacha = toADD;
        }
        else {
            toADD->nextSibling = Bacha;
            Bacha = toADD;
        }
    }

    Class* findClassByID(const string ID) const {
        Class* temp = Bacha;
        while (temp) {
            if (temp->classID == ID) {
                return temp;
            }
            temp = temp->nextSibling;
        }
        return nullptr;
    }

    Class* findClassByName(const string name) const {
        Class* temp = Bacha;
        while (temp) {
            if (temp->className == name) {
                return temp;
            }
            temp = temp->nextSibling;
        }
        return nullptr;
    }

    bool RemoveClassByID(string ID) {
        Class* temp = Bacha;
        Class* prev = nullptr;
        while (temp) {
            if (temp->classID == ID) {
                if (prev != nullptr) {
                    prev->nextSibling = temp->nextSibling;
                }
                else {
                    Bacha = temp->nextSibling; // Update head if removing first element
                }
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->nextSibling;
        }
        return false;
    }

    bool RemoveClassByName(string name) {
        Class* temp = Bacha;
        Class* prev = nullptr;
        while (temp) {
            if (temp->className == name) {
                if (prev != nullptr) {
                    prev->nextSibling = temp->nextSibling;
                }
                else {
                    Bacha = temp->nextSibling; // Update head if removing first element
                }
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->nextSibling;
        }
        return false;
    }

    void addStudentToClass(string classID, string studentID, string studentName, int age) {
        Class* cls = findClassByID(classID);
        if (cls) {
            cls->addStudent(Student(studentID, studentName, age));
        }
        else {
            cout << "Class with ID " << classID << " not found in Department " << deptName << endl;
        }
    }

    void display() const {
        Class* temp = Bacha;
        while (temp) {
            cout << "  Class ID: " << temp->classID << " | ";
            cout << "Class Name: " << temp->className << endl;
            temp->display();
            temp = temp->nextSibling;
        }
    }

    bool removeStudentByName(string classID, string studentID) {
        Class* cls = findClassByID(classID);
        if (cls) {
            return cls->deleteStudentbyID(studentID);
        }
        else {
            cout << "Class with ID " << classID << " not found in Department " << deptName << endl;
            return false;
        }
    }

    bool removeStudentByID(string classID, string studentName) {
        Class* cls = findClassByID(classID);
        if (cls) {
            return cls->deleteStudentByName(studentName);
        }
        else {
            cout << "Class with ID " << classID << " not found in Department " << deptName << endl;
            return false;
        }
    }

    void display() const {
        cout << "Department ID: " << deptID << ", Name: " << deptName << endl;
        Class* temp = Bacha;
        while (temp) {
            cout << "  Class ID: " << temp->classID << ", Name: " << temp->className << endl;
            temp->display();  // Display students in the class
            temp = temp->nextSibling;  // Move to next class
        }
    }
};

#endif // !DEPARTMENT_H
