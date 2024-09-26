#pragma once

#include "Indicator.h"
#include <vector>

class EMA : public Indicator {
public:
    EMA(const std::string& indicatorName, int period)
        : Indicator(indicatorName, period) {}

    double calculateSignal() override;
    static std::vector<double> calculate(const std::vector<double>& prices, std::size_t period);
};
