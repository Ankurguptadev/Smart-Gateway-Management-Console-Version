#include "Validation.h"

using namespace std;

bool Validation::validDegree(const string &degree)
{

    return degree == "BTech" ||
           degree == "BSc" ||
           degree == "MSc" ||
           degree == "BCA" ||
           degree == "MCA" ||
           degree == "MTech";
}

bool Validation::validYear(const string &degree, int year)
{

    if (degree == "BTech")
        return year >= 1 && year <= 4;

    if (degree == "BSc" || degree == "BCA" || degree == "MCA")
        return year >= 1 && year <= 3;

    if (degree == "MSc" || degree == "MTech")
        return year >= 1 && year <= 2;

    return false;
}

bool Validation::validName(const string &name)
{

    return !name.empty();
}