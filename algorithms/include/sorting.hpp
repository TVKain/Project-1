#pragma once 
#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>
#include <functional>

namespace algo {

    /* Insertion sort implentation 
     * Default sorting from min to max
     * Uses the < operator
     */
    template <typename T>
    void insertion_sort(T* first, T* last) {
        for (auto i = first + 1; i < last; ++i) {
            T key = *i;
            auto j = i - 1;
            while (j >= first && key < *j) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    }

    /* Insertion sort implentation 
     * Sorts based on the compare function
     */
    template <typename T, typename Compare>
    void insertion_sort(T* first, T* last, Compare compare) {
        for (auto i = first + 1; i < last; ++i) {
            T key = *i;
            auto j = i - 1;
            while (j >= first && compare(key, j)) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    };

    /* Bubble sort implementation
     * Default sorting from min to max
     * Uses the < operator
     */
    template <typename T>
    void bubble_sort(T *first, T* last) {
        for (auto i = first; i < last - 1; ++i) {
            for (auto j = last - 1; j >= i + 1; --j) {
                if (*(j) < *(j - 1)) {
                    std::swap(*(j), *(j - 1));
                }
            }
        }
    }

    /* Bubble sort implementation
     * Sorts based on the compare function
     */
    template<typename T, typename Compare>
    void bubble_sort(T* first, T* last, Compare compare) {
        for (auto i = first; i < last - 1; ++i) {
            for (auto j = last - 1; j >= i + 1; --j) {
                if (compare(*j, *(j - 1))) {
                    std::swap(*j, *(j - 1));
                }
            }
        }
    }
}

#endif
