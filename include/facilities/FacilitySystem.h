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

    // Helper: Add mosque location to linked list (with duplicate check)
    void addMosqueLocationToList(Location& mosqueLocation) {
        Location* temp = mosqueLocationHead;
        while (temp) {
            if (temp == &mosqueLocation) return;
            temp = temp->next;
        }
        mosqueLocation.next = mosqueLocationHead;
        mosqueLocationHead = &mosqueLocation;
    }

    // Helper: Remove mosque location from linked list
    void removeMosqueLocationFromList(Location& mosqueLocation) {
        if (!mosqueLocationHead) return;
        if (mosqueLocationHead == &mosqueLocation) {
            mosqueLocationHead = mosqueLocationHead->next;
            mosqueLocation.next = nullptr;
            return;
        }
        Location* temp = mosqueLocationHead;
        while (temp->next) {
            if (temp->next == &mosqueLocation) {
                temp->next = mosqueLocation.next;
                mosqueLocation.next = nullptr;
                return;
            }
            temp = temp->next;
        }
    }

    // Helper: Add park location to linked list (with duplicate check)
    void addParkLocationToList(Location& parkLocation) {
        Location* temp = parkLocationHead;
        while (temp) {
            if (temp == &parkLocation) return;
            temp = temp->next;
        }
        parkLocation.next = parkLocationHead;
        parkLocationHead = &parkLocation;
    }

    // Helper: Remove park location from linked list
    void removeParkLocationFromList(Location& parkLocation) {
        if (!parkLocationHead) return;
        if (parkLocationHead == &parkLocation) {
            parkLocationHead = parkLocationHead->next;
            parkLocation.next = nullptr;
            return;
        }
        Location* temp = parkLocationHead;
        while (temp->next) {
            if (temp->next == &parkLocation) {
                temp->next = parkLocation.next;
                parkLocation.next = nullptr;
                return;
            }
            temp = temp->next;
        }
    }

    // Helper: Add cooler location to linked list (with duplicate check)
    void addCoolerLocationToList(Location& coolerLocation) {
        Location* temp = coolerLocationHead;
        while (temp) {
            if (temp == &coolerLocation) return;
            temp = temp->next;
        }
        coolerLocation.next = coolerLocationHead;
        coolerLocationHead = &coolerLocation;
    }

    // Helper: Remove cooler location from linked list
    void removeCoolerLocationFromList(Location& coolerLocation) {
        if (!coolerLocationHead) return;
        if (coolerLocationHead == &coolerLocation) {
            coolerLocationHead = coolerLocationHead->next;
            coolerLocation.next = nullptr;
            return;
        }
        Location* temp = coolerLocationHead;
        while (temp->next) {
            if (temp->next == &coolerLocation) {
                temp->next = coolerLocation.next;
                coolerLocation.next = nullptr;
                return;
            }
            temp = temp->next;
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

    // Getters for location heads (for visualization)
    Location* getMosqueLocationHead() const { return mosqueLocationHead; }
    Location* getParkLocationHead() const { return parkLocationHead; }
    Location* getCoolerLocationHead() const { return coolerLocationHead; }
};

#endif // !FACILITYSYSTEM_H