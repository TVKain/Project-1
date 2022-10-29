#pragma once 
#ifndef SORTING_HPP
#define SORTING_HPP

namespace algo {
    template <typename T>
    void insertion_sort(T*, T*);

    template <typename T>
    void insertion_sort(T*, T*, bool (T, T));

    template <typename T>
    void bubble_sort(T*, T*, bool (T, T));
}

#endif
