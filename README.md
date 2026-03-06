# Smart Campus Gate Management System (Console Version)

## Overview

The **Smart Campus Gate Management System** is a C++ console-based
application that simulates a real-world campus security gate system.

The system manages entry and exit of **students, staff, and visitors**,
records gate activity, generates attendance reports, and maintains
security logs.

It demonstrates **object-oriented programming, modular architecture,
file-based data storage, and system analytics**.

------------------------------------------------------------------------

# Features

## User Management

-   Add students
-   Add staff
-   Add visitors
-   Remove users
-   Block or unblock users
-   Auto-generated IDs

## Gate Entry System

-   ID-based gate scanning
-   Automatic entry/exit detection
-   Exit reason recording
-   Late entry detection

## Visitor Management

-   Visitor registration
-   Purpose tracking
-   Meeting person tracking

## Security System

-   Admin authentication
-   Security event logging
-   Blocked user detection

## Reporting & Analytics

-   Daily attendance reports
-   CSV export of attendance
-   Activity timeline
-   Gate statistics
-   Peak hour detection

## Search System

-   Partial name search for users

------------------------------------------------------------------------

# Technologies Used

  Technology                    Purpose
  ----------------------------- --------------------------------
  C++                           Core programming language
  STL                           Data structures and algorithms
  File handling                 Persistent storage
  Object-Oriented Programming   System design

------------------------------------------------------------------------

# Project Structure

    SmartGateSystem

    main.cpp

    models
        Student.h
        Staff.h
        Visitor.h

    services
        GateSystem.h
        GateSystem.cpp
        AdminSystem.h
        AdminSystem.cpp

    utils
        Validation.h
        Validation.cpp
        SecurityLogger.h
        SecurityLogger.cpp

    data
        students.txt
        staff.txt
        visitors.txt
        admins.txt

    logs
        student_logs.txt
        staff_logs.txt
        visitor_logs.txt
        security_logs.txt
        late_entries.txt

    reports
        attendance_students.csv
        attendance_staff.csv
        attendance_visitors.csv

------------------------------------------------------------------------

# Compilation

Compile using **g++**

    g++ main.cpp services/*.cpp utils/*.cpp -o SmartGate

Run the program

    SmartGate.exe

------------------------------------------------------------------------

# Example Program Output

### Main Menu

    SMART GATE SYSTEM

    1 Admin Login
    2 Scan ID
    3 Exit

------------------------------------------------------------------------

### Admin Panel

    ------ ADMIN PANEL ------

    1 Add Student
    2 Add Staff
    3 Add Visitor
    4 Remove Student
    5 Remove Staff
    6 Block/Unblock User
    7 Show Students
    8 Show Staff
    9 Show Visitors
    10 Search User
    11 Daily Attendance Report
    12 Export Attendance CSV
    13 Activity Timeline
    14 Gate Statistics
    15 Gate Analytics
    16 Logout

------------------------------------------------------------------------

# Learning Outcomes

This project demonstrates:

-   Object-Oriented System Design
-   Modular C++ Architecture
-   File-based Database Design
-   Security Logging Systems
-   Attendance Analytics
-   Command-line Interface Design

------------------------------------------------------------------------

# Future Improvements

Possible upgrades:

-   Qt GUI dashboard
-   RFID / QR code scanning
-   SQL database integration
-   Mobile monitoring application
-   Cloud analytics system

------------------------------------------------------------------------

# Author

Developed as a **C++ system programming project** demonstrating campus
access management and monitoring systems.
