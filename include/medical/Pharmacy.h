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
public:
	Pharmacy(string n, string loc, string i) : name(n), location(loc), id(i)
	{
		medsFormulaBasedTable = new Medicine*[101]; 
		medsNameBasedTable = new Medicine*[101];
	}
	~Pharmacy() {
		delete[] medsFormulaBasedTable;
		delete[] medsNameBasedTable;
	}
	void addMedicine(Medicine& med)
	{
		Medicine* new_med = new Medicine(med);
		// Add medicine to formula-based table
		int index = Polynomial_Rolling_Hash_V2(med.getFormulation()) % 101;
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
		index = Polynomial_Rolling_Hash_V2(med.getName()) % 101;
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
		void searchMedByFormula(string& formula) 
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
		void searchMedByName(string& name)
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


	}
};
#endif // !PHARMACY_H
