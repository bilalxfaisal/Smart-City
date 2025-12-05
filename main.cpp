//<<<<<<< Updated upstream
//#include "../Smart-City-DS-Project/include/utils/Stack_Heap_nMORE.h"
//#include "../Smart-City-DS-Project/include/utils/Nodes.h"
//#include "../Smart-City-DS-Project/include/medical/Hospital.h"
//=======
#include "../Smart-City-DS-Project/include/Run.h"
#include <iostream>
#include <string>
using namespace std;

//int main() 
//{
//	Hospital* h1 = new Hospital("City Hospital", "H001", "General", 50);
//	Hospital* h2 = new Hospital("Hadiah Hospital", "H002", "Specialized", 50);
//	Hospital* h3 = new Hospital("Hashim Hospital", "H003", "Specialized", 20);
//	Hospital* h4 = new Hospital("Maryum Hospital", "H004", "Specialized", 10);
//	Hospital* h5 = new Hospital("FAST NU", "H005", "Specialized", 90);
//	Hospital* h6 = new Hospital("MMMMMmMMm^", "H006", "Specialized", 130);
//	Hospital* h7 = new Hospital("OIJSDJFO", "H007", "Specialized", 10);
//	MaxHeap hospitalHeap(10, compareHospitals);
//	hospitalHeap.insert((h1));
//	hospitalHeap.insert((h2));
//	hospitalHeap.insert(static_cast<void*>(h3));
//	hospitalHeap.insert(static_cast<void*>(h4));
//	hospitalHeap.insert(static_cast<void*>(h5));
//	hospitalHeap.insert(static_cast<void*>(h6));
//	hospitalHeap.insert(static_cast<void*>(h7));
//	Hospital* topHospital = static_cast<Hospital*>(hospitalHeap.getMax());
//	cout << "Hospital with highest emergency bed count: " << topHospital->getName() << " with " << topHospital->getEmergencyBedNum() << " beds." << endl;
//
//	return 0;
//}

   


int main()
{
    int mainMenuCh = 0;
    showMainMenu(mainMenuCh);
    simulateBasedOnMainChoice(mainMenuCh);

    return 0;
}
