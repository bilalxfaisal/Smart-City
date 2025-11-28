#include "../Smart-City-DS-Project/include/education/EducationSystem.h"
#include <iostream>
#include <string>


using namespace std;

void showMenu() {
    cout << "\n====== EDUCATION SYSTEM MENU ======\n";
    cout << "1. Add School\n";
    cout << "2. Add Department to School\n";
    cout << "3. Add Class to Department\n";
    cout << "4. Add Student to Class\n";
    cout << "5. Add Faculty to School\n";
    cout << "6. Show Max Rated School\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    EducationSystem ES(20, 50);  // Capacity: 20 schools, hash=50

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            // ADD SCHOOL
            string id, name, sector;
            int campus;

            cout << "Enter School ID: ";
            getline(cin, id);
            cout << "Enter School Name: ";
            getline(cin, name);
            cout << "Enter Sector: ";
            getline(cin, sector);
            cout << "Enter Campus No: ";
            cin >> campus;

            School sch(id, name, sector, campus);
            ES.addSchool(sch);

            cout << "School added successfully!\n";
        }

        else if (choice == 2) {
            // ADD DEPARTMENT
            string schoolID, deptID, deptName;

            cout << "Enter School ID: ";
            cin.ignore();
            getline(cin, schoolID);

            cout << "Enter Department ID: ";
            getline(cin, deptID);
            cout << "Enter Department Name: ";
            getline(cin, deptName);

            Department dp;
            dp.deptID = deptID;
            dp.deptName = deptName;

            if (ES.addDepartment(schoolID, dp))
                cout << "Department added!\n";
            else
                cout << "School not found!\n";
        }

        else if (choice == 3) {
            // ADD CLASS
            string schoolID, deptID, classID, className;

            cout << "Enter School ID: ";
            cin.ignore();
            getline(cin, schoolID);

            cout << "Enter Department ID: ";
            getline(cin, deptID);

            cout << "Enter Class ID: ";
            getline(cin, classID);
            cout << "Enter Class Name: ";
            getline(cin, className);

            Class cls;
            cls.classID = classID;
            cls.className = className;

            if (ES.addClass(schoolID, deptID, cls))
                cout << "Class added!\n";
            else
                cout << "School/Department not found!\n";
        }

        else if (choice == 4) {
            // ADD STUDENT
            string schoolID, deptID, classID, studentID, studentName;
            int age;

            cout << "Enter School ID: ";
            cin.ignore();
            getline(cin, schoolID);

            cout << "Enter Department ID: ";
            getline(cin, deptID);

            cout << "Enter Class ID: ";
            getline(cin, classID);

            cout << "Enter Student ID: ";
            getline(cin, studentID);
            cout << "Enter Student Name: ";
            getline(cin, studentName);
            cout << "Enter Age: ";
            cin >> age;

            Student st(studentID, studentName, age);

            if (ES.addStudent(st, schoolID, deptID, classID))
                cout << "Student added!\n";
            else
                cout << "Error: Could not add student.\n";
        }

        else if (choice == 5) {
            // ADD FACULTY
            string schoolID, facID, name, spec;

            cout << "Enter School ID: ";
            cin.ignore();
            getline(cin, schoolID);

            cout << "Enter Faculty ID: ";
            getline(cin, facID);
            cout << "Enter Faculty Name: ";
            getline(cin, name);
            cout << "Enter Specialization: ";
            getline(cin, spec);

            Faculty f(facID, name, spec);

            if (ES.addFaculty(schoolID, f))
                cout << "Faculty added!\n";
            else
                cout << "Could not add faculty.\n";
        }

        else if (choice == 6) {
            // SHOW TOP SCHOOL BY RATING
            School* max = ES.getMaxRatedSchool();
            if (max) {
                cout << "\n===== TOP RATED SCHOOL =====\n";
                cout << "ID: " << max->schoolID << endl;
                cout << "Name: " << max->schoolName << endl;
                cout << "Rating: " << max->rating << endl;
            }
            else {
                cout << "No schools in the system yet.\n";
            }
        }

        else if (choice == 0) {
            cout << "Exiting system… Goodbye!\n";
        }

        else {
            cout << "Invalid option, try again.\n";
        }

    } while (choice != 0);

    return 0;
}
