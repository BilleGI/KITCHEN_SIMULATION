#include "courier.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex courierAccess;
std::condition_variable courierVar;

Courier::Courier(const int& time, const std::vector<std::string>& orders)
{
    this->time = time;
    for(int i = 0; i < orders.size(); ++i)
        this->orders.emplace_back(orders[i]);
}

int Courier::getTime() const
{
    return time;
}

int Courier::getNumOrder() const
{
    return orders.size();
}

std::string Courier::order(const int& i) const
{
    return orders[i];
}

void Courier::deliveryClub(const int& id)
{
    static int deliveryNum = 0;
    std::unique_lock<std::mutex> lockCourier(courierAccess);
    while(id != deliveryNum)
        courierVar.wait(lockCourier);

    std::cout << "\nThe courier " << id << " will be in " << time << " second" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(time));
    std::cout << "\nThe courier took the dishes: ";
    for(int i = 0; i < orders.size(); ++i)
    {
        if( i == (orders.size() - 1))
            std::cout << orders[i] << "." << std::endl;
        else
            std::cout << orders[i] << ", ";
    }
    ++deliveryNum;
    courierVar.notify_all();
}
