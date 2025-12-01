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
	string storeID;
	string storeName;
	string mallID;
	ProductHashTable** productsTable;
	int productCount;
	Store* nextStore;
	
public:
	Store(string id = "", string name = "", string mall_id = "", int productsNum = 0)
	{
		storeID = id;
		storeName = name;
		mallID = mall_id;
		productsTable = nullptr;
		productsTable = new Product * [productsNum](); // initializes to nullptr
		productCount = 0;
		nextStore = nullptr;
	}
};

#endif