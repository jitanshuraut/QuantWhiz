#pragma once
#include <vector>
#include <string>

class StockDataFetcher {
public:
    static std::vector<double> fetchStockData(const std::string& stockSymbol, int timePeriod);
};
