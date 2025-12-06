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

    void printRec(Citizen* node, int depth) const
    {
        if (!node) return;
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << node->getName() << " (" << node->getAge() << ")\n";
        printRec(node->firstChild, depth + 1);
        printRec(node->nextSibling, depth);
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
    void printFamily() const
    {
        printRec(familyHead, 3);
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
