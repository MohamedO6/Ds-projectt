#pragma once
#include <iostream>
using namespace std;

class Event
{
protected:
    int TS;
public:
    Event(int ts) : TS(ts) {}

    void setTS(int ts) { TS = ts; }
    int getTS() const { return TS; }

    virtual void Execute(class Restaurant* restaurant) = 0;
    virtual void Print() const = 0;
    virtual ~Event() {}
};

class ArrivalEvent : public Event {
public:
    char Type;
    int ID;
    int Size;
    double Money;

    ArrivalEvent(int ts, char type, int id, int size, double money)
        : Event(ts), Type(type), ID(id), Size(size), Money(money) {
    }

    void Execute(Restaurant* restaurant) override;
    void Print() const override {
        cout << "Arrival Event TS: " << getTS() << ", Type: " << Type
            << ", ID: " << ID << ", Size: " << Size << ", Money: " << Money << endl;
    }
};

class CancellationEvent : public Event {
public:
    int ID;
    CancellationEvent(int ts, int id) : Event(ts), ID(id) {}

    void Execute(Restaurant* restaurant) override;
    void Print() const override {
        cout << "Cancellation Event TS: " << getTS() << ", ID: " << ID << endl;
    }
};

class PromotionEvent : public Event {
public:
    int ID;
    double ExMoney;
    PromotionEvent(int ts, int id, double exMoney)
        : Event(ts), ID(id), ExMoney(exMoney) {
    }
    void Execute(Restaurant* restaurant) override;
    void Print() const override {
        cout << "Promotion Event: TS: " << getTS() << ", ID: " << ID
            << ", Extra Money: " << ExMoney << endl;
    }
};

class ExpressEvent : public Event {
public:
    int ID;
    int Size;
    double Money;
    ExpressEvent(int ts, int id, int size, double money)
        : Event(ts), ID(id), Size(size), Money(money) {
    }
    void Execute(Restaurant* restaurant) override;
    void Print() const override {
        cout << "Express Event TS: " << getTS() << ", ID: " << ID
            << ", Size: " << Size << ", Money: " << Money << endl;
    }
};