#include "SMA_Algorithm.hpp"
#include <stdexcept>
#include <numeric>

double SMA::calculateSignal()
{
    if (prices.size() < period)
    {
        throw std::runtime_error("Not enough data to calculate SMA.");
    }

    double sum = std::accumulate(prices.end() - period, prices.end(), 0.0);
    double sma = sum / period;

    signals.push_back(sma);
    return sma;
}

std::vector<double> SMA::calculate(const std::vector<double> &prices, int period)
{
}
