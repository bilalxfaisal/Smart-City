#ifndef CITIZEN_H
#define CITIZEN_H

#include <iostream>
#include <string>
using namespace std;

class Citizen
{
private:
    int age;
    string name;
    string CNIC;
    string gender;
    string Occupation;
    string address;

public:
    //FOR TREE
    Citizen* nextSibling = nullptr;
    Citizen* firstChild = nullptr;

    //NEXT PTR FOR HASHTABLE
    Citizen* nextCitizen = nullptr;
    Citizen()
    {
        age = 0;
        name = "";
        CNIC = "";
        gender = "";
        Occupation = "";
        address = "";
    }

    Citizen(string cn, string n, int ag, string sec, int sn, int hn, string occ)
    {
        CNIC = cn;
        name = n;
        age = ag;
    
        address = sec + " " + to_string(sn) + " " + to_string(hn);
        Occupation = occ;
    }

    string getName() const
    {
        return name;
    }
    string getCNIC() const 
    {
        return CNIC;
    }
    int getAge() const
    {
        return age;
    }
    string  getOccupation() const 
    {
        return Occupation;
    }
    void displayCitizenInfo() const
    {
        cout << "Name: " << name << endl;
        cout << "CNIC: " << CNIC << endl;
        cout << "Age: " << age << endl;
    }

    void UpdateAge(int newAge)
    {
        age = newAge;
    }

    Citizen* get1stChild()
    {
        return firstChild;
    }

    Citizen* getSibling()
    {
        return nextSibling;
    }
};

#endif // CITIZEN_H
