#include "sorting.hpp"
#include <utility>

namespace algo {
    template <typename T>
    void insertion_sort(T* first, T* last) {
        auto i = first + 1;

        for (auto i = first + 1; i < last; ++i) {
            
            auto j = i - 1;
            while (j > first && *j > *i) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = *i;
        }
    }

}

