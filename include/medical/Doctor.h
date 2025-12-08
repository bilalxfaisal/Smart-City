#ifndef  DOCTOR_H
#define DOCTOR_H
#include "../utils/Nodes.h"
class Doctor
{
private:
	string name;
	string id;
	string specialization;
	int* myAppointment = nullptr;
	int appointmentCount = 0;
	int appointmentCap = 10;

public:
	//FOR HASH TABLE COLLISIONS
	Doctor* nextDoctor = nullptr;
	Doctor(const string& nam = "", const string& spec = "", const string& Id = "")
	{
		name = nam;
		id = Id;
		specialization = spec;
		appointmentCount = 0;
		appointmentCap = 10;

	}
	void display() const
	{
		cout << "Doctor ID: " << id
			<< ", Name: " << name
			<< ", Specialization: " << specialization
			<< ", Appointments Count: " << appointmentCount << endl;
		// Add logic to display appointments if needed
	}
	void addAppointment(int indexToBeAdded)
	{
		if (appointmentCount >= appointmentCap)
		{
			ResizeAppointments();

		}
		myAppointment[appointmentCount] = indexToBeAdded;
		appointmentCount++;
	}
	void ResizeAppointments()
	{
				appointmentCap *= 2;
				int* newAppointments = new int[appointmentCap];
				for (int i = 0; i < appointmentCount; i++)
				{
					newAppointments[i] = myAppointment[i];
				}
				delete[] myAppointment;
				myAppointment = newAppointments;
	}
	 string getId()
	 {
		return id;
	 }
	 string getName() 
	 {
		 return name;
	 }
	 string getSpecialization()
	 {
		 return specialization;
	 }
};
#endif // ! DOCTOR_H
