#include <iostream>
#include <string>

#include "array_list.hpp"

void selectionSort(ds::array_list<int> &a) {
    for (int i = 0; i < a.size() - 1; ++i) {
        for (int j = i + 1; j < a.size(); ++j) {
            if (a[i] > a[j]) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int main() {
    ds::array_list<int> a = {2, 3, 9, 8, 10, 98, 1, 2, -1, 3};

    selectionSort(a);

    for (auto &i : a) {
        std::cout << i << " ";
    }

    return 0;
}

