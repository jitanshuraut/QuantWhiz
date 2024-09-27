#include "algorithm/MACD_Algorithm.hpp"
#include "algorithm/EMA_Algorithm.hpp"
#include <stdexcept>

double MACD::calculateSignal()
{
    if (signals.empty())
    {
        throw std::runtime_error("Not enough data to calculate MACD.");
    }

    return signals.back();
}

std::pair<std::vector<double>, std::vector<double>> MACD::calculate(const std::vector<double> &prices, int shortPeriod, int longPeriod, int signalPeriod)
{
    if (prices.size() < longPeriod)
    {
        throw std::runtime_error("Not enough data to calculate MACD.");
    }

    std::vector<double> shortEMA = EMA::calculate(prices, shortPeriod);
    std::vector<double> longEMA = EMA::calculate(prices, longPeriod);

    std::vector<double> macd(prices.size(), 0.0);
    for (size_t i = 0; i < prices.size(); ++i)
    {
        macd[i] = shortEMA[i] - longEMA[i];
    }

    std::vector<double> signalLine = EMA::calculate(macd, signalPeriod);

    return {macd, signalLine};
}
