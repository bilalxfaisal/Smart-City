#include "PublicFacility.h"
#include "../utils/Nodes.h"
#ifndef FACILITYSYSTEM_H
#define FACILITYSYSTEM_H
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class FacilitySystem
{
private:
    Mosque** mosquesTable;
    int mosqueCount;
    int mosqueTableSize;

    Park** parksTable;
    int parkCount;
    int parkTableSize;

    WaterCooler** coolersTable;
    int coolerCount;
    int coolerTableSize;

    // Location linked lists for visualization
    Location* mosqueLocationHead = nullptr;
    Location* parkLocationHead = nullptr;
    Location* coolerLocationHead = nullptr;

    // === ADD FUNCTIONS (allocate new nodes) ===
    void addMosqueLocationToList(const Location& loc) {
        // Prevent duplicates by coordinates
        for (Location* temp = mosqueLocationHead; temp; temp = temp->next) {
            if (temp->x == loc.x && temp->y == loc.y) return;
        }
        Location* newNode = new Location(loc);      // deep copy on heap
        newNode->next = mosqueLocationHead;
        mosqueLocationHead = newNode;
    }

    void addParkLocationToList(const Location& loc) {
        for (Location* temp = parkLocationHead; temp; temp = temp->next) {
            if (temp->x == loc.x && temp->y == loc.y) return;
        }
        Location* newNode = new Location(loc);
        newNode->next = parkLocationHead;
        parkLocationHead = newNode;
    }

    void addCoolerLocationToList(const Location& loc) {
        for (Location* temp = coolerLocationHead; temp; temp = temp->next) {
            if (temp->x == loc.x && temp->y == loc.y) return;
        }
        Location* newNode = new Location(loc);
        newNode->next = coolerLocationHead;
        coolerLocationHead = newNode;
    }

    // === REMOVE FUNCTIONS (delete our own node, not the original) ===
    void removeMosqueLocationFromList(const Location& loc) {
        if (!mosqueLocationHead) return;

        if (mosqueLocationHead->x == loc.x && mosqueLocationHead->y == loc.y) {
            Location* toDelete = mosqueLocationHead;
            mosqueLocationHead = mosqueLocationHead->next;
            delete toDelete;
            return;
        }

        Location* curr = mosqueLocationHead;
        while (curr->next) {
            if (curr->next->x == loc.x && curr->next->y == loc.y) {
                Location* toDelete = curr->next;
                curr->next = curr->next->next;
                delete toDelete;
                return;
            }
            curr = curr->next;
        }
    }

    void removeParkLocationFromList(const Location& loc) {
        if (!parkLocationHead) return;

        if (parkLocationHead->x == loc.x && parkLocationHead->y == loc.y) {
            Location* toDelete = parkLocationHead;
            parkLocationHead = parkLocationHead->next;
            delete toDelete;
            return;
        }

        Location* curr = parkLocationHead;
        while (curr->next) {
            if (curr->next->x == loc.x && curr->next->y == loc.y) {
                Location* toDelete = curr->next;
                curr->next = curr->next->next;
                delete toDelete;
                return;
            }
            curr = curr->next;
        }
    }

    void removeCoolerLocationFromList(const Location& loc) {
        if (!coolerLocationHead) return;

        if (coolerLocationHead->x == loc.x && coolerLocationHead->y == loc.y) {
            Location* toDelete = coolerLocationHead;
            coolerLocationHead = coolerLocationHead->next;
            delete toDelete;
            return;
        }

        Location* curr = coolerLocationHead;
        while (curr->next) {
            if (curr->next->x == loc.x && curr->next->y == loc.y) {
                Location* toDelete = curr->next;
                curr->next = curr->next->next;
                delete toDelete;
                return;
            }
            curr = curr->next;
        }
    }

public:
    FacilitySystem() {
        mosqueCount = 0;
        mosqueTableSize = 100;
        mosquesTable = new Mosque * [mosqueTableSize]();
        for (int i = 0; i < mosqueTableSize; i++) {
            mosquesTable[i] = nullptr;
        }

        parkCount = 0;
        parkTableSize = 100;
        parksTable = new Park * [parkTableSize]();
        for (int i = 0; i < parkTableSize; i++) {
            parksTable[i] = nullptr;
        }

        coolerCount = 0;
        coolerTableSize = 100;
        coolersTable = new WaterCooler * [coolerTableSize]();
        for (int i = 0; i < coolerTableSize; i++) {
            coolersTable[i] = nullptr;
        }
    }

    // Destructor
    ~FacilitySystem() {
        for (int i = 0; i < mosqueTableSize; i++) {
            Mosque* current = mosquesTable[i];
            while (current != nullptr) {
                Mosque* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] mosquesTable;

        for (int i = 0; i < parkTableSize; i++) {
            Park* current = parksTable[i];
            while (current != nullptr) {
                Park* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] parksTable;

        for (int i = 0; i < coolerTableSize; i++) {
            WaterCooler* current = coolersTable[i];
            while (current != nullptr) {
                WaterCooler* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] coolersTable;
    }

    // Resize functions
    void resizeMosqueTable() {
        int newSize = mosqueTableSize * 2;
        Mosque** newTable = new Mosque * [newSize]();
        for (int i = 0; i < newSize; i++) {
            newTable[i] = nullptr;
        }

        for (int i = 0; i < mosqueTableSize; i++) {
            Mosque* current = mosquesTable[i];
            while (current != nullptr) {
                Mosque* nextMosque = current->next;
                int index = Polynomial_Rolling_Hash_V1(current->getName()) % newSize;
                if (newTable[index]) {
                    current->next = newTable[index];
                    newTable[index] = current;
                }
                else {
                    current->next = nullptr;
                    newTable[index] = current;
                }
                current = nextMosque;
            }
        }
        delete[] mosquesTable;
        mosquesTable = newTable;
        mosqueTableSize = newSize;
    }

    void resizeParkTable() {
        int newSize = parkTableSize * 2;
        Park** newTable = new Park * [newSize]();
        for (int i = 0; i < newSize; i++) {
            newTable[i] = nullptr;
        }

        for (int i = 0; i < parkTableSize; i++) {
            Park* current = parksTable[i];
            while (current != nullptr) {
                Park* nextPark = current->next;
                int index = Polynomial_Rolling_Hash_V1(current->getName()) % newSize;
                if (newTable[index]) {
                    current->next = newTable[index];
                    newTable[index] = current;
                }
                else {
                    current->next = nullptr;
                    newTable[index] = current;
                }
                current = nextPark;
            }
        }
        delete[] parksTable;
        parksTable = newTable;
        parkTableSize = newSize;
    }

    void resizeCoolerTable() {
        int newSize = coolerTableSize * 2;
        WaterCooler** newTable = new WaterCooler * [newSize]();
        for (int i = 0; i < newSize; i++) {
            newTable[i] = nullptr;
        }

        for (int i = 0; i < coolerTableSize; i++) {
            WaterCooler* current = coolersTable[i];
            while (current != nullptr) {
                WaterCooler* nextCooler = current->next;
                int index = Polynomial_Rolling_Hash_V1(current->getName()) % newSize;
                if (newTable[index]) {
                    current->next = newTable[index];
                    newTable[index] = current;
                }
                else {
                    current->next = nullptr;
                    newTable[index] = current;
                }
                current = nextCooler;
            }
        }
        delete[] coolersTable;
        coolersTable = newTable;
        coolerTableSize = newSize;
    }

    // Add functions
    bool addMosque(Mosque& m) {
        Mosque* toAdd = new Mosque(m);
        addMosqueLocationToList(toAdd->getLocation());
        int index = Polynomial_Rolling_Hash_V1(toAdd->getName()) % mosqueTableSize;

        if (mosquesTable[index]) {
            toAdd->next = mosquesTable[index];
            mosquesTable[index] = toAdd;
        }
        else {
            mosquesTable[index] = toAdd;
            mosqueCount++;
        }
        return true;
    }

    bool addPark(Park& p) {
        Park* toAdd = new Park(p);
        addParkLocationToList(toAdd->getLocation());
        int index = Polynomial_Rolling_Hash_V1(toAdd->getName()) % parkTableSize;

        if (parksTable[index]) {
            toAdd->next = parksTable[index];
            parksTable[index] = toAdd;
        }
        else {
            parksTable[index] = toAdd;
            parkCount++;
        }
        return true;
    }

    bool addWaterCooler(WaterCooler& w) {
        WaterCooler* toAdd = new WaterCooler(w);
        addCoolerLocationToList(toAdd->getLocation());
        int index = Polynomial_Rolling_Hash_V1(toAdd->getName()) % coolerTableSize;

        if (coolersTable[index]) {
            toAdd->next = coolersTable[index];
            coolersTable[index] = toAdd;
        }
        else {
            coolersTable[index] = toAdd;
            coolerCount++;
        }
        return true;
    }
    void displayAllMosques() const {
        cout << "\n=== All Mosques ===" << endl;
        for (int i = 0; i < mosqueTableSize; i++) {
            Mosque* current = mosquesTable[i];
            while (current != nullptr) {
                current->display();
                cout << endl;
                current = current->next; // Move to next mosque
            }
        }
    }

    void displayAllParks() const {
        cout << "\n=== All Parks ===" << endl;
        for (int i = 0; i < parkTableSize; i++) {
            Park* current = parksTable[i];
            while (current != nullptr) {
                current->display();
                cout << endl;
                current = current->next; // Move to next park
            }
        }
    }

    void displayAllWaterCoolers() const {
        cout << "\n=== All Water Coolers ===" << endl;
        for (int i = 0; i < coolerTableSize; i++) {
            WaterCooler* current = coolersTable[i];
            while (current != nullptr) {
                current->display();
                cout << endl;
                current = current->next; // Move to next cooler
            }
        }
    }

    void display() const 
    {
        displayAllMosques();
        displayAllParks();
        displayAllWaterCoolers();
    }
    // Delete functions
    void deleteMosque(const string& name) {
        int index = Polynomial_Rolling_Hash_V1(name) % mosqueTableSize;

        if (mosquesTable[index] == nullptr) return;

        Mosque* current = mosquesTable[index];
        Mosque* previous = nullptr;

        while (current != nullptr) {
            if (current->getName() == name) {
                removeMosqueLocationFromList(current->getLocation());
                if (previous == nullptr) {
                    mosquesTable[index] = current->next;
                }
                else {
                    previous->next = current->next;
                }
                delete current;
                mosqueCount--;
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "\nMosque not found." << endl;
    }

    void deletePark(const string& name) {
        int index = Polynomial_Rolling_Hash_V1(name) % parkTableSize;

        if (parksTable[index] == nullptr) return;

        Park* current = parksTable[index];
        Park* previous = nullptr;

        while (current != nullptr) {
            if (current->getName() == name) {
                removeParkLocationFromList(current->getLocation());
                if (previous == nullptr) {
                    parksTable[index] = current->next;
                }
                else {
                    previous->next = current->next;
                }
                delete current;
                parkCount--;
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "\nPark not found." << endl;
    }

    void deleteWaterCooler(const string& name) {
        int index = Polynomial_Rolling_Hash_V1(name) % coolerTableSize;

        if (coolersTable[index] == nullptr) return;

        WaterCooler* current = coolersTable[index];
        WaterCooler* previous = nullptr;

        while (current != nullptr) {
            if (current->getName() == name) {
                removeCoolerLocationFromList(current->getLocation());
                if (previous == nullptr) {
                    coolersTable[index] = current->next;
                }
                else {
                    previous->next = current->next;
                }
                delete current;
                coolerCount--;
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "\nWater Cooler not found." << endl;
    }

    // Find functions
    Mosque* findMosque(const string& name) {
        int index = Polynomial_Rolling_Hash_V1(name) % mosqueTableSize;
        Mosque* current = mosquesTable[index];

        while (current != nullptr) {
            if (current->getName() == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Park* findPark(const string& name) {
        int index = Polynomial_Rolling_Hash_V1(name) % parkTableSize;
        Park* current = parksTable[index];

        while (current != nullptr) {
            if (current->getName() == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    WaterCooler* findWaterCooler(const string& name) {
        int index = Polynomial_Rolling_Hash_V1(name) % coolerTableSize;
        WaterCooler* current = coolersTable[index];

        while (current != nullptr) {
            if (current->getName() == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Display functions
    void displayAllMosques() {
        cout << "\n=== All Mosques ===" << endl;
        for (int i = 0; i < mosqueTableSize; i++) {
            Mosque* current = mosquesTable[i];
            while (current != nullptr) {
                current->display();
                cout << endl;
                current = current->next;
            }
        }
    }

    void displayAllParks() {
        cout << "\n=== All Parks ===" << endl;
        for (int i = 0; i < parkTableSize; i++) {
            Park* current = parksTable[i];
            while (current != nullptr) {
                current->display();
                cout << endl;
                current = current->next;
            }
        }
    }

    void displayAllWaterCoolers() {
        cout << "\n=== All Water Coolers ===" << endl;
        for (int i = 0; i < coolerTableSize; i++) {
            WaterCooler* current = coolersTable[i];
            while (current != nullptr) {
                current->display();
                cout << endl;
                current = current->next;
            }
        }
    }

    void displayAllFacilities() {
        displayAllMosques();
        displayAllParks();
        displayAllWaterCoolers();
    }

    // Getters for counts
    int getMosqueCount() const { return mosqueCount; }
    int getParkCount() const { return parkCount; }
    int getCoolerCount() const { return coolerCount; }
};

#endif // !FACILITYSYSTEM_H