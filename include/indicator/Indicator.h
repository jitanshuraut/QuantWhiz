#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "OHLCV.hpp"

class Indicator
{
protected:
    std::vector<double> prices;
    std::vector<double> signals;
    int period;
    std::string name;

public:
    Indicator(const std::string &indicatorName, int period)
        : name(indicatorName), period(period) {}

    virtual ~Indicator() = default;

    void addPrice(double price)
    {
        prices.push_back(price);
        if (prices.size() > period)
        {
            prices.erase(prices.begin());
        }
    }

    virtual double calculateSignal() = 0;

    double getLastSignal() const
    {
        return !signals.empty() ? signals.back() : 0.0;
    }

    const std::vector<double> &getHistoricalSignals() const
    {
        return signals;
    }

    void reset()
    {
        prices.clear();
        signals.clear();
    }

    const std::string &getName() const { return name; }
    int getPeriod() const { return period; }
    int getPriceSize() const {return prices.size();}
    int getSignalSize() const {return signals.size();}

    virtual void adjustParameters(int newPeriod)
    {
        period = newPeriod;
    }

    void backtest(const std::vector<double> &historicalPrices)
    {
        reset();
        for (double price : historicalPrices)
        {
            addPrice(price);
            double signal = calculateSignal();
            signals.push_back(signal);
        }
    }

    void logComputation() const
    {
    }
};
