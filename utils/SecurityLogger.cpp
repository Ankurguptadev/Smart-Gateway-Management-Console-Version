#include "SecurityLogger.h"
#include <fstream>
#include <ctime>

using namespace std;

void SecurityLogger::logEvent(const string &message)
{

    ofstream file("logs/security_log.txt", ios::app);

    time_t now = time(0);

    file << ctime(&now) << " : " << message << endl;
}