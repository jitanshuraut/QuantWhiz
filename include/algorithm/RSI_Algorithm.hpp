#ifndef RSI_HPP
#define RSI_HPP

#include "indicator/Indicator.h"
#include <vector>

class RSI : public Indicator {
public:
    RSI(const std::string& indicatorName, int period)
        : Indicator(indicatorName, period) {}

    double calculateSignal() override; 
    static std::vector<double> calculate(const std::vector<double>& prices, std::size_t period);
};

#endif
