#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "ticket.h"
#include "rail.h"
#include "utils.h"

// GENERATE TICKET
void Ticket::generateTicket(std::string n, Rail b)
{
    name =n;
    pnrNo = generatePNR(99999).c_str();
    date =getCurrentDate().c_str();
    rail = b;
}

// DISPLAY TICKET DETAILS
void Ticket::displayTicket()
{
    std::cout << "\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    std::cout << "\t\t\t\t\t\t\t\t\t\t Name:-> " << getName();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t PNR No:-> " << getPnrNo();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t rail No:-> " << rail.getRailNo();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Seat No.:-> " << rail.getBookedSeats();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Date:-> " << getDate();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t From:-> " << rail.getSource();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t To:-> " << rail.getDestination();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Source Time:-> " << rail.getSourceTime();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t Destination Time:-> " << rail.getDestinationTime();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t rail Fare:-> " << rail.getRailFare();
    std::cout << "\n\t\t\t\t\t\t\t\t\t\t-------------------------------------------------\n";
    std::cout << "\n";
}

// BOOK TICKET
void Ticket::bookTicket()
{
    system("cls");

    std::string from;
    std::string to;

    int chk = 0;

    Rail b;
    std::fstream railFileStream;
    std::fstream ticketFileStream;
    std::fstream tempFileStream;

    printHeading("BOOK TICKET");

    railFileStream.open("railes.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (railFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }
    else
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
        std::cin.ignore();
        std::getline(std::cin,from);
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
        std::getline(std::cin,to);

        system("cls");
        printHeading("AVAILABLE RAILS");

        railFileStream.read((char *)&b, sizeof(b));
        while (!railFileStream.eof())
        {
            if (b.getSource() == from && b.getDestination() == to)
            {
                b.showRailDetails();
                chk = 1;
            }
            railFileStream.read((char *)&b, sizeof(b));
        }

        railFileStream.close();

        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tNo rails Found...!!\n";
        }
        else
        {
            std::string bNo;
            int booked = 0;

            std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter RAIL Number:-> ";
            std::getline(std::cin,bNo);

            railFileStream.open("railes.txt", std::ios::in | std::ios::app | std::ios::binary);
            tempFileStream.open("temp.txt", std::ios::out | std::ios::app | std::ios::binary);

            railFileStream.read((char *)&b, sizeof(b));
            while (!railFileStream.eof())
            {
                if (b.getSource() == from && b.getDestination() == to && b.getRailNo().compare(bNo) == 0)
                {
                    if (b.getBookedSeats() >= 32)
                    {
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\tSeat not available...!!\n";
                        break;
                    }
                    else
                    {
                        system("cls");
                        printHeading("BOOK TICKET");
                        std::string n;
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Customer Name :-> ";
                        std::getline(std::cin,n);
                        b.setBookedSeats();
                        generateTicket(n, b);
                        ticketFileStream.open("tickets.txt", std::ios::out | std::ios::app | std::ios::binary);
                        ticketFileStream.write((char *)this, sizeof(*this));
                        ticketFileStream.close();
                        tempFileStream.write((char *)&b, sizeof(b));

                        booked = 1;
                        system("cls");
                        printHeading("BOOKING DETAILS");
                        displayTicket();
                        std::cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Booked Successfully...!!\n";
                    }
                }
                else
                {
                    tempFileStream.write((char *)&b, sizeof(b));
                }
                railFileStream.read((char *)&b, sizeof(b));
            }

            if (booked == 1)
            {
                railFileStream.close();
                tempFileStream.close();
                remove("railes.txt");
                rename("temp.txt", "railes.txt");
            }
        }
        railFileStream.close();
    }
}

// CANCEL TICKET
void Ticket::cancelTicket()
{
    system("cls");

    std::string pnr;
    int chk = 0;

    std::fstream railFileStream;
    std::fstream ticketFileStream;
    std::fstream tempFileStream;
    std::fstream railTempFileStream;

    printHeading("CANCEL TICKET");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    std::cin.ignore();
    std::getline(std::cin,pnr);

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);
    tempFileStream.open("temp.txt", std::ios::out | std::ios::app | std::ios::binary);

    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getPnrNo().compare(pnr) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                Rail b;
                railFileStream.open("railes.txt",std::ios::in | std::ios::app | std::ios::binary);
                railTempFileStream.open("railtemp.txt", std::ios::out | std::ios::app | std::ios::binary);

                railFileStream.read((char *)&b, sizeof(b));
                while (!railFileStream.eof())
                {
                    if (b.getRailNo().compare(rail.getRailNo()) == 0)
                    {
                        b.setCancelTicket();
                        railTempFileStream.write((char *)&b, sizeof(b));
                    }
                    else
                    {
                        railTempFileStream.write((char *)&b, sizeof(b));
                    }
                    railFileStream.read((char *)&b, sizeof(b));
                }
                railFileStream.close();
                railTempFileStream.close();
                remove("railes.txt");
                rename("railtemp.txt", "railes.txt");
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            ticketFileStream.close();
            tempFileStream.close();
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!\n";
        }
        else
        {
            ticketFileStream.close();
            tempFileStream.close();
            remove("tickets.txt");
            rename("temp.txt", "tickets.txt");
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Cancelled...!!\n";
        }
    }
}

// EDIT TICKET
void Ticket::editTicket()
{
    system("cls");

    std::string pnr;
    int chk = 0;

    std::fstream ticketFileStream;
    std::fstream tempFileStream;

    printHeading("EDIT TICKET");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    std::cin.ignore();
    std::getline(std::cin, pnr);

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);

    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        tempFileStream.open("temp.txt", std::ios::out | std::ios::app | std::ios::binary);

        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getPnrNo().compare(pnr) == 0)
            {
                system("cls");
                printHeading("EDIT TICKET");

                displayTicket();
                std::string n;
                std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name :-> ";
                std::getline(std::cin,n);
                setName(n);
                tempFileStream.write((char *)this, sizeof(*this));

                chk = 1;
            }
            else
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 1)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Updated Successfully...!!\n";
        }
        else
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!\n";
        }

        ticketFileStream.close();
        tempFileStream.close();
        remove("tickets.txt");
        rename("temp.txt", "tickets.txt");
    }
}

// SHOW TICKET BY PNR
void Ticket::showTicketsByPNR()
{
    system("cls");

    std::string pnr;
    int chk = 0;
    std::fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY PNR");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    std::cin.ignore();
    std::getline(std::cin,pnr);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getPnrNo().compare(pnr) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY NAME
void Ticket::showTicketsByName()
{
    system("cls");

    std::string n;
    int chk = 0;
    std::fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Passenger Name:-> ";
    std::cin.ignore();
    std::getline(std::cin,n);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (getName()== n)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

void Ticket::showTicketsByRail()
{
    system("cls");

    std::string bNo;
    int chk = 0;
    std::fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter rail Number:-> ";
    std::cin.ignore();
    std::getline(std::cin,bNo);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (rail.getRailNo().compare(bNo) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY SOURCE
void Ticket::showTicketsBySource()
{
    system("cls");

    std::string s;
    int chk = 0;
    std::fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY SOURCE");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Source:-> ";
    std::cin.ignore();
    std::getline(std::cin,s);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (rail.getSource() == s)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW TICKET BY DESTINATION
void Ticket::showTicketsByDestination()
{
    system("cls");

    std::string d;
    int chk = 0;
    std::fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY DESTINATION");
    std::cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Destination:-> ";
    std::cin.ignore();
    std::getline(std::cin,d);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (rail.getDestination() == d)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            std::cout << "\n\t\t\t\t\t\t\t\t\t\tNo Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

// SHOW ALL BOOKINGS
void Ticket::showAllTickets()
{
    system("cls");

    std::fstream ticketFileStream;

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.txt", std::ios::in | std::ios::app | std::ios::binary);
    if (ticketFileStream.fail())
    {
        std::cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            displayTicket();
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        ticketFileStream.close();
    }
}
