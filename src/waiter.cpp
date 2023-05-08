#include "waiter.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <condition_variable>

std::mutex orderAccess;
std::condition_variable orderVar;

enum dish
{
    PIZZA = 1,
    SOUP = 2,
    STEAK = 4,
    SALAD = 8,
    SUSHI = 16,
};

Waiter::Waiter(const int& numDish, const int& time)
{
    if(pow(2,numDish) == dish::PIZZA) order = "pizza";
    else if(pow(2, numDish) == dish::SOUP) order = "soup";
    else if(pow(2, numDish) == dish::STEAK) order = "steak";
    else if(pow(2, numDish) == dish::SALAD) order = "salad";
    else if(pow(2,numDish) == dish::SUSHI) order = "sushi";
    this->time = time;
}

std::string Waiter::getOrder() const
{
    return order;
}

int Waiter::getTime() const
{
    return time;
}

void Waiter::newOrder(const int& id)
{
    static int numOrder =0;
    std::unique_lock<std::mutex> lockAccess(orderAccess);
    while(id != numOrder)
        orderVar.wait(lockAccess);
    std::cout << "\nThe " << order << " dish was order." << std::endl;
    std::cout << "\nTime order: " << time << " id: " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(time));
    std::cout << "\nDish " << order << " ordered." << std::endl;
    ++numOrder;
    orderVar.notify_all();
}
