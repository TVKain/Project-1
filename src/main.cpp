#include <iostream>
#include <string>
#include <algorithm>

#include "array_list.hpp"
#include "sorting.hpp"

int main() {
    ds::array_list<int> a = {1, -1, 2, 3, 2};


    algo::bubble_sort(a.begin(), a.end());

    for (const auto &i : a) {
        std::cout << i << " ";
    }

    return 0;
}

