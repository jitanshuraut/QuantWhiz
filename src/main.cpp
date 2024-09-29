#include <iostream>
#include <vector>
#include "StockDataFetcher.hpp"
#include "algorithm/SMA.hpp"
#include "SignalResult.hpp"
#include "algorithm/EMA.hpp"
#include "algorithm/RSI.hpp"
#include "algorithm/BollingerBands.hpp"
#include "algorithm/ADX.hpp"
#include "algorithm/APO.hpp"
#include "algorithm/ATR.hpp"
#include "algorithm/CCI.hpp"
#include "algorithm/DividendYield.hpp"
#include "algorithm/FibonacciRetracement.hpp"
#include "algorithm/MFI.hpp"
#include "algorithm/MA.hpp"
#include "algorithm/OBV.hpp"
#include "algorithm/PERatio.hpp"
#include "algorithm/StochasticOscillator.hpp"
#include "algorithm/VWAP.hpp"
#include "utils.hpp"
#include "OHLCV.hpp"
#include <iomanip>
#include <ctime>
#include <chrono>
#include <ctime>

std::time_t now = std::time(nullptr);
std::tm startingTimestamp;
std::vector<OHLCV> historicalData;
int period;

void RUN_SMA()
{

    SMA sma("Simple Moving Average", period);

    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        sma.addData(historicalData[i]);
        std::cout << sma.getDataSize() << std::endl;
        if (sma.getDataSize() >= period)
        {
            try
            {
                SignalResult smaValue = sma.calculateSignal();
                std::tm timeInfo = startingTimestamp;
                timeInfo.tm_min += i * 15;
                std::mktime(&timeInfo);
                std::cout << "SMA at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                          << ": " << smaValue.getSingleValue() << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error calculating SMA: " << e.what() << std::endl;
            }
        }
    }
}

void RUN_EMA()
{

    EMA ema("Exponential Moving Average", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        ema.addData(historicalData[i]);
        if (ema.getDataSize() >= period)
        {
            SignalResult emaValue = ema.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "EMA at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << emaValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_RSI()
{

    RSI rsi("Relative Strength Index", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        rsi.addData(historicalData[i]);
        if (rsi.getDataSize() >= period)
        {
            SignalResult rsiValue = rsi.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "RSI at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << rsiValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_MFI()
{

    MFI mfi("Money Flow Index", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        mfi.addData(historicalData[i]);
        if (mfi.getDataSize() >= period)
        {
            SignalResult mfiValue = mfi.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "MFI at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << mfiValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_ADX()
{

    ADX adx("Average Directional Index", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        adx.addData(historicalData[i]);
        if (adx.getDataSize() >= period)
        {
            SignalResult adxValue = adx.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "ADX at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << adxValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_APO(int long_, int short_)
{

    APO apo("Absolute Price Oscillator ", short_, long_);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        apo.addData(historicalData[i]);
        if (apo.getDataSize() > short_ and apo.getDataSize() > long_)
        {
            SignalResult apoValue = apo.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "APO at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << apoValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_ATR()
{

    ATR atr("Average True Range ", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        atr.addData(historicalData[i]);
        if (atr.getDataSize() >= period)
        {
            SignalResult atrValue = atr.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "ATR at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << atrValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_VWAP()
{

    VWAP vwap(" Volume-Weighted Average");
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        vwap.addData(historicalData[i]);
        if (vwap.getDataSize() >= 1)
        {
            SignalResult vwapValue = vwap.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "VWAP at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << std::endl;

            for (auto x : vwapValue.getVectorValue())
            {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }
}

void RUN_DividendYield()
{

    DividendYield Dy("DividendYield", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        Dy.addData(historicalData[i]);
        if (Dy.getDataSize() >= period)
        {
            SignalResult DyValue = Dy.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "DividendYield at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << DyValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_MA()
{

    MA ma("moving average", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        ma.addData(historicalData[i]);
        if (ma.getDataSize() >= period)
        {
            SignalResult maValue = ma.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "moving average at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << maValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_OBV()
{

    OBV obv("Balance Volume");
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        obv.addData(historicalData[i]);
        if (obv.getDataSize() >= period)
        {
            SignalResult obvValue = obv.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "moving average at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << std::endl;

            for (auto x : obvValue.getVectorValue())
            {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }
}

void RUN_StochasticOscillator(int smoothK, int smoothD)
{

    StochasticOscillator sov("StochasticOscillator", period, smoothK, smoothD);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        sov.addData(historicalData[i]);
        if (sov.getDataSize() >= period)
        {
            SignalResult sovValue = sov.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "StochasticOscillator at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << sovValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_FibonacciRetracement()
{

    FibonacciRetracement fub("FibonacciRetracement");
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        fub.addData(historicalData[i]);
        if (fub.getDataSize() >= period)
        {
            SignalResult fubValue = fub.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "FibonacciRetracement at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << std::endl;

            for (auto x : fubValue.getVectorValue())
            {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }
}

void RUN_CCI()
{

    CCI cci("Commodity Channel Index ", period);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        cci.addData(historicalData[i]);
        if (cci.getDataSize() > period)
        {
            SignalResult cciValue = cci.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "CCI at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << cciValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_PER(int earningsPerShare)
{

    PERatio pe("PERatio ", earningsPerShare);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        pe.addData(historicalData[i]);
        if (pe.getDataSize() > earningsPerShare)
        {
            SignalResult peValue = pe.calculateSignal();
            std::tm timeInfo = startingTimestamp;
            timeInfo.tm_min += i * 15;
            std::mktime(&timeInfo);
            std::cout << "CCI at " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S")
                      << ": " << peValue.getSingleValue() << std::endl;
        }
    }
}

void RUN_BollingerBands(double stdDevMultiplier)
{

    BollingerBands bb("Bollinger Bands", period, stdDevMultiplier);
    for (size_t i = 0; i < historicalData.size(); ++i)
    {
        bb.addData(historicalData[i]);
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

void PRINT_DATA()
{
    for (auto data : historicalData)
    {
        std::cout << "High: " << data.high << std::endl;
        std::cout << "Low: " << data.low << std::endl;
        std::cout << "Close: " << data.close << std::endl;
        std::cout << "Volume: " << data.volume << std::endl;
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

    historicalData = StockDataFetcher::fetchStockData(stockSymbol, timePeriod,15);
    startingTimestamp = *std::localtime(&now);

    PRINT_DATA();
    std::cout << "Enter SMA Period: ";
    std::cin >> period;
    auto start = std::chrono::high_resolution_clock::now();
    RUN_SMA();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;
    start = decltype(start)();
    end = decltype(end)();

    // std::cout << "Enter EMA Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_EMA();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter RSI Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_RSI();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter Bollinger Bands Period: ";
    // std::cin >> period;
    // std::cout << "Enter Standard Deviation Multiplier: ";
    // double stdDevMultiplier;
    // std::cin >> stdDevMultiplier;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_BollingerBands(stdDevMultiplier);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter Average Directional Index Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_ADX();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter Absolute Price Oscillator  Period: ";
    // int long_, short_;
    // std::cin >> long_ >> short_;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_APO(long_, short_);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter Average True Range  Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_ATR();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter Commodity Channel Index  Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_CCI();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter DividendYield  Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_DividendYield();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter FibonacciRetracement  Period: ";
    // start = std::chrono::high_resolution_clock::now();
    // RUN_FibonacciRetracement();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter moving average  Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_MA();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter  Money Flow Index  Period: ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_MFI();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter  Balance Volume  : ";
    // std::cin >> period;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_OBV();
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter price-to-earnings  : ";
    // int earningsPerShare;
    // std::cin >> earningsPerShare;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_PER(earningsPerShare);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    // std::cout << "Enter StochasticOscillator period  : ";
    // std::cin >> period;
    // int smoothK, smoothD;
    // std::cin >> smoothK >> smoothD;
    // start = std::chrono::high_resolution_clock::now();
    // RUN_StochasticOscillator(smoothK, smoothD);
    // end = std::chrono::high_resolution_clock::now();
    // elapsed = end - start;
    // std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    std::cout << "Enter  Volume-Weighted Average   : ";

    start = std::chrono::high_resolution_clock::now();
    RUN_VWAP();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Calculation executed in: " << elapsed.count() << " ms" << std::endl;

    return 0;
}
