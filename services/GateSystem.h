#pragma once

#include <map>
#include "../models/Student.h"
#include "../models/Staff.h"
#include "../models/Visitor.h"

class GateSystem {

public:

    std::map<int, Student> students;
    std::map<int, Staff> staff;
    std::map<int, Visitor> visitors;

    void loadStudents();
    void loadStaff();
    void loadVisitors();

    void saveStudents();
    void saveStaff();
    void saveVisitors();

    void scanID(int id);

private:

    void handleStudent(int id);
    void handleStaff(int id);
    void handleVisitor(int id);
};