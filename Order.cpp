#include "Order.h"


ostream& operator<<(ostream& os, const Order* order) {
    order->Print();
    return os;
}
