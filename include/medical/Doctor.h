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
	Doctor(string nam = "", string spec = "", int Id = 0)
	{
		name = nam;
		id = Id;
		specialization = spec;
		 appointmentCount = 0;
		 appointmentCap = 10;

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

};
#endif // ! DOCTOR_H
