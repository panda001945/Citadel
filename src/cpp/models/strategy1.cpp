#include "strategy1.hpp"
#include <algorithm>

TradingStrategy::TradingStrategy() : short_window(50), long_window(200) {}

std::map<std::string, std::string> TradingStrategy::generate_signals(const std::vector<double>& prices, const std::string& symbol) {
    std::map<std::string, std::string> signals;

    if (prices.size() < long_window) return signals;

    std::vector<double> short_ma, long_ma;
    for (size_t i = short_window - 1; i < prices.size(); ++i) {
        double sum_short = 0, sum_long = 0;
        for (int j = 0; j < short_window; ++j) sum_short += prices[i - j];
        for (int j = 0; j < long_window; ++j) sum_long += prices[i - j];
        
        short_ma.push_back(sum_short / short_window);
        long_ma.push_back(sum_long / long_window);

        if (short_ma.back() > long_ma.back() && (i == short_window || short_ma[short_ma.size() - 2] <= long_ma[long_ma.size() - 2])) {
            signals[std::to_string(i)] = "BUY";
        } else if (short_ma.back() < long_ma.back() && (i == short_window || short_ma[short_ma.size() - 2] >= long_ma[long_ma.size() - 2])) {
            signals[std::to_string(i)] = "SELL";
        }
    }
    return signals;
}

double TradingStrategy::get_current_price(const std::string& symbol) {
    // Placeholder for fetching current price, should use DataFetcher in real scenario
    return 100.0; // Arbitrary price for simulation
}