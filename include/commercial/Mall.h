#include<iostream>
#include "../utils/Nodes.h"
#include "StoresHashTable.h"
#include "Store.h"
#ifndef MALL_H
#define MALL_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Commercial entities

class Mall
{
	int mallID;
	string mallName;
	Location location;
	int storeCount;
	Store** storesTable;
	int storeTableSize;

public:
	Mall* nextMall;
	// constructor
	Mall(int id = 0, string name = "", Location loc = { 0,0 }, int storesNum = 10)
	{
		mallID = id;
		mallName = name;
		location = loc;
		nextMall = nullptr;
		storeTableSize = storesNum;
		storesTable = new Store * [storesNum](); // initializes to nullptr
		Product** productsTable;
		int productTableSize;
		int ProductCap;
	}
	// copy constructor
	/*Mall(Mall& mall)
	{
		mallID = mall.mallID;
		mallName = mall.mallName;
		location.x = mall.location.x;
		location.y = mall.location.y;
	}*/
	int getMallID() const { return mallID; }
	string getMallName() const { return mallName; }
	Location getLocation() const { return location; }
	int getStoreCount() const { return storeCount; }
<<<<<<< Updated upstream
	void resizeStoreMap()
	{
		int newSize = storeTableSize * 2;
		Store** newTable = new Store * [newSize]();
		for (int i = 0; i < newSize; i++) {
			newTable[i] = nullptr;
		}
		for (int i = 0; i < storeTableSize; i++) {
			Store* current = storesTable[i];
			while (current != nullptr) {
				Store* nextStore = current->nextStore;
				int index = Polynomial_Rolling_Hash_V1(current->getStoreName()) % newSize;
				if (newTable[index]) {
					current->nextStore = newTable[index];
					newTable[index] = current;
				}
				else {
					current->nextStore = nullptr;
					newTable[index] = current;
				}
				current = nextStore;
			}
		}
		delete[] storesTable;
		storesTable = newTable;
		storeTableSize = newSize;
	}
=======

>>>>>>> Stashed changes
	void addStore(Store& store)
	{
		if (storeCount >= storeTableSize)
		{
			resizeStoreMap();
		}
		Store* toAdd = new Store(store);
		int index = Polynomial_Rolling_Hash_V1(store.getStoreName());
		index = index % storeTableSize;

		if (storesTable[index] == nullptr)
			storesTable[index] = toAdd;
		else
		{
			Store* curr = storesTable[index];
			while (curr->nextStore) { curr = curr->nextStore; }
			curr->nextStore = toAdd;
		}
	}
	Store* findStoreByName(string name)
	{
		int index = Polynomial_Rolling_Hash_V1(name);
		index = index % storeTableSize;

		if (storesTable[index] == nullptr) return nullptr;
		else
			return storesTable[index];
	}

	Product* findProductInStore(string storeName, string catName, string productName)
	{
		Store* store = findStoreByName(storeName);
		if (store != nullptr)
		{
			return store->findProductByName(productName, catName);
		}
		cout << "\nNo store of name " << storeName << " exists !";
		return nullptr; // Store not found
	}

	bool addProductToStore(string storeName, string catName, Product& product)
	{
		Store* store = findStoreByName(storeName);

		if (store == nullptr)
		{
			cout << "\nNo store of name " << storeName << " exists !";
			return false;
		}
		return store->addProduct(catName, product);
	}
	bool addCategoryToStore(string storeName, string catName)
	{
		Store* store = findStoreByName(storeName);
		if (store == nullptr)
		{
			cout << "\nNo store of name " << storeName << " exists !";
			return false;
		}
		return store->addCategory(catName);
	}

	//Product* findProductInMall(string productName)
	//{
	//	for (int i = 0; i < storeTableSize; i++)
	//	{
	//		Store* store = storesTable[i];
	//		while (store != nullptr)
	//		{
	//			Product* product = store->findProductByName(productName);
	//			if (product != nullptr)
	//			{
	//				return product; // Product found
	//			}
	//			store = store->nextStore;
	//		}
	//	}
	//	return nullptr; // Product not found in any store
	//}

	bool removeProductFromStore(string storeName, string catName, string productName)
	{
		Store* store = findStoreByName(storeName);
		if (store != nullptr)
		{
			return store->removeProductByName(productName, catName);
		}
		cout << "\nNo store of name " << storeName << " exists !";
		return false;
	}
	bool removeStore(string name)
	{
		int index = Polynomial_Rolling_Hash_V1(name);
		index = index % storeTableSize;

		if (storesTable[index] == nullptr) 
		{
			return false;
		}
		else
		{
			Store* store = storesTable[index];
			if (store->getStoreName() == name)
			{
				storesTable[index] = store->nextStore;
				delete store;
				cout << "\nStore of name (" << name << ") removed successfully.";
				return true;
			}
		}
	}

	bool buyProductFromStore(string storeName, string catName, string productName)
	{
		Store* store = findStoreByName(storeName);
		if (store != nullptr)
		{
			return store->buyProduct(productName, catName);
		}
		return false;
	}

	bool removeAllProductsFromStore(string storeName, string catName, string productName)
	{
		Store* store = findStoreByName(storeName);
		if (store != nullptr)
		{
			return store->removeAllProductsOfName(productName, catName);
		}
		return false;
	}

	void displayProductsInStore(string storeName)
	{
		Store* store = findStoreByName(storeName);
		if (store != nullptr)
		{
			if (store->getStoreName() == storeName)
			{
				cout << "\nProducts in store (" << storeName << "):";
				store->displayAllProductsInStore();
				return;
			}
			store = store->nextStore;
		}
		else
		{
			cout << "\nNo store of name (" << storeName << ") exists.";
		}
	}
	void displayProductsInStoreFromCategory(string storeName, string catName)
	{
		Store* store = findStoreByName(storeName);
		if (store != nullptr)
		{
			if (store->getStoreName() == storeName)
			{
				cout << "\nProducts in store (" << storeName << ") in category (" << catName << "):";
				store->displayProductsInCategory(catName);
				return;
			}
			store = store->nextStore;
		}
		else
		{
			cout << "\nNo store of name (" << storeName << ") exists.";
		}
	}


};

#endif