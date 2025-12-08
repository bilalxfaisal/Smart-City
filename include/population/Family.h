#ifndef FAMILY_H
#define FAMILY_H

#include "../population/Citizen.h"
#include <string>
using std::string;
using std::cout;

class Family
{
private:
    Citizen* familyHead = nullptr;

    void addChild(Citizen* parent, Citizen* child)
    {
        if (!parent || !child) return;
        child->nextSibling = nullptr;
        if (parent->firstChild == nullptr)
        {
            parent->firstChild = child;
            return;
        }
        Citizen* cur = parent->firstChild;
        while (cur->nextSibling)
            cur = cur->nextSibling;
        cur->nextSibling = child;
    }



    bool searchRec(Citizen* node, const string& cnic) const
    {
        if (!node) return false;
        if (node->getCNIC() == cnic) return true;
        if (searchRec(node->firstChild, cnic)) return true;
        return searchRec(node->nextSibling, cnic);
    }

public:
    Family() {}
    Citizen* getCitizenHead()  const
    {
        return familyHead;
    }
    void insertMember(Citizen& c)
    {
        Citizen* n = &c;
        n->firstChild = nullptr;
        n->nextSibling = nullptr;

        if (!familyHead)
        {
            familyHead = n;
            return;
        }

        if (n->getAge() > familyHead->getAge())
        {
            n->firstChild = familyHead;
            familyHead = n;
            return;
        }

        addChild(familyHead, n);
    }

    bool containsCitizen(const string& cnic) const
    {
        return searchRec(familyHead, cnic);
    }
    void display() const {
        cout << "Family Members:" << endl;
        if (familyHead) {
            printRec(familyHead, 0);
        }
        else {
            cout << "No family members." << endl;
        }
    }

    void printRec(Citizen* node, int depth) const {
        if (!node) return;

        // Print current citizen
        for (int i = 0; i < depth; i++) cout << "  "; // Indent based on depth
        node->displayCitizenInfo();

        // Print children (if any)
        if (node->firstChild) {
            printRec(node->firstChild, depth + 1);
        }

        // Print siblings
        if (node->nextSibling) {
            printRec(node->nextSibling, depth);
        }
    }
    int RecCalculation(Citizen* node)
    {
        if (node == nullptr) 
        {
            return 0;
        }
        return 1 + RecCalculation(node->firstChild) + RecCalculation(node->nextSibling);
    }
    int calculateMemberNum() 
    {
        return RecCalculation(familyHead);
    }
};

#endif
