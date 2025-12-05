#include "../utils/Nodes.h"
#include "Mall.h"
#ifndef COMMERCIALSYSTEM_H
#define COMMERCIALSYSTEM_H
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class CommercialSystem
{
private:
    Mall** mallsTable;
    int mallCount;
    int mallTableSize;

public:

	CommercialSystem() {
		mallCount = 0;
		mallTableSize = 100;
		mallsTable = new Mall * [mallTableSize]();
		for (int i = 0; i < mallTableSize; i++) {
			mallsTable[i] = nullptr;
		}
	}
	void resizeMallMap() 
	{
		int newSize = mallTableSize * 2;
		Mall** newTable = new Mall * [newSize]();
		for (int i = 0; i < newSize; i++) {
			newTable[i] = nullptr;
		}
		for (int i = 0; i < mallTableSize; i++) {
			Mall* current = mallsTable[i];
			while (current != nullptr) {
				Mall* nextMall = current->nextMall;
				int index = Polynomial_Rolling_Hash_V1(current->getMallName()) % newSize;
				if (newTable[index]) {
					current->nextMall = newTable[index];
					newTable[index] = current;
				}
				else {
					current->nextMall = nullptr;
					newTable[index] = current;
				}
				current = nextMall;
			}
		}
		delete[] mallsTable;
		mallsTable = newTable;
		mallTableSize = newSize;
	}
    bool addMall(Mall& m1)
    {
        Mall* toAdd = new Mall(m1);
        int index = Polynomial_Rolling_Hash_V1(toAdd->getMallName());
        index = index % mallTableSize;
        if (mallsTable[index])
        {
            toAdd->nextMall = mallsTable[index];
            mallsTable[index] = toAdd;
            return true;
        }
        else
        {
            mallsTable[index] = toAdd;
            mallCount++;
            return true;
        }
        return false;
    }

    void deleteMall(string& mallName) {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        if (mallsTable[index] == nullptr) return;

        Mall* current = mallsTable[index];
        Mall* previous = nullptr;

        while (current != nullptr) {
            if (current->getMallName() == mallName) {
                if (previous == nullptr) {
                    mallsTable[index] = current->nextMall;
                }
                else {
                    previous->nextMall = current->nextMall;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
    }

    bool addStoreToMall(string& mallName, Store& store)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr) {
            if (current->getMallName() == mallName) {
                current->addStore(store);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }

    bool addCategoryToStoreInMall(string mallName, string storeName, string categoryName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName) {
                current->addCategoryToStore(storeName, categoryName);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }

    bool removeStoreFromMall(string& mallName, string& storeName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr) {
            if (current->getMallName() == mallName) {
                current->removeStore(storeName);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }
    bool addProductToStore(string& mallName, string& storeName, string& categoryName, Product& product)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName) {
                current->addProductToStore(storeName, categoryName, product);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found.";
        return false;
    }
    bool removeProduct(string& mallName, string& storeName, string& categoryName, string& productName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName) {
                current->removeProductFromStore(storeName, categoryName, productName);
                return true;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }

    void findProductInStore(string& mallName, string& storeName, string& category, string& productName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName)
            {
                Product* prod = current->findProductInStore(storeName, category, productName);
                if (prod) {
                    cout << "Product found: ";
                    prod->displayProduct();
                }
                else {
                    cout << "Product not found in the specified store and category." << endl;
                }
                return;
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
    }

    void displayProductsInMallFromStore(string mallName, string storeName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName)
            {
                current->displayProductsInStore(storeName);
                return;
            }
            current = current->nextMall;
        }
        cout << "Mall not found." << endl;
        return;
    }

    void displayAllProductsInCategoryFromStore(string& mallName, string& storeName, string& category)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;

        Mall* current = mallsTable[index];
        while (current != nullptr)
        {
            if (current->getMallName() == mallName)
            {
                current->displayProductsInStoreFromCategory(storeName, category);
                return;
            }
            current = current->nextMall;
        }
        cout << "Mall not found." << endl;
        return;
    }

    bool buyProduct(string& mallName, string& storeName, string& category, string& productName)
    {
        int index = Polynomial_Rolling_Hash_V1(mallName);
        index = index % mallTableSize;
        Mall* current = mallsTable[index];
        while (current != nullptr) {
            if (current->getMallName() == mallName) {
                bool success = current->buyProductFromStore(storeName, category, productName);
                if (success)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            current = current->nextMall;
        }
        cout << "\nMall not found." << endl;
        return false;
    }
};
#endif // !COMMERCIALSYSTEM_H
