#include "../utils/Nodes.h"
#include <string>
using namespace std;

#ifndef PUBLICFACILITY_H
#define PUBLICFACILITY_H

// Base struct with all common functionality
struct PublicFacility {
	Location location;
	string name;

	// Constructors
	PublicFacility() : location(), name("") {}
	PublicFacility(const Location& loc, const string& n) : location(loc), name(n) {}

	// Copy Constructor
	PublicFacility(const PublicFacility& other) : location(other.location), name(other.name) {}

	// Copy Assignment Operator
	PublicFacility& operator=(const PublicFacility& other) {
		if (this != &other) {
			location = other.location;
			name = other.name;
		}
		return *this;
	}
	// Display function
	virtual void display() const {
		cout << "Public Facility: " << name << " at ";
		location.display(); // Assuming location has a display method
	}
	// Destructor
	virtual ~PublicFacility() {}

	// Getters
	Location getLocation() const { return location; }
	string getName() const { return name; }

	// Setters
	void setLocation(const Location& loc) { location = loc; }
	void setName(const string& n) { name = n; }

	// Display function (virtual for derived classes to override)
	virtual void display() const {
		cout << "Public Facility: " << name << " at ";
		location.display();
	}
};

// Derived structs
struct Mosque : public PublicFacility
{
	// Constructors
	Mosque* next = nullptr; // For chaining in hash table
	Mosque() : PublicFacility() {}
	Mosque(const Location& loc, const string& n) : PublicFacility(loc, n) {}

	// Override display
	void display() const override {
		cout << "Mosque: " << name << " at ";
		location.display();
	}
	void display() const override {
		cout << "Mosque: " << name << " at ";
		location.display();
	}
};

struct Park : public PublicFacility 
{
	// Constructors
	Park* next = nullptr; // For chaining in hash table
	Park() : PublicFacility() {}
	Park(const Location& loc, const string& n) : PublicFacility(loc, n) {}

	// Override display
	void display() const override {
		cout << "Park: " << name << " at ";
		location.display();
	}
	void display() const override {
		cout << "Park: " << name << " at ";
		location.display();
	}
};

struct WaterCooler : public PublicFacility {
	// Constructors
	WaterCooler* next = nullptr; // For chaining in hash table
	WaterCooler() : PublicFacility() {}
	WaterCooler(const Location& loc, const string& n) : PublicFacility(loc, n) {}

	// Override display
	void display() const override {
		cout << "Water Cooler: " << name << " at ";
		location.display();
	}
	void display() const override 
	{
		cout << "Water Cooler: " << name << " at ";
		location.display();
	}
};

#endif // !PUBLICFACILITY_H
