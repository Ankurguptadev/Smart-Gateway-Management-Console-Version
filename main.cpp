#include <iostream>
#include "services/GateSystem.h"
#include "services/AdminSystem.h"

using namespace std;

int main()
{

    GateSystem system;
    AdminSystem admin;

    system.loadStudents();
    system.loadStaff();
    system.loadVisitors();

    admin.loadAdmins();
    admin.initializeIDs(system);

    int choice;

    while (true)
    {
        cout << "\nSMART GATE SYSTEM\n";
        cout << "1 Admin Login\n";
        cout << "2 Scan ID\n";
        cout << "3 Exit\n";

        cin >> choice;
        switch (choice)
        {
        case 1:
            if (admin.login())
                admin.adminMenu(system);
            break;
        case 2:
            int id;
            cout << "Scan ID: ";
            cin >> id;

            system.scanID(id);
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid Option\n";
            break;
        }
    }

    return 0;
}