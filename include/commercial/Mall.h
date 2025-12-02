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
	Mall* nextMall;
	int storeCount;
	StoresHashTable** storesTable;

public:
	Mall(int id = 0, string name = "", Location loc = { 0,0 }, int storesNum = 0)
	{
		mallID = id;
		mallName = name;
		location = loc;
		nextMall = nullptr;
		storeCount = 0;
		storesTable = new Store * [storesNum](); // initializes to nullptr
		firstStore = nullptr;
	}
	int getMallID() const { return mallID; }
	string getMallName() const { return mallName; }
	Location getLocation() const { return location; }
	int getStoreCount() const { return storeCount; }
	
};

#endif