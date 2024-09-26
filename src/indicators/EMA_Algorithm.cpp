#include "EMA_Algorithm.hpp"

double EMA::calculateSignal()
{
    if (prices.empty())
    {
        throw std::runtime_error("Not enough data to calculate EMA.");
    }

    std::vector<double> ema(prices.size(), 0.0);
    double multiplier = 2.0 / (period + 1);

    double sum = 0.0;
    for (std::size_t i = 0; i < period && i < prices.size(); ++i)
    {
        sum += prices[i];
    }
    ema[period - 1] = sum / period;

    for (std::size_t i = period; i < prices.size(); ++i)
    {
        ema[i] = ((prices[i] - ema[i - 1]) * multiplier) + ema[i - 1];
    }
    signals.push_back(ema.back());
    return signals.back();
}

std::vector<double> EMA::calculate(const std::vector<double> &prices, std::size_t period)
{
    std::vector<double> ema(prices.size(), 0.0);
    double multiplier = 2.0 / (period + 1);

    double sum = 0.0;
    for (std::size_t i = 0; i < period && i < prices.size(); ++i)
    {
        sum += prices[i];
    }
    if (period > 0 && prices.size() > 0)
    {
        ema[period - 1] = sum / period;
    }

    for (std::size_t i = period; i < prices.size(); ++i)
    {
        ema[i] = ((prices[i] - ema[i - 1]) * multiplier) + ema[i - 1];
    }

    return ema;
}
