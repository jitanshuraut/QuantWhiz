#include "RSI_Algorithm.hpp"
#include <stdexcept>
#include <numeric>

double RSI::calculateSignal()
{
    if (prices.size() < period)
    {
        throw std::runtime_error("Not enough data to calculate RSI.");
    }

    std::vector<double> gains;
    std::vector<double> losses;

    for (std::size_t i = 1; i < prices.size(); ++i)
    {
        double change = prices[i] - prices[i - 1];
        if (change > 0)
        {
            gains.push_back(change);
            losses.push_back(0.0);
        }
        else
        {
            losses.push_back(-change);
            gains.push_back(0.0);
        }
    }

    double avgGain = std::accumulate(gains.end() - period, gains.end(), 0.0) / period;
    double avgLoss = std::accumulate(losses.end() - period, losses.end(), 0.0) / period;

    if (avgLoss == 0)
        return 100.0;

    double rs = avgGain / avgLoss;
    double rsi = 100.0 - (100.0 / (1.0 + rs));

    signals.push_back(rsi);
    return rsi;
}

std::vector<double> RSI::calculate(const std::vector<double> &prices, std::size_t period)
{
}
