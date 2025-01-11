#include "data_fetcher.hpp"
#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

DataFetcher::DataFetcher(const std::string& api_key, const std::string& base_url)
    : api_key(api_key), base_url(base_url) {}

std::string DataFetcher::fetch_data(const std::string& endpoint) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        std::string url = base_url + "/" + endpoint;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("X-API-KEY: " + api_key).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return readBuffer;
}