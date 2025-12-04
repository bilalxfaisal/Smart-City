#include "../utils/Nodes.h"
#include "Mall.h"
#ifndef COMMERCIALSYSTEM_H
#define	COMMERCIALSYSTEM_H
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

	void addMall(Mall& m1) {
		Mall* toAdd = new Mall(m1);
		int index = Polynomial_Rolling_Hash_V1(toAdd->getMallName());
		index = index % mallTableSize;
		if (mallsTable[index]) {
			// chaining
			toAdd->nextMall = mallsTable[index];
			mallsTable[index] = toAdd;
		}
		else {
			mallsTable[index] = toAdd;
			mallCount++;
		}
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
	}
	void addStoreToMall(string& mallName, Store& store) {
		int index = Polynomial_Rolling_Hash_V1(mallName);
		index = index % mallTableSize;

		Mall* current = mallsTable[index];
		while (current != nullptr) {
			if (current->getMallName() == mallName) {
				current->addStore(store);
				return;
			}
			current = current->nextMall;
		}
	}

	void removeStoreFromMall(string& mallName, string& storeName) {
		int index = Polynomial_Rolling_Hash_V1(mallName);
		index = index % mallTableSize;
		Mall* current = mallsTable[index];
		while (current != nullptr) {
			if (current->getMallName() == mallName) {
				current->removeStore(storeName);
				return;
			}
			current = current->nextMall;
		}
	}

	void addProductToStore(string& mallName, string& storeName, string& categoryName,  Product& product) {
		int index = Polynomial_Rolling_Hash_V1(mallName);
		index = index % mallTableSize;

		Mall* current = mallsTable[index];
		while (current != nullptr) {
			if (current->getMallName() == mallName) {
				current->addProductToStore(storeName, categoryName, product);
				return;
			}
			current = current->nextMall;
		}
	}

	void removeProduct(string& mallName, string& storeName, string& categoryName, string& productName) {
		int index = Polynomial_Rolling_Hash_V1(mallName);
		index = index % mallTableSize;
		Mall* current = mallsTable[index];
		while (current != nullptr) {
			if (current->getMallName() == mallName) {
				current->removeAllProductsFromStore(storeName, categoryName, productName);
				return;
			}
			current = current->nextMall;
		}
	}

	void findProductInStore(string& mallName, string& storeName, string& category, string& productName) {
		int index = Polynomial_Rolling_Hash_V1(mallName);
		index = index % mallTableSize;
		Mall* current = mallsTable[index];
		while (current != nullptr) {
			if (current->getMallName() == mallName) {
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
	}

	void buyProduct(string& mallName, string& storeName, string& category, string& productName) {
		int index = Polynomial_Rolling_Hash_V1(mallName);
		index = index % mallTableSize;
		Mall* current = mallsTable[index];
		while (current != nullptr) {
			if (current->getMallName() == mallName) {
				bool success = current->buyProductFromStore(storeName, category, productName);
				if (success) {
					cout << "Product purchased successfully." << endl;
					//cout << 
				}
				else {
					cout << "Failed to purchase product. It may be out of stock or not found." << endl;
				}
				return;
			}
			current = current->nextMall;
		}
	}
};
#endif // !COMMERCIALSYSTEM_H