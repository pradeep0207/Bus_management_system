#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "rail.h"
#include "ticket.h"
#include "utils.h"

void Rail::addRail()
{
    std::fstream railFileStream;

    system("cls");

    printHeading("ADD RAIL");

    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Rail Number:-> ";
    std::cin.ignore();
    std::getline(std::cin, RailNo);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    std::getline(std::cin,source);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    std::getline(std::cin,destination);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source Time:-> ";
    std::getline(std::cin,sourceTime);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination Time:-> ";
    std::getline(std::cin,destinationTime);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter rail Fare:-> ";
    std::cin >> RailFare;

    railFileStream.open("railes.txt", std::ios::out | std::ios::app | std::ios::binary);
    railFileStream.write((char *)this, sizeof(*this));
    railFileStream.close();

    std::cout << "\n\t\t\t\t\t\t\t\t\t\trail Added Successfully...!!!:-> \n";
}

void Rail::showRailDetails()
{
    std::cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    std::cout << "\t\t\t\t\t\t\t\t\t\t Rail No:-> " << getRailNo();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Source:-> " << getSource();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Destination:-> " << getDestination();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Time:-> " << getSourceTime() << " - " << getDestinationTime();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Total Seats:-> " << getMaxSeats();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Seats Remaining:-> " << (getMaxSeats() - getBookedSeats());
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Rail Fare:-> " << getRailFare();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    std::cout << "\n";
}

void Rail::showAllRail()
{
    system("cls");

    std::fstream railFileStream;

    railFileStream.open("railes.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (!railFileStream)
        std::cout << "\n\t\t\t\tFile Not Found...!!!";
    else
    {
        printHeading("RailES");

        railFileStream.read((char *)this, sizeof(*this));

        while (!railFileStream.eof())
        {
            showRailDetails();
            railFileStream.read((char *)this, sizeof(*this));
        }
        railFileStream.close();
    }
}

void Rail::viewRailDetails()
{
    system("cls");

    std::string bNo= "";
    int chk = 0;
    std::fstream railFileStream;

    printHeading("VIEW Rail INFO");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Rail Number:-> ";
    std::cin.ignore();
    std::getline(std::cin,bNo);

    system("cls");
    printHeading("Rail INFO");

    railFileStream.open("railes.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (railFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        railFileStream.read((char *)this, sizeof(*this));
        while (!railFileStream.eof())
        {
            if (getRailNo().compare(bNo) == 0)
            {
                showRailDetails();
                chk = 1;
            }
            railFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tRail Not Found...!!\n";
        }
        railFileStream.close();
    }
}

void Rail::editRail()
{
    system("cls");

    std::string bNo="";
    int chk = 0;

    std::fstream railFileStream;
    std::fstream tempFileStream;

    printHeading("EDIT rail");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Rail Number:-> ";
    std::cin.ignore();
    std::getline(std::cin,bNo);

    railFileStream.open("railes.txt", std::ios::in | std::ios::app | std::ios::binary);

    if (railFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        tempFileStream.open("temp.txt", std::ios::out | std::ios::app | std::ios::binary);

        railFileStream.read((char *)this, sizeof(*this));
        while (!railFileStream.eof())
        {
            if (getRailNo().compare(bNo) == 0)
            {
                system("cls");
                printHeading("EDIT rail");

                showRailDetails();

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
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Rail Fare:-> ";
                std::cin.ignore();
                std::cin >> fare;
                setSource(s);
                setDestination(d);
                setSourceTime(sTime);
                setDestinationTime(dTime);
                setRailFare(fare);
                tempFileStream.write((char *)this, sizeof(*this));

                chk = 1;
            }
            else
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            railFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 1)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tRail Updated Successfully...!!\n";
        }
        else
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tRail Not Found...!!\n";
        }

        railFileStream.close();
        tempFileStream.close();
        remove("railes.txt");
        rename("temp.txt", "railes.txt");
    }
}

void Rail::deleteRail()
{
    system("cls");

    std::string bNo="";
    int chk = 0;
    std::fstream railFileStream;
    std::fstream tempFileStream;

    printHeading("DELETE Rail");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Rail No:-> ";
    std::cin.ignore();
    std::getline(std::cin,bNo);

    railFileStream.open("railes.txt", std::ios::in | std::ios::app | std::ios::binary);

    if (railFileStream.fail())
    {
        std::cout << "\n\\t\t\t\t\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else
    {
        tempFileStream.open("temp.txt", std::ios::out | std::ios::app | std::ios::binary);
        railFileStream.read((char *)this, sizeof(*this));
        while (!railFileStream.eof())
        {
            if (getRailNo().compare(bNo) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                chk = 1;
            }
            railFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tRail Not Found...!!\n";
        }
        else
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tRail Deleted...!!\n";
        }

        railFileStream.close();
        tempFileStream.close();
        remove("railes.txt");
        rename("temp.txt", "railes.txt");
    }
}
