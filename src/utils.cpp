#include "utils.hpp"

#include <chrono>
#include <ctime>
#include <string>
#include <random>

namespace utils {
    std::string get_current_time() {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        
        char buff[30];
        std::strftime(buff, sizeof(buff), "%Hh%Mp%Ss %m-%d-%Y", std::localtime(&now_time));

        std::string ret(buff);

        return ret;
    }

    int generate_random_num(const int &start, const int &end) {
        std::random_device dev;
        std::mt19937 rgn(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distribute(start, end);

        return distribute(rgn);
    }
}



