#include <iostream>
#include "services/GateSystem.h"

using namespace std;

int main(){

    GateSystem system;

    system.loadStudents();
    system.loadStaff();
    system.loadVisitors();

    cout<<"Smart Gate System Started\n";

    cout<<"Databases loaded successfully\n";

    return 0;
}