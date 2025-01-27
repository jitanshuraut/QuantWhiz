#pragma once

#include "indicator/Indicator.h"
#include <vector>
#include "SignalResult.hpp"

class ADX : public Indicator
{
public:
    ADX(const std::string &indicatorName, int period)
        : Indicator(indicatorName, period) {}

    SignalResult calculateSignal() override;
    static std::vector<double> calculate(const std::vector<OHLCV> &data, int period);
};
