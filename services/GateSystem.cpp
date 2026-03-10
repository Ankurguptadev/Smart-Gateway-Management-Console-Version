#include "GateSystem.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <limits>

using namespace std;

void GateSystem::loadStudents()
{
    try
    {
        ifstream file;
        file.exceptions(ifstream::failbit | ifstream::badbit);
        file.open("data/students.txt");

        int id, year, batch, inside, blocked;
        string name, degree, branch;

        while (file >> id >> name >> degree >> branch >> year >> batch >> inside >> blocked)
        {
            students[id] = Student(id, name, degree, branch, year, batch, inside, blocked);
        }

        file.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Error loading students file: " << e.what() << endl;
    }
}

void GateSystem::loadStaff()
{
    try
    {
        ifstream file;
        file.exceptions(ifstream::failbit | ifstream::badbit);
        file.open("data/staff.txt");

        int id, inside, blocked;
        string name, dept, role;

        while (file >> id >> name >> dept >> role >> inside >> blocked)
        {
            staff[id] = Staff(id, name, dept, role, inside, blocked);
        }

        file.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Error loading staff file: " << e.what() << endl;
    }
}

void GateSystem::loadVisitors()
{
    try
    {
        ifstream file;
        file.exceptions(ifstream::failbit | ifstream::badbit);
        file.open("data/visitors.txt");

        int id, inside;
        string name, purpose, meet;

        while (file >> id >> name >> purpose >> meet >> inside)
        {
            visitors[id] = Visitor(id, name, purpose, meet, inside);
        }

        file.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Error loading visitors file: " << e.what() << endl;
    }
}

void GateSystem::saveStudents()
{
    try
    {
        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit);
        file.open("data/students.txt");

        for (auto &s : students)
            file << s.second.serialize() << endl;

        file.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Error saving students file: " << e.what() << endl;
    }
}

void GateSystem::saveStaff()
{
    try
    {
        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit);
        file.open("data/staff.txt");

        for (auto &s : staff)
            file << s.second.serialize() << endl;

        file.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Error saving staff file: " << e.what() << endl;
    }
}

void GateSystem::saveVisitors()
{
    try
    {
        ofstream file;
        file.exceptions(ofstream::failbit | ofstream::badbit);
        file.open("data/visitors.txt");

        for (auto &v : visitors)
            file << v.second.serialize() << endl;

        file.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Error saving visitors file: " << e.what() << endl;
    }
}

void GateSystem::scanID(int id)
{
    if (id >= 1000 && id < 2000)
        handleStudent(id);
    else if (id >= 2000 && id < 3000)
        handleStaff(id);
    else if (id >= 5000 && id < 6000)
        handleVisitor(id);
    else
    {
        cout << "Unknown ID\n";

        try
        {
            ofstream log;
            log.exceptions(ofstream::failbit | ofstream::badbit);
            log.open("logs/security_log.txt", ios::app);

            time_t now = time(0);
            log << ctime(&now) << "UNKNOWN ID " << id << endl;

            log.close();
        }
        catch (const ios_base::failure &e)
        {
            cout << "Logging error: " << e.what() << endl;
        }
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

        try
        {
            ofstream log;
            log.exceptions(ofstream::failbit | ofstream::badbit);
            log.open("logs/security_log.txt", ios::app);

            time_t now = time(0);
            log << ctime(&now) << "BLOCKED STUDENT " << id << endl;

            log.close();
        }
        catch (const ios_base::failure &e)
        {
            cout << "Logging error: " << e.what() << endl;
        }

        return;
    }

    time_t now = time(0);
    tm *t = localtime(&now);

    cout << "\nStudent Information\n";
    cout << "-------------------\n";
    cout << "Name   : " << s.name << endl;
    cout << "Branch : " << s.branch << endl;
    cout << "Year   : " << s.year << endl;

    try
    {
        ofstream log;
        log.exceptions(ofstream::failbit | ofstream::badbit);
        log.open("logs/student_logs.txt", ios::app);

        if (!s.inside)
        {
            if (t->tm_hour > 20 || (t->tm_hour == 20 && t->tm_min > 30))
            {
                cout << "WARNING: Returning after curfew (8:30 PM)\n";

                ofstream curfew("logs/curfew_violations.txt", ios::app);
                curfew << id << " " << s.name << " " << now << endl;
            }

            s.inside = true;
            cout << "Status : ENTERED\n";
            log << id << " " << s.name << " ENTER " << now << " NA\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string reason;
            cout << "Reason for exit: ";
            getline(cin, reason);

            if (reason == "")
                reason = "NA";

            s.inside = false;

            cout << "Status : EXITED\n";
            log << id << " " << s.name << " EXIT " << now << " " << reason << endl;
        }

        log.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Student log error: " << e.what() << endl;
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

        try
        {
            ofstream log("logs/security_log.txt", ios::app);
            time_t now = time(0);
            log << ctime(&now) << "BLOCKED STAFF " << id << endl;
        }
        catch (...)
        {
            cout << "Logging error\n";
        }

        return;
    }

    time_t now = time(0);

    cout << "\nStaff Information\n";
    cout << "-----------------\n";
    cout << "Name       : " << s.name << endl;
    cout << "Department : " << s.department << endl;
    cout << "Role       : " << s.role << endl;

    try
    {
        ofstream log;
        log.exceptions(ofstream::failbit | ofstream::badbit);
        log.open("logs/staff_logs.txt", ios::app);

        if (!s.inside)
        {
            s.inside = true;
            cout << "Status : ENTERED\n";
            log << id << " " << s.name << " ENTER " << now << " NA\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string reason;
            cout << "Reason (optional): ";
            getline(cin, reason);

            if (reason == "")
                reason = "NA";

            s.inside = false;

            cout << "Status : EXITED\n";
            log << id << " " << s.name << " EXIT " << now << " " << reason << endl;
        }

        log.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Staff log error: " << e.what() << endl;
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

    cout << "\nVisitor Information\n";
    cout << "-------------------\n";
    cout << "Name   : " << v.name << endl;
    cout << "Purpose: " << v.purpose << endl;
    cout << "Meeting: " << v.personToMeet << endl;

    try
    {
        ofstream log;
        log.exceptions(ofstream::failbit | ofstream::badbit);
        log.open("logs/visitor_logs.txt", ios::app);

        if (!v.inside)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string reason;
            cout << "Reason for entry: ";
            getline(cin, reason);

            if (reason == "")
                reason = "NA";

            v.inside = true;

            cout << "Status : ENTERED\n";
            log << id << " " << v.name << " ENTER " << now << " " << reason << endl;
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string reason;
            cout << "Reason (optional): ";
            getline(cin, reason);

            if (reason == "")
                reason = "NA";

            v.inside = false;

            cout << "Status : EXITED\n";
            log << id << " " << v.name << " EXIT " << now << " " << reason << endl;
        }

        log.close();
    }
    catch (const ios_base::failure &e)
    {
        cout << "Visitor log error: " << e.what() << endl;
    }

    saveVisitors();
}
