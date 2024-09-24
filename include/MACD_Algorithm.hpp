#ifndef MACD_ALGORITHM_HPP
#define MACD_ALGORITHM_HPP

#include <vector>
#include <utility>

class MACD {
public:
    static std::pair<std::vector<double>, std::vector<double>> calculate(const std::vector<double>& prices, std::size_t shortPeriod, std::size_t longPeriod, std::size_t signalPeriod);
};

#endif 
