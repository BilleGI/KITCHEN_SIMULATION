#pragma once
#include <vector>
#include <string>

class Courier
{
    int time = 0;
    std::vector<std::string> orders;
public:
    Courier(const int& time, const std::vector<std::string>& orders);
    int getTime() const;
    int getNumOrder() const;
    std::string order(const int& i) const;
    void deliveryClub(const int &id);
};
