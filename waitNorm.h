#include "LinkedQueue.h"
#include "Order.h"
#include <iostream>
#pragma once
using namespace std;


class waitNorm : public LinkedQueue<Order*> {
public:
    bool CancelOrder(int ID) {
        LinkedQueue<Order*> temp;
        Order* order;
        bool found = false;

        while (dequeue(order)) {
            if (order->getID() == ID) {
                found = true;
                delete order;
            }
            else {
                temp.enqueue(order);
            }
        }

        while (temp.dequeue(order)) {
            enqueue(order);
        }
        return found;
    }

    Order* getOrder(int ID) {
        LinkedQueue<Order*> temp;
        Order* order;
        Order* target = nullptr;
        while (dequeue(order)) {
            if (order->getID() == ID) {
                target = order;
            }
            else {
                temp.enqueue(order);
            }
        }

        while (temp.dequeue(order)) {
            enqueue(order);
        }
        return target;
    }
};
