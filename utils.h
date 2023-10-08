#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <chrono>

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

std::string getCurrentDate()
{
    auto now = std::chrono::system_clock::now();

    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm tPtr = *std::localtime(&t);

    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &tPtr);

    return std::string(buffer);
}
#endif
