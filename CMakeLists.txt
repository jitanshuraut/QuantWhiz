cmake_minimum_required(VERSION 3.10)
project(AlgoEnginePrimer)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)

add_executable(AlgoEnginePrimer
    src/main.cpp
    src/StockDataFetcher.cpp
    src/indicators/SMA.cpp
    src/indicators/EMA.cpp
    src/indicators/RSI.cpp
    src/indicators/BollingerBands.cpp
    src/indicators/StochasticOscillator.cpp
    src/indicators/ADX.cpp
    src/indicators/APO.cpp
    src/indicators/ATR.cpp
    src/indicators/CCI.cpp
    src/indicators/DividendYield.cpp
    src/indicators/FibonacciRetracement.cpp
    src/indicators/MA.cpp
    src/indicators/MFI.cpp
    src/indicators/OBV.cpp
    src/indicators/PERatio.cpp
    src/indicators/VWAP.cpp
    src/indicators/StochasticOscillator.cpp
    src/utils.cpp
    src/Strategy/custom.cpp  
)

target_link_libraries(AlgoEnginePrimer PRIVATE CURL::libcurl jsoncpp_lib)
