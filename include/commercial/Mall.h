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
	Mall(int id = 0, string name = "", Location loc = { 0,0 }, int storesNum = 0)
	{
		mallID = id;
		mallName = name;
		location = loc;
		nextMall = nullptr;
		storeCount = 0;
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
	
	void addStore(Store& store)
	{
		Store* toAdd = new Store(store);
		int index = Polynomial_Rolling_Hash_V1(store.getStoreName());
		index = index % storeTableSize;

		if (storesTable[index] == nullptr)
			storesTable[index] = toAdd;
		else
		{
			toAdd->nextStore = storesTable[index];
			storesTable[index] = toAdd;
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

	Product* findProductInStore(string storeName, string productName)
	{
		Store* store = findStoreByName(storeName);
		if (store != nullptr)
		{
			return store->findProductByName(productName);
		}
		return nullptr; // Store not found
	}

	Product* findProductInMall(string productName)
	{
		for (int i = 0; i < storeTableSize; i++)
		{
			Store* store = storesTable[i];
			while (store != nullptr)
			{
				Product* product = store->findProductByName(productName);
				if (product != nullptr)
				{
					return product; // Product found
				}
				store = store->nextStore;
			}
		}
		return nullptr; // Product not found in any store
	}

	bool removeStore(string name)
	{
		int index = Polynomial_Rolling_Hash_V1(name);
		index = index % storeTableSize;

		if (storesTable[index] == nullptr) return false;
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

};

#endif