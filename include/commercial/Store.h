#pragma once
#include <iostream>
#include "../utils/Nodes.h"
#include "Store.h"
#include "Product.h"

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
	int CatTableSize;
	int CatTableCount;
	int productsTableSize = 10;


public:
	Store* nextStore;
	Store(int id = 0, string name = "", string mall_id = "")
	{
		storeID = id;
		storeName = name;
		mallID = mall_id;

		CategoriesTable = new Category * [10](); // initializes to nullptr
		CatTableCount = 10;
		CatTableSize = 10;
		nextStore = nullptr;
	}
	Store(Store& store)
	{
		storeID = store.storeID;
		storeName = store.storeName;
		mallID = store.mallID;
		CategoriesTable = store.CategoriesTable;
		CatTableSize = store.CatTableSize;

	}
	int getStoreID() const { return storeID; }
	string getStoreName() const { return storeName; }
	string getMallID() const { return mallID; }
	void resizeCategoryMap()
	{
		int newSize = CatTableSize * 2;
		Category** newTable = new Category * [newSize]();
		for (int i = 0; i < newSize; i++) {
			newTable[i] = nullptr;
		}
		for (int i = 0; i < CatTableSize; i++) {
			Category* current = CategoriesTable[i];
			while (current != nullptr) {
				Category* nextCat = current->nextCategory;
				int index = Polynomial_Rolling_Hash_V1(current->getCategoryName()) % newSize;
				if (newTable[index]) {
					current->nextCategory = newTable[index];
					newTable[index] = current;
				}
				else {
					current->nextCategory = nullptr;
					newTable[index] = current;
				}
				current = nextCat;
			}
		}
		delete[] CategoriesTable;
		CategoriesTable = newTable;
		CatTableSize = newSize;
	}
	bool addProduct(string categoryName, Product& product)
	{
		if (CatTableCount >= CatTableSize)
		{
			resizeCategoryMap();
		}
		Product* toAdd = new Product(product);

		int index = Polynomial_Rolling_Hash_V1(categoryName);
		index = index % CatTableSize;

		if (CategoriesTable[index] == nullptr)
		{
			CategoriesTable[index] = new Category(categoryName);
		}

		CategoriesTable[index]->addProductToCategory(product);
		return true;
	}
	bool addCategory(string categoryName)
	{
		int index = Polynomial_Rolling_Hash_V1(categoryName);
		index = index % CatTableSize;
		if (CategoriesTable[index] == nullptr)
		{
			CategoriesTable[index] = new Category(categoryName);
			return true;
		}
		else
		{
			Category* curr = CategoriesTable[index];
			while (curr->nextCategory) 
			{ 
				if (curr->getCategoryName() == categoryName) 
					return false; // cant be more than one category with same name
				curr = curr->nextCategory; 
			}
			curr->nextCategory = new Category(categoryName);
			return true;
		}
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

	bool buyProduct(string productName, string categoryName)
	{
		int index = Polynomial_Rolling_Hash_V1(categoryName);
		index = index % CatTableSize;
		if (CategoriesTable[index] == nullptr)
		{
			cout << "\nNo product of name (" << productName << ") exists";
			return false;
		}
		else
		{
			Category* category = CategoriesTable[index];
			if (category != nullptr)
			{
				return category->buyProduct(productName);
			}
		}
	}
	bool removeProductByName(string name, string categoryName)
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
				return category->removeProductByName(name);
			}
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

	Category* findCategory(string name)
	{
		int index = Polynomial_Rolling_Hash_V1(name);
		index = index % CatTableSize;

		Category* category = CategoriesTable[index];

		if (category == nullptr) return nullptr;
		else
		{
			while (category != nullptr)
			{
				if (category->getCategoryName() == name)
					return category;
				category = category->nextCategory;
			}
		}

	}

	void displayProductsInCategory(string categoryName)
	{
		Category* category = findCategory(categoryName);
		if (category == nullptr)
		{
			cout << "\nNo category of name (" << categoryName << ") exists in store (" << storeName << ").";
		}
		else
		{
			if (category->getCategoryName() == categoryName)
			{
				cout << "\nAll products in category (" << categoryName << ") :\n";
				category->displayProducts();
				return;
			}
			category = category->nextCategory;
		}
	}
	void displayAllProductsInStore()
	{
		for (int i = 0; i < CatTableSize; i++)
		{
			Category* category = CategoriesTable[i];

			while (category)
			{
				category->displayProducts();
				category = category->nextCategory;
			}
		}

	}

	void displayStore()
	{
		cout << "Store ID: " << storeID
			<< ", Name: " << storeName
			<< ", Mall ID: " << mallID
			<< ", Categories: " << CatTableCount << endl;

		for (int i = 0; i < CatTableSize; i++) {
			Category* category = CategoriesTable[i];
			while (category != nullptr) {
				cout << "  Category: " << category->getCategoryName() << endl;

				for (int i = 0; i < category->productsTableSizeCat; i++)
				{
					Product* product = category->productsTable[i];
					while (product != nullptr)
					{
						product->displayProduct();
						product = product->next; // Assuming linked list structure
					}
				}
				category = category->nextCategory; // Move to next category
			}
		}
	}


};

#endif