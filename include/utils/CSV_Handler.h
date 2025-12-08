#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "../utils/Nodes.h"
#include "../medical/Hospital.h"
#include "../medical/Pharmacy.h"
#include "../education/School.h"
#include "../transport/Bus.h"
#include "../transport/BusStop.h"
#include "../population/Citizen.h"

using namespace std;

class CSVHandler
{
private:
    // Helper to convert string to int safely
    int strToInt(string s) {
        if (s == "") return 0;
        try {
            return stoi(s);
        }
        catch (...) {
            return 0;
        }
    }

public:
    Hospital* traverseHospitalFile(string path, int& numOfHospitals)
    {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << path << endl;
            numOfHospitals = 0;
            return nullptr;
        }

        string line;
        int count = 0;

        //Count
        // Skip Header
        getline(file, line);

        // Count remaining lines
        while (getline(file, line)) {
            if (!line.empty()) count++;
        }

        numOfHospitals = count;

        // Reset file to read from the beginning again
        file.clear();
        file.seekg(0);
        getline(file, line); // Skip header again


// Allocate Array

        Hospital* hospitalList = new Hospital[numOfHospitals];


        // Parse Data 

        int index = 0;
        while (getline(file, line) && index < numOfHospitals)
        {
            if (line.empty()) continue;

            string rowData[5]; // ID, Name, Sector, Beds, Specs
            int colIdx = 0;

            string buffer = "";
            bool inQuotes = false;

            // --- CUSTOM PARSING LOGIC ---
            for (int i = 0; i < line.length(); i++)
            {
                char c = line[i];

                if (c == '"') {
                    inQuotes = !inQuotes; // Toggle quote state
                }
                else if (c == ',' && !inQuotes) {
                    // Found a separator (comma outside of quotes)
                    if (colIdx < 5) rowData[colIdx++] = buffer;
                    buffer = ""; // Reset buffer
                }
                else {
                    buffer += c; // Add character to current word
                }
            }
            // Add the last column (Specialization)
            if (colIdx < 5) rowData[colIdx] = buffer;

            // --- MAPPING CSV TO OBJECT ---
            // CSV Order: ID [0], Name [1], Sector [2], Beds [3], Specs [4]
            string hID = rowData[0];
            string hName = rowData[1];
            string hSector = rowData[2];
            int hBeds = strToInt(rowData[3]);
            string hSpecs = rowData[4];

            // Use the setter we added to Hospital.h
            hospitalList[index].setHospitalDetails(hName, hID, hSector, hBeds, hSpecs);

            index++;
        }

        file.close();
        return hospitalList;
    }
    Pharmacy* traversePharmacyFile(string path, int& numOfPharmacies)
    {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << path << endl;
            numOfPharmacies = 0;
            return nullptr;
        }

        string line;
        int count = 0;

        // 1. Count Rows (Skip Header)
        getline(file, line);
        while (getline(file, line)) {
            if (!line.empty()) count++;
        }

        numOfPharmacies = count;

        // Reset file
        file.clear();
        file.seekg(0);
        getline(file, line); // Skip header

        // 2. Allocate Array
        Pharmacy* pharmList = new Pharmacy[numOfPharmacies];

        // 3. Parse Data
        int index = 0;
        while (getline(file, line) && index < numOfPharmacies)
        {
            if (line.empty()) continue;

            string rowData[6]; // ID, Name, Sector, MedName, Formula, Price
            int colIdx = 0;
            string buffer = "";
            bool inQuotes = false;

            // Manual CSV Parsing
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                if (c == '"') inQuotes = !inQuotes;
                else if (c == ',' && !inQuotes) {
                    if (colIdx < 6) rowData[colIdx++] = buffer;
                    buffer = "";
                }
                else buffer += c;
            }
            if (colIdx < 6) rowData[colIdx] = buffer;

            // Extract Strings
            string pID = rowData[0];
            string pName = rowData[1];
            string pSector = rowData[2];
            string mName = rowData[3];
            string mFormula = rowData[4];
            int mPrice = strToInt(rowData[5]); // Uses the helper from previous answer

            // Setup Pharmacy
            pharmList[index].setPharmacyDetails(pName, pID, pSector);

            // Create and Add Medicine
       
            Medicine newMed(mName, mFormula, mPrice);

            pharmList[index].addMedicine(newMed);

            index++;
        }

        file.close();
        return pharmList;
    }
    // Helper for float conversion
    float strToFloat(string s) {
        if (s == "") return 0.0f;
        try {
            return stof(s);
        }
        catch (...) {
            return 0.0f;
        }
    }

    School* traverseSchoolFile(string path, int& numOfSchools)
    {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << path << endl;
            numOfSchools = 0;
            return nullptr;
        }

        string line;
        int count = 0;

        // 1. Count Rows
        getline(file, line); // Skip Header
        while (getline(file, line)) {
            if (!line.empty()) count++;
        }

        numOfSchools = count;

        // Reset File
        file.clear();
        file.seekg(0);
        getline(file, line); // Skip Header

        // 2. Allocate Array
        School* schoolList = new School[numOfSchools];

        // 3. Parse Data
        int index = 0;
        while (getline(file, line) && index < numOfSchools)
        {
            if (line.empty()) continue;

            string rowData[5]; // ID, Name, Sector, Rating, Subjects
            int colIdx = 0;
            string buffer = "";
            bool inQuotes = false;

            // --- MAIN CSV PARSING ---
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                if (c == '"') {
                    inQuotes = !inQuotes; // Toggle, but don't add '"' to buffer
                }
                else if (c == ',' && !inQuotes) {
                    if (colIdx < 5) rowData[colIdx++] = buffer;
                    buffer = "";
                }
                else 
                {
                    buffer += c;
                }
            }
            if (colIdx < 5) rowData[colIdx] = buffer;

            // Extract Basic Data
            string sID = rowData[0];
            string sName = rowData[1];
            string sSector = rowData[2];
            float sRating = strToFloat(rowData[3]);
            string sSubjectsRaw = rowData[4]; // "Math, Physics, English"

            // A. Set Basic Details
            schoolList[index].setSchoolDetails(sID, sName, sSector, sRating);

            // B. Parse Subjects (The "List inside a List")
            string subBuffer = "";
            for (int k = 0; k < sSubjectsRaw.length(); k++) {
                char sc = sSubjectsRaw[k];

                if (sc == ',') {
                    // Found a subject separator
                    // Trim leading space if exists
                    if (subBuffer.length() > 0 && subBuffer[0] == ' ')
                        subBuffer = subBuffer.substr(1);

                    schoolList[index].addSubject(subBuffer);
                    subBuffer = "";
                }
                else {
                    subBuffer += sc;
                }
            }
            // Add the last subject
            if (!subBuffer.empty()) {
                if (subBuffer.length() > 0 && subBuffer[0] == ' ')
                    subBuffer = subBuffer.substr(1);
                schoolList[index].addSubject(subBuffer);
            }

            index++;
        }

        file.close();
        return schoolList;
    }

   // 1. Parse Bus Stops 

    BusStop* traverseBusStops(string path, int& count)
    {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: Could not open " << path << endl;
            count = 0; return nullptr;
        }

        string line;
        int rowCount = 0;

        // Count Rows
        getline(file, line); // Skip Header
        while (getline(file, line)) { if (!line.empty()) rowCount++; }

        count = rowCount;
        BusStop* stops = new BusStop[count]; // Allocate Acorray

        // Reset File
        file.clear();
        file.seekg(0);
        getline(file, line); // Skip Header

        int index = 0;
        while (getline(file, line) && index < count)
        {
            if (line.empty()) continue;

            string rowData[3]; // ID, Name, Coordinates
            int colIdx = 0;
            string buffer = "";
            bool inQuotes = false;

            // Parse Line
            for (int i = 0; i < line.length(); i++) {
                char c = line[i];
                if (c == '"') inQuotes = !inQuotes;
                else if (c == ',' && !inQuotes) {
                    if (colIdx < 3) rowData[colIdx++] = buffer;
                    buffer = "";
                }
                else buffer += c;
            }
            if (colIdx < 3) rowData[colIdx] = buffer;


            string sName = rowData[1];
            string sCoords = rowData[2]; // "33.684, 73.025"

            // Parse Coordinates manually
            float lat = 0, lon = 0;
            int commaPos = sCoords.find(',');
            if (commaPos != string::npos) {
                lat = strToFloat(sCoords.substr(0, commaPos));
                lon = strToFloat(sCoords.substr(commaPos + 1));
            }

            stops[index].setStopDetails(sName, lat, lon);
            index++;
        }
        file.close();
        return stops;
    }


    // Parse Buses

    Bus* traverseBuses(string path, int& count)
    {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: Could not open " << path << endl;
            count = 0; return nullptr;
        }

        string line;
        int rowCount = 0;

        // Count Rows
        getline(file, line);
        while (getline(file, line)) { if (!line.empty()) rowCount++; }

        count = rowCount;
        Bus* buses = new Bus[count];

        // Reset File
        file.clear();
        file.seekg(0);
        getline(file, line);

        int index = 0;
        while (getline(file, line) && index < count)
        {
            if (line.empty()) continue;

            string rowData[4]; // BusNo, Company, CurrentStop, Route
            int colIdx = 0;
            string buffer = "";

            
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    if (colIdx < 4) rowData[colIdx++] = buffer;
                    buffer = "";
                }
                else {
                    buffer += line[i];
                }
            }
            if (colIdx < 4) rowData[colIdx] = buffer;

            string bID = rowData[0];
            string bComp = rowData[1];
            string bCurrStop = rowData[2]; // "Stop3"
            string bRoute = rowData[3];    // "Stop1 > Stop2 > ..."

            buses[index].setBusDetails(bID, bComp, bCurrStop, bRoute);
            index++;
        }
        file.close();
        return buses;
    }
    // Helper to remove '\r' if present (common in Windows CSVs)
    string cleanString(string s) {
        if (!s.empty() && s[s.length() - 1] == '\r') {
            return s.substr(0, s.length() - 1);
        }
        return s;
    }

    Citizen* traversePopulationFile(string path, int& numOfCitizens)
    {
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << path << endl;
            numOfCitizens = 0;
            return nullptr;
        }

        string line;
        int count = 0;

        // 1. Count Rows (Skip Header)
        getline(file, line);
        while (getline(file, line)) {
            if (!line.empty()) count++;
        }

        numOfCitizens = count;

        // Reset File
        file.clear();
        file.seekg(0);
        getline(file, line); // Skip Header

        // 2. Allocate Array
        Citizen* citizenList = new Citizen[numOfCitizens];

        // 3. Parse Data
        int index = 0;
        while (getline(file, line) && index < numOfCitizens)
        {
            if (line.empty()) continue;

            string rowData[7];
            // 0:CNIC, 1:Name, 2:Age, 3:Sector, 4:Street, 5:HouseNo, 6:Occupation

            int colIdx = 0;
            string buffer = "";

            // Simple CSV Split (assuming no commas inside names/occupation)
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    if (colIdx < 7) rowData[colIdx++] = buffer;
                    buffer = "";
                }
                else {
                    buffer += line[i];
                }
            }
            if (colIdx < 7) rowData[colIdx] = buffer;

            // Extract & Convert
            string cCNIC = rowData[0];
            string cName = rowData[1];
            int cAge = strToInt(rowData[2]);
            string cSector = rowData[3];
            int cStreet = strToInt(rowData[4]);
            int cHouse = strToInt(rowData[5]);
            string cOcc = cleanString(rowData[6]); 

            // Fill Object
            citizenList[index].setCitizenDetails(cCNIC, cName, cAge, cSector, cStreet, cHouse, cOcc);
            // Add debug output to loadCitizensFromCSV()
            cout << "Loading citizen: " << citizenList[index].getName() << endl;


            index++;
        }

        file.close();
        return citizenList;
    }

};



#endif // CSV_HANDLER_H
