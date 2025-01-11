cmake_minimum_required(VERSION 3.10)
project(citadel)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(SQLite3 REQUIRED)

# C++ Source files
set(CPP_SOURCES
    src/cpp/data/data_fetcher.cpp
    src/cpp/models/strategy1.cpp
    src/cpp/utils/config_loader.cpp
    src/cpp/utils/database_logger.cpp
    src/cpp/execution/trade_executor.cpp
    src/cpp/main.cpp
)

# Add executable and link libraries
add_executable(citadel ${CPP_SOURCES})
target_link_libraries(citadel PRIVATE Qt5::Widgets Qt5::Sql SQLite3::SQLite3)

qt5_use_modules(citadel Widgets Sql)

# Add custom command for generating moc files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include the UI file if using Qt Designer
set(CMAKE_INCLUDE_CURRENT_DIR ON)