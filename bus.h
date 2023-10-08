#ifndef BUS_H
#define BUS_H

#include <iostream>

using namespace std;

// CLASS BUS
class Bus
{
private:
    int maxSeats;
    int bookedSeats;
    double busFare;
    std::string<int, 10> busNo;
    std::string<int, 20> source;
    std::string<int, 20>destination;
    std::string<int, 20>sourceTime;
    std::string<int, 20>destinationTime;

public:
    Bus(int a=32,int b=0,double c=0.0)
    {
        strcpy(busNo, "");
        maxSeats=a;
        bookedSeats=b;
        busFare=c;
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(sourceTime, "");
        strcpy(destinationTime, "");
    }

    // METHODS
    void addBus();
    void showAllBus();
    void showBusDetails();
    void viewBusDetails();
    void deleteBus();
    void editBus();

    // GETTERS
    char *getBusNo()
    {
        return busNo;
    }

    char *getSource()
    {

        return source;
    }

    char *getDestination()
    {
        return destination;
    }

    char *getSourceTime()
    {
        return sourceTime;
    }

    char *getDestinationTime()
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

    double getBusFare()
    {
        return busFare;
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

    void setSource(char *s)
    {
        if (s && s[0])
            strcpy(source, s);
    }

    void setDestination(char *d)
    {
        if (d && d[0])
            strcpy(destination, d);
    }

    void setSourceTime(char *s)
    {
        if (s && s[0])
            strcpy(sourceTime, s);
    }

    void setDestinationTime(char *d)
    {
        if (d && d[0])
            strcpy(destinationTime, d);
    }

    void setBusFare(double f)
    {
        if (f)
            busFare = f;
    }
};
#endif // !BUS_H
