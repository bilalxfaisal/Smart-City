#include "../utils/Nodes.h"
#include <iostream>
#ifndef PRODUCT_H
#define PRODUCT_H

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Commercial entities

class Product
{
    bool soldOut;
    int productID;
    string productName;
    float price;
    int quantity = 0;
    

public:
    Product* next;
    // constructor
    Product(int id = 0, string name = "", float pr = 0.0f)
    {
        productID = id;
        productName = name;
        price = pr;
		soldOut = false;
        next = nullptr;
    }
    // copy constructor
    Product(Product& product)
    {
        productID = product.productID;
        productName = product.productName;
        price = product.price;
        soldOut = product.soldOut;
		next = nullptr;
    }
	bool isProductSoldOut() const { return soldOut; }
	int getProductID() const { return productID; }
	string getProductName() const { return productName; }
	float getPrice() const { return price; }
    void changePrice(float newPrice) { price = newPrice; }
    void displayProduct()
    {
        cout << "\nID: " << productID << " | Name: " << productName << " | Price: " << price;
    }
    void displayProduct() const
    {
        cout << "Product ID: " << productID << ", Name: " << productName << ", Price: " << price
            << ", Quantity: " << quantity
            << (soldOut ? " (Sold Out)" : "") << endl;
    }
    void addOneMore() { quantity++; if (quantity > 0) soldOut = false; }
	void addQuantity(int qty) { quantity += qty; if (quantity > 0) soldOut = false; }
    int getQuantity() { return quantity; }
    void removeOne() { if (quantity > 1) quantity--; }
};

class Category
{
    string categoryName;
	Product** productsTable;
    int productCountCat;
    int productsTableSizeCat;

public:
    Category* nextCategory;
    Category(string name = "", int productsNum = 10)
    {
        categoryName = name;
        nextCategory = nullptr;
    
        productsTable = new Product * [productsNum](); // initializes to nullptr
        productCountCat = 0;
        productsTableSizeCat = productsNum;
    }
	string getCategoryName() const { return categoryName; }
    void addProductToCategory(Product& product)
    {
        Product* toAdd = new Product(product);
        int index = Polynomial_Rolling_Hash_V1(product.getProductName());
        index = index % productsTableSizeCat;

        if (productsTable[index] == nullptr)
            productsTable[index] = toAdd;
        else
        {
            // same product comes again then increase it's quantity
            if (productsTable[index]->getProductName() == toAdd->getProductName())
            {
                productsTable[index]->addOneMore();
            }
            else
            {
                Product* curr = productsTable[index];
                while (curr->next) 
                { 
                    if (curr->getProductName() == toAdd->getProductName())
                    {
                        curr->addOneMore();
                        return;
                    }
                    curr = curr->next; 
                }
                curr->next = toAdd;
            }
        }
	}
    Product* findProductByName(string name)
    {
        int index = Polynomial_Rolling_Hash_V1(name);
        index = index % productsTableSizeCat;
        if (productsTable[index] == nullptr) return nullptr;
        else
        {
            Product* current = productsTable[index];
            while (current != nullptr)
            {
                if (current->getProductName() == name)
                    return current;
                current = current->next;
            }
        }
        return nullptr;
    }
    bool buyProduct(string productName)
    {
        int index = Polynomial_Rolling_Hash_V1(productName);
        index = index % productsTableSizeCat;

        if (productsTable[index] == nullptr)
        {
            cout << "\nNo product of name (" << productName << ") exists in category (" << categoryName << ").";
            return false;
        }
        Product* current = productsTable[index];
        Product* prev = nullptr;
        bool found = false;
        while (current != nullptr)
        {
            if (current->getProductName() == productName)
            {
                found = true;
                if (current->getQuantity() > 1)
                {
                    current->removeOne();
                    return true;
                }
                else 
                {
                    if (prev == nullptr)
                    {
                        productsTable[index] = current->next;
                        delete current;
                        current = productsTable[index];
                        return true;
                    }
                    else
                    {
                        prev->next = current->next;
                        delete current;
                        current = prev->next;
                        return true;
                    }
                }
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }
    bool removeProductByName(string productName)
    {
        int index = Polynomial_Rolling_Hash_V1(productName);
        index = index % productsTableSizeCat;
        if (productsTable[index] == nullptr)
        {
            cout << "\nNo product of name (" << productName << ") exists in category (" << categoryName << ").";
            return false;
        }
        Product* current = productsTable[index];
        Product* prev = nullptr;
        while (current != nullptr)
        {
            if (current->getProductName() == productName)
            {
                if (prev == nullptr)
                {
                    productsTable[index] = current->next;
                    delete current;
                    return true;
                }
                else
                {
                    prev->next = current->next;
                    delete current;
                    return true;
                }
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        cout << "\nNo product of name (" << productName << ") exists in category (" << categoryName << ").";
		return false;
    }
    bool removeAllProductsByName(string productName)
    {
        int index = Polynomial_Rolling_Hash_V1(productName);
        index = index % productsTableSizeCat;
        if (productsTable[index] == nullptr)
        {
            cout << "\nNo product of name (" << productName << ") exists in category (" << categoryName << ").";
            return false;
        }
        Product* current = productsTable[index];
        Product* prev = nullptr;
        bool found = false;
        while (current != nullptr)
        {
            if (current->getProductName() == productName)
            {
                found = true;
                if (prev == nullptr)
                {
                    productsTable[index] = current->next;
                    delete current;
                    current = productsTable[index];
                }
                else
                {
                    prev->next = current->next;
                    delete current;
                    current = prev->next;
                }
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        if (!found)
        {
            cout << "\nNo product of name (" << productName << ") exists in category (" << categoryName << ").";
            return false;
        }
        return true;
    }
    void displayProducts()
    {
        int n = productsTableSizeCat;

        for (int i = 0; i < n; i++)
        {
            Product* product = productsTable[i];
            while (product != nullptr)
            {
                product->displayProduct();
                product = product->next;
            }
        }
    }



};

#endif 