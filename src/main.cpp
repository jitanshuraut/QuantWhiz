#include <iostream>
#include <vector>
#include "StockDataFetcher.hpp"
#include "SMA_Algorithm.hpp"
#include "MACD_Algorithm.hpp"
#include "RSI_Algorithm.hpp"
#include "KNN_Algorithm.hpp"
#include "BollingerBands_Algorithm.hpp"
#include "EMA_Algorithm.hpp"
#include "utils.hpp"

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

void executeAlgorithm(AlgorithmType algorithm, const std::vector<double> &historicalPrices)
{
    for (int i = 0; i < historicalPrices.size(); i++)
    {
        std::cout << " hist price: " << historicalPrices[i] << " ";
    }
    std::cout << std::endl;
    int period;
    switch (algorithm)
    {
    case AlgorithmType::SMA:
        std::cout << "Enter SMA Period: ";
        std::cin >> period;
        {
            SMA sma("Simple Moving Average", period);

            for (size_t i = 0; i < historicalPrices.size(); ++i)
            {
                sma.addPrice(historicalPrices[i]);
                if (i >= period - 1)
                {
                    try
                    {
                        double smaValue = sma.calculateSignal();
                        std::cout << "SMA Day " << i + 1 << ": " << smaValue << std::endl;
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
            for (size_t i = 0; i < historicalPrices.size(); ++i)
            {
                ema.addPrice(historicalPrices[i]);
                if (ema.getPriceSize() >= period)
                {
                    double emaValue = ema.calculateSignal();
                    std::cout << "EMA Day " << i + 1 << ": " << emaValue << std::endl;
                }
            }
        }
        break;

    case AlgorithmType::RSI:
        std::cout << "Enter RSI Period: ";
        std::cin >> period;
        {

            RSI rsi("Relative Strength Index", period);
            for (size_t i = 0; i < historicalPrices.size(); ++i)
            {
                rsi.addPrice(historicalPrices[i]);
                if (rsi.getPriceSize() >= period)
                {
                    double rsiValue = rsi.calculateSignal();
                    std::cout << "RSI Day " << i + 1 << ": " << rsiValue << std::endl;
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
            auto macdValuesPair = macd.calculate(historicalPrices, shortPeriod, longPeriod, signalPeriod);
            std::vector<double> macdLine = macdValuesPair.first;
            std::vector<double> signalLine = macdValuesPair.second;

            for (size_t i = 0; i < signalLine.size(); i++)
            {
                macd.addPrice(historicalPrices[i]);
                std::cout << macd.getPriceSize() << std::endl;

                if (macd.getSignalSize() >= longPeriod + signalPeriod)
                {
                    double macdValue = macd.calculateSignal();
                    std::cout << "MACD" << macdValue << std::endl;

                    if (macd.getSignalSize() > 0 && macd.signalLine.size() > 0)
                    {
                        std::cout << "MACD Day " << i + 1 << ": MACD: " << macdValue
                                  << ", Signal: " << macd.signalLine.back() << std::endl;
                    }
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
            for (size_t i = 0; i < historicalPrices.size(); ++i)
            {
                bb.addPrice(historicalPrices[i]);
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

    std::vector<double> historicalPrices = StockDataFetcher::fetchStockData(stockSymbol, timePeriod);

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

        executeAlgorithm(selectedAlgorithm, historicalPrices);
    }

    return 0;
}
