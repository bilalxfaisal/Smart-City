
#include "include/utils/Nodes.h"
#include "../Smart-City-DS-Project/include/utils/CSV_Handler.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


int main() {
    CSVHandler reader;
    int sCount = 0;

    School* mySchools = reader.traverseSchoolFile("schools.csv", sCount);

    cout << "Loaded " << sCount << " schools." << endl;

    for (int i = 0; i < sCount; i++) {
        cout << "School: " << mySchools[i].schoolName
            << " | Rating: " << mySchools[i].rating << endl;

        cout << "Subjects: ";
        for (int j = 0; j < mySchools[i].subjectCount; j++) {
            cout << mySchools[i].subjects[j] << ", ";
        }
        cout << endl << "-------------------" << endl;
    }

    delete[] mySchools;
    return 0;
}
