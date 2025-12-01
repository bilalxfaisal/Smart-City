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
    bool soldOut
    string productID;
    string productName;
    float price;

public:
    Product(string id = "", string name = "", float pr = 0.0f)
    {
        productID = id;
        productName = name;
        price = pr;
		soldOut = false;
    }
};

#endif 