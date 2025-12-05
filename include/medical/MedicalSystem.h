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
	void searchPatientByName(const string& patientId);
	void resizeHospitalMap();
};

void MedicalSystem::addHospital(Hospital& h1)
{
	if (hospitalCount >= hospitalTableSize) {
		resizeHospitalMap();
	}
	Hospital* toAdd = new Hospital(h1);
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
#endif