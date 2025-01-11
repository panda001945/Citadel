#include "database_logger.hpp"
#include <iostream>

DatabaseLogger::DatabaseLogger(const std::string& db_path) {
    int rc = sqlite3_open(db_path.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS logs(id INTEGER PRIMARY KEY AUTOINCREMENT, level TEXT, message TEXT, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void DatabaseLogger::log(const std::string& level, const std::string& message) {
    std::string sql = "INSERT INTO logs (level, message) VALUES ('" + level + "', '" + message + "');";
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}