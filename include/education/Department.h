#include "../utils/Nodes.h"
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
};


#endif // !DEPARTMENT_H