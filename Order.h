#include <iostream>
#include "Chief.h"
using namespace std;
#pragma once

class Order
{
    int ID;
    char Type;
    int RequestTime;
    int Size;
    double Money;
    int AssignmentTime;
    int FinishTime;
    Chief* AssignedChief;
    int Priority;

public:
    Order(int id, char type, int rt, int size, double money)
        : ID(id), Type(type), RequestTime(rt), Size(size), Money(money),
        AssignmentTime(0), FinishTime(0), AssignedChief(nullptr), Priority(0) {
        if (Type == 'V') {
            Priority = (Money / Size) - RequestTime / 100.0;
        }
    }

    void setID(int id) { ID = id; }
    void setType(char type) { Type = type; }
    void setRequestTime(int rt) { RequestTime = rt; }
    void setSize(int size) { Size = size; }
    void setMoney(double money) { Money = money; }
    void setAssignmentTime(int at) { AssignmentTime = at; }
    void setFinishTime(int ft) { FinishTime = ft; }
    void setPriority(int ip) { Priority = ip; }
    void setAssignedChief(Chief* chief) { AssignedChief = chief; }

    int getID() const { return ID; }
    char getType() const { return Type; }
    int getRequestTime() const { return RequestTime; }
    int getSize() const { return Size; }
    double getMoney() const { return Money; }
    int getAssignmentTime() const { return AssignmentTime; }
    int getFinishTime() const { return FinishTime; }
    int getPriority() const { return Priority; }
    Chief* getAssignedChief() const { return AssignedChief; }

    void promoteToVIP(double extraMoney = 0) {
        if (Type != 'V') {
            Type = 'V';
            Money += extraMoney;
            Priority = (Money / Size) - RequestTime / 100.0;
        }
    }

    void Print() const {
        cout << "Order ID: " << getID() << ", Type: ";
        if (Type == 'N') cout << "Normal";
        else if (Type == 'G') cout << "Vegan";
        else if (Type == 'V') cout << "VIP";
        else if (Type == 'E') cout << "Express"; // Bonus: Express Orders
        cout << ", RT: " << getRequestTime() << ", Size: " << getSize() << ", Money: " << getMoney();
        if (getAssignmentTime() > 0) cout << ", GT: " << getAssignmentTime();
        if (getFinishTime() > 0) cout << ", FT: " << getFinishTime();
        if (AssignedChief) cout << ", Chief ID: " << AssignedChief->getID();
        cout << endl;
    }
};

ostream& operator<<(ostream& os, const Order* order);