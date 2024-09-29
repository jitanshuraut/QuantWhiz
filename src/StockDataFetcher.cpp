#include "StockDataFetcher.hpp"
#include "utils.hpp"
#include <curl/curl.h>
#include <json/json.h>
#include <iostream>
#include <string>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t totalSize = size * nmemb;
    s->append((char *)contents, totalSize);
    return totalSize;
}
std::string getCurrentDate()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *gmtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tstruct);
    return std::string(buf);
}

std::string getDateNDaysAgo(int daysAgo)
{
    time_t now = time(0);
    struct tm tstruct;
    now -= daysAgo * 24 * 60 * 60;
    tstruct = *gmtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tstruct);
    return std::string(buf);
}

std::vector<OHLCV> StockDataFetcher::fetchStockData(const std::string &stockSymbol, int timePeriod, int Min)
{
    std::vector<OHLCV> ohlcvData;
    std::string apiKey = getEnvVariable("APCA_API_KEY_ID");
    std::string apiSecret = getEnvVariable("APCA_API_SECRET_KEY");

    if (apiKey.empty() || apiSecret.empty())
    {
        std::cerr << "API keys not set. Please set environment variables." << std::endl;
        return ohlcvData;
    }

    std::string currentDate = getCurrentDate();
    std::string startDate = getDateNDaysAgo(timePeriod);

    std::string url = "https://data.alpaca.markets/v2/stocks/" + stockSymbol +
                      "/bars?timeframe=" + std::to_string(Min) + "Min&start=" + startDate + "&end=" + currentDate + "&limit=1000&adjustment=raw&feed=iex&sort=asc";

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if (curl)
    {
        std::string readBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("APCA-API-KEY-ID: " + apiKey).c_str());
        headers = curl_slist_append(headers, ("APCA-API-SECRET-KEY: " + apiSecret).c_str());
        headers = curl_slist_append(headers, "accept: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        // Parse the JSON response
        Json::Reader reader;
        Json::Value jsonData;
        reader.parse(readBuffer, jsonData);
        if (!reader.parse(readBuffer, jsonData))
        {
            std::cerr << "Failed to parse JSON: " << reader.getFormattedErrorMessages() << std::endl;
            return ohlcvData;
        }
        // std::cout << "JSON Response: " << readBuffer << std::endl;
        if (jsonData.isMember("bars"))
        {
            for (const auto &bar : jsonData["bars"])
            {
                OHLCV ohlcv;
                ohlcv.open = bar["o"].asDouble();
                ohlcv.high = bar["h"].asDouble();
                ohlcv.low = bar["l"].asDouble();
                ohlcv.close = bar["c"].asDouble();
                ohlcv.volume = bar["v"].asDouble();
                ohlcv.timestamp = bar["t"].asString();

                ohlcvData.push_back(ohlcv);
            }
        }
        else
        {
            std::cerr << "No data found for symbol: " << stockSymbol << std::endl;
        }
    }

    // for (const auto &data : ohlcvData)
    // {
    //     std::cout << "Timestamp: " << data.timestamp
    //               << ", Open: " << data.open
    //               << ", High: " << data.high
    //               << ", Low: " << data.low
    //               << ", Close: " << data.close
    //               << ", Volume: " << data.volume << std::endl;
    // }

    return ohlcvData;
}