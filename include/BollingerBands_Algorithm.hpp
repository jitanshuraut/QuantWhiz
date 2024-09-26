#ifndef BOLLINGERBANDS_HPP
#define BOLLINGERBANDS_HPP

#include "Indicator.h" // Include the base class header
#include <vector>
#include <utility>

class BollingerBands : public Indicator
{
private:
    double numStdDev;

public:
    BollingerBands(const std::string &indicatorName, int period, double numStdDev)
        : Indicator(indicatorName, period), numStdDev(numStdDev) {}
    double calculateSignal() override;
    void addPrice(double price)
    {
        prices.push_back(price);
        if (prices.size() >= period)
        {
            calculateSignal();
        }
    }
    std::pair<double, double> calculate() const;
};

#endif
