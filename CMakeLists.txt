cmake_minimum_required(VERSION 3.10)
project(AlgoEnginePrimer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)

add_executable(AlgoEnginePrimer
    src/main.cpp
    src/StockDataFetcher.cpp
    src/indicators/SMA_Algorithm.cpp
    src/indicators/EMA_Algorithm.cpp
    src/indicators/RSI_Algorithm.cpp
    src/indicators/MACD_Algorithm.cpp
    src/indicators/BollingerBands_Algorithm.cpp
    src/indicators/KNN_Algorithm.cpp
    src/indicators/StochasticOscillator_Algorithm.cpp
    src/indicators/ATR_Algorithm.cpp
    src/utils.cpp
    src/Strategy/custom.cpp  
)

target_link_libraries(AlgoEnginePrimer PRIVATE CURL::libcurl jsoncpp_lib)
