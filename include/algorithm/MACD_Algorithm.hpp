#ifndef MACD_ALGORITHM_HPP
#define MACD_ALGORITHM_HPP

#include "indicator/Indicator.h"
#include "EMA_Algorithm.hpp"  
#include <vector>
#include <utility>

class MACD : public Indicator
{
public:
    MACD(const std::string &indicatorName, int shortPeriod, int longPeriod, int signalPeriod)
        : Indicator(indicatorName, shortPeriod), shortPeriod(shortPeriod), longPeriod(longPeriod), signalPeriod(signalPeriod)
    {
    }

    double calculateSignal() override;
    void addPrice(double price)
    {
        Indicator::addPrice(price);
        if (prices.size() >= shortPeriod)
        {
            shortEMA = EMA::calculate(prices, shortPeriod);
        }
        if (prices.size() >= longPeriod)
        {
            longEMA = EMA::calculate(prices, longPeriod);
        }
        if (shortEMA.size() > 0 && longEMA.size() > 0)
        {
            double macdValue = shortEMA.back() - longEMA.back();
            macd.push_back(macdValue);
            if (macd.size() >= signalPeriod)
            {
                signalLine = EMA::calculate(macd, signalPeriod);
            }
            if (!macd.empty())
            {
                signals.push_back(macd.back());
            }
        }
    };
    static std::pair<std::vector<double>, std::vector<double>> calculate(const std::vector<OHLCV> &ohlcvData, int shortPeriod, int longPeriod, int signalPeriod);


public:
    int shortPeriod;
    int longPeriod;
    int signalPeriod;

    std::vector<double> shortEMA;
    std::vector<double> longEMA;
    std::vector<double> macd;
    std::vector<double> signalLine;
};

#endif
