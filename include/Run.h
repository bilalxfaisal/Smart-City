#pragma once
#ifndef CITY_MANAGER_H
#define CITY_MANAGER_H

#include "transport/TransportSystem.h" 
#include "commercial/CommercialSystem.h"
#include "utils/CSV_Handler.h"
#include "education/EducationSystem.h"
#include "medical/MedicalSystem.h"
#include "facilities/FacilitySystem.h"
#include "population/PopulationSystem.h"
#include "utils/LocationManager.h"
#include "visualizer/visualizer.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>

using namespace std;

class CityManager
{
private:
    // Core Systems
    locationManager locationMgr;
    CSVHandler csvHandler;
    Visualizer cityVisualizer;

    // Subsystems
    CommercialSystem commercial;
    TransportSystem transport;
    EducationSystem education;
    MedicalSystem medical;
    FacilitySystem facility;
    PopulationSystem population;

    // State tracking
    bool csvDataLoaded;

    // ==================== UTILITY FUNCTIONS ====================

    void waitForEnter()
    {
        cout << "\nPress ENTER to continue...\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

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

    float readFloat(const string& prompt)
    {
        while (true)
        {
            string s = readLine(prompt);
            try {
                return stof(s);
            }
            catch (...) {
                cout << "Invalid input. Try again.\n";
            }
        }
    }

    // ==================== MENU DISPLAY FUNCTIONS ====================

    void showMainMenu(int& choice)
    {
        int ch;
        cout << "\n============================================\n";
        cout << "   SMART CITY MANAGEMENT SYSTEM - ISLAMABAD\n";
        cout << "============================================\n";
        cout << "1. Commercial System\n";
        cout << "2. Education System\n";
        cout << "3. Medical System\n";
        cout << "4. Population System\n";
        cout << "5. Transport System\n";
        cout << "6. Public Facility System\n";
        cout << "7. Visualize City Map\n";
        cout << "8. Find Shortest Path Between Locations\n";
        cout << "0. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter choice: ";
        cin >> ch;
        choice = ch;
    }

    int showDataInputMenu()
    {
        int ch;
        cout << "\n====== DATA INPUT METHOD ======\n";
        cout << "1. Load from CSV Files\n";
        cout << "2. Manual Input\n";
        cout << "0. Go Back\n";
        cout << "\nEnter choice: ";
        cin >> ch;
        return ch;
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
        cout << "8. Display All Companies\n";
        cout << "9. Visualize Transport System\n";
        cout << "0. Exit to main menu\n";
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
        cout << "9. Display All Malls\n";
        cout << "0. Exit to main menu\n";
        cout << "Enter choice: ";
        cin >> ch;
        return ch;
    }

    int showEducationMenu()
    {
        int ch;
        cout << "\n====== EDUCATION SYSTEM MENU ======\n";
        cout << "1. Add School\n";
        cout << "2. Add Department\n";
        cout << "3. Add Faculty Member\n";
        cout << "4. Add Class\n";
        cout << "5. Add Student\n";
        cout << "6. Add Subject\n";
        cout << "7. Remove Student By Name\n";
        cout << "8. Remove Student By ID\n";
        cout << "9. Remove Faculty Member\n";
        cout << "10. Display Students in Class\n";
        cout << "11. Display All Students in School\n";
        cout << "12. Find Student\n";
        cout << "13. Display All Schools\n"; 
        cout << "14. Visualize Education System\n";
        cout << "0. Exit to main menu\n";
        cout << "Enter choice: ";
        cin >> ch;
        return ch;
    }

    int showMedicalSystemMenu()
    {
        int ch;
        cout << "\n====== MEDICAL SYSTEM MENU ======\n";
        cout << "1. Add Hospital\n";
        cout << "2. Remove Hospital\n";
        cout << "3. Add Pharmacy\n";
        cout << "4. Remove Pharmacy\n";
        cout << "5. Add Doctor To Hospital\n";
        cout << "6. Remove Doctor From Hospital\n";
        cout << "7. Add Patient To Hospital\n";
        cout << "8. Remove Patient From Hospital\n";
        cout << "9. Add Medicine To Pharmacy\n";
        cout << "10. Remove Medicine By Name\n";
        cout << "11. Remove Medicine By Formulation\n";
        cout << "12. Search Medicine By Name\n";
        cout << "13. Search Medicine By Formulation\n";
        cout << "14. Search Hospital By Name\n";
        cout << "15. Search Pharmacy By Name\n";
        cout << "16. Search Patient By Name\n";
        cout << "17. Display All Hospitals\n";  // ADD THIS
        cout << "18. Display All Pharmacies\n";
        cout << "19. Visualize Medical System\n";
        cout << "0. Exit to main menu\n";
        cout << "Enter choice: ";
        cin >> ch;
        return ch;
    }

    int showFacilityMenu()
    {
        int ch;
        cout << "\n====== FACILITY SYSTEM MENU ======\n";
        cout << "1. Add Mosque\n";
        cout << "2. Add Park\n";
        cout << "3. Add Water Cooler\n";
        cout << "4. Display All Mosques\n";
        cout << "5. Display All Parks\n";
        cout << "6. Display All Water Coolers\n";
        cout << "7. Visualize Facility System\n";
        cout << "0. Exit to main menu\n";
        cout << "Enter choice: ";
        cin >> ch;
        return ch;
    }

    int showPopulationMenu()
    {
        int ch;
        cout << "\n====== POPULATION SYSTEM MENU ======\n";
        cout << "1. Add Sector\n";
        cout << "2. Add Street\n";
        cout << "3. Add House\n";
        cout << "4. Add Citizen\n";
        cout << "5. Search Individual by CNIC\n";
        cout << "6. Age Distribution Report\n";
        cout << "7. Occupation Summary Report\n";
        cout << "8. Population Density Report\n";
        cout << "9. Display Members of a House\n";
        cout << "10. Display Houses in a Street\n";
        cout << "11. Display All Sectors\n";
        cout << "12. Visualize Population System\n";
        cout << "0. Exit to main menu\n";
        cout << "Enter choice: ";
        cin >> ch;
        return ch;
    }

    // ==================== CSV LOADING FUNCTIONS ====================

    void loadHospitalsFromCSV()
    {
        string path = readLine("Enter path to hospitals CSV file: ");
        int count = 0;
        Hospital* hospitals = csvHandler.traverseHospitalFile(path, count);

        if (hospitals) {
            for (int i = 0; i < count; i++) {
                locationMgr.addToCityGrid(
                    hospitals[i].getHospitalName(),
                    hospitals[i].getHospitalSector(),
                    "Hospital",
                    hospitals[i].getHospitalLocation()
                );
                medical.addHospital(hospitals[i]);
            }
            cout << "Loaded " << count << " hospitals.\n";
            delete[] hospitals;
        }
        else {
            cout << "Failed to load hospitals.\n";
        }
    }

    void loadPharmaciesFromCSV()
    {
        string path = readLine("Enter path to pharmacies CSV file: ");
        int count = 0;
        Pharmacy* pharmacies = csvHandler.traversePharmacyFile(path, count);

        if (pharmacies) {
            for (int i = 0; i < count; i++) {
                locationMgr.addToCityGrid(
                    pharmacies[i].getPharmacyName(),
                    pharmacies[i].getPharmacySector(),
                    "Pharmacy",
                    pharmacies[i].getPharmacyLocation()
                );
                medical.addPharmacy(pharmacies[i]);
            }
            cout << "Loaded " << count << " pharmacies.\n";
            delete[] pharmacies;
        }
        else {
            cout << "Failed to load pharmacies.\n";
        }
    }

    void loadSchoolsFromCSV()
    {
        string path = readLine("Enter path to schools CSV file: ");
        int count = 0;
        School* schools = csvHandler.traverseSchoolFile(path, count);

        if (schools) {
            for (int i = 0; i < count; i++) {
                locationMgr.addToCityGrid(
                    schools[i].getSchoolName(),
                    schools[i].getSchoolSector(),
                    "School",
                    schools[i].getSchoolLocation()
                );
                education.addSchool(schools[i]);
            }
            cout << "Loaded " << count << " schools.\n";
            delete[] schools;
        }
        else {
            cout << "Failed to load schools.\n";
        }
    }

    void loadBusStopsFromCSV()
    {
        string path = readLine("Enter path to bus stops CSV file: ");
        int count = 0;
        BusStop* stops = csvHandler.traverseBusStops(path, count);

        if (stops) {
            for (int i = 0; i < count; i++) {
                locationMgr.addToCityGrid(
                    stops[i].getStopName(),
                    stops[i].getStopSector(),
                    "Bus Stop",
                    stops[i].getLocation()
                );
            }
            cout << "Loaded " << count << " bus stops.\n";
            delete[] stops;
        }
        else {
            cout << "Failed to load bus stops.\n";
        }
    }

    void loadBusesFromCSV()
    {
        string path = readLine("Enter path to buses CSV file: ");
        int count = 0;
        Bus* buses = csvHandler.traverseBuses(path, count);

        if (buses) {
            cout << "Loaded " << count << " buses.\n";
            delete[] buses;
        }
        else {
            cout << "Failed to load buses.\n";
        }
    }

    void loadCitizensFromCSV()
    {
        string path = readLine("Enter path to citizens CSV file: ");
        int count = 0;
        Citizen* citizens = csvHandler.traversePopulationFile(path, count);

        if (citizens) {
            for (int i = 0; i < count; i++) {
                string sector = citizens[i].getCitizenSector();
                int street = citizens[i].getCitizenStreet();
                int house = citizens[i].getCitizenHouse();

                population.addCitizen(citizens[i], sector, street, house);
            }
            cout << "Loaded " << count << " citizens.\n";
            delete[] citizens;
        }
        else {
            cout << "Failed to load citizens.\n";
        }
    }

    // ==================== VISUALIZATION FUNCTIONS ====================

    void runVisualization()
    {
        system("cls");
        cout << "\n===========================================\n";
        cout << "      FULL CITY VISUALIZATION              \n";
        cout << "===========================================\n";
        cout << "Launching full city visualizer...\n";
        cout << "\nControls:\n";
        cout << "  - Left-click: Zoom into a sector\n";
        cout << "  - Right-click: Zoom out\n";
        cout << "  - Press 'H': Toggle heatmap mode (shows population density)\n";
        cout << "  - Press 'Enter': Exit heatmap mode\n";
        cout << "  - Close window: Return to main menu\n";
        cout << "\nPress ENTER to start...\n";
        cin.ignore();
        cin.get();

        cityVisualizer.removeLocationHead();

        Location* allLocations = locationMgr.getAllLocations();
        cityVisualizer.setLocationHead(allLocations);

        population.GetMinMaxPop();
        SectorPopNode* popList = population.getSectorPopulationList();
        cityVisualizer.setSectorPopHead(popList);
        cityVisualizer.setMinMaxPop(
            population.getMinPopulation(),
            population.getMaxPopulation()
        );

        cityVisualizer.run();

        cout << "\nVisualizer closed. Returning to main menu...\n";
        waitForEnter();
    }

    void runSystemVisualization(Location* systemLocationHead, const string& systemName)
    {
        if (!systemLocationHead) {
            cout << "\nNo locations found in " << systemName << ".\n";
            waitForEnter();
            return;
        }

        system("cls");
        cout << "\n===========================================\n";
        cout << "      " << systemName << " VISUALIZATION\n";
        cout << "===========================================\n";
        cout << "Launching " << systemName << " visualizer...\n";
        cout << "\nNote: Showing only " << systemName << " locations on the city grid.\n";
        cout << "\nControls:\n";
        cout << "  - Left-click: Zoom into a sector\n";
        cout << "  - Right-click: Zoom out\n";
        cout << "  - Close window: Return to menu\n";
        cout << "\nPress ENTER to start...\n";
        cin.ignore();
        cin.get();

        cityVisualizer.removeLocationHead();
        cityVisualizer.setLocationHead(systemLocationHead);
        cityVisualizer.setSectorPopHead(nullptr);

        cityVisualizer.run();

        cout << "\nVisualizer closed. Returning to " << systemName << " menu...\n";
        waitForEnter();
    }

    // ==================== SHORTEST PATH FUNCTION ====================

    void findShortestPathBetweenLocations()
    {
        system("cls");
        cout << "\n===========================================\n";
        cout << "      SHORTEST PATH FINDER                 \n";
        cout << "===========================================\n";
        cout << "Find the shortest route between two locations in Islamabad.\n\n";

        cout << "Available Landmarks:\n";
        cout << "  - BlueArea (F-8, G-8)\n";
        cout << "  - Centaurus (F-8)\n";
        cout << "  - PIMS Hospital (G-8)\n";
        cout << "  - Faisal Mosque (E-8)\n";
        cout << "  - Lake View (F-9)\n";
        cout << "Or use sector names: D-5 to J-12\n\n";

        // Get start location
        cout << "=== START LOCATION ===\n";
        cout << "Enter start location: ";
        string startInput;
        cin.ignore();
        getline(cin, startInput);

        // Get end location
        cout << "\n=== END LOCATION ===\n";
        cout << "Enter end location: ";
        string endInput;
        getline(cin, endInput);

        // Convert inputs to coordinates
        int startX, startY, endX, endY;

        // Try to get sector bounds for start
        if (!locationMgr.getSectorBounds(startInput, startX, startY)) {
            cout << "\n[ERROR] Could not find start location '" << startInput << "'.\n";
            cout << "Please use valid sector names (D-5 to J-12) or registered landmarks.\n";
            waitForEnter();
            return;
        }

        // Try to get sector bounds for end
        if (!locationMgr.getSectorBounds(endInput, endX, endY)) {
            cout << "\n[ERROR] Could not find end location '" << endInput << "'.\n";
            cout << "Please use valid sector names (D-5 to J-12) or registered landmarks.\n";
            waitForEnter();
            return;
        }

        // IMPORTANT: Add the START offsets to match the coordinate system
        startX += 80;
        startY += 50;
        endX += 80;
        endY += 50;

        // Find the actual Location nodes in the graph
        Location* startLoc = nullptr;
        Location* endLoc = nullptr;
        Location* temp = locationMgr.getHead();

        // Find closest nodes to the coordinates
        while (temp) {
            if (temp->x == startX && temp->y == startY) {
                startLoc = temp;
            }
            if (temp->x == endX && temp->y == endY) {
                endLoc = temp;
            }
            if (startLoc && endLoc) break;
            temp = temp->next;
        }

        if (!startLoc || !endLoc) {
            cout << "\n[ERROR] Could not find location nodes in the city graph.\n";
            cout << "Debug Info:\n";
            cout << "  Looking for start: (" << startX << ", " << startY << ")\n";
            cout << "  Looking for end: (" << endX << ", " << endY << ")\n";
            waitForEnter();
            return;
        }

        // Find shortest path using Dijkstra's algorithm
        cout << "\n[INFO] Calculating shortest path...\n";
        PathNode* path = locationMgr.findShortestPath(startLoc, endLoc);

        if (!path) {
            cout << "\n[ERROR] No path found between the two locations!\n";
            waitForEnter();
            return;
        }

        // Display the path
        cout << "\n===========================================\n";
        cout << "      SHORTEST PATH FOUND                  \n";
        cout << "===========================================\n";
        cout << "From: " << startInput << " (" << startX << ", " << startY << ")\n";
        cout << "To: " << endInput << " (" << endX << ", " << endY << ")\n";
        cout << "Total Distance: " << endLoc->minDist << " units\n\n";

        cout << "===========================================\n";
        cout << "                  ROUTE                    \n";
        cout << "===========================================\n";
        int step = 1;
        PathNode* current = path;

        while (current) {
            Location* loc = current->loc;

            // Format step number
            cout << "Step " << step << ": ";

            // Display location info
            cout << loc->name;

            // Add type badge
            if (loc->type == "Intersection") {
                cout << " [Intersection]";
            }
            else if (loc->type == "Hospital") {
                cout << " [Hospital]";
            }
            else if (loc->type == "School") {
                cout << " [School]";
            }
            else if (loc->type == "Mall") {
                cout << " [Mall]";
            }
            else if (loc->type == "Bus Stop") {
                cout << " [Bus Stop]";
            }
            else {
                cout << " [" << loc->type << "]";
            }

            cout << "\n       Location: (" << loc->x << ", " << loc->y << ")";

            if (current->next) {
                float segmentDist = current->next->loc->minDist - loc->minDist;
                cout << "\n       -> Distance to next: " << segmentDist << " units\n";
            }
            else {
                cout << "\n       [DESTINATION REACHED]\n";
            }

            cout << "-------------------------------------------\n";

            current = current->next;
            step++;
        }

        cout << "\n[SUCCESS] Total Steps: " << (step - 1) << "\n";
        cout << "[SUCCESS] Total Distance: " << endLoc->minDist << " units\n";
        cout << "===========================================\n";

        // Clean up path
        while (path) {
            PathNode* temp = path;
            path = path->next;
            delete temp;
        }

        waitForEnter();
    }

    // ==================== SYSTEM RUNNER FUNCTIONS ====================

    void runTransportSystem()
    {
        while (true)
        {
            system("cls");
            int choice = showTransportMenu();
            cin.ignore();

            if (choice == 0) {
                cout << "Exiting Transport System...\n";
                break;
            }

            if (choice == 8) {
                if (!csvDataLoaded) {
                    cout << "\nPlease load CSV data first before visualizing.\n";
                    waitForEnter();
                    continue;
                }
                Location* transportLocations = transport.getBusStopLocationHead();
                runSystemVisualization(transportLocations, "Transport System");
                continue;
            }

            switch (choice)
            {
            case 1: // Add Transport Company
            {
                cout << "\n=== Add Transport Company ===\n";
                string name = readLine("Enter company name: ");
                TransportCompany tc(name);
                transport.addTransportCompany(tc);
                cout << "[SUCCESS] Company added successfully!\n";
                break;
            }
            case 2: // Add Bus Route
            {
                cout << "\n=== Add Bus Route ===\n";
                string rname = readLine("Enter route name: ");
                int rid = readInt("Enter route ID: ");
                int stops = readInt("Initial stop count: ");
                BusRoute route(rname, rid, stops);
                transport.addBusRoute(route);
                cout << "[SUCCESS] Bus route added successfully!\n";
                break;
            }
            case 3: // Add Bus Stop to Route
            {
                cout << "\n=== Add Stop to Route ===\n";
                string rname = readLine("Enter route name: ");
                string stopName = readLine("Enter new stop name: ");
                string sect = readLine("Enter the sector or location area: ");
                bool afterFlag = readInt("Add AFTER(1) or BEFORE(0) a stop? ");
                string after = afterFlag ? readLine("Add AFTER which stop? (exact name): ")
                    : readLine("Add BEFORE which stop? (exact name): ");

                BusStop bs(stopName, sect);
                locationMgr.addToCityGrid(stopName, sect, "Bus Stop", bs.getLocation());

                int idx = Polynomial_Rolling_Hash_V1(rname) % 20;
                BusRoute* rt = transport.getRouteHashTable()[idx];

                while (rt && rt->getRouteName() != rname)
                    rt = rt->nextRoute;

                if (rt) {
                    bool added = afterFlag ? rt->addStop_AFTR(bs, after)
                        : rt->addStop_B4(bs, after);
                    if (added) {
                        cout << "[SUCCESS] Stop added successfully!\n";
                    }
                    else {
                        cout << "[ERROR] Failed to add stop.\n";
                    }
                }
                else {
                    cout << "[ERROR] Route not found.\n";
                }
                break;
            }
            case 4: // Add Bus to Company
            {
                cout << "\n=== Add Bus to Company ===\n";
                string comp = readLine("Enter company name: ");
                string busID = readLine("Enter bus ID: ");
                string routeID = readLine("Enter route name: ");
                int cap = readInt("Enter capacity: ");
                int startingStopID = transport.getStartingBusStopID(routeID);
                Bus b(busID, routeID, startingStopID, cap, true, true);
                transport.addBusToTransportCompany(b, comp);
                cout << "[SUCCESS] Bus added successfully!\n";
                break;
            }
            case 5: // Simulate Bus Movement
            {
                cout << "\n=== Simulating Bus Movement ===\n";
                transport.simulateBusMovement();
                cout << "[SUCCESS] Simulation step completed.\n";
                break;
            }
            case 6: // Display Company Status
            {
                string comp = readLine("\nEnter company name: ");
                transport.displayCompanyStatus(comp);
                break;
            }
            case 7: // Show Routes
            {
                string comp = readLine("Enter Company Name: ");
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

    void runCommercialSystem()
    {
        while (true)
        {
            system("cls");
            int choice = showCommercialMenu();
            cin.ignore();

            if (choice == 0) {
                cout << "Exiting Commercial System...\n";
                break;
            }

            switch (choice)
            {
            case 1: // Add Mall
            {
                cout << "\n=== Add Mall ===\n";
                string name = readLine("Enter mall name: ");
                int mallID = readInt("Enter mall ID: ");
                string sect = readLine("Enter location for the mall (sector or area): ");
                Mall mall(mallID, name);
                locationMgr.addToCityGrid(name, sect, "Mall", mall.getLocation());
                commercial.addMall(mall);
                cout << "[SUCCESS] Mall '" << name << "' added successfully!\n";
                break;
            }
            case 2: // Add Store to Mall
            {
                cout << "\n=== Add Store to Mall ===\n";
                string mallName = readLine("Enter mall name: ");
                string storeName = readLine("Enter store name: ");
                int storeID = readInt("Enter store ID: ");
                Store store(storeID, storeName);
                if (commercial.addStoreToMall(mallName, store))
                    cout << "[SUCCESS] Store '" << storeName << "' added to mall '" << mallName << "'.\n";
                break;
            }
            case 3: // Add Category to Store
            {
                cout << "\n=== Add Category to Store ===\n";
                string mallName = readLine("Enter mall name: ");
                string storeName = readLine("Enter store name: ");
                string categoryName = readLine("Enter category name: ");
                if (commercial.addCategoryToStoreInMall(mallName, storeName, categoryName))
                    cout << "[SUCCESS] Category '" << categoryName << "' added successfully.\n";
                break;
            }
            case 4: // Add Product
            {
                cout << "\n=== Add Product to Store in Category ===\n";
                string mallName = readLine("Enter mall name: ");
                string storeName = readLine("Enter store name: ");
                string categoryName = readLine("Enter category name: ");
                int productID = readInt("Enter product ID: ");
                string productName = readLine("Enter product name: ");
                float price = readFloat("Enter product price: ");
                Product product(productID, productName, price);
                if (commercial.addProductToStore(mallName, storeName, categoryName, product))
                    cout << "[SUCCESS] Product '" << productName << "' added successfully.\n";
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
            case 6: // Display Products from Category
            {
                cout << "\n=== Display Products in Store from Category ===\n";
                string mallName = readLine("Enter mall name: ");
                string storeName = readLine("Enter store name: ");
                string categoryName = readLine("Enter category name: ");
                commercial.displayAllProductsInCategoryFromStore(mallName, storeName, categoryName);
                break;
            }
            case 7: // Search Product
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
                    cout << "[SUCCESS] Product '" << productName << "' purchased successfully!\n";
                else
                    cout << "[ERROR] Failed to purchase product.\n";
                break;
            }
            case 9: // Display All Malls - ADD THIS ENTIRE CASE
            {
                cout << "\n=== Display All Malls ===\n";
                commercial.display();
                break;
            }
            default:
                cout << "Invalid choice. Try again.\n";
                break;
            }
            waitForEnter();
        }
    }

    void runEducationSystem()
    {
        while (true)
        {
            system("cls");
            int choice = showEducationMenu();
            cin.ignore();

            if (choice == 0) {
                cout << "Exiting Education System...\n";
                break;
            }

            if (choice == 14) {
                if (!csvDataLoaded) {
                    cout << "\nPlease load CSV data first before visualizing.\n";
                    waitForEnter();
                    continue;
                }
                Location* eduLocations = education.getSchoolLocationsHead();
                runSystemVisualization(eduLocations, "Education System");
                continue;
            }

            switch (choice)
            {
            case 1: // Add School
            {
                cout << "\n=== Add School ===\n";
                string name = readLine("Enter School name: ");
                string id = readLine("Enter School ID: ");
                string sector = readLine("Enter sector name: ");
                int campus = readInt("Enter the campus number: ");
                School school(id, name, sector, campus);
                locationMgr.addToCityGrid(name, sector, "School", school.getSchoolLocation());
                education.addSchool(school);
                cout << "[SUCCESS] School '" << name << "' added successfully!\n";
                break;
            }
            case 2: // Add Department
            {
                cout << "\n=== Add Department ===\n";
                string schoolID = readLine("Enter School ID: ");
                string deptName = readLine("Enter Department name: ");
                string deptID = readLine("Enter Department ID: ");
                Department dept(deptName, deptID);
                if (education.addDepartment(schoolID, dept))
                    cout << "[SUCCESS] Department '" << deptName << "' successfully added!\n";
                else
                    cout << "[ERROR] Department '" << deptName << "' can't be added!\n";
                break;
            }
            case 3: // Add Faculty Member
            {
                cout << "\n=== Add Faculty Member ===\n";
                string schoolID = readLine("Enter School ID: ");
                string facID = readLine("Enter Faculty Member ID: ");
                string facName = readLine("Enter Faculty Member name: ");
                string spec = readLine("Enter Faculty specialization: ");
                Faculty fac(facID, facName, spec);
                if (education.addFaculty(schoolID, fac))
                    cout << "[SUCCESS] Faculty Member '" << facName << "' successfully added!\n";
                else
                    cout << "[ERROR] Faculty Member '" << facName << "' can't be added!\n";
                break;
            }
            case 4: // Add Class
            {
                cout << "\n=== Add Class ===\n";
                string schoolID = readLine("Enter School ID: ");
                string depID = readLine("Enter Department ID: ");
                string className = readLine("Enter Class name: ");
                string classID = readLine("Enter Class ID: ");
                Class cl(className, classID);
                if (education.addClass(schoolID, depID, cl))
                    cout << "[SUCCESS] Class '" << className << "' successfully added!\n";
                else
                    cout << "[ERROR] Class '" << className << "' can't be added!\n";
                break;
            }
            case 5: // Add Student
            {
                cout << "\n=== Add Student ===\n";
                string schoolID = readLine("Enter School ID: ");
                string depID = readLine("Enter Department ID: ");
                string classID = readLine("Enter Class ID: ");
                string name = readLine("Enter Student name: ");
                string id = readLine("Enter Student ID: ");
                int age = readInt("Enter Student age: ");
                Student student(id, name, age);
                if (education.addStudent(student, schoolID, depID, classID))
                    cout << "[SUCCESS] Student '" << name << "' successfully added!\n";
                else
                    cout << "[ERROR] Student '" << name << "' can't be added!\n";
                break;
            }
            case 6: // Add Subject
            {
                cout << "\n=== Add Subject ===\n";
                string schoolID = readLine("Enter School ID: ");
                string name = readLine("Enter Subject name: ");
                if (education.addSubject(schoolID, name))
                    cout << "[SUCCESS] Subject '" << name << "' successfully added!\n";
                break;
            }
            case 7: // Remove Student By Name
            {
                cout << "\n=== Remove Student by Name ===\n";
                string schoolID = readLine("Enter School ID: ");
                string depID = readLine("Enter Department ID: ");
                string classID = readLine("Enter Class name: ");
                string name = readLine("Enter Student name: ");
                if (education.removeStudentByName(schoolID, depID, classID, name))
                    cout << "[SUCCESS] Student with Name '" << name << "' removed successfully!\n";
                break;
            }
            case 8: // Remove Student By ID
            {
                cout << "\n=== Remove Student by ID ===\n";
                string schoolID = readLine("Enter School ID: ");
                string depID = readLine("Enter Department ID: ");
                string classID = readLine("Enter Class name: ");
                string id = readLine("Enter Student ID: ");
                if (education.removeStudentByID(schoolID, depID, classID, id))
                    cout << "[SUCCESS] Student with ID '" << id << "' removed successfully!\n";
                break;
            }
            case 9: // Remove Faculty
            {
                cout << "\n=== Remove Faculty Member ===\n";
                string schoolID = readLine("Enter School ID: ");
                string facName = readLine("Enter Faculty Member name: ");
                if (education.removeFacultyByName(schoolID, facName))
                    cout << "[SUCCESS] Faculty Member '" << facName << "' removed successfully!\n";
                break;
            }
            case 10: // Display Students in Class
            {
                cout << "\n=== Displaying Students in Class ===\n";
                string schoolID = readLine("Enter School ID: ");
                string deptID = readLine("Enter Department ID: ");
                string classID = readLine("Enter Class ID: ");
                education.displayStudentsInClass(schoolID, deptID, classID);
                break;
            }
            case 11: // Display All Students in School
            {
                cout << "\n=== Displaying All Students in School ===\n";
                string schoolID = readLine("Enter School ID: ");
                education.displayStudentsInSchool(schoolID);
                break;
            }
            case 13: // Display All Schools - ADD THIS CASE
            {
                cout << "\n=== Display All Schools ===\n";
                education.display();
                break;
            }
            default:
                break;
            }
            waitForEnter();
        }
    }

    void runMedicalSystem()
    {
        while (true)
        {
            system("cls");
            int choice = showMedicalSystemMenu();
            cin.ignore();

            if (choice == 0) {
                cout << "Exiting Medical System...\n";
                break;
            }

            if (choice == 19) {  // CHANGE from 17
                if (!csvDataLoaded) {
                    cout << "\nPlease load CSV data first before visualizing.\n";
                    waitForEnter();
                    continue;
                }
                Location* hospitalLocs = medical.getHospitalLocationHead();
                Location* pharmacyLocs = medical.getPharmacyLocationHead();

                // Merge both lists temporarily for visualization
                if (hospitalLocs && pharmacyLocs) {
                    Location* temp = hospitalLocs;
                    while (temp->next) temp = temp->next;
                    temp->next = pharmacyLocs;
                }

                runSystemVisualization(hospitalLocs ? hospitalLocs : pharmacyLocs, "Medical System");

                // Unlink after visualization
                if (hospitalLocs && pharmacyLocs) {
                    Location* temp = hospitalLocs;
                    while (temp->next != pharmacyLocs) temp = temp->next;
                    temp->next = nullptr;
                }
                continue;
            }

            switch (choice)
            {
            case 1: // Add Hospital
            {
                cout << "\n=== Add Hospital ===\n";
                string name = readLine("Enter hospital name: ");
                string id = readLine("Enter hospital ID: ");
                string sec = readLine("Enter sector: ");
                string specs = readLine("Enter specializations (comma separated): ");
                int bedNum = readInt("Enter number of beds: ");
                Hospital hospital(name, id, sec, bedNum, specs);
                locationMgr.addToCityGrid(name, sec, "Hospital", hospital.getHospitalLocation());
                medical.addHospital(hospital);
                cout << "[SUCCESS] Hospital added successfully!\n";
                break;
            }
            case 2: // Remove Hospital
            {
                cout << "\n=== Remove Hospital ===\n";
                string name = readLine("Enter hospital name: ");
                medical.removeHospital(name);
                break;
            }
            case 3: // Add Pharmacy
            {
                cout << "\n=== Add Pharmacy ===\n";
                string name = readLine("Enter pharmacy name: ");
                string id = readLine("Enter pharmacy id: ");
                string sec = readLine("Enter the sector or location tag: ");
                Pharmacy pharmacy(name, id);
                locationMgr.addToCityGrid(name, sec, "Pharmacy", pharmacy.getPharmacyLocation());
                medical.addPharmacy(pharmacy);
                cout << "[SUCCESS] Pharmacy added successfully!\n";
                break;
            }
            case 4: // Remove Pharmacy
            {
                cout << "\n=== Remove Pharmacy ===\n";
                string name = readLine("Enter pharmacy name: ");
                medical.removePharmacy(name);
                break;
            }
            case 5: // Add Doctor To Hospital
            {
                cout << "\n=== Add Doctor To Hospital ===\n";
                string hosName = readLine("Enter hospital name: ");
                string name = readLine("Enter doctor's name: ");
                string id = readLine("Enter doctor's ID: ");
                string spec = readLine("Enter doctor's specialization: ");
                Doctor doc(name, spec, id);
                medical.addDoctorToHospital(hosName, doc);
                break;
            }
            case 6: // Remove Doctor From Hospital
            {
                cout << "\n=== Remove Doctor From Hospital ===\n";
                string hosName = readLine("Enter hospital name: ");
                string id = readLine("Enter doctor's ID: ");
                medical.removeDoctorFromHospital(hosName, id);
                break;
            }
            case 7: // Add Patient To Hospital
            {
                cout << "\n=== Add Patient To Hospital ===\n";
                string hosName = readLine("Enter hospital name: ");
                string name = readLine("Enter patient's name: ");
                string id = readLine("Enter patient's ID: ");
                float weight = readFloat("Enter patient's weight: ");
                Patient pat(name, weight, id);
                medical.addPatientToHospital(hosName, pat);
                break;
            }
            case 8: // Remove Patient From Hospital
            {
                cout << "\n=== Remove Patient From Hospital ===\n";
                string hosName = readLine("Enter hospital name: ");
                string id = readLine("Enter patient's ID: ");
                medical.removePatientFromHospital(hosName, id);
                break;
            }
            case 9: // Add Medicine To Pharmacy
            {
                cout << "\n=== Add Medicine To Pharmacy ===\n";
                string pharmName = readLine("Enter pharmacy name: ");
                string name = readLine("Enter medicine name: ");
                string form = readLine("Enter medicine formulation: ");
                int quan = readInt("Enter medicine quantity: ");
                float price = readFloat("Enter medicine price: ");
                Medicine med(name, form, quan, price);
                medical.addMedicineToPharmacy(pharmName, med);
                break;
            }
            case 10: // Remove Medicine By Name
            {
                cout << "\n=== Remove Medicine By Name ===\n";
                string pharmName = readLine("Enter pharmacy name: ");
                string name = readLine("Enter medicine name: ");
                medical.removeMedicineByName(pharmName, name);
                break;
            }
            case 11: // Remove Medicine By Formulation
            {
                cout << "\n=== Remove Medicine By Formulation ===\n";
                string pharmName = readLine("Enter pharmacy name: ");
                string form = readLine("Enter medicine formulation: ");
                medical.removeMedicineByFormulation(pharmName, form);
                break;
            }
            case 12: // Search Medicine By Name
            {
                cout << "\n=== Search Medicine By Name ===\n";
                string pharmName = readLine("Enter pharmacy name: ");
                string name = readLine("Enter medicine name: ");
                medical.searchMedicineByName(pharmName, name);
                break;
            }
            case 13: // Search Medicine By Formulation
            {
                cout << "\n=== Search Medicine By Formulation ===\n";
                string pharmName = readLine("Enter pharmacy name: ");
                string form = readLine("Enter medicine formulation: ");
                medical.searchMedicineByFormulation(pharmName, form);
                break;
            }
            case 14: // Search Hospital By Name
            {
                cout << "\n=== Search Hospital By Name ===\n";
                string hosName = readLine("Enter hospital name: ");
                medical.searchHospitalByName(hosName);
                break;
            }
            case 15: // Search Pharmacy By Name
            {
                cout << "\n=== Search Pharmacy By Name ===\n";
                string pharmName = readLine("Enter pharmacy name: ");
                medical.searchPharmacyByName(pharmName);
                break;
            }
            case 16: // Search Patient By Name
            {
                cout << "\n=== Search Patient By Name ===\n";
                string id = readLine("Enter patient's ID: ");
                medical.searchPatientByID(id);
                break;
            }
            case 17: // Display All Hospitals - ADD THIS CASE
            {
                cout << "\n=== Display All Hospitals ===\n";
                medical.display();
                break;
            }
            case 18: // Display All Pharmacies - ADD THIS CASE
            {
                cout << "\n=== Display All Pharmacies ===\n";
                medical.display();
                break;
            }
            default:
                cout << "\nInvalid choice! Try again.\n";
                break;
            }
            waitForEnter();
        }
    }

    void runFacilitySystem()
    {
        while (true)
        {
            system("cls");
            int choice = showFacilityMenu();
            cin.ignore();

            if (choice == 0) {
                cout << "Exiting Facility System...\n";
                break;
            }

            if (choice == 7) {
                Location* mosqueLocs = facility.getMosqueLocationHead();
                Location* parkLocs = facility.getParkLocationHead();
                Location* coolerLocs = facility.getCoolerLocationHead();

                // Link them together temporarily
                Location* facilityHead = mosqueLocs;
                if (mosqueLocs) {
                    Location* temp = mosqueLocs;
                    while (temp->next) temp = temp->next;
                    temp->next = parkLocs;
                    if (parkLocs) {
                        temp = parkLocs;
                        while (temp->next) temp = temp->next;
                        temp->next = coolerLocs;
                    }
                }
                else if (parkLocs) {
                    facilityHead = parkLocs;
                    Location* temp = parkLocs;
                    while (temp->next) temp = temp->next;
                    temp->next = coolerLocs;
                }
                else {
                    facilityHead = coolerLocs;
                }

                runSystemVisualization(facilityHead, "Facility System");

                // Unlink after visualization
                if (mosqueLocs && parkLocs) {
                    Location* temp = mosqueLocs;
                    while (temp->next != parkLocs) temp = temp->next;
                    temp->next = nullptr;
                }
                if (parkLocs && coolerLocs) {
                    Location* temp = parkLocs;
                    while (temp->next != coolerLocs) temp = temp->next;
                    temp->next = nullptr;
                }
                continue;
            }

            switch (choice)
            {
            case 1: // Add Mosque
            {
                int x, y;
                cout << "\n=== Add Mosque ===\n";
                string name = readLine("Enter mosque name: ");
                cout << "Enter mosque location (x, y): ";
                cin >> x >> y;
                Mosque mosque(Location(x, y), name);
                facility.addMosque(mosque);
                cout << "[SUCCESS] Mosque added successfully!\n";
                break;
            }
            case 2: // Add Park
            {
                int x, y;
                cout << "\n=== Add Park ===\n";
                string name = readLine("Enter park name: ");
                cout << "Enter park location (x, y): ";
                cin >> x >> y;
                Park park(Location(x, y), name);
                facility.addPark(park);
                cout << "[SUCCESS] Park added successfully!\n";
                break;
            }
            case 3: // Add Water Cooler
            {
                int x, y;
                cout << "\n=== Add Water Cooler ===\n";
                string name = readLine("Enter water cooler name: ");
                cout << "Enter water cooler location (x, y): ";
                cin >> x >> y;
                WaterCooler cooler(Location(x, y), name);
                facility.addWaterCooler(cooler);
                cout << "[SUCCESS] Water cooler added successfully!\n";
                break;
            }
            case 4: // Display All Mosques
            {
                cout << "\n=== Display All Mosques ===\n";
                facility.displayAllMosques();
                break;
            }
            case 5: // Display All Parks
            {
                cout << "\n=== Display All Parks ===\n";
                facility.displayAllParks();
                break;
            }
            case 6: // Display All Water Coolers
            {
                cout << "\n=== Display All Water Coolers ===\n";
                facility.displayAllWaterCoolers();
                break;
            }
            default:
                cout << "\nInvalid choice! Try again.\n";
                break;
            }
            waitForEnter();
        }
    }

    void runPopulationSystem()
    {
        while (true)
        {
            system("cls");
            int choice = showPopulationMenu();
            cin.ignore();

            if (choice == 0) {
                cout << "Exiting Population System...\n";
                break;
            }

            if (choice == 12) {
                if (!csvDataLoaded) {
                    cout << "\nPlease load CSV data first before visualizing.\n";
                    waitForEnter();
                    continue;
                }
                Location* houseLocs = population.getHouseLocationHead();
                runSystemVisualization(houseLocs, "Population System");
                continue;
            }

            switch (choice)
            {
            case 1: // Add Sector
            {
                cout << "\n=== Add Sector ===\n";
                string name = readLine("Enter sector name: ");
                Sector sector(name);
                population.addSector(sector);
                cout << "[SUCCESS] Sector added successfully!\n";
                break;
            }
            case 2: // Add Street
            {
                cout << "\n=== Add Street ===\n";
                string sectorName = readLine("Enter sector name: ");
                string streetName = readLine("Enter street name: ");
                int streetID = readInt("Enter street ID: ");
                Street street(streetName, streetID);
                population.addStreet(street, sectorName);
                cout << "[SUCCESS] Street added successfully!\n";
                break;
            }
            case 3: // Add House
            {
                cout << "\n=== Add House ===\n";
                string sectorName = readLine("Enter sector name: ");
                int streetNo = readInt("Enter street number: ");
                int houseNumber = readInt("Enter house number: ");
                House house(houseNumber, streetNo, sectorName);
                population.addHouse(house, sectorName, streetNo);
                locationMgr.addToCityGrid("House", sectorName, "House", house.getHouseLocation());
                cout << "[SUCCESS] House added successfully!\n";
                break;
            }
            case 4: // Add Citizen
            {
                cout << "\n=== Add Citizen ===\n";
                string cnic = readLine("Enter CNIC: ");
                string name = readLine("Enter name: ");
                int age = readInt("Enter age: ");
                string sector = readLine("Enter sector name: ");
                int streetNo = readInt("Enter street number: ");
                int houseNo = readInt("Enter house number: ");
                string occupation = readLine("Enter occupation: ");
                Citizen citizen(cnic, name, age, sector, streetNo, houseNo, occupation);
                population.addCitizen(citizen, sector, streetNo, houseNo);
                cout << "[SUCCESS] Citizen added successfully!\n";
                break;
            }
            case 5: // Search Individual by CNIC
            {
                cout << "\n=== Search Individual by CNIC ===\n";
                string cnic = readLine("Enter CNIC: ");
                population.searchIndividual(cnic);
                break;
            }
            case 6: // Age Distribution Report
            {
                cout << "\n=== Age Distribution Report ===\n";
                population.reportAgeDistribution();
                break;
            }
            case 7: // Occupation Summary Report
            {
                cout << "\n=== Occupation Summary Report ===\n";
                population.reportOccupationSummary();
                break;
            }
            case 8: // Population Density Report
            {
                cout << "\n=== Population Density Report ===\n";
                population.reportPopulationDensity();
                break;
            }
            case 9: // Display Members of a House
            {
                cout << "\n=== Display Members of a House ===\n";
                string sectorName = readLine("Enter sector name: ");
                int streetNo = readInt("Enter street number: ");
                int houseNo = readInt("Enter house number: ");
                population.displayMembersOfHouse(sectorName, streetNo, houseNo);
                break;
            }
            case 10: // Display Houses in a Street
            {
                cout << "\n=== Display Houses in a Street ===\n";
                string sectorName = readLine("Enter sector name: ");
                int streetNo = readInt("Enter street number: ");
                population.displayHousesInStreet(sectorName, streetNo);
                break;
            }
            case 11: // Display All Sectors - ADD THIS CASE
            {
                cout << "\n=== Display All Sectors ===\n";
                population.display();
                break;
            }
            default:
                cout << "\nInvalid choice! Try again.\n";
                break;
            }
            waitForEnter();
        }
    }

    // ==================== MAIN SIMULATION LOGIC ====================

    void simulateBasedOnMainChoice(int ch)
    {
        int choice = ch;

        // Handle visualization separately
        if (choice == 7) {
            if (!csvDataLoaded) {
                cout << "\n[WARNING] No CSV data has been loaded yet!\n";
                cout << "Please load data from at least one system before visualizing.\n";
                cout << "\nPress ENTER to return to menu...\n";
                cin.ignore();
                cin.get();
                return;
            }
            runVisualization();
            return;
        }

        // Handle shortest path finder
        if (choice == 8) {
            findShortestPathBetweenLocations();
            return;
        }

        // Ask for input method
        system("cls");
        int inputMethod = showDataInputMenu();
        cin.ignore();

        if (inputMethod == 0) {
            return; // Go back to main menu
        }
        else if (inputMethod == 1) {
            // Load from CSV
            cout << "\n=== Loading data from CSV files ===\n";

            switch (choice)
            {
            case 1: // Commercial
                cout << "[ERROR] CSV loading for Commercial System is not available.\n";
                cout << "Please use manual input instead.\n";
                break;

            case 2: // Education
                loadSchoolsFromCSV();
                csvDataLoaded = true;
                break;

            case 3: // Medical
                loadHospitalsFromCSV();
                loadPharmaciesFromCSV();
                csvDataLoaded = true;
                break;

            case 4: // Population
                loadCitizensFromCSV();
                csvDataLoaded = true;
                break;

            case 5: // Transport
                loadBusStopsFromCSV();
                loadBusesFromCSV();
                csvDataLoaded = true;
                break;

            case 6: // Facility
                cout << "[ERROR] CSV loading not implemented for Facility System yet.\n";
                break;

            default:
                cout << "Invalid system choice.\n";
                break;
            }

            cout << "\n[SUCCESS] Data loading completed!\n";
            waitForEnter();
        }

        // Now run the appropriate system
        switch (choice)
        {
        case 1: runCommercialSystem(); break;
        case 2: runEducationSystem(); break;
        case 3: runMedicalSystem(); break;
        case 4: runPopulationSystem(); break;
        case 5: runTransportSystem(); break;
        case 6: runFacilitySystem(); break;
        default:
            cout << "Invalid choice. Exiting...\n";
            break;
        }
    }

public:
    // Constructor
    CityManager() : education(20), csvDataLoaded(false)
    {
        // LocationManager constructor already initializes the road network
        cout << "[SUCCESS] City Manager initialized successfully!\n";
    }

    // Destructor
    ~CityManager()
    {
        // Cleanup if needed
    }

    // Main run function
    void run()
    {
        int mainMenuCh = 0;
        do {
            system("cls");
            showMainMenu(mainMenuCh);
            if (mainMenuCh != 0) {
                simulateBasedOnMainChoice(mainMenuCh);
            }
        } while (mainMenuCh != 0);

        cout << "\n===========================================\n";
        cout << "  Thank you for using Smart City System!  \n";
        cout << "===========================================\n";
    }
};

#endif // CITY_MANAGER_H
