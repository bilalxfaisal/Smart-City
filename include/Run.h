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
    locationManager locationMgr;
    CSVHandler csvHandler;
    Visualizer cityVisualizer;

    CommercialSystem commercial;
    TransportSystem transport;
    EducationSystem education;
    MedicalSystem medical;
    FacilitySystem facility;
    PopulationSystem population;

    bool csvDataLoaded;

    void findShortestPathBetweenLocations()
    {
        system("cls");
        cout << "\n===========================================\n";
        cout << "      SHORTEST PATH FINDER                 \n";
        cout << "===========================================\n";
        cout << "Find the shortest route between ANY two locations.\n\n";

        cout << "You can search by:\n";
        cout << "  1. Sector names (e.g., F-8, G-8)\n";
        cout << "  2. Landmarks (e.g., BlueArea, Centaurus)\n";
        cout << "  3. Specific locations (Hospital, School, Mall, House)\n\n";

        cout << "=== START LOCATION ===\n";
        cout << "Enter start location: ";
        string startInput;
        cin.ignore();
        getline(cin, startInput);

        cout << "\nSearching for start location...\n";
        locationMgr.searchLocations(startInput);

        cout << "\n=== END LOCATION ===\n";
        cout << "Enter end location: ";
        string endInput;
        getline(cin, endInput);

        cout << "\nSearching for end location...\n";
        locationMgr.searchLocations(endInput);

        cout << "\n=== PATH MODE ===\n";
        cout << "1. Normal Path (considers traffic)\n";
        cout << "2. Emergency Path (60% faster, priority lanes)\n";
        cout << "Enter choice: ";
        int pathMode;
        cin >> pathMode;
        cin.ignore();

        bool emergencyMode = (pathMode == 2);

        cout << "\n=== CONFIRM SELECTION ===\n";
        cout << "Press ENTER to find path, or type 'cancel': ";
        string confirm;
        getline(cin, confirm);

        if (confirm == "cancel" || confirm == "CANCEL") {
            cout << "Path finding cancelled.\n";
            waitForEnter();
            return;
        }

        Location* startLoc = locationMgr.findLocationByName(startInput);
        Location* endLoc = locationMgr.findLocationByName(endInput);

        if (!startLoc) {
            int startX, startY;
            if (locationMgr.getSectorBounds(startInput, startX, startY)) {
                startX += 80;
                startY += 50;

                Location* temp = locationMgr.getHead();
                while (temp) {
                    if (temp->x == startX && temp->y == startY) {
                        startLoc = temp;
                        break;
                    }
                    temp = temp->next;
                }
            }
        }

        if (!endLoc) {
            int endX, endY;
            if (locationMgr.getSectorBounds(endInput, endX, endY)) {
                endX += 80;
                endY += 50;

                Location* temp = locationMgr.getHead();
                while (temp) {
                    if (temp->x == endX && temp->y == endY) {
                        endLoc = temp;
                        break;
                    }
                    temp = temp->next;
                }
            }
        }

        if (!startLoc) {
            cout << "\n[ERROR] Could not find start location.\n";
            waitForEnter();
            return;
        }

        if (!endLoc) {
            cout << "\n[ERROR] Could not find end location.\n";
            waitForEnter();
            return;
        }

        locationMgr.addTemporaryEdge(startLoc, endLoc);

        if (emergencyMode) {
            cout << "\n[EMERGENCY] Calculating fastest route...\n";
            cout << "[EMERGENCY] Priority lanes activated!\n";
        }
        else {
            cout << "\n[INFO] Calculating shortest path...\n";
        }

        PathNode* path = locationMgr.findShortestPath(startLoc, endLoc, emergencyMode);

        if (!path) {
            cout << "\n[ERROR] No path found!\n";
            locationMgr.removeTemporaryEdge(startLoc, endLoc);
            waitForEnter();
            return;
        }

        locationMgr.addPathEdgesToVisualization(path);

        cout << "\n===========================================\n";
        if (emergencyMode) {
            cout << "      EMERGENCY PATH FOUND                 \n";
            cout << "===========================================\n";
            cout << "[!] EMERGENCY ROUTE - PRIORITY ACCESS [!]\n";
        }
        else {
            cout << "      SHORTEST PATH FOUND                  \n";
            cout << "===========================================\n";
        }
        cout << "From: " << startLoc->name << " [" << startLoc->type << "]\n";
        cout << "      (" << startLoc->x << ", " << startLoc->y << ")\n";
        cout << "To:   " << endLoc->name << " [" << endLoc->type << "]\n";
        cout << "      (" << endLoc->x << ", " << endLoc->y << ")\n";

        if (emergencyMode) {
            cout << "Emergency Distance: " << endLoc->minDist << " units (60% faster)\n";
            cout << "Normal Distance: " << (endLoc->minDist * 1.67f) << " units\n";
        }
        else {
            cout << "Distance: " << endLoc->minDist << " units\n";
        }
        cout << "\n";

        cout << "===========================================\n";
        cout << "                  ROUTE                    \n";
        cout << "===========================================\n";
        int step = 1;
        PathNode* current = path;

        while (current) {
            Location* loc = current->loc;

            cout << "Step " << step << ": " << loc->name;

            if (loc->type == "Intersection") cout << " [Intersection]";
            else if (loc->type == "Hospital") cout << " [Hospital]";
            else if (loc->type == "School") cout << " [School]";
            else if (loc->type == "Mall") cout << " [Mall]";
            else if (loc->type == "Bus Stop") cout << " [Bus Stop]";
            else if (loc->type == "House") cout << " [House]";
            else if (loc->type == "Pharmacy") cout << " [Pharmacy]";
            else cout << " [" << loc->type << "]";

            cout << "\n       Location: (" << loc->x << ", " << loc->y << ")";

            if (current->next) {
                float segmentDist = current->next->loc->minDist - loc->minDist;
                cout << "\n       -> Distance: " << segmentDist << " units";
                if (emergencyMode) {
                    cout << " [PRIORITY LANE]";
                }
                cout << "\n";
            }
            else {
                cout << "\n       [DESTINATION]\n";
            }

            cout << "-------------------------------------------\n";

            current = current->next;
            step++;
        }

        cout << "\n[SUCCESS] Total Steps: " << (step - 1) << "\n";
        if (emergencyMode) {
            cout << "[SUCCESS] Emergency Distance: " << endLoc->minDist << " units\n";
            cout << "[SUCCESS] Time Saved: ~40% faster than normal route\n";
        }
        else {
            cout << "[SUCCESS] Total Distance: " << endLoc->minDist << " units\n";
        }
        cout << "===========================================\n";

        cout << "\nVisualize path? (y/n): ";
        string visualize;
        getline(cin, visualize);

        if (visualize == "y" || visualize == "Y") {
            visualizeShortestPath(path);
        }

        locationMgr.removePathEdgesFromVisualization(path);

        while (path) {
            PathNode* temp = path;
            path = path->next;
            delete temp;
        }

        locationMgr.removeTemporaryEdge(startLoc, endLoc);
        waitForEnter();
    }


    void visualizeShortestPath(PathNode* path) {
        if (!path) return;

        system("cls");
        cout << "\n===========================================\n";
        cout << "      PATH VISUALIZATION                   \n";
        cout << "===========================================\n";
        cout << "Press ENTER to start...\n";
        cin.get();

        Location* pathHead = nullptr;
        Location* pathTail = nullptr;

        PathNode* current = path;
        while (current) {
            Location* locCopy = new Location(
                current->loc->x,
                current->loc->y,
                current->loc->name,
                current->loc->type
            );

            if (!pathHead) {
                pathHead = locCopy;
                pathTail = locCopy;
            }
            else {
                pathTail->next = locCopy;
                pathTail = locCopy;
            }

            current = current->next;
        }

        cityVisualizer.removeLocationHead();
        cityVisualizer.setLocationHead(pathHead);
        cityVisualizer.setSectorPopHead(nullptr);

        cityVisualizer.run();

        while (pathHead) {
            Location* temp = pathHead;
            pathHead = pathHead->next;
            delete temp;
        }

        cout << "\nVisualizer closed.\n";
    }

    void searchForLocation() {
        system("cls");
        cout << "\n===========================================\n";
        cout << "      LOCATION SEARCH                      \n";
        cout << "===========================================\n";

        cout << "Enter search term: ";
        string searchTerm;
        cin.ignore();
        getline(cin, searchTerm);

        locationMgr.searchLocations(searchTerm);

        cout << "\n===========================================\n";
        cout << "1. Search again\n";
        cout << "2. Find path from location\n";
        cout << "3. View location types\n";
        cout << "0. Return to main menu\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            searchForLocation();
            break;
        case 2:
            findShortestPathBetweenLocations();
            break;
        case 3:
            displayLocationTypes();
            break;
        default:
            break;
        }
    }

    void displayLocationTypes() {
        system("cls");
        cout << "\n===========================================\n";
        cout << "      LOCATION TYPES IN CITY               \n";
        cout << "===========================================\n";

        int counts[10] = { 0 };
        string types[] = { "Intersection", "Hospital", "School", "Mall",
                         "Bus Stop", "House", "Pharmacy", "Mosque", "Park", "Water Cooler" };

        Location* temp = locationMgr.getHead();
        while (temp) {
            for (int i = 0; i < 10; i++) {
                if (temp->type == types[i]) {
                    counts[i]++;
                    break;
                }
            }
            temp = temp->next;
        }

        cout << "\nLocation Statistics:\n";
        cout << "-------------------------------------------\n";
        for (int i = 0; i < 10; i++) {
            if (counts[i] > 0) {
                cout << types[i] << ": " << counts[i] << "\n";
            }
        }
        cout << "===========================================\n";

        waitForEnter();
    }

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
        cout << "9. Search for a Location\n";
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
        cout << "17. Display All Hospitals\n";
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
        cout << "  - Press 'H': Toggle heatmap mode\n";
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
        cout << "\nNote: Showing only " << systemName << " locations.\n";
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

    void runTransportSystem() { /* Keep existing */ }
    void runCommercialSystem() { /* Keep existing */ }
    void runEducationSystem() { /* Keep existing */ }
    void runMedicalSystem() { /* Keep existing */ }
    void runFacilitySystem() { /* Keep existing */ }
    void runPopulationSystem() { /* Keep existing */ }

    void simulateBasedOnMainChoice(int ch)
    {
        int choice = ch;

        if (choice == 7) {
            runVisualization();
            return;
        }

        if (choice == 8) {
            findShortestPathBetweenLocations();
            return;
        }

        if (choice == 9) {
            searchForLocation();
            return;
        }

        system("cls");
        int inputMethod = showDataInputMenu();
        cin.ignore();

        if (inputMethod == 0) {
            return;
        }
        else if (inputMethod == 1)
        {
            cout << "\n=== Loading data from CSV files ===\n";

            switch (choice)
            {
            case 1:
                cout << "[ERROR] CSV loading not available for Commercial.\n";
                break;
            case 2:
                loadSchoolsFromCSV();
                csvDataLoaded = true;
                break;
            case 3:
                loadHospitalsFromCSV();
                loadPharmaciesFromCSV();
                csvDataLoaded = true;
                break;
            case 4:
                loadCitizensFromCSV();
                csvDataLoaded = true;
                break;
            case 5:
                loadBusStopsFromCSV();
                loadBusesFromCSV();
                csvDataLoaded = true;
                break;
            case 6:
                cout << "[ERROR] CSV loading not available for Facility.\n";
                break;
            default:
                cout << "Invalid choice.\n";
                break;
            }

            cout << "\n[SUCCESS] Data loading completed!\n";
            waitForEnter();
        }

        switch (choice)
        {
        case 1: runCommercialSystem(); break;
        case 2: runEducationSystem(); break;
        case 3: runMedicalSystem(); break;
        case 4: runPopulationSystem(); break;
        case 5: runTransportSystem(); break;
        case 6: runFacilitySystem(); break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }

public:
    CityManager() : education(20), csvDataLoaded(false)
    {
        cout << "[SUCCESS] City Manager initialized!\n";
    }

    ~CityManager() {}

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

#endif

