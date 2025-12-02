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
    Product* next;

public:
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

};

#endif 