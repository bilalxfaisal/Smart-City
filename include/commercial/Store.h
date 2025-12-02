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
	Store(Store& store)
	{
		storeID = store.storeID;
		storeName = store.storeName;
		mallID = store.mallID;
		productsTabble = store.productsTable;
		storeCount = store.storeCount;
	}
	int getStoreID() const { return storeID; }
	int getStoreName() const { return storeName; }
	int getMallID() const { return mallID; }

	void addProduct(Product& product)
	{
		Product* toAdd = new Product(product);

		int index = Polynomial_Rolling_Hash_V1(product.productName);
		index = index % productsTableSize;

		if (productsTable[index] == nullptr)
			productsTable[index] = toAdd;
		else
		{
			toAdd->next = productsTable[index];
			productsTable[index] = toAdd;
		}
	}
	Product* findProductByName(string name)
	{
		int index = Polynomial_Rolling_Hash_V1(name);
		index = index % productsTableSize;

		if (productsTable[index] == nullptr) return nullptr;
		else
			return productsTable[index];
	}

	bool removeAllProductsOfName(string name)
	{
		int index = Polynomial_Rolling_Hash_V1(name);
		index = index % productsTableSize;

		if (productsTable[index] == nullptr)
		{
			cout << "\nNo product of name (" << name << ") exists";
			return false;
		}
		else
		{
			productsTable[index] = nullptr;
			return true;
		}
	}
	bool removeProduct(string name)
	{
		int index = Polynomial_Rolling_Hash_V1(name);
		index = index % productsTableSize;

		if (productsTable[index] == nullptr)
		{
			cout << "\nNo product of name (" << name << ") exists";
			return false;
		}
		else
		{
			Product* product = productsTable[index];
			if (product->getProductName() == name)
			{
				productsTable[index] = product->next;
				delete product;
				cout << "\nProduct of name (" << name << ") removed successfully.";
				return true;
			}
		}
	}
};

#endif