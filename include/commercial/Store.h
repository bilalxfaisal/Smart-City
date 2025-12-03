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
	Category** CategoriesTable;
	int CatTableSize = 0;
	int CatTableCount = 0;
	int productsTableSize = 10;


public:
	Store* nextStore;
	Store(int id = 0, string name = "", string mall_id = "", int catNum = 10)
	{
		storeID = id;
		storeName = name;
		mallID = mall_id;

		CategoriesTable = new Category * [catNum](); // initializes to nullptr
		CatTableCount = 0;
		CatTableSize = catNum;
		nextStore = nullptr;
	}
	Store(Store& store)
	{
		storeID = store.storeID;
		storeName = store.storeName;
		mallID = store.mallID;
		CategoriesTable = store.CategoriesTable;

	}
	int getStoreID() const { return storeID; }
	string getStoreName() const { return storeName; }
	string getMallID() const { return mallID; }

	void addProduct(string categoryName, Product& product)
	{
		Product* toAdd = new Product(product);

		int index = Polynomial_Rolling_Hash_V1(categoryName);
		index = index % CatTableSize;

		if (CategoriesTable[index] == nullptr)
		{
			CategoriesTable[index] = new Category(categoryName);
		}

		CategoriesTable[index]->addProductToCategory(product);
	}
	Product* findProductByName(string name, string categoryName)
	{
		int index = Polynomial_Rolling_Hash_V1(categoryName);
		index = index % CatTableSize;
		if (CategoriesTable[index] == nullptr) return nullptr;
		else
		{
			return CategoriesTable[index]->findProductByName(name);
		}
	}

	bool removeAllProductsOfName(string name, string categoryName)
	{
		int index = Polynomial_Rolling_Hash_V1(categoryName);
		index = index % CatTableSize;

		if (CategoriesTable[index] == nullptr)
		{
			cout << "\nNo product of name (" << name << ") exists";
			return false;
		}
		else
		{
			Category* category = CategoriesTable[index];
			if (category != nullptr)
			{
				category->removeAllProductsByName(name);
			}
		}
	}

};

#endif