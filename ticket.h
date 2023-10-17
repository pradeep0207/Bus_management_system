#ifndef TICKET_H
#define TICKET_H

#include <iostream>

#include "rail.h"

// CLASS TICKET
class Ticket
{
private:
    std::string name="";
    std::string pnrNo="";
    std::string date="";
    Rail rail;

public:
    void generateTicket(std::string n, Rail);
    void displayTicket();
    void bookTicket();
    void cancelTicket();
    void editTicket();
    void showTicketsByPNR();
    void showTicketsByName();
    void showTicketsByRail();
    void showTicketsBySource();
    void showTicketsByDestination();
    void showAllTickets();

    // GETTERS
    std::string getName()
    {
        return name;
    }

    std::string getPnrNo()
    {
        return pnrNo;
    }

    std::string getDate()
    {
        return date;
    }

    // SETTERS
    void setName(const std::string &n)const 
    {
        if (!n.empty())
            name= n;
    }
};
#endif // !TICKET_H
