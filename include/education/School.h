#include "../utils/Nodes.h"
#include <iostream>

#ifndef School_H
#define School_H

using std::cout;
using std::cin;
using std::endl;
using std::string;


School::School(string ID, string name, string sector, int campus) {
	schoolID = ID;
	schoolName = name;
	this->sector = sector;
	campusNo = campus;
	subjects = nullptr;
	subjectCount = 0;
	totalSubjets = 10; // initial size
	subjects = new string[totalSubjets]();
	rating = 0.0f;
	Bacha = nullptr;
	FacultyHead = nullptr;
	nextSibling = nullptr;
}

void School::addSubject(const string& sub) {
	if (subjectCount >= totalSubjets) {
		// need to resize
		int newSize = totalSubjets * 2;
		string* newSubjects = new string[newSize]();
		// copy old subjects
		for(int i = 0; i < subjectCount; i++) {
			newSubjects[i] = subjects[i];
		}
		// delete old array
		delete[] subjects;
		subjects = newSubjects;
		totalSubjets = newSize;
	}
	else {
		// enough space
		subjects[subjectCount] = sub;
	}
}


#endif