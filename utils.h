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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n - 1);

    // Generate a random number
    int randomNo = dis(gen);

    return "PNR" + std::to_string(randomNo);
}

std::string getCurrentDate()
{
    auto now = std::chrono::system_clock::now();

    auto time = std::chrono::system_clock::to_time_t(now);
    struct tm tmInfo;
    
    #ifdef _WIN32
    localtime_s(&tmInfo, &time); // Windows version of localtime_r
    #else
    localtime_r(&time, &tmInfo); // POSIX version of localtime_r
    #endif

    std::string formattedDate = std::to_string(tmInfo.tm_mday) + "-" +
                                std::to_string(tmInfo.tm_mon + 1) + "-" +
                                std::to_string(tmInfo.tm_year + 1900);

    return formattedDate;
}
#endif
