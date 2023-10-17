#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "bus.h"
#include "ticket.h"
#include "utils.h"

// ADD BUS
void Bus::addBus()
{
    std::fstream busFileStream;

    system("cls");

    printHeading("ADD BUS");

    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    std::cin.ignore();
    std::getline(std::cin, busNo);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    std::getline(std::cin,source);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    std::getline(std::cin,destination);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source Time:-> ";
    std::getline(std::cin,sourceTime);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination Time:-> ";
    std::getline(std::cin,destinationTime);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Fare:-> ";
    std::cin >> busFare;

    busFileStream.open("buses.txt", std::ios::out | std::ios::app | std::ios::binary);
    busFileStream.write((char *)this, sizeof(*this));
    busFileStream.close();

    std::cout << "\n\t\t\t\t\t\t\t\t\t\tBus Added Successfully...!!!:-> \n";
}

// SHOW BUS DETAILS
void Bus::showBusDetails()
{
    std::cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    std::cout << "\t\t\t\t\t\t\t\t\t\t Bus No:-> " << getBusNo();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Source:-> " << getSource();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Destination:-> " << getDestination();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Time:-> " << getSourceTime() << " - " << getDestinationTime();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Total Seats:-> " << getMaxSeats();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Seats Remaining:-> " << (getMaxSeats() - getBookedSeats());
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Bus Fare:-> " << getBusFare();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    std::cout << "\n";
}

// VIEW ALL BUS INFO
void Bus::showAllBus()
{
    system("cls");

    std::fstream busFileStream;

    busFileStream.open("buses.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (!busFileStream)
        std::cout << "\n\t\t\t\tFile Not Found...!!!";
    else
    {
        printHeading("BUSES");

        busFileStream.read((char *)this, sizeof(*this));

        while (!busFileStream.eof())
        {
            showBusDetails();
            busFileStream.read((char *)this, sizeof(*this));
        }
        busFileStream.close();
    }
}

// VIEW BUS INFO
void Bus::viewBusDetails()
{
    system("cls");

    std::string bNo= "";
    int chk = 0;
    std::fstream busFileStream;

    printHeading("VIEW BUS INFO");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    std::cin.ignore();
    std::getline(std::cin,bNo);

    system("cls");
    printHeading("BUS INFO");

    busFileStream.open("buses.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (busFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (getBusNo().compare(bNo) == 0)
            {
                showBusDetails();
                chk = 1;
            }
            busFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }
        busFileStream.close();
    }
}

// EDIT BUS
void Bus::editBus()
{
    system("cls");

    std::string bNo="";
    int chk = 0;

    std::fstream busFileStream;
    std::fstream tempFileStream;

    printHeading("EDIT BUS");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Number:-> ";
    std::cin.ignore();
    std::getline(std::cin,bNo);

    busFileStream.open("buses.txt", std::ios::in | std::ios::app | std::ios::binary);

    if (busFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        tempFileStream.open("temp.txt", std::ios::out | std::ios::app | std::ios::binary);

        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (getBusNo().compare(bNo) == 0)
            {
                system("cls");
                printHeading("EDIT BUS");

                showBusDetails();

                std::string s="";
                std::string d="";
                std::string sTime="";
                std::string dTime="";
                double fare;
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
                std::getline(std::cin,s);
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
                std::getline(std::cin,d);
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source Time:-> ";
                std::getline(std::cin,sTime);
                std::getline(std::cin,dTime);
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus Fare:-> ";
                std::cin.ignore();
                std::cin >> fare;
                setSource(s);
                setDestination(d);
                setSourceTime(sTime);
                setDestinationTime(dTime);
                setBusFare(fare);
                tempFileStream.write((char *)this, sizeof(*this));

                chk = 1;
            }
            else
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 1)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tBus Updated Successfully...!!\n";
        }
        else
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.txt");
        rename("temp.txt", "buses.txt");
    }
}

// DELETE BUS
void Bus::deleteBus()
{
    system("cls");

    std::string bNo="";
    int chk = 0;
    std::fstream busFileStream;
    std::fstream tempFileStream;

    printHeading("DELETE BUS");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus No:-> ";
    std::cin.ignore();
    std::getline(std::cin,bNo);

    busFileStream.open("buses.txt", std::ios::in | std::ios::app | std::ios::binary);

    if (busFileStream.fail())
    {
        std::cout << "\n\\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        tempFileStream.open("temp.txt", std::ios::out | std::ios::app | std::ios::binary);
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (getBusNo().compare(bNo) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                chk = 1;
            }
            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tBus Not Found...!!\n";
        }
        else
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tBus Deleted...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.txt");
        rename("temp.txt", "buses.txt");
    }
}
