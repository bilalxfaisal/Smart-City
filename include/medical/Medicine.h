#ifndef  MEDICINE_H
#define MEDICINE_H
#include "../utils/Nodes.h"
class Medicine 
{
	string name;
	string formulation;
	int quantity;
	float price;
	public:
		//FOR HASHMAPS COLLISIONS
		Medicine* nextMedicine = nullptr;
		Medicine(string& nam, string& form, int q, float p) 
		{
			name = nam;
			formulation = form;
			quantity = q;
			price = p;

		}
		void updateStock(int num)
		{
			if (num > 0) 
			{
				quantity += num;
			}
		}
		bool buyMedicine(int quant)
		{
			if (quant <= quantity) 
			{
				quantity -= quant;
				return true;
			}
			else
			{
				cout << "Buy failed: Insufficient stock. Only " << quantity << " available." << endl;
				return false;
			}
		}
		string getName() const
		{
			return name;
		}
		string getFormulation() const
		{
			return formulation;
		}
		void DisplayInfo() 
		{
			cout << "Medicine Name: " << name << endl;
			cout << "Formulation: " << formulation << endl;
			cout << "Price: Rs:" << price << endl;
			cout << "Available Quantity: " << quantity << endl;
		}

	~Medicine() = default;
};
#endif // ! MEDICINE_H
