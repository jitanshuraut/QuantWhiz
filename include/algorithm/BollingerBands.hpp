#ifndef BOLLINGERBANDS_HPP
#define BOLLINGERBANDS_HPP

#include "indicator/Indicator.h"
#include <vector>
#include <utility>

class BollingerBands : public Indicator
{
private:
    double numStdDev;

public:
    BollingerBands(const std::string &indicatorName, int period, double numStdDev)
        : Indicator(indicatorName, period), numStdDev(numStdDev) {}

    SignalResult calculateSignal() override; 
    std::pair<double, double> calculate() const;
    static std::pair<double, double> calculate(const std::vector<double> &prices, int period, double numStdDev);
};

#endif
