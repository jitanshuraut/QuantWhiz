#pragma once
#include <vector>

class SMA {
public:
    static std::vector<double> calculate(const std::vector<double>& prices, int period);
};
