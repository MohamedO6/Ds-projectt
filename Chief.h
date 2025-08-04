#pragma once
#include <iostream>
using namespace std;

class Chief
{
    char Type;
    int Speed;
    int BreakDuration;
    int OrdersServed;
    int BreakEndTime;
    bool isInjured;        // Bonus: Health Emergency
    int injuryRestPeriod;  // Bonus: Health Emergency
    int ID;                // Bonus: Unique ID for printing

public:
    Chief(char type, int speed, int breakDuration, int id)
        : Type(type), Speed(speed), BreakDuration(breakDuration),
        OrdersServed(0), BreakEndTime(0), isInjured(false), injuryRestPeriod(0), ID(id) {
    }

    char getType() const { return Type; }
    int getSpeed() const { return isInjured ? Speed / 2 : Speed; } // Bonus: Half speed if injured
    int getBreakDuration() const { return BreakDuration; }
    int getOrdersServed() const { return OrdersServed; }
    int getBreakEndTime() const { return BreakEndTime; }
    bool getIsInjured() const { return isInjured; }
    int getInjuryRestPeriod() const { return injuryRestPeriod; }
    int getID() const { return ID; }

    void setType(char type) { Type = type; }
    void setSpeed(int speed) { Speed = speed; }
    void setBreakDuration(int duration) { BreakDuration = duration; }
    void setOrdersServed(int count) { OrdersServed = count; }
    void incrementOrdersServed() { OrdersServed++; }
    void setBreakEndTime(int bt) { BreakEndTime = bt; }
    void setInjured(bool status, int restPeriod) {
        isInjured = status;
        injuryRestPeriod = restPeriod;
    }

    void Print() const {
        cout << "Chief ID: " << ID << ", Type: " << Type << ", Speed: " << getSpeed()
            << ", Break Duration: " << BreakDuration << ", Orders Served: " << OrdersServed;
        if (BreakEndTime > 0) cout << ", Break End: " << BreakEndTime;
        if (isInjured) cout << ", Injured: Yes, Rest Period: " << injuryRestPeriod;
        cout << endl;
    }
};

ostream& operator<<(ostream& os, const Chief* chief);