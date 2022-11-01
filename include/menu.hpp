#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <cstddef>
#include <chrono>
#include <utility>

#include "array_list.hpp"

enum class InputMethod {
    EMPTY_INPUT = 0,
    FROM_KEYBOARD = 1, 
    FROM_FILE = 2,
    FROM_RANDOM = 3,
};

enum class SortingAlgorithm {
    EMPTY_ALGORITHM = 0, 
    INSERTION_SORT = 1, 
    BUBBLE_SORT = 2, 
    HEAP_SORT = 3, 
    MERGE_SORT = 4, 
    QUICK_SORT = 5
};

class Menu {
private:
    ds::array_list<int> size_array;
    
    int choice;
    InputMethod im = InputMethod::EMPTY_INPUT; 
    SortingAlgorithm sa = SortingAlgorithm::EMPTY_ALGORITHM;
    std::string file_name;
    ds::array_list<int> array;

    void read_array_from_file();
    void write_array_to_file(std::string, std::chrono::nanoseconds);
public:
    Menu() : size_array({10, 100, 1000, 10000, 100000, 1000000}) {}

    int get_choice();
    int get_im();
    int get_sa();

    void run_all_algorithms();
    void input_choice();
    void input_input_method();
    void input_sorting_algorithm();
    void input_array_keyboard();
    void input_array_file();
    void input_array_random(std::size_t);

    void sort_array();

    void print_array();
    
    void print_menu();
    void print_input_methods();
    void print_sorting_algorithms();

    
    
    void generate_data_for_report();
   
};



#endif