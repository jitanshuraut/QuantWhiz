#pragma once
#include <vector>
#include <string>
#include "OHLCV.hpp"

class StockDataFetcher {
public:
    static std::vector<OHLCV> fetchStockData(const std::string& stockSymbol, int timePeriod,int Min);
};
