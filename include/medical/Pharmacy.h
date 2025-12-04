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
	int currMedCount = 0;
	int medTableSize;
public:
	Pharmacy* nextPharmacy = nullptr; // For chaining in hash table
	Pharmacy(string n, string loc, string i) : name(n), location(loc), id(i)
	{
		medTableSize = 101;
		medsFormulaBasedTable = new Medicine*[medTableSize](); 
		medsNameBasedTable = new Medicine*[medTableSize]();
	}
	~Pharmacy() {
		delete[] medsFormulaBasedTable;
		delete[] medsNameBasedTable;
	}
	void addMedicine(const Medicine& med)
	{
		Medicine* new_med = new Medicine(med);
		// Add medicine to formula-based table
		int index = Polynomial_Rolling_Hash_V2(med.getFormulation()) % medTableSize;
		if (medsFormulaBasedTable[index] != nullptr)
		{

			new_med->nextMedicine = medsFormulaBasedTable[index];
			medsFormulaBasedTable[index] = new_med;
		}
		else
		{
			medsFormulaBasedTable[index] = new_med;
		}
		// Add medicine to name-based table
		index = Polynomial_Rolling_Hash_V2(med.getName()) % medTableSize;
		if (medsNameBasedTable[index] != nullptr)
		{
			new_med->nextMedicine = medsNameBasedTable[index];
			medsNameBasedTable[index] = new_med;
		}
		else
		{
			medsNameBasedTable[index] = new_med;
		}
		
	}
	void searchMedByFormula(const string& formula) 
	{
		int index = Polynomial_Rolling_Hash_V2(formula);
		index %= 101;
		if (medsFormulaBasedTable[index] == nullptr) 
		{
			cout << "No medicine found with formulation: " << formula << endl;
		}
		else
		{
			Medicine* current = medsFormulaBasedTable[index];
			while (current != nullptr) 
			{
				if (current->getFormulation() == formula)
				{
					current->DisplayInfo();
					return;
				}
				current = current->nextMedicine;
			}
			cout << "No medicine found with formulation: " << formula << endl;
		}

	}
	void searchMedByName(const string& name)
	{
		int index = Polynomial_Rolling_Hash_V2(name);
		index %= 101;
		if (medsNameBasedTable[index] == nullptr) 
		{
			cout << "No medicine found with name: " << name << endl;
		}
		else
		{
			Medicine* current = medsNameBasedTable[index];
			while (current != nullptr) 
			{
				if (current->getName() == name)
				{
					current->DisplayInfo();
					return;
				}
				current = current->nextMedicine;
			}
			cout << "No medicine found with name: " << name << endl;
		}
	}
	bool removeMedicineByName(const string& name) 
	{
		int index = Polynomial_Rolling_Hash_V2(name) % medTableSize;
		Medicine* current = medsNameBasedTable[index];
		Medicine* prev = nullptr;
		while (current != nullptr) 
		{
			if (current->getName() == name) 
			{
				if (prev == nullptr) 
				{
					medsNameBasedTable[index] = current->nextMedicine;
				}
				else 
				{
					prev->nextMedicine = current->nextMedicine;
				}
				delete current;
				return true;
			}
			prev = current;
			current = current->nextMedicine;
		}
		return false;
	}
	bool removeMedicineByFormula(const string& formula) 
	{
		int index = Polynomial_Rolling_Hash_V2(formula) % medTableSize;
		Medicine* current = medsFormulaBasedTable[index];
		Medicine* prev = nullptr;
		while (current != nullptr) 
		{
			if (current->getFormulation() == formula) 
			{
				if (prev == nullptr) 
				{
					medsFormulaBasedTable[index] = current->nextMedicine;
				}
				else 
				{
					prev->nextMedicine = current->nextMedicine;
				}
				delete current;
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
#endif // !PHARMACY_H
