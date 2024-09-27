#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include "Indicator.h"

template <typename IndicatorType>
class Strategy
{
private:
    std::map<std::string, std::unique_ptr<IndicatorType>> indicatorStorage;

public:
    template <typename T>
    void addIndicator(const std::string &indicatorName, std::unique_ptr<T> indicator)
    {
        indicatorStorage[indicatorName] = std::move(indicator);
    }

    void calculateIndicator(const std::string &indicatorName)
    {
        auto it = indicatorStorage.find(indicatorName);
        if (it != indicatorStorage.end())
        {
            it->second->calculateSignal();
        }
        else
        {
            std::cerr << "Indicator not found: " << indicatorName << std::endl;
        }
    }
    virtual std::string calculateSignal() = 0;
};

#endif
