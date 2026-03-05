#pragma once

#include <string>

class Validation {

public:

    static bool validDegree(const std::string &degree);

    static bool validYear(const std::string &degree, int year);

    static bool validName(const std::string &name);
};