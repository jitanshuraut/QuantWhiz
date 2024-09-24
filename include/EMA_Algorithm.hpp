#ifndef EMAALGORITHM_HPP
#define EMAALGORITHM_HPP

#include <vector>

class EMA {
public:
    static std::vector<double> calculate(const std::vector<double>& prices, std::size_t period);
};

#endif 
