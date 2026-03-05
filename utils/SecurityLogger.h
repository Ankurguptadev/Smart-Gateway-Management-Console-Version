#pragma once
#include <string>

class SecurityLogger
{
public:
    static void logEvent(const std::string &message);
};