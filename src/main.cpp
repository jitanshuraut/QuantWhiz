#include <iostream>
#include <vector>
#include "StockDataFetcher.hpp"
#include "algorithm/SMA_Algorithm.hpp"
#include "algorithm/EMA_Algorithm.hpp"
#include "algorithm/RSI_Algorithm.hpp"
#include "algorithm/MACD_Algorithm.hpp"
#include "algorithm/KNN_Algorithm.hpp"
#include "algorithm/BollingerBands_Algorithm.hpp"
#include "utils.hpp"
#include "OHLCV.hpp"
#include <iomanip> 
#include <ctime>

enum class AlgorithmType
{
    SMA,
    EMA,
    MACD,
    KNN,
    BollingerBands,
    RSI,
    Invalid
};

std::time_t now = std::time(nullptr);
std::tm startingTimestamp;

AlgorithmType getAlgorithmType(int choice)
{
    switch (choice)
    {
    case 1:
        return AlgorithmType::SMA;
    case 2:
        return AlgorithmType::EMA;
    case 3:
        return AlgorithmType::RSI;
    case 4:
        return AlgorithmType::MACD;
    case 5:
        return AlgorithmType::BollingerBands;
    case 6:
        return AlgorithmType::KNN;
    default:
        return AlgorithmType::Invalid;
    }
}

void executeAlgorithm(AlgorithmType algorithm, const std::vector<OHLCV> &historicalData)
{
    // for (const auto &data : historicalData)
    // {
    //     std::cout << "Open: " << data.open << " High: " << data.high
    //               << " Low: " << data.low << " Close: " << data.close
    //               << " Volume: " << data.volume << std::endl;
    // }
    // std::cout << std::endl;

    int period;
    switch (algorithm)
    {
    case AlgorithmType::SMA:
        std::cout << "Enter SMA Period: ";
        std::cin >> period;
        {
            SMA sma("Simple Moving Average", period);

            for (size_t i = 0; i < historicalData.size(); ++i)
            {
                sma.addPrice(historicalData[i].close); // Use close price for SMA
                if (i >= period - 1)
                {
                    try
                    {
                        double smaValue = sma.calculateSignal();
                        std::tm timeInfo = startingTimestamp;
                        timeInfo.tm_min += i * 15;
                        std::mktime(&timeInfo);
                        std::cout << "SMA at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                                  << ": " << smaValue << std::endl;
                    }
                    catch (const std::runtime_error &e)
                    {
                        std::cerr << "Error calculating SMA: " << e.what() << std::endl;
                    }
                }
            }
        }
        break;

    case AlgorithmType::EMA:
        std::cout << "Enter EMA Period: ";
        std::cin >> period;
        {
            EMA ema("Exponential Moving Average", period);
            for (size_t i = 0; i < historicalData.size(); ++i)
            {
                ema.addPrice(historicalData[i].close);
                if (ema.getPriceSize() >= period)
                {
                    double emaValue = ema.calculateSignal();
                    std::tm timeInfo = startingTimestamp;
                    timeInfo.tm_min += i * 15;
                    std::mktime(&timeInfo);
                    std::cout << "EMA at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                              << ": " << emaValue << std::endl;
                }
            }
        }
        break;

    case AlgorithmType::RSI:
        std::cout << "Enter RSI Period: ";
        std::cin >> period;
        {
            RSI rsi("Relative Strength Index", period);
            for (size_t i = 0; i < historicalData.size(); ++i)
            {
                rsi.addPrice(historicalData[i].close);
                if (rsi.getPriceSize() >= period)
                {
                    double rsiValue = rsi.calculateSignal();
                    std::tm timeInfo = startingTimestamp;
                    timeInfo.tm_min += i * 15;
                    std::mktime(&timeInfo);
                    std::cout << "RSI at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                              << ": " << rsiValue << std::endl;
                }
            }
        }
        break;

    case AlgorithmType::MACD:
        std::cout << "Enter Short EMA Period: ";
        int shortPeriod, longPeriod, signalPeriod;
        std::cin >> shortPeriod;
        std::cout << "Enter Long EMA Period: ";
        std::cin >> longPeriod;
        std::cout << "Enter Signal Period: ";
        std::cin >> signalPeriod;
        {
            MACD macd("Moving Average Convergence Divergence", shortPeriod, longPeriod, signalPeriod);
            auto macdValuesPair = macd.calculate(historicalData, shortPeriod, longPeriod, signalPeriod);
            std::vector<double> macdLine = macdValuesPair.first;
            std::vector<double> signalLine = macdValuesPair.second;

            for (size_t i = 0; i < signalLine.size(); i++)
            {
                macd.addPrice(historicalData[i].close); 

                if (macd.getSignalSize() >= longPeriod + signalPeriod)
                {
                    double macdValue = macd.calculateSignal();
                    std::tm timeInfo = startingTimestamp;
                    timeInfo.tm_min += i * 15;
                    std::mktime(&timeInfo);

                    std::cout << "MACD at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                              << ": " << ": MACD: " << macdValue
                              << ", Signal: " << macd.signalLine.back() << std::endl;
                }
            }
        }
        break;

    case AlgorithmType::BollingerBands:
        std::cout << "Enter Bollinger Bands Period: ";
        std::cin >> period;
        std::cout << "Enter Standard Deviation Multiplier: ";
        double stdDevMultiplier;
        std::cin >> stdDevMultiplier;
        {
            BollingerBands bb("Bollinger Bands", period, stdDevMultiplier);
            for (size_t i = 0; i < historicalData.size(); ++i)
            {
                bb.addPrice(historicalData[i].close); 
                try
                {
                    auto [upperBand, lowerBand] = bb.calculate();
                    std::cout << "Upper Band: " << upperBand << ", Lower Band: " << lowerBand << std::endl;
                }
                catch (const std::runtime_error &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
        }
        break;

    default:
        std::cout << "Invalid choice." << std::endl;
        break;
    }
}

int main()
{
    std::string apiKey = getEnvVariable("APCA_API_KEY_ID");
    std::string apiSecret = getEnvVariable("APCA_API_SECRET_KEY");

    if (apiKey.empty() || apiSecret.empty())
    {
        std::cerr << "API keys not set. Please set environment variables in the .env file." << std::endl;
        return 1;
    }

    std::string stockSymbol;
    int timePeriod;

    std::cout << "Enter Stock Symbol (e.g., AAPL, TSLA): ";
    std::cin >> stockSymbol;

    std::cout << "Enter Time Period (in days): ";
    std::cin >> timePeriod;

    std::vector<OHLCV> historicalData = StockDataFetcher::fetchStockData(stockSymbol, timePeriod);
    startingTimestamp = *std::localtime(&now);

    for (auto data : historicalData)
    {
        std::cout << data.high << std::endl;
    }

    while (true)
    {
        int choice;
        std::cout << "Select Trading Algorithm:\n";
        std::cout << "1. Simple Moving Average (SMA)\n";
        std::cout << "2. Exponential Moving Average (EMA)\n";
        std::cout << "3. Relative Strength Index (RSI)\n";
        std::cout << "4. Moving Average Convergence Divergence (MACD)\n";
        std::cout << "5. Bollinger Bands\n";
        std::cout << "6. K-Nearest Neighbors (KNN)\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        AlgorithmType selectedAlgorithm = getAlgorithmType(choice);

        if (selectedAlgorithm == AlgorithmType::Invalid)
        {
            std::cout << "Invalid choice. Please select a valid algorithm." << std::endl;
            continue;
        }

        executeAlgorithm(selectedAlgorithm, historicalData);
    }

    return 0;
}
