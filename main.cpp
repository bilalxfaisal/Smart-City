
#include "../Smart-City-DS-Project/include/education/EducationSystem.h"
#include <iostream>
#include <string>


using namespace std;

static string readLine(const string& prompt)
{
    string line;
    cout << prompt;
    std::getline(cin, line);
    return line;
}

static int readInt(const string& prompt)
{
    while (true)
    {
        string s = readLine(prompt);
        try
        {
            size_t pos = 0;
            int val = stoi(s, &pos);
            if (pos == s.length()) return val;
        }
        catch (...) { /* fallthrough to retry */ }
        cout << "Invalid number, please try again.\n";
    }
}

void showMenu()
{
    cout << "\n====== EDUCATION SYSTEM MENU ======\n";
    cout << "1. Add School\n";
    cout << "2. Add Department to School\n";
    cout << "3. Add Class to Department\n";
    cout << "4. Add Student to Class\n";
    cout << "5. Add Faculty to School\n";
    cout << "6. Show Max Rated School\n";
    cout << "7. DISSplay \n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main()
{
    EducationSystem ES(20);  // Capacity: 20 schools

    int choice = -1;
    do
    {
        showMenu();
        
        string choiceLine;
        std::getline(cin, choiceLine);
        try
        {
            choice = stoi(choiceLine);
        }
        catch (...)
        {
            choice = -1;
        }

        if (choice == 1)
        {
            // ADD SCHOOL
            string id = readLine("Enter School ID: ");
            string name = readLine("Enter School Name: ");
            string sector = readLine("Enter Sector: ");
            int campus = readInt("Enter Campus No: ");

            School sch(id, name, sector, campus);
            ES.addSchool(sch);

            cout << "School added successfully!\n";
        }
        else if (choice == 2)
        {
            // ADD DEPARTMENT
            string schoolID = readLine("Enter School ID: ");
            string deptID = readLine("Enter Department ID: ");
            string deptName = readLine("Enter Department Name: ");

            Department dp;
            dp.deptID = deptID;
            dp.deptName = deptName;

            if (ES.addDepartment(schoolID, dp))
                cout << "Department added!\n";
            else
                cout << "School not found!\n";
        }
        else if (choice == 3)
        {
            // ADD CLASS
            string schoolID = readLine("Enter School ID: ");
            string deptID = readLine("Enter Department ID: ");
            string classID = readLine("Enter Class ID: ");
            string className = readLine("Enter Class Name: ");

            Class cls;
            cls.classID = classID;
            cls.className = className;

            if (ES.addClass(schoolID, deptID, cls))
                cout << "Class added!\n";
            else
                cout << "School/Department not found!\n";
        }
        else if (choice == 4)
        {
            // ADD STUDENT
            string schoolID = readLine("Enter School ID: ");
            string deptID = readLine("Enter Department ID: ");
            string classID = readLine("Enter Class ID: ");
            string studentID = readLine("Enter Student ID: ");
            string studentName = readLine("Enter Student Name: ");
            int age = readInt("Enter Age: ");

            Student st(studentID, studentName, age);

            if (ES.addStudent(st, schoolID, deptID, classID))
                cout << "Student added!\n";
            else
                cout << "Error: Could not add student.\n";
        }
        else if (choice == 5)
        {
            // ADD FACULTY
            string schoolID = readLine("Enter School ID: ");
            string facID = readLine("Enter Faculty ID: ");
            string name = readLine("Enter Faculty Name: ");
            string spec = readLine("Enter Specialization: ");

            Faculty f(facID, name, spec);

            if (ES.addFaculty(schoolID, f))
                cout << "Faculty added!\n";
            else
                cout << "Could not add faculty.\n";
        }
        else if (choice == 6)
        {
            // SHOW TOP SCHOOL BY RATING
            School* max = ES.getMaxRatedSchool();
            if (max)
            {
                cout << "\n===== TOP RATED SCHOOL =====\n";
                cout << "ID: " << max->schoolID << endl;
                cout << "Name: " << max->schoolName << endl;
                cout << "Rating: " << max->rating << endl;
            }
            else
            {
                cout << "No schools in the system yet.\n";
            }
        }
        else if (choice == 7)
        {
            ES.display();
        }
        else if (choice == 0)
        {
            cout << "Exiting system… Goodbye!\n";
        }
        else
        {
            cout << "Invalid option, try again.\n";
        }

    } while (choice != 0);

    return 0;
}