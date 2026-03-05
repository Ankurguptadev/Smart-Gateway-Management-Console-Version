#pragma once
#include <string>
#include <iostream>

class Staff
{

public:
    int id;
    std::string name;
    std::string department;
    std::string role;
    bool inside;
    bool blocked;

    Staff() {}

    Staff(int i, std::string n, std::string d, std::string r,
          bool in = false, bool bl = false)
    {
        id = i;
        name = n;
        department = d;
        role = r;
        inside = in;
        blocked = bl;
    }

    void display()
    {

        std::cout << id << " | " << name << " | "
                  << department << " | " << role
                  << " | " << (inside ? "Inside" : "Outside")
                  << " | " << (blocked ? "Blocked" : "Active")
                  << std::endl;
    }

    std::string serialize()
    {

        return std::to_string(id) + " " + name + " " +
               department + " " + role + " " +
               std::to_string(inside) + " " +
               std::to_string(blocked);
    }
};