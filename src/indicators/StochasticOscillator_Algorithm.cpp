#include "algorithm/StochasticOscillator_Algorithm.hpp"
#include <algorithm>
#include <numeric>

double StochasticOscillator::calculateSignal()
{
    if (prices.size() < period)
    {
        throw std::runtime_error("Not enough data to calculate Stochastic Oscillator.");
    }

    double currentClose = prices.back();
    double lowestLow = *std::min_element(prices.end() - period, prices.end());
    double highestHigh = *std::max_element(prices.end() - period, prices.end());

    double k = (currentClose - lowestLow) / (highestHigh - lowestLow) * 100.0;
    signals.push_back(k);
    return k;
}

std::vector<std::pair<double, double>> StochasticOscillator::calculate(const std::vector<double> &high, const std::vector<double> &low, const std::vector<double> &close, int period, int smoothK, int smoothD)
{
    // Implementation details...
}