#include "RSI_Algorithm.hpp"


std::vector<double> RSI::calculate(const std::vector<double>& prices, std::size_t period) {
    std::vector<double> rsi(prices.size(), 0.0);
    
    for (std::size_t i = 1; i < prices.size(); ++i) {
        double gain = 0.0;
        double loss = 0.0;
        
        if (prices[i] > prices[i - 1]) {
            gain = prices[i] - prices[i - 1];
        } else {
            loss = prices[i - 1] - prices[i];
        }

        if (i < period) {
            rsi[i] = (gain - loss) / (gain + loss) * 100.0;
        } else if (i == period) {
            rsi[i] = (gain - loss) / (gain + loss) * 100.0;
        } else {
            rsi[i] = (rsi[i - 1] * (period - 1) + ((gain - loss) / (gain + loss) * 100.0)) / period;
        }
    }
    
    return rsi;
}
