#ifndef PHARMACY_H
#define PHARMACY_H
#include "../utils/Nodes.h"
#include "Medicine.h"

class Pharmacy
{
    string name;
    string location;
    string id;

    Medicine** medsFormulaBasedTable;
    Medicine** medsNameBasedTable;

    int currMedCount_Form = 0;
    int medTableSize_Form;

    int currMedCount_Name = 0;
    int medTableSize_Name;

public:
    Pharmacy* nextPharmacy = nullptr;

    Pharmacy(string n, string loc, string i)
        : name(n), location(loc), id(i)
    {
        medTableSize_Form = 101;
        medTableSize_Name = 101;

        medsFormulaBasedTable = new Medicine * [medTableSize_Form]();
        medsNameBasedTable = new Medicine * [medTableSize_Name]();
    }

    ~Pharmacy() {
        delete[] medsFormulaBasedTable;
        delete[] medsNameBasedTable;
    }

    void resizeMedsFormulaTable()
    {
        int newSize = medTableSize_Form * 2 + 1;
        Medicine** newTable = new Medicine * [newSize]();

        for (int i = 0; i < medTableSize_Form; i++) {
            Medicine* curr = medsFormulaBasedTable[i];
            while (curr) {
                Medicine* next = curr->nextMedicine;

                int idx = Polynomial_Rolling_Hash_V2(curr->getFormulation()) % newSize;
                curr->nextMedicine = newTable[idx];
                newTable[idx] = curr;

                curr = next;
            }
        }

        delete[] medsFormulaBasedTable;
        medsFormulaBasedTable = newTable;
        medTableSize_Form = newSize;
    }

    void resizeMedsTable()
    {
        int newSize = medTableSize_Name * 2 + 1;
        Medicine** newTable = new Medicine * [newSize]();

        for (int i = 0; i < medTableSize_Name; i++) {
            Medicine* curr = medsNameBasedTable[i];
            while (curr) {
                Medicine* next = curr->nextMedicine;

                int idx = Polynomial_Rolling_Hash_V2(curr->getName()) % newSize;
                curr->nextMedicine = newTable[idx];
                newTable[idx] = curr;

                curr = next;
            }
        }

        delete[] medsNameBasedTable;
        medsNameBasedTable = newTable;
        medTableSize_Name = newSize;
    }

    void addMedicine(const Medicine& med)
    {
        if (currMedCount_Form>= medTableSize_Form)
            resizeMedsFormulaTable();

        if (currMedCount_Name >= medTableSize_Name)
            resizeMedsTable();

        Medicine* medForm = new Medicine(med);
        Medicine* medName = new Medicine(med);

        int indexForm = Polynomial_Rolling_Hash_V2(med.getFormulation()) % medTableSize_Form;
        medForm->nextMedicine = medsFormulaBasedTable[indexForm];
        medsFormulaBasedTable[indexForm] = medForm;
        currMedCount_Form++;

        int indexName = Polynomial_Rolling_Hash_V2(med.getName()) % medTableSize_Name;
        medName->nextMedicine = medsNameBasedTable[indexName];
        medsNameBasedTable[indexName] = medName;
        currMedCount_Name++;
    }

    void searchMedByFormula(const string& formula)
    {
        int index = Polynomial_Rolling_Hash_V2(formula) % medTableSize_Form;

        Medicine* current = medsFormulaBasedTable[index];
        while (current) {
            if (current->getFormulation() == formula) {
                current->DisplayInfo();
                return;
            }
            current = current->nextMedicine;
        }

        cout << "No medicine found with formulation: " << formula << endl;
    }

    void searchMedByName(const string& name)
    {
        int index = Polynomial_Rolling_Hash_V2(name) % medTableSize_Name;

        Medicine* current = medsNameBasedTable[index];
        while (current) {
            if (current->getName() == name) {
                current->DisplayInfo();
                return;
            }
            current = current->nextMedicine;
        }

        cout << "No medicine found with name: " << name << endl;
    }

    bool removeMedicineByName(const string& name)
    {
        int index = Polynomial_Rolling_Hash_V2(name) % medTableSize_Name;
        Medicine* current = medsNameBasedTable[index];
        Medicine* prev = nullptr;

        while (current) {
            if (current->getName() == name) {
                if (prev == nullptr)
                    medsNameBasedTable[index] = current->nextMedicine;
                else
                    prev->nextMedicine = current->nextMedicine;

                delete current;
                currMedCount_Name--;
                return true;
            }
            prev = current;
            current = current->nextMedicine;
        }

        return false;
    }

    bool removeMedicineByFormula(const string& formula)
    {
        int index = Polynomial_Rolling_Hash_V2(formula) % medTableSize_Form;
        Medicine* current = medsFormulaBasedTable[index];
        Medicine* prev = nullptr;

        while (current) {
            if (current->getFormulation() == formula) {
                if (prev == nullptr)
                    medsFormulaBasedTable[index] = current->nextMedicine;
                else
                    prev->nextMedicine = current->nextMedicine;

                delete current;
                currMedCount_Form--;
                return true;
            }
            prev = current;
            current = current->nextMedicine;
        }

        return false;
    }

    string getName()
    {
        return name;
    }
};

#endif
