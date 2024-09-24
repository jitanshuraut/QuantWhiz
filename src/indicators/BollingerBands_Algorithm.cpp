#include "BollingerBands_Algorithm.hpp"
#include <cmath>
#include <vector>

std::pair<std::vector<double>, std::vector<double>> BollingerBands::calculate(const std::vector<double>& prices, std::size_t period, double numStdDev) {
    std::vector<double> upperBand(prices.size(), 0.0);
    std::vector<double> lowerBand(prices.size(), 0.0);
    
    for (std::size_t i = 0; i <= prices.size() - period; ++i) {
        double sum = 0.0;
        double sq_sum = 0.0;
        
        for (std::size_t j = 0; j < period; ++j) {
            sum += prices[i + j];
            sq_sum += prices[i + j] * prices[i + j];
        }
        
        double mean = sum / period;
        double variance = (sq_sum / period) - (mean * mean);
        double stdDev = std::sqrt(variance);
        
        upperBand[i + period - 1] = mean + numStdDev * stdDev;
        lowerBand[i + period - 1] = mean - numStdDev * stdDev;
    }
    
    return {upperBand, lowerBand};
}
