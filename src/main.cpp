#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <utility>

#include "array_list.hpp"
#include "sort.hpp"

template <typename T>
void print_array(ds::array_list<T> &v) {
    for (const auto &i : v) {
        std::cout << i << " ";
    }
}


int main() {
    ds::array_list<int> v = {1, 2, 3, 4, 5, 1, 2, 3};

    algo::sort::heap_sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    

    print_array(v);
    
    return 0;
}

