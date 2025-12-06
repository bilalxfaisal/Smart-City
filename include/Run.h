#pragma once
#include "../Smart-City-DS-Project/include/transport/TransportSystem.h" 
#include "../Smart-City-DS-Project/include/commercial/CommercialSystem.h"
#include "../Smart-City-DS-Project/include/education/EducationSystem.h"
#include "../Smart-City-DS-Project/include/medical/MedicalSystem.h"
#include "../Smart-City-DS-Project/include/facilities/FacilitySystem.h"
#include "../Smart-City-DS-Project/include/population/PopulationSystem.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void waitForEnter()
{
    cout << "\nPress ENTER to continue...\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// FUNCTION DECLARATIONS

void runTheCitySystem();
void showMainMenu(int& choice);
int showTransportMenu();
int showCommercialMenu();
int showEducationMenu();
int showMedicalSystemMenu();
int showFacilityMenu();
int showPopulationMenu();
void simulateBasedOnMainChoice(int ch);
void runTransportSystem(TransportSystem&);
void runCommercialSystem(CommercialSystem&);
void runEducationSystem(EducationSystem&);
void runMedicalSystem(MedicalSystem&);
void runFacilitySystem(FacilitySystem&);
void runPopulationSystem(PopulationSystem&);

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

// FUNCION DEFINITIONS

void runTheCitySystem()
{
    int mainMenuCh = 0;
    do {
        system("cls");
        showMainMenu(mainMenuCh);
        if (mainMenuCh != 0) {
            simulateBasedOnMainChoice(mainMenuCh);
        }
    } while (mainMenuCh != 0);
	cout << "Exiting Smart City System. Goodbye!\n";
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
    cout << "6. Public Facility\n";
    cout << "0. Exit to main menu\n";
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
    cout << "9. Display Memebers of a House\n";
	cout << "10. Display Houses in a Street\n";
    cout << "0. Exit to main menu\n";
    cout << "Enter choice: ";
    cin >> ch;
    return ch;
}

void simulateBasedOnMainChoice(int ch)
{
    CommercialSystem commercial;
    TransportSystem transport;
    EducationSystem education(20);
    MedicalSystem medical;
    FacilitySystem facility;
	PopulationSystem population;

    int choice = ch;

    switch (choice)
    {
	    case 1: // Commercial System
        {
            runCommercialSystem(commercial);
            break;
        }
	    case 2: // Education System
        {
            runEducationSystem(education);
            break;
        }
	    case 3: // Medical System
        {
            runMedicalSystem(medical);
            break;
        }
	    case 4: // Population System
        {
            runPopulationSystem(population);
            break;
        }
	    case 5: // Transport System
        {
            runTransportSystem(transport);
            break;
        }
	    case 6: // Public Facility
        {
            runFacilitySystem(facility);
            break;
        }
        default:
        {
            cout << "Invalid choice. Exiting...\n";
            break;
        }
    }
}

void runEducationSystem(EducationSystem& education)
{
    while (true)
    {
        system("cls");

        int choice = showEducationMenu();
        cin.ignore();

        if (choice == 0)
        {
            cout << "Exiting...\n";
            break;
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
            education.addSchool(school);
            cout << "School '" << name << "' added succesfully !";
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
                cout << "Department '" << deptName << "' successfully added in school with ID '" << schoolID << "' ! ";
            else
                cout << "Error! Department '" << deptName << "' can't be added !";
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
                cout << "Faculty Member '" << facName << "' successfullty added in school with ID '" << schoolID << "' !";
            else
                cout << "Error! Faculty Member '" << facName << "' can't be added !";
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
                cout << "Class '" << className << "' successfullty added in school with ID '" << schoolID << "' !";
            else
                cout << "Error! Class '" << className << "' can't be added !";
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
                cout << "Student '" << name << "' successfullty added in Class 'with ID " << classID << "' !";
            else
                cout << "Error! Student '" << name << "' can't be added !";
            break;
        }
        case 6: // Add Subject
        {
            cout << "\n=== Add Subject ===\n";
            string schoolID = readLine("Enter School ID: ");
            string name = readLine("Enter Subject name: ");
            if (education.addSubject(schoolID, name))
                cout << "Subject '" << name << "' successfullty added in School with ID '" << schoolID << "' !";
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
                cout << "Student with Name '" << name << "' removed successfully !";
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
                cout << "Student with ID '" << id << "' removed successfully !";
            break;
        }
        case 9: // Remove Faculty
        {
            cout << "\n=== Remove Faculty Member ===\n";
            string schoolID = readLine("Enter School ID: ");
            string facName = readLine("Enter Faculty Member name: ");
            if (education.removeFacultyByName(schoolID, facName))
                cout << "Faculty Member '" << facName << "' removed successfully !";
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
        default:
            break;
        }
        waitForEnter();
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


void runMedicalSystem(MedicalSystem& medical)
{
    while (true)
    {
        system("cls");

        int choice = showMedicalSystemMenu();
        cin.ignore();

        if (choice == 0)
        {
            cout << "Exiting Medical System...\n";
            break;
        }

        switch (choice)
        {
        case 1: // Add Hospital
        {
            cout << "\n=== Add Hospital ===\n";
            string name = readLine("Enter hospital name: ");
            string id = readLine("Enter hospital ID: ");
            string sec = readLine("Enter sector: ");
            int bedNum = readInt("Enter number of beds: ");
            Hospital hospital(name, id, sec, bedNum);
            medical.addHospital(hospital);
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
            string location = readLine("Enter pharmacy location: ");
            string id = readLine("Enter pharmacy id: ");
            string loc = readLine("Enter location: ");
            Pharmacy pharmacy(name, loc, id);
            medical.addPharmacy(pharmacy);
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
            float price = readFloat("Enter medicine quantity: ");
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

        default:
            cout << "\nInvalid choice! Try again.\n";
            break;
        }

        waitForEnter();
    }
}

void runFacilitySystem(FacilitySystem& facility)
{
    while (true)
    {
        system("cls");
        int choice = showFacilityMenu();
        cin.ignore();

        if (choice == 0)
        {
            cout << "Exiting Facility System...\n";
            break;
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
void runPopulationSystem(PopulationSystem& population)
{
    while (true)
    {
        system("cls");
        int choice = showPopulationMenu();
        cin.ignore();

        if (choice == 0)
        {
            cout << "Exiting Population System...\n";
            break;
        }
        switch (choice)
        {
        case 1: // Add Sector
        {
            cout << "\n=== Add Sector ===\n";
            string name = readLine("Enter sector name: ");
            Sector sector(name);
            population.addSector(sector);
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
        default:
            cout << "\nInvalid choice! Try again.\n";
            break;
        }
        waitForEnter();
    }
}
