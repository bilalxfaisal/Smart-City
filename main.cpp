#include "../DS_PROJECT/include/transport/TransportSystem.h"
#include <iostream>
#include <string>
using namespace std;

// Read helpers
string readLine(const string& prompt)
{
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

int readInt(const string& prompt)
{
    while (true)
    {
        string s = readLine(prompt);
        try {
            return stoi(s);
        }
        catch (...) {
            cout << "Invalid input. Try again.\n";
        }
    }
}

void showMenu()
{
    cout << "\n====== TRANSPORT SYSTEM MENU ======\n";
    cout << "1. Add Transport Company\n";
    cout << "2. Add Bus Route\n";
    cout << "3. Add Bus Stop to Route\n";
    cout << "4. Add Bus to Transport Company\n";
    cout << "5. Simulate Bus Movement\n";
    cout << "6. Display Transport Company Status\n";
    cout << "7. Show Routes\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main()
{
    TransportSystem system(20, 20); 

    while (true)
    {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(); // flush newline

        if (choice == 0)
        {
            cout << "Exiting...\n";
            break;
        }

        switch (choice)
        {
        case 1:
        {
            cout << "\n=== Add Transport Company ===\n";
            string name = readLine("Enter company name: ");

            TransportCompany tc(name);
            system.addTransportCompany(tc);

            cout << "Company added.\n";
            break;
        }

        case 2:
        {
            cout << "\n=== Add Bus Route ===\n";
            string rname = readLine("Enter route name: ");
            int rid = readInt("Enter route ID: ");
            int stops = readInt("Initial stop count: ");

            BusRoute route(rname, rid, stops);
            system.addBusRoute(route);

            cout << "Bus route added.\n";
            break;
        }

        case 3:
        {
            cout << "\n=== Add Stop to Route ===\n";
            string rname = readLine("Enter route name: ");

            string stopName = readLine("Enter new stop name: ");
            int x = readInt("Enter X coordinate: ");
            int y = readInt("Enter Y coordinate: ");
			bool afterFlag = readInt("Add AFTER(1) or BEFORE(0) a stop? ");
            
			string after = afterFlag ? readLine("Add AFTER which stop? (exact name): ") : readLine("Add BEFORE which stop? (exact name): ");
               

            BusStop bs(stopName, x, y);

            // Must find route (simple hash lookup)
            int idx = Polynomial_Rolling_Hash_V1(rname);
            idx %= 20;

            BusRoute* rt = system.getRouteHashTable()[idx];

            while (rt && rt->getRouteName() != rname)
                rt = rt->nextRoute;

            if (rt)
            {
                bool added = false;
                if(afterFlag)
                     added = rt->addStop_AFTR(bs, after);
				else
                     added = rt->addStop_B4(bs, after);

                if (added) {
                    cout << "Stop added.\n";
                }
                else {
                    cout << "NOPE\n";
                }
            }
            else
            {
                cout << "Route not found.\n";
            }

            break;
        }

        case 4:
        {
            cout << "\n=== Add Bus to Company ===\n";
            string comp = readLine("Enter company name: ");

            string busID = readLine("Enter bus ID: ");
            string routeID = readLine("Enter route name: ");
            int cap = readInt("Enter capacity: ");

			int startingStopID = system.getStartingBusStopID(routeID);
            Bus b(busID, routeID, startingStopID, cap, true, true);
            
            system.addBusToTransportCompany(b, comp);

            cout << "Bus added.\n";

            break;
        }

        case 5:
        {
            cout << "\n=== Simulating movement... ===\n";
            system.simulateBusMovement();
            cout << "Simulation step completed.\n";
            break;
        }

        case 6:
        {
            string comp = readLine("\nEnter company name: ");
            system.displayCompanyStatus(comp);
            break;
        }

        case 7:
        {
            string comp;
            cout << "Enter Company Name: ";
            cin >> comp;
            system.displayRoutes(comp);
            break;
        }
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
