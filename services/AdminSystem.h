#pragma once

#include "GateSystem.h"
#include <map>
#include <string>

class AdminSystem {

private:

    std::map<std::string,std::string> admins;

    int nextStudentID = 1001;
    int nextStaffID   = 2001;
    int nextVisitorID = 5001;

public:

    void loadAdmins();
    bool login();

    void initializeIDs(GateSystem &system);

    void adminMenu(GateSystem &system);

private:

    void addStudent(GateSystem &system);
    void addStaff(GateSystem &system);
    void addVisitor(GateSystem &system);

    void removeStudent(GateSystem &system);
    void removeStaff(GateSystem &system);

    void blockUnblock(GateSystem &system);

    void searchUser(GateSystem &system);

    void showStudents(GateSystem &system);
    void showStaff(GateSystem &system);
    void showVisitors(GateSystem &system);

    void exportCSV();

    void activityTimeline();

    void gateStatistics(GateSystem &system);
    void dailyAttendanceReport();
    void gateAnalytics();
    void liveCampusStatus(GateSystem &system);
};