#ifndef RSI_HPP
#define RSI_HPP

#include <vector>

class RSI {
public:
    static std::vector<double> calculate(const std::vector<double>& prices, std::size_t period);
};

#endif 
