#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

using namespace std;

void printHeading(const std::string& header)
{
    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t==========================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t                       " << header << "                     \n";
    cout << "\t\t\t\t\t\t\t\t\t\t==========================================================\n\n";
}

std::string generatePNR(int n)
{
    std::srand(std::time(0)); // Seed the random number generator

    int randomNo = std::rand() % n;

    return "PNR" + std::to_string(randomNo);
}

string getCurrentDate()
{
    time_t t = time(NULL);
    tm *tPtr = localtime(&t);

    return to_string(tPtr->tm_mday) + "-" + to_string((tPtr->tm_mon) + 1) + "-" + to_string((tPtr->tm_year) + 1900);
}
#endif // UTILS_H
