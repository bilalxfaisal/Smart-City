#include "../utils/Nodes.h"
#ifndef PATIENT_H
#define PATIENT_H'
using std::string;

class Patient
{
private:

	string Name = "";
	float weight = 0.0;
	string patientId = "";
	int* myAppointment = nullptr;
	int appointmentCount = 0;
	int appointmentCap = 10;

	



public:
	//FOR HASHMAPS 
	Patient* nextPatient = nullptr;
	Patient(string nam="", float wt=0.0, string ptId="")
	{
		Name = nam;
		weight = wt;
		patientId = ptId;
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
		return patientId;
	}
	string getName()
	{
		return Name;
	}
	

};
#endif
