#ifndef HOSPITAL_H
#define HOSPITAL_H
#include "../utils/Nodes.h"
#include "Patient.h"
#include "Doctor.h"
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Appointment 
{
	private:
	string appointmentId = "";
	Doctor* docPtr = nullptr;
	Patient* patPtr = nullptr;
	string appDate;
	string appTime;
public:
	//FOR HASH TABLE COLLISIONS
	Appointment* nextAppointment = nullptr;
	Appointment(Doctor* dPtr = nullptr, Patient* pPtr = nullptr, string date = "", string time = "")
	{
		docPtr = dPtr;
		patPtr = pPtr;
		appDate = date;
		appTime = time;
	}
	Patient* getPatient()
	{
		return patPtr;
	}
	Doctor* getDoctor()
	{
		return docPtr;
	}
};
class Hospital 
{
private:
	string name;	
	string id;
	//HASH TABLE -->DOCTORS
	Doctor** doctorsArray = nullptr;
	int doctorCount = 0;
	int docTableCap =	100;
	static int patientIdCounter; // Static counter for patient IDs
	static int doctorIdCounter; // Static counter for patient IDs
	//PATIENTS
	Patient** patientsArray = nullptr;
	int patCount = 0;
	int PatTableCap = 100;
	//APPOINTMENTS
	Appointment** appointmentsArray = nullptr;
	int appointmentCount = 0;
	int appointmentCap = 100;

	int EmergencyBedNum = 0;
	string sector = "";	
	Location hospitalLocation;
	//
public:
	Hospital* nextHospital = nullptr; // For chaining in hash table
	Hospital( string nam = "", string Id = "", string sec = "", int emBedNum = 0)
	{
		name = nam;
		id = Id;
		sector = sec;
		EmergencyBedNum = emBedNum;
		doctorsArray = new Doctor * [docTableCap];
		for (int i = 0; i < docTableCap; i++)
		{
			doctorsArray[i] = nullptr;
		}
		patientsArray = new Patient * [PatTableCap];
		for (int i = 0; i < PatTableCap; i++)
		{
			patientsArray[i] = nullptr;
		}
		appointmentsArray = new Appointment * [appointmentCap];
		for (int i = 0; i < appointmentCap; i++)
		{
			appointmentsArray[i] = nullptr;
		}
		srand(time(0));
	}
	void registerPatient(string Nam = "", float wt = 0)
	{
		// If weight not provided, generate random weight
		if (wt == 0)
		{
			// Random float between 40 and 120 (example realistic range)
			wt = 40 + (rand() % 81);
		}

		string Id = "Pt-" + to_string(patientIdCounter++);
		Patient* newPatient = new Patient(Nam, wt, Id);

		int index = Polynomial_Rolling_Hash_V2(Id);
		index %= PatTableCap;

		// Insert into hash table
		if (patientsArray[index] == nullptr)
		{
			patientsArray[index] = newPatient;
		}
		else
		{
			newPatient->nextPatient = patientsArray[index];
			patientsArray[index] = newPatient;
		}
	}

	void registerDoctor(const string& nam, const string& spec)
	{
		string Id = "Dr-" + to_string(doctorIdCounter++);
		Doctor* newDoctor = new Doctor(nam, spec, Id);
		int index = Polynomial_Rolling_Hash_V2(Id);
		if(doctorsArray[index] == nullptr)
		{
			doctorsArray[index] = newDoctor;
		}
		else
		{
			newDoctor->nextDoctor = doctorsArray[index];
			doctorsArray[index] = newDoctor;
		}
	}
	void addAppointment(string& PatientId, string& DoctorId)
	{
		//APPOINTMENT ONLY WORKS IF PATIENT AND DOCTOR ARE REGISTERED
		Patient* patient = findPatientById(PatientId);
		Doctor* doctor = findDoctorById(DoctorId);
		if (patient == nullptr || doctor == nullptr) {
			cout << "Invalid patient or doctor ID." << endl;
			return;
		}
		Appointment* newAppointment = new Appointment(doctor, patient);
		string appId = doctor->getId()  + patient->getId();
		
		int index = Polynomial_Rolling_Hash_V2(appId) % appointmentCap;
		doctor->addAppointment(index);
		patient->addAppointment(index);
		if (appointmentsArray[index] == nullptr)
		{
				appointmentsArray[index] = newAppointment;
		}
		else
		{
			newAppointment->nextAppointment = appointmentsArray[index];
		}
		// Add the appointment to the hospital's appointment list
	}
	Patient* findPatientById(const string& patientId)
	{
		int index = Polynomial_Rolling_Hash_V2(patientId) % PatTableCap;
		Patient* current = patientsArray[index];
		while (current != nullptr) {
			if (current->getId() == patientId)
			{
				return current;
			}
			current = current->nextPatient;
		}
		return nullptr; // Patient not found
	}

	Doctor* findDoctorById(const string& doctorId)
	{
		int index = Polynomial_Rolling_Hash_V2(doctorId) % docTableCap;
		Doctor* current = doctorsArray[index];
		while (current != nullptr) {
			if (current->getId() == doctorId)
			{
				return current;
			}
			current = current->nextDoctor;
		}
		return nullptr; // Doctor not found
	}
	void cancelAppointment(string& patientId, string doctorId)
	{
		string appId = doctorId + patientId;
		int index = Polynomial_Rolling_Hash_V2(appId) % appointmentCap;
		Appointment* current = appointmentsArray[index];
		Appointment* prev = nullptr;
		while (current != nullptr) {
			if (current->getPatient()->getId() == patientId && current->getDoctor()->getId() == doctorId) {
				if (prev == nullptr) {
					appointmentsArray[index] = current->nextAppointment;
				} else {
					prev->nextAppointment = current->nextAppointment;
				}
				delete current;
				return;
			}
			prev = current;
			current = current->nextAppointment;
		}
	}
	void removePatientById(const string& patientId)
	{
		int index = Polynomial_Rolling_Hash_V2(patientId) % PatTableCap;
		Patient* current = patientsArray[index];
		Patient* previous = nullptr;
		while (current != nullptr) 
		{
			if (current->getId() == patientId) {
				if (previous == nullptr) {
					patientsArray[index] = current->nextPatient;
				}
				else {
					previous->nextPatient = current->nextPatient;
				}
				delete current;
				return;
			}
			previous = current;
			current = current->nextPatient;
		}
	}
	int getEmergencyBedNum() const
	{
		return EmergencyBedNum;
	}
	string getName()
	{
		return name;
	}

	void removeDoctorById(const string& doctorId)
	{
		int index = Polynomial_Rolling_Hash_V2(doctorId) % docTableCap;
		Doctor* current = doctorsArray[index];
		Doctor* previous = nullptr;
		while (current != nullptr) {
			if (current->getId() == doctorId) {
				if (previous == nullptr) {
					doctorsArray[index] = current->nextDoctor;
				}
				else {
					previous->nextDoctor = current->nextDoctor;
				}
				delete current;
				return;
			}
			previous = current;
			current = current->nextDoctor;
		}
	}

};
int Hospital::patientIdCounter = 1;
int Hospital::doctorIdCounter = 1;
int compareHospitals(void* hospital1, void* hospital2) //true if hospital 1 
{
	Hospital* h1 = static_cast<Hospital*> (hospital1);
	Hospital* h2 = static_cast<Hospital*>(hospital2);
	return(h2->getEmergencyBedNum() < h1->getEmergencyBedNum());


}



#endif // !HOSPITAL_H

//int arrays of indexes in hospital table given to doctor and patient
//Register a patient
//Appointment creating checks existing existence

