#include "algorithm/ATR_Algorithm.hpp"
#include <algorithm>
#include <cmath>

double ATR::calculateSignal()
{
    if (prices.size() < 2)
    {
        throw std::runtime_error("Not enough data to calculate ATR.");
    }

    double high = prices[prices.size() - 2];
    double low = prices[prices.size() - 1];
    double close = prices.back();

    double tr = std::max({high - low, std::abs(high - previousClose), std::abs(low - previousClose)});
    previousClose = close;

    if (signals.empty())
    {
        signals.push_back(tr);
    }
    else
    {
        double atr = (signals.back() * (period - 1) + tr) / period;
        signals.push_back(atr);
    }

    return signals.back();
}

std::vector<double> ATR::calculate(const std::vector<double> &high, const std::vector<double> &low, const std::vector<double> &close, int period)
{
    // Implementation details...
}