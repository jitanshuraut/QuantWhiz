// #include "indicator/Strategy.hpp"
// #include "algorithm/EMA_Algorithm.hpp"

// template <typename IndicatorType>
// class Custom : public Strategy<IndicatorType>
// {
// public:
//     std::string calculateSignal()
//     {
//         return "buy";
//     }
// };

// int main()
// {

//     Custom<Indicator> strategy;
//     strategy.addIndicator("EMA", std::make_unique<EMA>("EMA",6));
//     strategy.calculateIndicator("EMA");
//     std::string action = strategy.calculateSignal();
//     std::cout << action << std::endl;

//     return 0;
// }
