#ifndef TRADE_EXECUTOR_HPP
#define TRADE_EXECUTOR_HPP

#include <string>

class TradeExecutor {
public:
    void execute_trade(const std::string& action, const std::string& symbol, double quantity, double price);
};

#endif // TRADE_EXECUTOR_HPP