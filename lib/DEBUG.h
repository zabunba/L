#ifndef DEBUG_H
#define DEBUG_H


#include <variant>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>

auto programStart = std::chrono::steady_clock::now();

std::string getElapsedTime() {
    using namespace std::chrono;
    auto now = steady_clock::now();
    auto elapsed = duration_cast<milliseconds>(now - programStart);

    auto ms = elapsed.count() % 1000;
    auto s = (elapsed.count() / 1000) % 60;
    auto m = (elapsed.count() / 60000) % 60;
    auto h = (elapsed.count() / 3600000);

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d.%03d", (int)h, (int)m, (int)s, (int)ms);

    return std::string(buffer);
}

template<typename... Args>
void DEBUG(Args&&... args) {
    std::ostringstream oss;
    (oss << ... << args);
    std::cout << "[DEBUG] [" << getElapsedTime() << "] " << oss.str() << std::flush << "\n";
}

#endif