#include "AdminSystem.h"
#include "../utils/SecurityLogger.h"
#include "../utils/Validation.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void printStudentCard(Student &s)
{
    cout << "\n-----------------------------\n";
    cout << "        CAMPUS ID CARD\n";
    cout << "-----------------------------\n";

    cout << "Name   : " << s.name << endl;
    cout << "Type   : Student\n";
    cout << "ID     : " << s.id << endl;
    cout << "Branch : " << s.branch << endl;
    cout << "Year   : " << s.year << endl;
    cout << "Batch  : " << s.batch << endl;

    cout << "-----------------------------\n";
}

void printStaffCard(Staff &s)
{
    cout << "\n-----------------------------\n";
    cout << "        CAMPUS ID CARD\n";
    cout << "-----------------------------\n";

    cout << "Name       : " << s.name << endl;
    cout << "Type       : Staff\n";
    cout << "ID         : " << s.id << endl;
    cout << "Department : " << s.department << endl;
    cout << "Role       : " << s.role << endl;

    cout << "-----------------------------\n";
}

void AdminSystem::loadAdmins()
{
    ifstream file("data/admins.txt");

    string user, password;
    while (file >> user >> password)
        admins[user] = password;
}

bool AdminSystem::login()
{
    string user, password;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> password;

    if (admins.find(user) != admins.end() && admins[user] == password)
    {
        SecurityLogger::logEvent("ADMIN LOGIN SUCCESS " + user);
        cout << "Login Successful\n";
        return true;
    }
    SecurityLogger::logEvent("ADMIN LOGIN FAILED " + user);
    cout << "Invalid credentials\n";
    return false;
}

void AdminSystem::initializeIDs(GateSystem &system)
{
    for (auto &s : system.students)
    {
        if (s.first >= nextStudentID)
            nextStudentID = s.first + 1;
    }
    for (auto &s : system.staff)
    {
        if (s.first >= nextStaffID)
            nextStaffID = s.first + 1;
    }
    for (auto &v : system.visitors)
    {
        if (v.first >= nextVisitorID)
            nextVisitorID = v.first + 1;
    }
}

void AdminSystem::adminMenu(GateSystem &system)
{
    int choice;

    while (true)
    {

        cout << "\n------ ADMIN PANEL ------\n";

        cout << "1 Add Student\n";
        cout << "2 Add Staff\n";
        cout << "3 Add Visitor\n";
        cout << "4 Remove Student\n";
        cout << "5 Remove Staff\n";
        cout << "6 Block/Unblock User\n";
        cout << "7 Show Students\n";
        cout << "8 Show Staff\n";
        cout << "9 Show Visitors\n";
        cout << "10 Search User\n";
        cout << "11 Daily Attendance Report\n";
        cout << "12 Export Attendance CSV\n";
        cout << "13 Activity Timeline\n";
        cout << "14 Gate Statistics\n";
        cout << "15 Gate Analytics\n";
        cout << "16 Live Campus Status\n";
        cout << "17 Logout\n";

        cin >> choice;

        switch (choice)
        {

        case 1:
            addStudent(system);
            break;
        case 2:
            addStaff(system);
            break;
        case 3:
            addVisitor(system);
            break;
        case 4:
            removeStudent(system);
            break;
        case 5:
            removeStaff(system);
            break;
        case 6:
            blockUnblock(system);
            break;
        case 7:
            showStudents(system);
            break;
        case 8:
            showStaff(system);
            break;
        case 9:
            showVisitors(system);
            break;
        case 10:
            searchUser(system);
            break;
        case 11:
            dailyAttendanceReport();
            break;
        case 12:
            exportCSV();
            break;
        case 13:
            activityTimeline();
            break;
        case 14:
            gateStatistics(system);
            break;
        case 15:
            gateAnalytics();
            break;
        case 16:
            liveCampusStatus(system);
            break;
        default:
            return;
        }
    }
}

void AdminSystem::addStudent(GateSystem &system)
{
    string name, degree, branch;
    int year, batch;

    cout << "Name: ";
    cin >> name;
    cout << "Degree: ";
    cin >> degree;

    if (!Validation::validDegree(degree))
    {
        cout << "Invalid Degree\n";
        return;
    }

    cout << "Branch: ";
    cin >> branch;
    cout << "Year: ";
    cin >> year;

    if (!Validation::validYear(degree, year))
    {
        cout << "Invalid Year\n";
        return;
    }

    cout << "Batch: ";
    cin >> batch;

    int id = nextStudentID++;
    Student st(id, name, degree, branch, year, batch, false, false);
    system.students[id] = st;
    system.saveStudents();

    cout << "Student added successfully\n\n";
    printStudentCard(st);
}

void AdminSystem::addStaff(GateSystem &system)
{
    string name, dept, role;

    cout << "Name: ";
    cin >> name;
    cout << "Department: ";
    cin >> dept;
    cout << "Role: ";
    cin >> role;

    int id = nextStaffID++;
    Staff s(id, name, dept, role, false, false);
    system.staff[id] = s;
    system.saveStaff();

    cout << "Staff member added successfully\n\n";
    printStaffCard(s);
}

void AdminSystem::addVisitor(GateSystem &system)
{
    string name, purpose, meet;
    cout << "Name: ";
    cin >> name;
    cout << "Purpose: ";
    cin >> purpose;
    cout << "Person to meet: ";
    cin >> meet;

    int id = nextVisitorID++;
    system.visitors[id] = Visitor(id, name, purpose, meet, false);
    system.saveVisitors();
    cout << "Visitor added successfully.\nID = " << id << endl;
}

void AdminSystem::removeStudent(GateSystem &system)
{
    int id;

    cout << "Enter student ID: ";
    cin >> id;

    system.students.erase(id);
    system.saveStudents();

    cout << "Student removed\n";
}

void AdminSystem::removeStaff(GateSystem &system)
{
    int id;

    cout << "Enter staff ID: ";
    cin >> id;

    system.staff.erase(id);
    system.saveStaff();

    cout << "Staff removed\n";
}

void AdminSystem::blockUnblock(GateSystem &system)
{
    int id;
    cout << "Enter ID: ";
    cin >> id;

    if (system.students.find(id) != system.students.end())
    {
        system.students[id].blocked = !system.students[id].blocked;
        system.saveStudents();
        cout << "Student status changed\n";
    }
    else if (system.staff.find(id) != system.staff.end())
    {
        system.staff[id].blocked = !system.staff[id].blocked;
        system.saveStaff();
        cout << "Staff status changed\n";
    }
    else
        cout << "User not found\n";
}

void AdminSystem::searchUser(GateSystem &system)
{
    string name;

    cout << "Enter Name: ";
    cin >> name;

    for (auto &s : system.students)
    {
        if (s.second.name.find(name) != string::npos)
            s.second.display();
    }
    for (auto &s : system.staff)
    {
        if (s.second.name.find(name) != string::npos)
            s.second.display();
    }
    for (auto &v : system.visitors)
    {
        if (v.second.name.find(name) != string::npos)
            v.second.display();
    }
}

void AdminSystem::showStudents(GateSystem &system)
{
    for (auto &s : system.students)
        s.second.display();
}

void AdminSystem::showStaff(GateSystem &system)
{
    for (auto &s : system.staff)
        s.second.display();
}

void AdminSystem::showVisitors(GateSystem &system)
{
    for (auto &v : system.visitors)
        v.second.display();
}

void AdminSystem::exportCSV()
{
    int id;
    string name, action, reason;
    long time;

    ifstream s("logs/student_logs.txt");
    ofstream scsv("reports/students.csv");

    scsv << "ID,Name,Action,TimeStamp,Reason\n";

    while (s >> id >> name >> action >> time >> reason)
        scsv << id << "," << name << "," << action << "," << time << "," << reason << "\n";

    ifstream st("logs/staff_logs.txt");
    ofstream stcsv("reports/staff.csv");

    stcsv << "ID,Name,Action,TimeStamp,Reason\n";

    while (st >> id >> name >> action >> time >> reason)
        stcsv << id << "," << name << "," << action << "," << time << "," << reason << "\n";

    ifstream v("logs/visitor_logs.txt");
    ofstream vcsv("reports/visitors.csv");

    vcsv << "ID,Name,Action,TimeStamp,Reason\n";

    while (v >> id >> name >> action >> time >> reason)
        vcsv << id << "," << name << "," << action << "," << time << "," << reason << "\n";
}

void AdminSystem::activityTimeline()
{
    typedef struct
    {
        long time;
        string text;
    } LogEntry;

    vector<LogEntry> logs;
    int id;
    string name, action, reason;
    long time;

    ifstream s("logs/student_logs.txt");

    while (s >> id >> name >> action >> time >> reason)
        logs.push_back({time, "Student " + name + " " + action + " (" + reason + ")"});

    ifstream st("logs/staff_logs.txt");

    while (st >> id >> name >> action >> time >> reason)
        logs.push_back({time, "Staff " + name + " " + action + " (" + reason + ")"});

    ifstream v("logs/visitor_logs.txt");

    while (v >> id >> name >> action >> time >> reason)
        logs.push_back({time, "Visitor " + name + " " + action + " (" + reason + ")"});

    sort(logs.begin(), logs.end(),
         [](const LogEntry &a, const LogEntry &b)
         {
             return a.time < b.time;
         });

    cout << "\n------ ACTIVITY TIMELINE ------\n";

    for (auto &l : logs)
    {
        tm *t = localtime(&l.time);

        cout << t->tm_hour << ":"
             << t->tm_min << "  "
             << l.text << endl;
    }
}

void AdminSystem ::dailyAttendanceReport()
{
    ifstream file("logs/student_logs.txt");
    int id;
    string name, action, reason;
    long time;
    map<int, long> entryTime;

    cout << "\n------ DAILY ATTENDANCE REPORT ------\n";
    cout << "ID   Name   Duration\n";

    while (file >> id >> name >> action >> time >> reason)
    {
        if (action == "ENTER")
            entryTime[id] = time;
        else if (action == "EXIT")
        {
            if (entryTime.find(id) != entryTime.end())
            {
                long duration = time - entryTime[id];
                cout << id << " " << name << " " << duration << " seconds\n";
                entryTime.erase(id);
            }
        }
    }
}

void AdminSystem ::gateStatistics(GateSystem &system)
{
    int studentsInside = 0, staffInside = 0, visitorsInside = 0;

    for (auto &s : system.students)
        if (s.second.inside)
            studentsInside++;

    for (auto &s : system.staff)
        if (s.second.inside)
            staffInside++;

    for (auto &v : system.visitors)
        if (v.second.inside)
            visitorsInside++;

    cout << "\n------ GATE STATISTICS ------\n";

    cout << "Students Inside : " << studentsInside << endl;
    cout << "Staff Inside    : " << staffInside << endl;
    cout << "Visitors Inside : " << visitorsInside << endl;
}

void AdminSystem ::gateAnalytics()
{
    ifstream file("logs/student_logs.txt");

    int id;
    string name, action, reason;
    long time;
    int entries = 0, exits = 0;

    map<int, int> hourActivity;

    while (file >> id >> name >> action >> time >> reason)
    {
        tm *t = localtime(&time);
        int hour = t->tm_hour;
        hourActivity[hour]++;
        if (action == "ENTER")
            entries++;
        else if (action == "EXIT")
            exits++;
    }
    int peakHour = -1, maxAcitivity = 0;

    for (auto &h : hourActivity)
    {
        if (h.second > maxAcitivity)
        {
            maxAcitivity = h.second;
            peakHour = h.first;
        }
    }

    cout << "\n------ GATE ANALYTICS ------\n";

    cout << "Entries Today : " << entries << endl;
    cout << "Exits Today   : " << exits << endl;

    if (peakHour != -1)
        cout << "Peak Hour     : " << peakHour << ":00 - " << peakHour + 1 << ":00\n";
}

void AdminSystem ::liveCampusStatus(GateSystem &system)
{
    int studentsInside = 0, staffInside = 0, visitorsInside = 0;

    for (auto &s : system.students)
        if (s.second.inside)
            studentsInside++;

    for (auto &s : system.staff)
        if (s.second.inside)
            staffInside++;

    for (auto &v : system.visitors)
        if (v.second.inside)
            visitorsInside++;

    cout << "\n------ LIVE CAMPUS STATUS ------\n";

    cout << "Students Inside : " << studentsInside << endl;
    cout << "Staff Inside    : " << staffInside << endl;
    cout << "Visitors Inside : " << visitorsInside << endl;

    cout << "Total Inside    : "
         << studentsInside + staffInside + visitorsInside
         << endl;
}