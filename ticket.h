#ifndef TICKET_H
#define TICKET_H

#include <iostream>

#include "bus.h"

// CLASS TICKET
class Ticket
{
private:
    std::string<char, 20>name;
    std::string<char, 10>pnrNo;
    std::string<char, 20>date;
    Bus bus;

public:
    void generateTicket(char *, Bus);
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
    char *getName()
    {
        return name;
    }

    char *getPnrNo()
    {
        return pnrNo;
    }

    char *getDate()
    {
        return date;
    }

    // SETTERS
    void setName(const char *n)
    {
        if (n && n[0])
            strcpy(name, n);
    }
};
#endif // !TICKET_H
