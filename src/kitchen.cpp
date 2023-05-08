#include "kitchen.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::condition_variable accessVar;
std::mutex prepareAccess;

Kitchen::Kitchen(const std::string& order, const int& time)
{
    this->order = order;
    this->time = time;
}

int Kitchen::getTime() const
{
    return time;
}

std::string Kitchen::getOrder()const
{
    return order;
}

void Kitchen::prepareOrder(const int& id, const int& delay) const
{
    static int numKitchen = 0;
    std::unique_lock<std::mutex> guartPrepare(prepareAccess);
    while(id != numKitchen)
        accessVar.wait(guartPrepare);
//    if(id == 0)
//    {
//        std::cout << "\nWaiting for an order " << id << " - " << delay << " second." << std::endl;
//        std::this_thread::sleep_for(std::chrono::seconds(delay));
//    }
//    else if(id > 0 && delay > 0)
//    {
//        std::cout << "\nWaiting for an order " << id << " - " << delay << " second." << std::endl;
//        std::this_thread::sleep_for(std::chrono::seconds(delay));
//    }

    if(delay > 0)
    {
        std::cout << "\nWaiting for an order " << id << " - " << delay << " second." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(delay));
    }
    std::cout << "\nThe " << order << " dish has started cooking." << std::endl;
    std::cout << "\nTime cooking: " << this->time << " id: " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(this->time));
    std::cout << "\nThe " << order << " dish is cooked." << std::endl;
    ++numKitchen;
    accessVar.notify_all();
}
