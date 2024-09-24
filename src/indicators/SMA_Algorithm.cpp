#include "SMA_Algorithm.hpp"
#include <numeric>

std::vector<double> SMA::calculate(const std::vector<double>& prices, int period) {
    std::vector<double> smaValues;

    for (std::size_t i = 0; i <= prices.size() - period; ++i) {
        double sum = std::accumulate(prices.begin() + i, prices.begin() + i + period, 0.0);
        smaValues.push_back(sum / period);
    }

    return smaValues;
}
