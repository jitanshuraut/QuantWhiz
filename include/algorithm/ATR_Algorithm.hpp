#pragma once

#include "indicator/Indicator.h"
#include <vector>

class ATR : public Indicator
{
public:
    ATR(const std::string &indicatorName, int period)
        : Indicator(indicatorName, period) {}

    double calculateSignal() override;
    static std::vector<double> calculate(const std::vector<double> &high, const std::vector<double> &low, const std::vector<double> &close, int period);

private:
    double previousClose = 0.0;
};