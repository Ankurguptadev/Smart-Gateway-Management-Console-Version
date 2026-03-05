#pragma once
#include <string>
#include <iostream>

class Visitor
{

public:
    int id;
    std::string name;
    std::string purpose;
    std::string personToMeet;
    bool inside;

    Visitor() {}

    Visitor(int i, std::string n, std::string p,
            std::string meet, bool in = false)
    {
        id = i;
        name = n;
        purpose = p;
        personToMeet = meet;
        inside = in;
    }

    void display()
    {

        std::cout << id << " | " << name
                  << " | " << purpose
                  << " | " << personToMeet
                  << " | " << (inside ? "Inside" : "Outside")
                  << std::endl;
    }

    std::string serialize()
    {

        return std::to_string(id) + " " + name + " " +
               purpose + " " + personToMeet + " " +
               std::to_string(inside);
    }
};