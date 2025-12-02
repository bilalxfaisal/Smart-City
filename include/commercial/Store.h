#pragma once
#include <iostream>
#include "../utils/Nodes.h"
#include "Store.h"
#include "Product.h"
#include "ProductHashTable.h"
#ifndef STORE_H
#define STORE_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Store
{
	int storeID;
	string storeName;
	string mallID;
	ProductHashTable** productsTable;
	int productCount;
	Store* nextStore;
	
public:
	Store(int id = 0, string name = "", string mall_id = "", int productsNum = 0)
	{
		storeID = id;
		storeName = name;
		mallID = mall_id;
		productsTable = nullptr;
		productsTable = new Product * [productsNum](); // initializes to nullptr
		productCount = 0;
		nextStore = nullptr;
	}
	int getStoreID() const { return storeID; }
	int getStoreName() const { return storeName; }
	int getMallID() const { return mallID; }

};

#endif