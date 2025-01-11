#ifndef DATABASE_LOGGER_HPP
#define DATABASE_LOGGER_HPP

#include <string>
#include <sqlite3.h>

class DatabaseLogger {
public:
    DatabaseLogger(const std::string& db_path);
    void log(const std::string& level, const std::string& message);

private:
    sqlite3* db;
};

#endif // DATABASE_LOGGER_HPP