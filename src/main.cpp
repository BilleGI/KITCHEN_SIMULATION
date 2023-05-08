#include <iostream>
#include <thread>
#include <ctime>
#include <vector>
#include "waiter.h"
#include "kitchen.h"
#include "courier.h"

const int DISHES(10);
const int TIMECOURIER(30);

int main()
{
    std::srand(std::time(nullptr));
    std::vector<Waiter> waiters;
    std::vector<Kitchen> prepares;
    std::vector<Courier> couriers;

    std::cout << "The program simulates the operation of the kitchen" << std::endl;

    for (int i = 0; i < DISHES; ++i)
    {
        int numDish = (std::rand() % 5);
        int time = ((rand()%6)+5);
        Waiter waiter(numDish, time);
        waiters.push_back(waiter);
    }

    for (int i =0; i < DISHES; ++i)
    {
        int time = ((rand()%6)+10);
        Kitchen kitchen(waiters[i].getOrder(), time);
        prepares.push_back(kitchen);
    }

    std::vector<std::thread> orderThread;
    for(int i = 0; i < DISHES; ++i)
    {
        orderThread.emplace_back(&Waiter::newOrder,std::ref(waiters[i]), i);
    }

    int timeOrder = 0;
    int timeCooking = 0;
    std::vector<std::thread> preparesOrder;
    for(int i = 0; i < DISHES; ++i)
    {
        timeOrder+=waiters[i].getTime();
        preparesOrder.emplace_back(&Kitchen::prepareOrder, std::ref(prepares[i]), i, timeOrder - timeCooking);
        if(i == 0) timeOrder =0;
        if(timeOrder > timeCooking)
            timeCooking = timeOrder;
        timeCooking += prepares[i].getTime();
    }

    timeOrder = waiters[0].getTime();
    int *j = new int;
    *j = 0;
    for(int i = 0; i < (((timeCooking + waiters[0].getTime())/TIMECOURIER) + 1); ++i)
    {
        std::vector<std::string> orders;
        while(true)
        {
            timeOrder += prepares[*j].getTime();
            if(timeOrder > (TIMECOURIER * (i+1)))
            {
                timeOrder -= prepares[*j].getTime();
                break;
            }
            orders.emplace_back(prepares[*j].getOrder());
            ++(*j);
            if((*j) == DISHES) break;
        }
        Courier courier(TIMECOURIER, orders);
        couriers.push_back(courier);
    }
    delete j;

    std::vector<std::thread> threadDelivery;
    for(int i = 0; i < couriers.size(); ++i)
    {
        threadDelivery.emplace_back(&Courier::deliveryClub, std::ref(couriers[i]), i);
    }

    for(int i = 0; i < orderThread.size(); ++i)
        orderThread[i].join();

    for(int i = 0; i < preparesOrder.size(); ++i)
        preparesOrder[i].join();

    for(int i = 0; i < threadDelivery.size(); ++i)
        threadDelivery[i].join();

    return 0;
}



//for (int i = 0; i < DISHES; ++i)
//{
//    int time = ((rand()%6)+10);
//    Kitchen kitchen(waiters[i].getOrder(), time);
//    prepares.push_back(kitchen);
//}

////    std::vector<std::thread> orderThread;
////    for (int i = 0; i < DISHES; ++i) {
////        orderThread.emplace_back(&Waiter::newOrder, std::ref(waiters[i]), i);
////    }

//int  timeOrder=0;
//int timeCooking=0;
//std::vector<std::thread> preparesOrder;
//for(int i = 0; i < DISHES; ++i)
//{
//    timeOrder+=waiters[i].getTime();
//    preparesOrder.emplace_back(&Kitchen::prepareOrder,std::ref(prepares[i]), i, timeOrder - timeCooking);
//    if(i == 0) timeOrder = 0;
//    if(timeOrder > timeCooking)
//        timeCooking = timeOrder;
//    timeCooking +=prepares[i].getTime();
//}

////    timeOrder = waiters[0].getTime();
////    int *j = new int;
////    *j = 0;
////    for (int i = 0 ; i < (((timeCooking+waiters[0].getTime())/TIMECOURIER) + 1); ++i)
////    {
////        std::vector<std::string> orders;
////        while (true)
////        {
////            timeOrder += prepares[*j].getTime();
////            if(timeOrder >(TIMECOURIER* (i+1)))
////            {
////                timeOrder -=prepares[*j].getTime();
////                break;
////            }
////            orders.emplace_back(prepares[*j].getOrder());
////            ++(*j);
////            if((*j) == DISHES ) break;
////        }

////        Courier courier(TIMECOURIER, orders);
////        couriers.push_back(courier);
////    }
////    delete j;

////    std::vector<std::thread> threadDelivery;
////    for (int i = 0; i < couriers.size(); ++i)
////    {
////        threadDelivery.emplace_back(&Courier::deliveryClub, couriers[i], i);
////    }

////    for (int i = 0; i < DISHES; ++i)
////    {
////        orderThread[i].join();
////    }

//for(int i = 0; i < DISHES; ++i)
//    preparesOrder[i].join();
////    for (int i = 0; i < threadDelivery.size(); ++i)
////    {
////        threadDelivery[i].join();
////    }
