#ifndef DATA_FETCHER_HPP
#define DATA_FETCHER_HPP

#include <string>
#include <map>

class DataFetcher {
public:
    DataFetcher(const std::string& api_key, const std::string& base_url);
    std::string fetch_data(const std::string& endpoint);

private:
    std::string api_key;
    std::string base_url;
};

#endif // DATA_FETCHER_HPP
