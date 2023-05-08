#pragma once
#include <string>

class Kitchen
{
    int time = 0;
    std::string order = "NO ORDER";

public:
    Kitchen(const std::string& order, const int& time);
    int getTime() const;
    std::string getOrder() const;
    void prepareOrder(const int& id, const int& delay) const;
};
