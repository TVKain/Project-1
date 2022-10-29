#include <iostream>
#include <string>
#include <algorithm>

#include "array_list.hpp"
#include "sorting.hpp"

int main() {
    ds::array_list<int> a = {2, 3, 9, 8, 10, 98, 1, 2, -1, 3};

    algo::insertion_sort(a.begin(), a.end());

    return 0;
}

