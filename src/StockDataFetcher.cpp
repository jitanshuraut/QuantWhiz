#include "StockDataFetcher.hpp"
#include "utils.hpp"
#include <curl/curl.h>
#include <json/json.h>  
#include <iostream>
#include <string>


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

std::vector<double> StockDataFetcher::fetchStockData(const std::string& stockSymbol, int timePeriod) {
    std::vector<double> prices;
    std::string apiKey = getEnvVariable("APCA_API_KEY_ID");
    std::string apiSecret = getEnvVariable("APCA_API_SECRET_KEY");

    std::string url = "https://data.alpaca.markets/v2/stocks/" + stockSymbol + "/trades?limit=" + std::to_string(timePeriod);

    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();

    if (curl) {
        std::string readBuffer;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("APCA-API-KEY-ID: " + apiKey).c_str());
        headers = curl_slist_append(headers, ("APCA-API-SECRET-KEY: " + apiSecret).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);


        Json::Reader reader;
        Json::Value jsonData;
        reader.parse(readBuffer, jsonData);

        for (const auto& trade : jsonData["trades"]) {
            prices.push_back(trade["p"].asDouble());  
        }
    }

    return prices;
}
