#ifndef HOSPITAL_H
#define HOSPITAL_H
#include "../utils/Nodes.h"
class Hospital 
{
private:
	string name;	
	int id;
	Doctor** doctorsArray = nullptr;
	int doctorCount = 0;
	int docTableCap = 0;

	Patient** patientsArray = nullptr;
	int patCount = 0;
	int PatTableCap = 0;

	int EmergencyBedNum = 0;
	//
public:
	
};
#endif // !HOSPITAL_H
