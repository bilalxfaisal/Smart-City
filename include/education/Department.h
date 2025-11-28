#include "../utils/Nodes.h"
#include "../education/Class.h"
#include <iostream>

#ifndef DEPARTMENT_H
#define DEFINE_H

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

    Department()
    {
        Bacha = nullptr;
        nextSibling = nullptr;
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

    // find functions return the class if found else nullptr
    Class* findClassByID(string ID) {
		Class* temp = Bacha;
        while (temp) {
			if (temp->classID == ID) {
                return temp;
            }
            temp = temp->nextSibling;
        }
		return nullptr;
    }
    Class* findClassByName(string name) {
		Class* temp = Bacha;
        while (temp) {
            if (temp->className == name) {
                return temp;
            }
            temp = temp->nextSibling;
        }
        return nullptr;
    }

	// returns true if removed, false if not found
    bool RemoveClassByID(string ID) {
		Class* temp = Bacha;
		Class* prev = nullptr;
        while (temp) {
            if (temp->classID == ID) {
				prev->nextSibling = temp->nextSibling;
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
                    delete temp;
                    return true;
                }
                else {
					temp = temp->nextSibling;
					delete Bacha;
					Bacha = temp;
					return true;
                }
            }
            prev = temp;
            temp = temp->nextSibling;
        }
        return false;
    }
	//Add a student in respective class
    void addStudentToClass(string classID, string studentID, string studentName, int age) {
        Class* cls = findClassByID(classID);
        if (cls) 
        {
			cls->addStudent(Student(studentID, studentName, age));

        }
        else 
        {
            cout << "Class with ID " << classID << " not found in Department " << deptName << endl;
        }
	}

    void display() {
		Class* temp = Bacha;
        while (temp) {
            cout << "  Class ID: " << temp->classID << " | ";
            cout << "Class Name: " << temp->className << endl;
            temp->display();
            temp = temp->nextSibling;
        }
    }
};


#endif // !DEPARTMENT_H