#ifndef TICKET_H
#define TICKET_H

#include <iostream>

#include "bus.h"

// CLASS TICKET
class Ticket
{
private:
    std::string name;
    std::string pnrNo;
    std::string date;
    Bus bus;

public:
    void generateTicket(std::string n, Bus);
    void displayTicket();
    void bookTicket();
    void cancelTicket();
    void editTicket();
    void showTicketsByPNR();
    void showTicketsByName();
    void showTicketsByBus();
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
    void setName(const std::string& n)
    {
        if (!n.empty())
            std::string name= n;
    }
};
#endif // !TICKET_H
