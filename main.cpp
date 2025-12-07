
#include "include/utils/Nodes.h"
#include "../Smart-City-DS-Project/include/utils/CSV_Handler.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

int main() {
    CSVHandler reader;
    int count = 0;

    Citizen* myCitizens = reader.traversePopulationFile("population.csv", count);

    cout << "Loaded " << count << " citizens." << endl;

    for (int i = 0; i < count; i++) {
        cout << "Citizen: " << myCitizens[i].getName()
            << " | Occupation: " << myCitizens[i].getOccupation() << endl;
    }

    delete[] myCitizens;
    return 0;
}





