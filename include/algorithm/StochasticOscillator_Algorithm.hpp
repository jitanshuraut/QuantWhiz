#pragma once

#include "indicator/Indicator.h"
#include <vector>

class StochasticOscillator : public Indicator
{
public:
    StochasticOscillator(const std::string &indicatorName, int period, int smoothK, int smoothD)
        : Indicator(indicatorName, period), smoothK(smoothK), smoothD(smoothD) {}

    double calculateSignal() override;
    static std::vector<std::pair<double, double>> calculate(const std::vector<double> &high, const std::vector<double> &low, const std::vector<double> &close, int period, int smoothK, int smoothD);

private:
    int smoothK;
    int smoothD;
};