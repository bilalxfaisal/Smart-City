#pragma once
#include "../Smart-City-DS-Project/include/transport/TransportSystem.h" 
#include "../Smart-City-DS-Project/include/commercial/CommercialSystem.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void waitForEnter()
{
    cout << "\nPress ENTER to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void showMainMenu(int& choice);
void simulateBasedOnMainChoice(int ch);
void runTransportSystem(TransportSystem& transport);
void runCommercialSystem(CommercialSystem& commercial);


// Read helpers
string readLine(const string& prompt)
{
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

int readInt(const string& prompt)
{
    while (true)
    {
        string s = readLine(prompt);
        try {
            return stoi(s);
        }
        catch (...) {
            cout << "Invalid input. Try again.\n";
        }
    }
}

void showMainMenu(int& choice)
{
    int ch;
    cout << "====== SMART CITY ======\n";
    cout << "1. Commercial System\n";
    cout << "2. Education System\n";
    cout << "3. Medical System\n";
    cout << "4. Population System\n";
    cout << "5. Transport System\n";
    cout << "0. Exit\n";
    cout << "\nEnter choice: ";
    cin >> ch;
    choice = ch;
}
int showTransportMenu()
{
    int ch;
    cout << "\n====== TRANSPORT SYSTEM MENU ======\n";
    cout << "1. Add Transport Company\n";
    cout << "2. Add Bus Route\n";
    cout << "3. Add Bus Stop to Route\n";
    cout << "4. Add Bus to Transport Company\n";
    cout << "5. Simulate Bus Movement\n";
    cout << "6. Display Transport Company Status\n";
    cout << "7. Show Routes\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
    cin >> ch;
    return ch;
}
int showCommercialMenu()
{
    int ch;
    cout << "\n====== COMMERCIAL SYSTEM MENU ======\n";
    cout << "1. Add Mall\n";
    cout << "2. Add Store to Mall\n";
    cout << "3. Add Category to Store\n";
    cout << "4. Add Product to Store in Category\n";
    cout << "5. Display All Products in Store\n";
    cout << "6. Display Products in Store from Category\n";
	cout << "7. Search Product in Store\n";
    cout << "8. Buy Product\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
    cin >> ch;
    return ch;
}

void simulateBasedOnMainChoice(int ch)
{
    CommercialSystem commercial;
    TransportSystem transport;

    int choice = ch;

    switch (choice)
    {
    case 1:
    {
        runCommercialSystem(commercial);
        break;
    }
    case 2:
    {
         //runEducationSystem(transport);
        break;
    }
    case 3:
        break;
    case 4:
        break;
    case 5:
		runTransportSystem(transport);
        break;
    default:
        cout << "Invalid choice. Exiting...\n";
        break;
    }
}

void runTransportSystem(TransportSystem& transport)
{
    while (true)
    {
        system("cls");

        int choice = showTransportMenu();
        cin.ignore(); // flush newline

        if (choice == 0)
        {
            cout << "Exiting...\n";
            break;
        }

        switch (choice)
        {
        case 1:
        {
            cout << "\n=== Add Transport Company ===\n";
            string name = readLine("Enter company name: ");

            TransportCompany tc(name);
            transport.addTransportCompany(tc);

            cout << "Company added.\n";
            break;
        }

        case 2:
        {
            cout << "\n=== Add Bus Route ===\n";
            string rname = readLine("Enter route name: ");
            int rid = readInt("Enter route ID: ");
            int stops = readInt("Initial stop count: ");

            BusRoute route(rname, rid, stops);
            transport.addBusRoute(route);

            cout << "Bus route added.\n";
            break;
        }

        case 3:
        {
            cout << "\n=== Add Stop to Route ===\n";
            string rname = readLine("Enter route name: ");

            string stopName = readLine("Enter new stop name: ");
            int x = readInt("Enter X coordinate: ");
            int y = readInt("Enter Y coordinate: ");
            bool afterFlag = readInt("Add AFTER(1) or BEFORE(0) a stop? ");

            string after = afterFlag ? readLine("Add AFTER which stop? (exact name): ") : readLine("Add BEFORE which stop? (exact name): ");


            BusStop bs(stopName, x, y);

            // Must find route (simple hash lookup)
            int idx = Polynomial_Rolling_Hash_V1(rname);
            idx %= 20;

            BusRoute* rt = transport.getRouteHashTable()[idx];

            while (rt && rt->getRouteName() != rname)
                rt = rt->nextRoute;

            if (rt)
            {
                bool added = false;
                if (afterFlag)
                    added = rt->addStop_AFTR(bs, after);
                else
                    added = rt->addStop_B4(bs, after);

                if (added) {
                    cout << "Stop added.\n";
                }
                else {
                    cout << "NOPE\n";
                }
            }
            else
            {
                cout << "Route not found.\n";
            }

            break;
        }

        case 4:
        {
            cout << "\n=== Add Bus to Company ===\n";
            string comp = readLine("Enter company name: ");

            string busID = readLine("Enter bus ID: ");
            string routeID = readLine("Enter route name: ");
            int cap = readInt("Enter capacity: ");

            int startingStopID = transport.getStartingBusStopID(routeID);
            Bus b(busID, routeID, startingStopID, cap, true, true);

            transport.addBusToTransportCompany(b, comp);

            cout << "Bus added.\n";

            break;
        }

        case 5:
        {
            cout << "\n=== Simulating movement... ===\n";
            transport.simulateBusMovement();
            cout << "Simulation step completed.\n";
            break;
        }

        case 6:
        {
            string comp = readLine("\nEnter company name: ");
            transport.displayCompanyStatus(comp);
            break;
        }

        case 7:
        {
            string comp;
            cout << "Enter Company Name: ";
            cin >> comp;
            transport.displayRoutes(comp);
            break;
        }
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
		waitForEnter();
    }
}

void runCommercialSystem(CommercialSystem& commercial)
{

    while (true)
    {
        system("cls");

        int choice = showCommercialMenu();
        cin.ignore(); // flush newline

        if (choice == 0)
        {
            cout << "Exiting...\n";
            break;
        }
        switch (choice)
        {
        case 1: // Adding the Mall
        {
            int x = 0, y = 0;
            cout << "\n=== Add Mall ===\n";
            string name = readLine("Enter mall name: ");
            int mallID = readInt("Enter mall ID: ");
            cout << "\nEnter location for the mall (x, y): ";
            cin >> x >> y;
			cin.ignore(); // flush newline
            Mall mall(mallID, name, Location(x, y));
            commercial.addMall(mall);
            cout << "Mall '" << name << "'added !\n";
            break;
        }
        case 2: // Adding Store to Mall
        {
            cout << "\n=== Add Store to Mall ===\n";
            string mallName = readLine("Enter mall name: ");
            string storeName = readLine("Enter store name: ");
            int storeID = readInt("Enter store ID: ");
            Store store(storeID, storeName);
            if(commercial.addStoreToMall(mallName, store))
                cout << "Store '" << storeName << "' added to mall '" << mallName << "'.\n";
            break;
        }
        case 3: // Adding Category to Store
        {
            cout << "\n=== Add Category to Store ===\n";
            string mallName = readLine("Enter mall name: ");
            string storeName = readLine("Enter store name: ");
            string categoryName = readLine("Enter category name: ");
            if(commercial.addCategoryToStoreInMall(mallName, storeName, categoryName))
                cout << "Category '" << categoryName << "' added to store '" << storeName << "' in mall '" << mallName << "'.\n";
            break;
        }
        case 4: // Adding Product to Store in Category
        {
            cout << "\n=== Add Product to Store in Category ===\n";
            string mallName = readLine("Enter mall name: ");
            string storeName = readLine("Enter store name: ");
            string categoryName = readLine("Enter category name: ");
            int productID = readInt("Enter product ID: ");
            string productName = readLine("Enter product name: ");
            float price = stof(readLine("Enter product price: "));
            Product product(productID, productName, price);
            if(commercial.addProductToStore(mallName, storeName, categoryName, product))
                cout << "Product '" << productName << "' added to category '" << categoryName << "' in store '" << storeName << "' of mall '" << mallName << "'.\n";
            break;
        }
        case 5: // Display All Products in Store
        {
            cout << "\n=== Display Products in Store ===\n";
            string mallName = readLine("Enter mall name: ");
            string storeName = readLine("Enter store name: ");
            commercial.displayProductsInMallFromStore(mallName, storeName);
            break;
        }
        case 6: // Display Products in Store from Category
        {
            cout << "\n=== Display Products in Store from Category ===\n";
            string mallName = readLine("Enter mall name: ");
            string storeName = readLine("Enter store name: ");
            string categoryName = readLine("Enter category name: ");
            commercial.displayAllProductsInCategoryFromStore(mallName, storeName, categoryName);
            break;
        }
        case 7: // Search Product in Store
        {
            cout << "\n=== Search Product in Store ===\n";
            string mallName = readLine("Enter mall name: ");
            string storeName = readLine("Enter store name: ");
            string categoryName = readLine("Enter category name: ");
            string productName = readLine("Enter product name: ");
            commercial.findProductInStore(mallName, storeName, categoryName, productName);
            break;
        }
        case 8: // Buy Product
        {
            cout << "\n=== Buy Product ===\n";
            string mallName = readLine("Enter mall name: ");
            string storeName = readLine("Enter store name: ");
            string categoryName = readLine("Enter category name: ");
            string productName = readLine("Enter product name: ");
            bool success = commercial.buyProduct(mallName, storeName, categoryName, productName);
            if (success)
                cout << "Product '" << productName << "' purchased successfully from store '" << storeName << "' in mall '" << mallName << "'.\n";
            else
                cout << "Failed to purchase product '" << productName << "'. It may be out of stock or does not exist.\n";
            break;
        }
        case 0:
            cout << "Exiting Commercial System...\n";
            return;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
		waitForEnter();

    }
}
