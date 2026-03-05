#pragma once
#include <string>
#include <iostream>

class Student
{

public:
    int id;
    std::string name;
    std::string degree;
    std::string branch;
    int year;
    int batch;
    bool inside;
    bool blocked;

    Student() {}

    Student(int i, std::string n, std::string d, std::string b,
            int y, int ba, bool in = false, bool bl = false)
    {
        id = i;
        name = n;
        degree = d;
        branch = b;
        year = y;
        batch = ba;
        inside = in;
        blocked = bl;
    }

    void display()
    {

        std::cout << id << " | " << name << " | "
                  << degree << " | " << branch
                  << " | Year " << year
                  << " | Batch " << batch
                  << " | " << (inside ? "Inside" : "Outside")
                  << " | " << (blocked ? "Blocked" : "Active")
                  << std::endl;
    }

    std::string serialize()
    {

        return std::to_string(id) + " " + name + " " + degree + " " +
               branch + " " + std::to_string(year) + " " +
               std::to_string(batch) + " " +
               std::to_string(inside) + " " +
               std::to_string(blocked);
    }
};