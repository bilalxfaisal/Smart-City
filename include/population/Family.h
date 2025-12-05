#ifndef FAMILY_H
#define FAMILY_H

#include "../utils/Nodes.h"
#include "../population/Citizen.h"

using std::cout;
using std::cin;
using std::string;

class Family
{
private:
    Citizen* familyHead;  // Always the oldest person (max-heap root)

    // Add a child to a parent (append to sibling list)
    void addChild(Citizen* parent, Citizen* child)
    {
        if (parent->firstChild == nullptr)
        {
            parent->firstChild = child;
            return;
        }

        Citizen* current = parent->firstChild;
        while (current->nextSibling != nullptr)
            current = current->nextSibling;

        current->nextSibling = child;
    }
public:

    Family(Citizen* head = nullptr)
    {
        familyHead = head;
    }

    Citizen* getHead()
    {
        return familyHead;
    }


    void insertMember(Citizen* newMember)
    {
        if (newMember == nullptr) return;

        // Case 1: Empty family
        if (familyHead == nullptr)
        {
            familyHead = newMember;
            return;
        }

        if (newMember->getAge() > familyHead->getAge())
        {
            newMember->firstChild = familyHead;
            newMember->nextSibling = nullptr;

            familyHead = newMember;
            return;
        }

        // Case 3: Normal insertion under the existing root
        addChild(familyHead, newMember);
    }




    void printFamily(Citizen* node, int depth = 0)
    {
        if (!node) return;

        for (int i = 0; i < depth; i++)
            cout << "  ";

        cout << node->getName() << " (" << node->getAge() << ")" << endl;

        printFamily(node->firstChild, depth + 1);
        printFamily(node->nextSibling, depth);
    }


    void removeMember(Citizen* parent, Citizen* target)
    {
        if (target == nullptr) return;

        // Removing ROOT — you *cannot* magically pick a new oldest
        if (parent == nullptr)
        {
            familyHead = nullptr;
            return;
        }

        // Removing the FIRST CHILD
        if (parent->firstChild == target)
        {
            parent->firstChild = target->nextSibling;
            target->nextSibling = nullptr;
            return;
        }

        // Removing a sibling in the list
        Citizen* current = parent->firstChild;

        while (current != nullptr && current->nextSibling != nullptr)
        {
            if (current->nextSibling == target)
            {
                current->nextSibling = target->nextSibling;
                target->nextSibling = nullptr;
                return;
            }
            current = current->nextSibling;
        }
    }
};

#endif // FAMILY_H


//Address based hashing 
//House family insertion based on age
//Add citizen(Inside system) ; parse csv file for address-> hashing -> exists or not if yes house->family->insert
//When insering a citizen if house doesn't exists, make a house obj by parsing citizen object's address for house variables
