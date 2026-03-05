#include "GateSystem.h"
#include <fstream>
#include <iostream>
#include <ctime>

using namespace std;

void GateSystem::loadStudents()
{

    ifstream file("data/students.txt");

    int id, year, batch, inside, blocked;
    string name, degree, branch;

    while (file >> id >> name >> degree >> branch >> year >> batch >> inside >> blocked)
    {

        students[id] = Student(id, name, degree, branch, year, batch, inside, blocked);
    }
}

void GateSystem::loadStaff()
{

    ifstream file("data/staff.txt");

    int id, inside, blocked;
    string name, dept, role;

    while (file >> id >> name >> dept >> role >> inside >> blocked)
    {

        staff[id] = Staff(id, name, dept, role, inside, blocked);
    }
}

void GateSystem::loadVisitors()
{

    ifstream file("data/visitors.txt");

    int id, inside;
    string name, purpose, meet;

    while (file >> id >> name >> purpose >> meet >> inside)
    {

        visitors[id] = Visitor(id, name, purpose, meet, inside);
    }
}

void GateSystem::saveStudents()
{

    ofstream file("data/students.txt");

    for (auto &s : students)
        file << s.second.serialize() << endl;
}

void GateSystem::saveStaff()
{

    ofstream file("data/staff.txt");

    for (auto &s : staff)
        file << s.second.serialize() << endl;
}

void GateSystem::saveVisitors()
{

    ofstream file("data/visitors.txt");

    for (auto &v : visitors)
        file << v.second.serialize() << endl;
}

void GateSystem::scanID(int id)
{

    if (id >= 1000 && id < 2000)
    {

        handleStudent(id);
    }

    else if (id >= 2000 && id < 3000)
    {

        handleStaff(id);
    }

    else if (id >= 5000 && id < 6000)
    {

        handleVisitor(id);
    }

    else
    {

        cout << "Unknown ID\n";

        ofstream log("logs/security_log.txt", ios::app);

        time_t now = time(0);

        log << ctime(&now) << "UNKNOWN ID " << id << endl;
    }
}

void GateSystem::handleStudent(int id)
{

    if (students.find(id) == students.end())
    {

        cout << "Student not found\n";
        return;
    }

    Student &s = students[id];

    if (s.blocked)
    {

        cout << "Access Denied: Student Blocked\n";

        ofstream log("logs/security_log.txt", ios::app);

        time_t now = time(0);

        log << ctime(&now) << "BLOCKED STUDENT " << id << endl;

        return;
    }

    time_t now = time(0);
    tm *t = localtime(&now);

    ofstream log("logs/student_logs.txt", ios::app);

    cout << "\nStudent Information\n";
    cout << "-------------------\n";
    cout << "Name   : " << s.name << endl;
    cout << "Branch : " << s.branch << endl;
    cout << "Year   : " << s.year << endl;

    if (!s.inside)
    {

        if (t->tm_hour > 9 || (t->tm_hour == 9 && t->tm_min > 30))
        {

            cout << "Late Entry Warning\n";

            ofstream late("logs/late_entries.txt", ios::app);

            late << id << " " << s.name << " " << ctime(&now);
        }

        s.inside = true;

        cout << "Status : ENTERED\n";

        log << id << " " << s.name << " ENTER " << now << " NA\n";
    }

    else
    {

        s.inside = false;

        cin.ignore();

        string reason;

        cout << "Reason for exit: ";
        getline(cin, reason);

        cout << "Status : EXITED\n";

        log << id << " " << s.name << " EXIT " << now << " " << reason << endl;
    }

    saveStudents();
}

void GateSystem::handleStaff(int id)
{

    if (staff.find(id) == staff.end())
    {

        cout << "Staff not found\n";
        return;
    }

    Staff &s = staff[id];

    if (s.blocked)
    {

        cout << "Access Denied: Staff Blocked\n";

        ofstream log("logs/security_log.txt", ios::app);

        time_t now = time(0);

        log << ctime(&now) << "BLOCKED STAFF " << id << endl;

        return;
    }

    time_t now = time(0);

    ofstream log("logs/staff_logs.txt", ios::app);

    cout << "\nStaff Information\n";
    cout << "-----------------\n";
    cout << "Name       : " << s.name << endl;
    cout << "Department : " << s.department << endl;
    cout << "Role       : " << s.role << endl;

    if (!s.inside)
    {

        s.inside = true;

        cout << "Status : ENTERED\n";

        log << id << " " << s.name << " ENTER " << now << " NA\n";
    }

    else
    {

        s.inside = false;

        cin.ignore();

        string reason;

        cout << "Reason (optional): ";
        getline(cin, reason);

        if (reason == "")
            reason = "NA";

        cout << "Status : EXITED\n";

        log << id << " " << s.name << " EXIT " << now << " " << reason << endl;
    }

    saveStaff();
}

void GateSystem::handleVisitor(int id)
{

    if (visitors.find(id) == visitors.end())
    {

        cout << "Visitor not found\n";
        return;
    }

    Visitor &v = visitors[id];

    time_t now = time(0);

    ofstream log("logs/visitor_logs.txt", ios::app);

    cout << "\nVisitor Information\n";
    cout << "-------------------\n";
    cout << "Name   : " << v.name << endl;
    cout << "Purpose: " << v.purpose << endl;
    cout << "Meeting: " << v.personToMeet << endl;

    if (!v.inside)
    {

        v.inside = true;

        cout << "Status : ENTERED\n";

        log << id << " " << v.name << " ENTER " << now << " NA\n";
    }

    else
    {

        v.inside = false;

        cin.ignore();

        string reason;

        cout << "Reason for exit: ";
        getline(cin, reason);

        cout << "Status : EXITED\n";

        log << id << " " << v.name << " EXIT " << now << " " << reason << endl;
    }

    saveVisitors();
}