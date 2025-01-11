#ifndef STRATEGY1_HPP
#define STRATEGY1_HPP

#include <string>
#include <vector>
#include <map>

class TradingStrategy {
public:
    TradingStrategy();
    std::map<std::string, std::string> generate_signals(const std::vector<double>& prices, const std::string& symbol);
    double get_current_price(const std::string& symbol);

private:
    // Placeholder for strategy parameters
    int short_window;
    int long_window;
};

#endif // STRATEGY1_HPP