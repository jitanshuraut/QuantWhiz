#pragma once

#include "indicator/Indicator.h"
#include <vector>

class SMA : public Indicator
{
public:
    SMA(const std::string &indicatorName, int period)
        : Indicator(indicatorName, period) {}

    double calculateSignal() override;
    static std::vector<double> calculate(const std::vector<double> &prices, int period);
};
