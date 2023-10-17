#ifndef RAIL_H
#define RAIL_H

#include <iostream>

class Rail
{
private:
    int maxSeats=32;
    int bookedSeats=0;
    double RailFare=0.0;
    std::string RailNo="";
    std::string source="";
    std::string destination="";
    std::string sourceTime="";
    std::string destinationTime="";

public:

    // METHODS
    void addRail();
    void showAllRail();
    void showRailDetails();
    void viewRailDetails();
    void deleteRail();
    void editRail();

    // GETTERS
    std::string getRailNo()
    {
        return RailNo;
    }

    std::string getSource()
    {
        return source;
    }

    std::string getDestination()
    {
        return destination;
    }

    std::string getSourceTime()
    {
        return sourceTime;
    }

    std::string getDestinationTime()
    {
        return destinationTime;
    }

    int getBookedSeats()
    {
        return bookedSeats;
    }

    int getMaxSeats()
    {
        return maxSeats;
    }

    double getRailFare()
    {
        return RailFare;
    }

    // SETTERS
    void setBookedSeats()
    {
        bookedSeats++;
    }

    void setCancelTicket()
    {
        bookedSeats--;
    }

    void setSource(const std::string &s)const 
    {
        if (!s.empty())
            source= s;
    }

    void setDestination(const std::string &d)const 
    {
        if (!d.empty())
            destination= d;
    }

    void setSourceTime(const std::string &s)const 
    {
        if (!s.empty())
            sourceTime= s;
    }

    void setDestinationTime(const std::string &d)const 
    {
        if (!d.empty())
            destinationTime= d;
    }

    void setRailFare(double f)
    {
        if (f)
            RailFare = f;
    }
};
#endif // !RAIL_H
