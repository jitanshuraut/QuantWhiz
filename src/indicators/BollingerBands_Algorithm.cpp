#include "algorithm/BollingerBands_Algorithm.hpp"
#include <cmath>
#include <vector>
#include <stdexcept>

double BollingerBands::calculateSignal()
{
    if (prices.size() < period)
    {
        throw std::runtime_error("Not enough data to calculate Bollinger Bands.");
    }

    auto [upperBand, lowerBand] = calculate();

    signals.push_back(upperBand);
    signals.push_back(lowerBand);

    return upperBand;
}

std::pair<double, double> BollingerBands::calculate() const
{
    double sum = 0.0;
    double sq_sum = 0.0;

    for (std::size_t j = prices.size() - period; j < prices.size(); ++j)
    {
        sum += prices[j];
        sq_sum += prices[j] * prices[j];
    }

    double mean = sum / period;
    double variance = (sq_sum / period) - (mean * mean);
    double stdDev = std::sqrt(variance);

    double upperBand = mean + numStdDev * stdDev;
    double lowerBand = mean - numStdDev * stdDev;

    return {upperBand, lowerBand};
}