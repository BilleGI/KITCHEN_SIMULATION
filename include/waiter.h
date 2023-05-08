#pragma once
#include <string>
#include <mutex>

class Waiter
{
    int time = 0;
    std::string order = "NO ORDER";
public:
    Waiter(const int& numDish, const int& time);
    std::string getOrder() const;
    int getTime() const;
    void newOrder(const int& id);
};
