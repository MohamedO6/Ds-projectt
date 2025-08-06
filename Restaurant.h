#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include "Chief.h"
#include "Order.h"
#include "waitNorm.h"
#include "ArrayStack.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "Event.h"
using namespace std;
#pragma once

class Restaurant {
public:
    LinkedQueue<Event*> Events;
    priQueue<Order*> WaitingVIP;
    LinkedQueue<Order*> WaitingVegan;
    waitNorm WaitingNormal;
    LinkedQueue<Order*> WaitingExpress; // Bonus: Express Orders
    priQueue<Order*> InService;
    ArrayStack<Order*> Done;
    priQueue<Chief*> ReadyVIP;    // Changed to priQueue for Speed sorting
    priQueue<Chief*> ReadyVegan;  // Changed to priQueue
    priQueue<Chief*> ReadyNormal; // Changed to priQueue
    priQueue<Chief*> ReadyExpress; // Bonus: Express Chiefs
    priQueue<Chief*> InBreak;
    priQueue<Chief*> Busy;

    int N, G, V, E;
    int BO, BN, BG, BV, BE;
    int AutoP;
    bool isSilentMode; // Interactive/Silent Mode
    int totalVIPOrders, totalVeganOrders, totalNormalOrders, totalExpressOrders;
    int autoPromotedOrders;

    Restaurant() : N(0), G(0), V(0), E(0), BO(0), BN(0), BG(0), BV(0), BE(0), AutoP(0),
        isSilentMode(false), totalVIPOrders(0), totalVeganOrders(0),
        totalNormalOrders(0), totalExpressOrders(0), autoPromotedOrders(0) {
        srand((unsigned int)time(0));
    }

    void AddEvent(Event* event) { Events.enqueue(event); }
    void AddWaitingVIP(Order* order) { WaitingVIP.enqueue(order, order->getPriority()); totalVIPOrders++; }
    void AddWaitingVegan(Order* order) { WaitingVegan.enqueue(order); totalVeganOrders++; }
    void AddWaitingNormal(Order* order) { WaitingNormal.enqueue(order); totalNormalOrders++; }
    void AddWaitingExpress(Order* order) { WaitingExpress.enqueue(order); totalExpressOrders++; }
    void AddInService(Order* order) {
        order->setPriority(-order->getFinishTime());
        InService.enqueue(order, order->getPriority());
    }
    void AddDone(Order* order) { Done.push(order); }
    void AddReadyVIP(Chief* chief) { ReadyVIP.enqueue(chief, chief->getSpeed()); }
    void AddReadyVegan(Chief* chief) { ReadyVegan.enqueue(chief, chief->getSpeed()); }
    void AddReadyNormal(Chief* chief) { ReadyNormal.enqueue(chief, chief->getSpeed()); }
    void AddReadyExpress(Chief* chief) { ReadyExpress.enqueue(chief, chief->getSpeed()); }
    void AddInBreak(Chief* chief) { InBreak.enqueue(chief, -chief->getBreakEndTime()); }
    void AddBusy(Chief* chief) { Busy.enqueue(chief, -chief->getSpeed()); } // Priority based on speed (faster chiefs first)

    int CountEvents() { return Events.size(); }
    int CountWaitingVIP() { return WaitingVIP.size(); }
    int CountWaitingVegan() { return WaitingVegan.size(); }
    int CountWaitingNormal() { return WaitingNormal.size(); }
    int CountWaitingExpress() { return WaitingExpress.size(); }
    int CountInService() { return InService.size(); }
    int CountDone() { return Done.size(); }
    int CountReadyVIP() { return ReadyVIP.size(); }
    int CountReadyVegan() { return ReadyVegan.size(); }
    int CountReadyNormal() { return ReadyNormal.size(); }
    int CountReadyExpress() { return ReadyExpress.size(); }
    int CountInBreak() { return InBreak.size(); }
    int CountBusy() { return Busy.size(); }

    void PrintEventsLimited() {
        if (isSilentMode) return;
        cout << "Events (" << CountEvents() << "):" << endl;
        LinkedQueue<Event*> temp = Events;
        Event* event;
        int count = 0;
        while (temp.dequeue(event) && count < 10) {
            cout << "[";
            if (ArrivalEvent* a = dynamic_cast<ArrivalEvent*>(event)) {
                cout << a->Type << ", " << a->getTS() << ", " << a->ID << "] ";
            }
            else if (CancellationEvent* c = dynamic_cast<CancellationEvent*>(event)) {
                cout << "X, " << c->getTS() << ", " << c->ID << "] ";
            }
            else if (PromotionEvent* p = dynamic_cast<PromotionEvent*>(event)) {
                cout << "P, " << p->getTS() << ", " << p->ID << "] ";
            }
            else if (ExpressEvent* e = dynamic_cast<ExpressEvent*>(event)) {
                cout << "E, " << e->getTS() << ", " << e->ID << "] ";
            }
            count++;
        }
        cout << "\n" << endl;
    }

    void PrintOrders() {
        if (isSilentMode) return;
        cout << string(20, '-') << " Waiting Orders IDs: " << string(20, '-') << "\n" << endl;
        cout << CountWaitingNormal() << " NRM orders: ";
        LinkedQueue<Order*> tempN = WaitingNormal;
        Order* order;
        while (tempN.dequeue(order)) cout << order->getID() << " ";
        cout << endl;

        cout << CountWaitingVegan() << " VEG orders: ";
        LinkedQueue<Order*> tempG = WaitingVegan;
        while (tempG.dequeue(order)) cout << order->getID() << " ";
        cout << endl;

        cout << CountWaitingVIP() << " VIP orders: ";
        priQueue<Order*> tempV = WaitingVIP;
        int pri;
        while (tempV.dequeue(order, pri)) cout << order->getID() << " ";
        cout << endl;

        cout << CountWaitingExpress() << " EXP orders: ";
        LinkedQueue<Order*> tempE = WaitingExpress;
        while (tempE.dequeue(order)) cout << order->getID() << " ";
        cout << "\n" << endl;
    }

    void PrintChiefs() {
        if (isSilentMode) return;
        cout << string(20, '-') << " Available Chiefs IDs: " << string(20, '-') << "\n" << endl;
        cout << CountReadyNormal() << " NRM chiefs: ";
        priQueue<Chief*> tempN = ReadyNormal;
        Chief* chief;
        int pri;
        while (tempN.dequeue(chief, pri)) cout << chief->getID() << " ";
        cout << endl;

        cout << CountReadyVegan() << " VEG chiefs: ";
        priQueue<Chief*> tempG = ReadyVegan;
        while (tempG.dequeue(chief, pri)) cout << chief->getID() << " ";
        cout << endl;

        cout << CountReadyVIP() << " VIP chiefs: ";
        priQueue<Chief*> tempV = ReadyVIP;
        while (tempV.dequeue(chief, pri)) cout << chief->getID() << " ";
        cout << endl;

        cout << CountReadyExpress() << " EXP chiefs: ";
        priQueue<Chief*> tempE = ReadyExpress;
        while (tempE.dequeue(chief, pri)) cout << chief->getID() << " ";
        cout << endl;

        cout << CountInBreak() << " chiefs in break: ";
        priQueue<Chief*> tempB = InBreak;
        while (tempB.dequeue(chief, pri)) cout << chief->getID() << " ";
        cout << endl;

        cout << CountBusy() << " busy chiefs: ";
        priQueue<Chief*> tempBusy = Busy;
        while (tempBusy.dequeue(chief, pri)) cout << chief->getID() << " ";
        cout << "\n" << endl;
    }

    void PrintInService() {
        if (isSilentMode) return;
        cout << string(20, '-') << " In-service (" << CountInService() << "): " << string(20, '-') << "\n" << endl;
        priQueue<Order*> temp = InService;
        Order* order;
        int pri;
        while (temp.dequeue(order, pri)) {
            cout << order->getID() << "(" << order->getSize() << ")->"
                << order->getAssignedChief()->getID() << "(" << order->getAssignedChief()->getSpeed() << ") ";
        }
        cout << "\n" << endl;
    }

    void PrintDone() {
        if (isSilentMode) return;
        cout << string(20, '-') << " Done (" << CountDone() << "): " << string(20, '-') << endl;
        ArrayStack<Order*> temp = Done;
        Order* order;
        while (temp.pop(order)) cout << order->getID() << " ";
        cout << endl;
    }

    bool LoadFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;

        if (!(file >> N >> G >> V >> E)) return false;
        if (!(file >> BO >> BN >> BG >> BV >> BE)) return false;
        if (!(file >> AutoP)) return false;

        int id = 1;
        for (int i = 0; i < N; i++) {
            int speed, breakDuration;
            if (!(file >> speed >> breakDuration)) return false;
            AddReadyNormal(new Chief('N', speed, breakDuration, id++));
        }
        for (int i = 0; i < G; i++) {
            int speed, breakDuration;
            if (!(file >> speed >> breakDuration)) return false;
            AddReadyVegan(new Chief('G', speed, breakDuration, id++));
        }
        for (int i = 0; i < V; i++) {
            int speed, breakDuration;
            if (!(file >> speed >> breakDuration)) return false;
            AddReadyVIP(new Chief('V', speed, breakDuration, id++));
        }
        for (int i = 0; i < E; i++) {
            int speed, breakDuration;
            if (!(file >> speed >> breakDuration)) return false;
            AddReadyExpress(new Chief('E', speed, breakDuration, id++));
        }

        int M;
        if (!(file >> M)) return false;

        for (int i = 0; i < M; i++) {
            char eventType;
            int ts, id, size;
            double money;

            if (!(file >> eventType >> ts)) {
                cout << "[Error] Failed to read event type/timestamp.\n";
                return false;
            }

            if (eventType == 'R') {
                char type;
                if (!(file >> type >> id >> size >> money)) return false;
                Events.enqueue(new ArrivalEvent(ts, type, id, size, money));
            }
            else if (eventType == 'X') {
                if (!(file >> id)) return false;
                Events.enqueue(new CancellationEvent(ts, id));
            }
            else if (eventType == 'P') {
                double exMoney;
                if (!(file >> id >> exMoney)) return false;
                Events.enqueue(new PromotionEvent(ts, id, exMoney));
            }
            else if (eventType == 'E') {
                if (!(file >> id >> size >> money)) return false;
                Events.enqueue(new ExpressEvent(ts, id, size, money));
            }
            else {
                cout << "[Warning] Unknown event type: " << eventType << endl;
            }
        }

        file.close();
        cout << "[Info] File loaded successfully.\n";
        return true;
    }

    bool AssignChief(Order* order, int currentTime) {
        Chief* chief = nullptr;
        int pri;
        if (order->getType() == 'V') {
            if (!ReadyVIP.isEmpty()) ReadyVIP.dequeue(chief, pri);
            else if (!ReadyNormal.isEmpty()) ReadyNormal.dequeue(chief, pri);
            else if (!ReadyVegan.isEmpty()) ReadyVegan.dequeue(chief, pri);
        }
        else if (order->getType() == 'G') {
            if (!ReadyVegan.isEmpty()) ReadyVegan.dequeue(chief, pri);
        }
        else if (order->getType() == 'N') {
            if (!ReadyNormal.isEmpty()) ReadyNormal.dequeue(chief, pri);
            else if (!ReadyVIP.isEmpty()) ReadyVIP.dequeue(chief, pri);
        }
        else if (order->getType() == 'E') {
            if (!ReadyExpress.isEmpty()) ReadyExpress.dequeue(chief, pri);
        }

        if (chief) {
            if (chief->getIsInjured() && chief->getInjuryRestPeriod() > currentTime) {
                chief->setSpeed(chief->getSpeed() / 2);
            }

            // Check if chief is already busy by searching in busy queue
            priQueue<Chief*> tempBusy = Busy;
            Chief* tempChief;
            int tempPri;
            bool isBusy = false;
            while (tempBusy.dequeue(tempChief, tempPri)) {
                if (tempChief == chief) {
                    isBusy = true;
                    break;
                }
            }
            
            if (isBusy) {
                if (chief->getType() == 'V') AddReadyVIP(chief);
                else if (chief->getType() == 'G') AddReadyVegan(chief);
                else if (chief->getType() == 'N') AddReadyNormal(chief);
                else if(chief->getType() == 'E')AddReadyExpress(chief);
                else return false;
            }

            order->setAssignedChief(chief);
            order->setAssignmentTime(currentTime);
            int st = (int)ceil((double)order->getSize() / chief->getSpeed());
            order->setFinishTime(currentTime + st);
            chief->incrementOrdersServed();

            AddBusy(chief);

            return true;
        }
        return false;
    }

    void Simulate() {
        int currentTime = 0;
        Order* order;
        while (!Events.isEmpty() || !WaitingVIP.isEmpty() || !WaitingVegan.isEmpty() ||
            !WaitingNormal.isEmpty() || !WaitingExpress.isEmpty() || !InService.isEmpty()) {
            if (!isSilentMode) {
                cout << "\n=== Timestep " << currentTime << " ===" << "\n" << endl;
                PrintEventsLimited();
                PrintOrders();
                PrintChiefs();
                PrintInService();
                PrintDone();
                cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!" << endl;
                cin.get();
            }

            LinkedQueue<Event*> tempEvents;
            Event* event;
            while (Events.dequeue(event)) {
                if (event->getTS() > currentTime) {
                    tempEvents.enqueue(event);
                }
                else {
                    event->Execute(this);
                    delete event;
                }
            }
            while (tempEvents.dequeue(event)) {
                Events.enqueue(event);
            }

            // Check AutoP for Normal Orders
            waitNorm tempNormal = WaitingNormal;
            WaitingNormal.clear();
            while (tempNormal.dequeue(order)) {
                if (currentTime - order->getRequestTime() > AutoP && order->getType() == 'N') {
                    order->promoteToVIP(0);
                    autoPromotedOrders++;
                    AddWaitingVIP(order);
                }
                else {
                    WaitingNormal.enqueue(order);
                }
            }

            // Process Waiting Orders
            priQueue<Order*> tempVIP = WaitingVIP;
            WaitingVIP.clear();
            int pri;
            while (tempVIP.dequeue(order, pri)) {
                if (AssignChief(order, currentTime)) {
                    AddInService(order);
                }
                else {
                    WaitingVIP.enqueue(order, order->getPriority());
                }
            }

            LinkedQueue<Order*> tempVegan = WaitingVegan;
            WaitingVegan.clear();
            while (tempVegan.dequeue(order)) {
                if (AssignChief(order, currentTime)) {
                    AddInService(order);
                }
                else {
                    WaitingVegan.enqueue(order);
                }
            }

            tempNormal = WaitingNormal;
            WaitingNormal.clear();
            while (tempNormal.dequeue(order)) {
                if (AssignChief(order, currentTime)) {
                    AddInService(order);
                }
                else {
                    WaitingNormal.enqueue(order);
                }
            }

            LinkedQueue<Order*> tempExpress = WaitingExpress;
            WaitingExpress.clear();
            while (tempExpress.dequeue(order)) {
                if (AssignChief(order, currentTime)) {
                    AddInService(order);
                }
                else {
                    WaitingExpress.enqueue(order);
                }
            }

            // Process InService Orders
            priQueue<Order*> tempInService = InService;
            InService.clear();
            while (tempInService.dequeue(order, pri)) {
                if (order->getFinishTime() <= currentTime) {
                    Chief* chief = order->getAssignedChief();
                    if (chief) {
                        priQueue<Chief*> tempBusy = Busy;
                        Busy.clear();
                        Chief* tempChief;
                        int tempPri;
                        while (tempBusy.dequeue(tempChief, tempPri)) {
                            if (tempChief != chief) {
                                Busy.enqueue(tempChief, tempPri);
                            }
                        }
                        
                        if (chief->getOrdersServed() >= BO) {
                            chief->setBreakEndTime(currentTime + chief->getBreakDuration());
                            chief->setOrdersServed(0);
                            AddInBreak(chief);
                        } else {
                            if (chief->getType() == 'V') AddReadyVIP(chief);
                            else if (chief->getType() == 'G') AddReadyVegan(chief);
                            else if (chief->getType() == 'N') AddReadyNormal(chief);
                            else AddReadyExpress(chief);
                        }
                    }
                    AddDone(order);
                }
                else {
                    InService.enqueue(order, order->getPriority());
                }
            }

            // Process InBreak Chiefs
            priQueue<Chief*> tempInBreak = InBreak;
            InBreak.clear();
            Chief* chief;
            while (tempInBreak.dequeue(chief, pri)) {
                if (chief->getBreakEndTime() <= currentTime) {
                    chief->setBreakEndTime(0);
                    if (chief->getType() == 'V') AddReadyVIP(chief);
                    else if (chief->getType() == 'G') AddReadyVegan(chief);
                    else if (chief->getType() == 'N') AddReadyNormal(chief);
                    else AddReadyExpress(chief);
                }
                else {
                    InBreak.enqueue(chief, -chief->getBreakEndTime());
                }
            }

            //Health Emergency Check
            priQueue<Chief*> tempChiefs;
            tempChiefs = ReadyVIP;
            ReadyVIP.clear();
            while (tempChiefs.dequeue(chief, pri)) {
                if (rand() % 100 < 1 && !chief->getIsInjured()) {
                    chief->setInjured(true, currentTime + 5);
                }
                AddReadyVIP(chief);
            }

            tempChiefs = ReadyVegan;
            ReadyVegan.clear();
            while (tempChiefs.dequeue(chief, pri)) {
                if (rand() % 100 < 1 && !chief->getIsInjured()) {
                    chief->setInjured(true, currentTime + 5);
                }
                AddReadyVegan(chief);
            }

            tempChiefs = ReadyNormal;
            ReadyNormal.clear();
            while (tempChiefs.dequeue(chief, pri)) {
                if (rand() % 100 < 1 && !chief->getIsInjured()) {
                    chief->setInjured(true, currentTime + 5);
                }
                AddReadyNormal(chief);
            }

            tempChiefs = ReadyExpress;
            ReadyExpress.clear();
            while (tempChiefs.dequeue(chief, pri)) {
                if (rand() % 100 < 1 && !chief->getIsInjured()) {
                    chief->setInjured(true, currentTime + 5);
                }
                AddReadyExpress(chief);
            }

            currentTime++;
        }
        cout << "\nSimulation ended at timestep " << currentTime << endl;
    }

    void GenerateOutputFile(const string& filename) {
        ofstream file(filename);
        ArrayStack<Order*> temp = Done;
        Order* order;
        double totalWT = 0, totalST = 0;
        int count = 0;

        file << "FT ID RT WT ST\n";
        while (temp.pop(order)) {
            int wt = order->getAssignmentTime() - order->getRequestTime();
            int st = order->getFinishTime() - order->getAssignmentTime();
            file << order->getFinishTime() << " " << order->getID() << " "
                << order->getRequestTime() << " " << wt << " " << st << "\n";
            totalWT += wt;
            totalST += st;
            count++;
        }

        file << "\nStatistics:\n";
        file << "Total Orders: " << count << "\n";
        file << "VIP Orders: " << totalVIPOrders << "\n";
        file << "Vegan Orders: " << totalVeganOrders << "\n";
        file << "Normal Orders: " << totalNormalOrders << "\n";
        file << "Express Orders: " << totalExpressOrders << "\n";
        file << "Total Chiefs: " << (N + G + V + E) << "\n";
        file << "Normal Chiefs: " << N << "\n";
        file << "Vegan Chiefs: " << G << "\n";
        file << "VIP Chiefs: " << V << "\n";
        file << "Express Chiefs: " << E << "\n";
        file << "Average Waiting Time: " << (count ? totalWT / count : 0) << "\n";
        file << "Average Service Time: " << (count ? totalST / count : 0) << "\n";
        file << "Auto-Promoted Orders: " << (totalNormalOrders ? (autoPromotedOrders * 100.0 / totalNormalOrders) : 0) << "%\n";

        file.close();
    }

    void CleanUp() {
        Event* event;
        int pri;
        Order* order;
        Chief* chief;
        while (Events.dequeue(event)) delete event;
        while (WaitingVIP.dequeue(order, pri)) delete order;
        while (WaitingVegan.dequeue(order)) delete order;
        while (WaitingNormal.dequeue(order)) delete order;
        while (WaitingExpress.dequeue(order)) delete order;
        while (InService.dequeue(order, pri)) delete order;
        while (Done.pop(order)) delete order;
        while (ReadyVIP.dequeue(chief, pri)) delete chief;
        while (ReadyVegan.dequeue(chief, pri)) delete chief;
        while (ReadyNormal.dequeue(chief, pri)) delete chief;
        while (ReadyExpress.dequeue(chief, pri)) delete chief;
        while (InBreak.dequeue(chief, pri)) delete chief;
        while (Busy.dequeue(chief, pri)) delete chief;
    }
};