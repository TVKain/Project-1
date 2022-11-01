#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <limits>
#include <chrono>
#include <algorithm>
#include <locale>
#include <sstream>


#define clear_input() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') 


namespace utils {
    std::string get_current_time();

    int generate_random_num(const int &, const int &);

    template<typename Duration = std::chrono::nanoseconds, typename F, typename ... Args>
    Duration bench_time(F&& fun,  Args&&... args) {
        const auto beg = std::chrono::high_resolution_clock::now();
        std::forward<F>(fun)(std::forward<Args>(args)...);
        const auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<Duration>(end - beg);
    }

}



#endif