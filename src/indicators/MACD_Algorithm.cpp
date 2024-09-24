#include "MACD_Algorithm.hpp"
#include "EMA_Algorithm.hpp"

std::pair<std::vector<double>, std::vector<double>> MACD::calculate(const std::vector<double>& prices, std::size_t shortPeriod, std::size_t longPeriod, std::size_t signalPeriod) {
    

    std::vector<double> macdValues(prices.size(), 0.0);    
    std::vector<double> signalValues(prices.size(), 0.0);   
    
    std::vector<double> shortEma = EMA::calculate(prices, shortPeriod);
    std::vector<double> longEma = EMA::calculate(prices, longPeriod);
    
    for (std::size_t i = 0; i < prices.size(); ++i) {
        macdValues[i] = shortEma[i] - longEma[i];  
    }
    
    signalValues = EMA::calculate(macdValues, signalPeriod);
    
    return {macdValues, signalValues};
}
