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



enum class AlgorithmType {
    SMA,
    EMA,
    MACD,
    KNN,
    BollingerBands,
    RSI,
};

AlgorithmType getAlgorithmType(int choice) {
    switch (choice) {
        case 1: return AlgorithmType::SMA;
        case 2: return AlgorithmType::EMA;
        case 3: return AlgorithmType::RSI;
        case 4: return AlgorithmType::MACD;
        case 5: return AlgorithmType::BollingerBands;
        case 6: return AlgorithmType::KNN;
        
    }
}

int main() {
   
    std::string apiKey = getEnvVariable("APCA_API_KEY_ID");
    std::string apiSecret = getEnvVariable("APCA_API_SECRET_KEY");

    if (apiKey.empty() || apiSecret.empty()) {
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

while(true){
    int choice;
    std::cout << "Select Trading Algorithm:\n";
    std::cout << "1. Simple Moving Average (SMA)\n";
    std::cout << "2. Exponential Moving Average (EMA)\n";
    std::cout << "3. Relative Strength Index (RSI)\n";
    std::cout << "4. Moving Average Convergence Divergence (MACD)\n";
    std::cout << "5. Bollinger Bands\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    AlgorithmType selectedAlgorithm = getAlgorithmType(choice);
    int period;

    switch (selectedAlgorithm) {
        case AlgorithmType::SMA:
            std::cout << "Enter SMA Period: ";
            std::cin >> period;
            {
                std::vector<double> smaValues = SMA::calculate(historicalPrices, period);
                for (size_t i = 0; i < smaValues.size(); ++i) {
                    std::cout << "SMA Day " << i + period << ": " << smaValues[i] << std::endl;
                }
            }
            break;

        case AlgorithmType::EMA:
            std::cout << "Enter EMA Period: ";
            std::cin >> period;
            {
                std::vector<double> emaValues = EMA::calculate(historicalPrices, period);
                for (size_t i = 0; i < emaValues.size(); ++i) {
                    std::cout << "EMA Day " << i + period << ": " << emaValues[i] << std::endl;
                }
            }
            break;

        case AlgorithmType::RSI:
            std::cout << "Enter RSI Period: ";
            std::cin >> period;
            {
                std::vector<double> rsiValues = RSI::calculate(historicalPrices, period);
                for (size_t i = 0; i < rsiValues.size(); ++i) {
                    std::cout << "RSI Day " << i + period << ": " << rsiValues[i] << std::endl;
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
                auto macdValuesPair = MACD::calculate(historicalPrices, shortPeriod, longPeriod, signalPeriod);
                std::vector<double> macdLine = macdValuesPair.first;   
                std::vector<double> signalLine = macdValuesPair.second; 


                for (int i=0;i<signalLine.size();i++){

                std::cout << "MACD Day " << i + longPeriod + signalPeriod << ": MACD: " << macdLine[i]  << ", Signal: " << signalLine[i] << std::endl;
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
                std::pair<std::vector<double>, std::vector<double>> bbValues = BollingerBands::calculate(historicalPrices, period, stdDevMultiplier);
                for (size_t i = 0; i < bbValues.first.size(); ++i) {
                    std::cout << "Bollinger Bands Day " << i + period << ": Upper Band: " << bbValues.first[i] << ", Lower Band: " << bbValues.second[i] << std::endl;
                }
            }
            break;
        default:
            std::cout << "Invalid choice. Please select a valid algorithm." << std::endl;
            break;
    }   
}     

    return 0;
}
