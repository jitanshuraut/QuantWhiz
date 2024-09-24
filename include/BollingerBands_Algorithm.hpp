#ifndef BOLLINGERBANDS_HPP
#define BOLLINGERBANDS_HPP

#include <vector>

class BollingerBands {
public:
    static std::pair<std::vector<double>, std::vector<double>> calculate(const std::vector<double>& prices, std::size_t period, double numStdDev);
};

#endif 
