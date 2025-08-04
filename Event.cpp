#include "Event.h"
#include "Order.h"
#include "Restaurant.h"

void ArrivalEvent::Execute(Restaurant* restaurant) {
    Order* order = new Order(ID, Type, TS, Size, Money);
    if (Type == 'V') {
        restaurant->AddWaitingVIP(order);
    }
    else if (Type == 'G') {
        restaurant->AddWaitingVegan(order);
    }
    else {
        restaurant->AddWaitingNormal(order);
    }
}

void CancellationEvent::Execute(Restaurant* restaurant) {
    bool success = restaurant->WaitingNormal.CancelOrder(ID);
    if (!success) {
        cout << "[Warning] CancellationEvent failed: Order ID " << ID << " not found.\n";
    }
}

void PromotionEvent::Execute(Restaurant* restaurant) {
    Order* order = restaurant->WaitingNormal.getOrder(ID);
    if (order) {
        restaurant->WaitingNormal.CancelOrder(ID);
        order->promoteToVIP(ExMoney);
        restaurant->AddWaitingVIP(order);
    }
    else {
        cout << "[Warning] PromotionEvent failed: Order ID " << ID << " not found.\n";
    }
}

void ExpressEvent::Execute(Restaurant* restaurant) {
    Order* order = new Order(ID, 'E', TS, Size, Money);
    restaurant->AddWaitingExpress(order);
}