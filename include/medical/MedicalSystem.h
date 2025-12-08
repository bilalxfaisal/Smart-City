#include "../utils/Nodes.h"
#include "Hospital.h"
#include "Pharmacy.h"
#ifndef MEDICALSYSTEM_H
#define	MEDICALSYSTEM_H
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class MedicalSystem
{
	int hospitalCount;
	int hospitalTableSize;
	Hospital** hospitalsTable;

	//Max heap
	MaxHeap hospitalHeap = MaxHeap(100, compareHospitals);

	int pharmaciesCount;
	int pharmaciesTableSize;
	Pharmacy** pharmaciesTable;

	Location* hospitalLocationHead = nullptr;
	Location* pharmacyLocationHead = nullptr;
	// Helper: Add hospital location to linked list (with duplicate check)
	void addHospitalLocationToList(Location& hospitalLocation) {
		// Check if already in list
		Location* temp = hospitalLocationHead;
		while (temp) {
			if (temp == &hospitalLocation) {
				return; // Already exists
			}
			temp = temp->next;
		}

		// Add to head (O(1) operation)
		hospitalLocation.next = hospitalLocationHead;
		hospitalLocationHead = &hospitalLocation;
	}

	// Helper: Remove hospital location from linked list
	void removeHospitalLocationFromList(Location& hospitalLocation) {
		if (!hospitalLocationHead) return;

		// Check if it's the head
		if (hospitalLocationHead == &hospitalLocation) {
			hospitalLocationHead = hospitalLocationHead->next;
			hospitalLocation.next = nullptr;
			return;
		}

		// Search for the location
		Location* temp = hospitalLocationHead;
		while (temp->next) {
			if (temp->next == &hospitalLocation) {
				temp->next = hospitalLocation.next;
				hospitalLocation.next = nullptr;
				return;
			}
			temp = temp->next;
		}
	}

	// Helper: Add pharmacy location to linked list (with duplicate check)
	void addPharmacyLocationToList(Location& pharmacyLocation) {
		// Check if already in list
		Location* temp = pharmacyLocationHead;
		while (temp) {
			if (temp == &pharmacyLocation) {
				return; // Already exists
			}
			temp = temp->next;
		}

		// Add to head (O(1) operation)
		pharmacyLocation.next = pharmacyLocationHead;
		pharmacyLocationHead = &pharmacyLocation;
	}

	// Helper: Remove pharmacy location from linked list
	void removePharmacyLocationFromList(Location& pharmacyLocation) {
		if (!pharmacyLocationHead) return;

		// Check if it's the head
		if (pharmacyLocationHead == &pharmacyLocation) {
			pharmacyLocationHead = pharmacyLocationHead->next;
			pharmacyLocation.next = nullptr;
			return;
		}

		// Search for the location
		Location* temp = pharmacyLocationHead;
		while (temp->next) {
			if (temp->next == &pharmacyLocation) {
				temp->next = pharmacyLocation.next;
				pharmacyLocation.next = nullptr;
				return;
			}
			temp = temp->next;
		}
	}

public:
	MedicalSystem() {
		hospitalCount = 0;
		hospitalTableSize = 100;
		hospitalsTable = new Hospital * [hospitalTableSize]();
		for (int i = 0; i < hospitalTableSize; i++) {
			hospitalsTable[i] = nullptr;
		}
		pharmaciesCount = 0;
		pharmaciesTableSize = 100;
		pharmaciesTable = new Pharmacy * [pharmaciesTableSize]();
		for (int i = 0; i < pharmaciesTableSize; i++) {
			pharmaciesTable[i] = nullptr;
		}
	}

	// Add to MedicalSystem class public section:

	void connectMedicalSubgraph() {
		cout << "\n[INFO] Connecting medical facilities subgraph...\n";

		int connectedCount = 0;

		// Connect hospitals to nearby hospitals
		Location* h1 = hospitalLocationHead;
		while (h1) {
			Location* h2 = hospitalLocationHead;
			while (h2) {
				if (h1 != h2) {
					float dist = sqrt(
						pow(h2->x - h1->x, 2) +
						pow(h2->y - h1->y, 2)
					);

					if (dist < 250.0f && dist > 0) {
						bool edgeExists = false;
						Edge* e = h1->adjList;
						while (e) {
							if (e->destination == h2) {
								edgeExists = true;
								break;
							}
							e = e->nextEdge;
						}

						if (!edgeExists) {
							Edge* newEdge1 = new Edge(dist, h2);
							newEdge1->nextEdge = h1->adjList;
							h1->adjList = newEdge1;

							Edge* newEdge2 = new Edge(dist, h1);
							newEdge2->nextEdge = h2->adjList;
							h2->adjList = newEdge2;

							connectedCount++;
						}
					}
				}
				h2 = h2->next;
			}
			h1 = h1->next;
		}

		// Connect pharmacies to nearby pharmacies
		Location* p1 = pharmacyLocationHead;
		while (p1) {
			Location* p2 = pharmacyLocationHead;
			while (p2) {
				if (p1 != p2) {
					float dist = sqrt(
						pow(p2->x - p1->x, 2) +
						pow(p2->y - p1->y, 2)
					);

					if (dist < 150.0f && dist > 0) {
						bool edgeExists = false;
						Edge* e = p1->adjList;
						while (e) {
							if (e->destination == p2) {
								edgeExists = true;
								break;
							}
							e = e->nextEdge;
						}

						if (!edgeExists) {
							Edge* newEdge1 = new Edge(dist, p2);
							newEdge1->nextEdge = p1->adjList;
							p1->adjList = newEdge1;

							Edge* newEdge2 = new Edge(dist, p1);
							newEdge2->nextEdge = p2->adjList;
							p2->adjList = newEdge2;

							connectedCount++;
						}
					}
				}
				p2 = p2->next;
			}
			p1 = p1->next;
		}

		// Connect hospitals to nearby pharmacies
		h1 = hospitalLocationHead;
		while (h1) {
			Location* p = pharmacyLocationHead;
			while (p) {
				float dist = sqrt(
					pow(p->x - h1->x, 2) +
					pow(p->y - h1->y, 2)
				);

				if (dist < 180.0f && dist > 0) {
					bool edgeExists = false;
					Edge* e = h1->adjList;
					while (e) {
						if (e->destination == p) {
							edgeExists = true;
							break;
						}
						e = e->nextEdge;
					}

					if (!edgeExists) {
						Edge* newEdge1 = new Edge(dist, p);
						newEdge1->nextEdge = h1->adjList;
						h1->adjList = newEdge1;

						Edge* newEdge2 = new Edge(dist, h1);
						newEdge2->nextEdge = p->adjList;
						p->adjList = newEdge2;

						connectedCount++;
					}
				}
				p = p->next;
			}
			h1 = h1->next;
		}

		cout << "[SUCCESS] Connected " << connectedCount << " medical facility pairs.\n";
	}

	// Find shortest path between hospital and pharmacy
	PathNode* findPathToNearestPharmacy(string hospitalName) {
		// Find hospital
		int idx = Polynomial_Rolling_Hash_V1(hospitalName) % hospitalTableSize;
		Hospital* hosp = hospitalsTable[idx];

		while (hosp && hosp->getHospitalName() != hospitalName) {
			hosp = hosp->nextHospital;
		}

		if (!hosp) {
			cout << "[ERROR] Hospital not found.\n";
			return nullptr;
		}

		Location* start = &(hosp->getHospitalLocation());

		// Find nearest pharmacy using Dijkstra
		Location* allLocs = hospitalLocationHead;
		while (allLocs) {
			allLocs->minDist = std::numeric_limits<float>::max();
			allLocs->visited = false;
			allLocs->parent = nullptr;
			allLocs = allLocs->next;
		}

		allLocs = pharmacyLocationHead;
		while (allLocs) {
			allLocs->minDist = std::numeric_limits<float>::max();
			allLocs->visited = false;
			allLocs->parent = nullptr;
			allLocs = allLocs->next;
		}

		MinHeap pq(1000);
		start->minDist = 0;
		pq.push(start, 0);

		Location* nearestPharmacy = nullptr;
		float minPharmDist = std::numeric_limits<float>::max();

		while (!pq.isEmpty()) {
			Location* u = pq.extractMin();
			if (u->visited) continue;
			u->visited = true;

			// Check if this is a pharmacy
			if (u->type == "Pharmacy" && u->minDist < minPharmDist) {
				nearestPharmacy = u;
				minPharmDist = u->minDist;
			}

			Edge* e = u->adjList;
			while (e) {
				Location* v = e->destination;
				float weight = e->weight;
				if (!v->visited && u->minDist + weight < v->minDist) {
					v->minDist = u->minDist + weight;
					v->parent = u;
					pq.push(v, v->minDist);
				}
				e = e->nextEdge;
			}
		}

		if (!nearestPharmacy) {
			cout << "[ERROR] No pharmacy reachable from hospital.\n";
			return nullptr;
		}

		// Build path
		PathNode* pathHead = nullptr;
		Location* crawler = nearestPharmacy;
		while (crawler) {
			PathNode* newNode = new PathNode(crawler);
			newNode->next = pathHead;
			pathHead = newNode;
			crawler = crawler->parent;
		}

		return pathHead;
	}


	void display() const
	{
		cout << "=== Medical System ===" << endl;
		cout << "Total Hospitals: " << hospitalCount << endl;

		for (int i = 0; i < hospitalCount; i++) {
			if (hospitalsTable[i] != nullptr) {
				hospitalsTable[i]->display();  // Display each hospital
				cout << endl;
			}
		}
		cout << "==========================" << endl;
	}

	void addHospital(Hospital& h1);
	void removeHospital(const string& hospitalName);
	void addPharmacy(Pharmacy& p1);
	void removePharmacy(const string& pharmacyName);
	void addDoctorToHospital(const string& hospitalName, Doctor& d1);
	void removeDoctorFromHospital(const string& hospitalName, const string& doctorId);
	void addPatientToHospital(const string& hospitalName, Patient& p1);
	void removePatientFromHospital(const string& hospitalName, const string& patientId);
	void addMedicineToPharmacy(const string& pharmaName, Medicine& med);
	void removeMedicineByName(const string& pharmaName, const string& medName);
	void removeMedicineByFormulation(const string& pharmaName, const string& medName);
	void searchMedicineByName(const string& pharmaName, const string& medName);
	void searchMedicineByFormulation(const string& pharmaName, const string& medFormulation);
	void searchHospitalByName(const string& hospitalName);
	void searchPharmacyByName(const string& pharmacyName);
	void searchPatientByID(const string& patientId);
	void resizeHospitalMap();

	// Getters for location heads (for visualization)
	Location* getHospitalLocationHead() const { return hospitalLocationHead; }
	Location* getPharmacyLocationHead() const { return pharmacyLocationHead; }
};

void MedicalSystem::addHospital(Hospital& h1)
{
	if (hospitalCount >= hospitalTableSize) {
		resizeHospitalMap();
	}
	Hospital* toAdd = new Hospital(h1);

	// add location node
	addHospitalLocationToList(toAdd->getHospitalLocation());

	int index = Polynomial_Rolling_Hash_V1(toAdd->getName());
	index = index % hospitalTableSize;
	if (hospitalsTable[index]) {
		// chaining
		toAdd->nextHospital = hospitalsTable[index];
		hospitalsTable[index] = toAdd;
	}
	else {
		hospitalsTable[index] = toAdd;
		hospitalCount++;
	}
}

void MedicalSystem::removeHospital(const string& hospitalName) {
	int index = Polynomial_Rolling_Hash_V1(hospitalName);
	index = index % hospitalTableSize;
	if (hospitalsTable[index] == nullptr) return;
	Hospital* current = hospitalsTable[index];
	Hospital* previous = nullptr;
	while (current != nullptr) {
		if (current->getName() == hospitalName) {

			// remove hospital Location
			removeHospitalLocationFromList(current->getHospitalLocation());

			if (previous == nullptr) {
				hospitalsTable[index] = current->nextHospital;
			}
			else {
				previous->nextHospital = current->nextHospital;
			}
			delete current;
			hospitalCount--;
			return;
		}
		previous = current;
		current = current->nextHospital;
	}
}

void MedicalSystem::addPharmacy(Pharmacy& p1) {
	Pharmacy* toAdd = new Pharmacy(p1);

	// add location node
	addPharmacyLocationToList(toAdd->getPharmacyLocation());

	int index = Polynomial_Rolling_Hash_V1(toAdd->getName());
	index = index % pharmaciesTableSize;
	if (pharmaciesTable[index]) {
		// chaining
		toAdd->nextPharmacy = pharmaciesTable[index];
		pharmaciesTable[index] = toAdd;
	}
	else {
		pharmaciesTable[index] = toAdd;
		pharmaciesCount++;
	}
}

void MedicalSystem::removePharmacy(const string& pharmacyName) {
	int index = Polynomial_Rolling_Hash_V1(pharmacyName);
	index = index % pharmaciesTableSize;
	if (pharmaciesTable[index] == nullptr) return;
	Pharmacy* current = pharmaciesTable[index];
	Pharmacy* previous = nullptr;
	while (current != nullptr) {
		if (current->getName() == pharmacyName) {
			// remove location node
			removePharmacyLocationFromList(current->getPharmacyLocation());

			if (previous == nullptr) {
				pharmaciesTable[index] = current->nextPharmacy;
			}
			else {
				previous->nextPharmacy = current->nextPharmacy;
			}
			delete current;
			pharmaciesCount--;
			return;
		}
		previous = current;
		current = current->nextPharmacy;
	}
}

void MedicalSystem::addDoctorToHospital(const string& hospitalName, Doctor& d1) {
	int index = Polynomial_Rolling_Hash_V1(hospitalName);
	index = index % hospitalTableSize;
	Hospital* current = hospitalsTable[index];
	while (current != nullptr) {
		if (current->getName() == hospitalName) {
			current->registerDoctor(d1.getName(), d1.getSpecialization());
			return;
		}
		current = current->nextHospital;
	}
}

void MedicalSystem::removeDoctorFromHospital(const string& hospitalName, const string& doctorId) {
	int index = Polynomial_Rolling_Hash_V1(hospitalName);
	index = index % hospitalTableSize;
	Hospital* current = hospitalsTable[index];
	while (current) {
		if (current->getName() == hospitalName){
			current->removeDoctorById(doctorId);
			return;
		}
		current = current->nextHospital;
	}
}

void MedicalSystem::addMedicineToPharmacy(const string& pharmaName, Medicine& med) {
	int index = Polynomial_Rolling_Hash_V1(pharmaName);
	index = index % pharmaciesTableSize;
	Pharmacy* current = pharmaciesTable[index];
	while (current) {
		if (current->getName() == pharmaName) {
			current->addMedicine(med);
			return;
		}
		current = current->nextPharmacy;
	}
}

void MedicalSystem::removeMedicineByName(const string& pharmaName, const string& medName) {
	int index = Polynomial_Rolling_Hash_V1(pharmaName);
	index = index % pharmaciesTableSize;
	Pharmacy* current = pharmaciesTable[index];
	while (current) {

		if (current->getName() == pharmaName) {
			current->removeMedicineByName(medName);
			return;
		}
		current = current->nextPharmacy;
	}
}

void MedicalSystem::removeMedicineByFormulation(const string& pharmaName, const string& medFormulation) {
	int index = Polynomial_Rolling_Hash_V1(pharmaName);
	index = index % pharmaciesTableSize;
	Pharmacy* current = pharmaciesTable[index];
	while (current) {
		if (current->getName() == pharmaName) {
			current->removeMedicineByFormula(medFormulation);
			return;
		}
		current = current->nextPharmacy;
	}
}


void MedicalSystem::searchMedicineByName(const string& pharmaName, const string& medName) {
	int index = Polynomial_Rolling_Hash_V1(pharmaName);	
	index = index % pharmaciesTableSize;
	Pharmacy* current = pharmaciesTable[index];
	while (current) {
		if (current->getName() == pharmaName) {
			current->searchMedByName(medName);
			return;
		}
		current = current->nextPharmacy;
	}
}

void MedicalSystem::searchMedicineByFormulation(const string& pharmaName, const string& medFormulation) {
	int index = Polynomial_Rolling_Hash_V1(pharmaName);
	index = index % pharmaciesTableSize;
	Pharmacy* current = pharmaciesTable[index];
	while (current) {
		if (current->getName() == pharmaName) {
			current->searchMedByFormula(medFormulation);
			return;
		}
		current = current->nextPharmacy;
	}
}

void MedicalSystem::searchHospitalByName(const string& hospitalName) {
	int index = Polynomial_Rolling_Hash_V1(hospitalName);
	index = index % hospitalTableSize;
	Hospital* current = hospitalsTable[index];
	while (current) {
		if (current->getName() == hospitalName) {
			cout << "Hospital found: " << hospitalName << endl;
			return;
		}
		current = current->nextHospital;
	}
}

void MedicalSystem::searchPharmacyByName(const string& pharmacyName) {
	int index = Polynomial_Rolling_Hash_V1(pharmacyName);
	index = index % pharmaciesTableSize;
	Pharmacy* current = pharmaciesTable[index];
	while (current) {
		if (current->getName() == pharmacyName) {
			cout << "Pharmacy found: " << pharmacyName << endl;
			return;
		}
		current = current->nextPharmacy;
	}
}

void MedicalSystem::addPatientToHospital(const string& hospitalName, Patient& p1) {
	int index = Polynomial_Rolling_Hash_V1(hospitalName);
	index = index % hospitalTableSize;
	Hospital* current = hospitalsTable[index];
	while (current != nullptr) {
		if (current->getName() == hospitalName) {
			current->registerPatient(p1.getName());
			return;
		}
		current = current->nextHospital;
	}
}

void MedicalSystem::removePatientFromHospital(const string& hospitalName, const string& patientId) {
	int index = Polynomial_Rolling_Hash_V1(hospitalName);
	index = index % hospitalTableSize;
	Hospital* current = hospitalsTable[index];
	while (current) {
		if (current->getName() == hospitalName) {
			current->removePatientById(patientId);
			return;
		}
		current = current->nextHospital;
	}
}

void MedicalSystem::resizeHospitalMap()
{
	int newSize = hospitalTableSize * 2;
	Hospital** newTable = new Hospital * [newSize]();
	for (int i = 0; i < newSize; i++) {
		newTable[i] = nullptr;
	}
	for (int i = 0; i < hospitalTableSize; i++) {
		Hospital* current = hospitalsTable[i];
		while (current != nullptr) {
			Hospital* nextHospital = current->nextHospital;
			int index = Polynomial_Rolling_Hash_V1(current->getName()) % newSize;
			if (newTable[index]) {
				current->nextHospital = newTable[index];
				newTable[index] = current;
			}
			else {
				current->nextHospital = nullptr;
				newTable[index] = current;
			}
			current = nextHospital;
		}
	}
	delete[] hospitalsTable;
	hospitalsTable = newTable;
	hospitalTableSize = newSize;
}
void MedicalSystem::searchPatientByID(const string& patientId)
{
	bool found = false;
	for (int i = 0; i < hospitalTableSize; ++i) {
		Hospital* current = hospitalsTable[i];
		while (current != nullptr) {
			Patient* p = current->findPatientById(patientId);
			if (p != nullptr) {
				cout << "Patient found: ID: " << p->getId()
					<< " Name: " << p->getName()
					<< " in Hospital: " << current->getName() << endl;
				return; // stop at first match
			}
			current = current->nextHospital;
		}
	}
	cout << "Patient not found: " << patientId << endl;
}
#endif