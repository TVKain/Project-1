#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <limits>

#include <cstddef>
#include <ctime>

#include "menu.hpp"
#include "utils.hpp"
#include "array_list.hpp"
#include "sort.hpp"
#include <filesystem>

void Menu::print_menu() {
    std::cout << std::endl;
    std::cout << "      SORTING MENU" << std::endl;
    std::cout << "1. Choose input method" << std::endl;
    std::cout << "2. Choose sorting algorithm" << std::endl;
    std::cout << "3. Start sorting" << std::endl;
    std::cout << "4. Run all sorting algorithms" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void Menu::print_sorting_algorithms() {
    std::cout << std::endl;
    std::cout << "  SORTING ALGORITHMS" << std::endl;
    std::cout << "1. Insertion Sort" << std::endl;
    std::cout << "2. Bubble Sort" << std::endl;
    std::cout << "3. Heap Sort" << std::endl;
    std::cout << "4. Merge Sort" << std::endl;
    std::cout << "5. Quick Sort" << std::endl;
    std::cout << "6. Return" << std::endl;
}

void Menu::print_input_methods() {
    std::cout << std::endl;
    std::cout << "   Input Methods" << std::endl;
    std::cout << "1. Keyboard" << std::endl;
    std::cout << "2. File" << std::endl;
    std::cout << "3. Random" << std::endl;
    std::cout << "4. Return" << std::endl;
}

void Menu::input_choice() {
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    clear_input();
}

void Menu::input_input_method() {
    int input;
    std::cout << "Enter your choice: ";
    std::cin >> input;
    clear_input();

    im = static_cast<InputMethod>(input);
}

void Menu::input_sorting_algorithm() {
    int input;
    std::cout << "Enter your choice: ";
    std::cin >> input;
    clear_input();

    sa = static_cast<SortingAlgorithm>(input);
}

void Menu::input_array_keyboard() {
    std::string input;
    std::cout << "Enter array: ";
    std::getline(std::cin, input);

    int num;
    std::stringstream ssin(input);
    
    while (ssin >> num) {
        array.push_back(num);
    }
}

void Menu::input_array_file() {
    std::cout << "Enter file name: ";
    std::cin >> file_name;
    clear_input();
    read_array_from_file();
}

void Menu::input_array_random(std::size_t n) {
    decltype(n) i = 0;

    for (; i < n; ++i) {
        array.push_back(utils::generate_random_num(-n * 4, n * 4));
    }
}

void Menu::read_array_from_file() {
    if (file_name.empty()) {
        std::cout << "File name has not been set" << std::endl;
        return;
    }

    std::ifstream file(file_name);
    int num;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ssin(line);
            ssin >> num;
            array.push_back(num);
        }
    } else {
        std::cout << "Can not open file" << std::endl;
    }

}

void Menu::write_array_to_file(std::string sorting_algo, std::chrono::nanoseconds time_elapsed) {
    std::string folder_name = utils::get_current_time();

    auto size = array.size();
    
    std::string file_name = sorting_algo + "-" + std::to_string(size);

    if (!std::filesystem::create_directory(folder_name)) {
        std::cout << "Created directory failed" << std::endl;
        return;
    }

    std::ofstream file(folder_name + "/" + file_name, std::ios::out);

    if (file.is_open()) {
        file << time_elapsed.count() << " ns" << std::endl;
        for (const auto &i : array) {
            file << i << std::endl;
        }
        file.close();
    } else {
        std::cout << "Can not open file" << std::endl;
    }

}

/* @brief: sort the current array will stop if array is empty or no algorithm has been chosen 
 * @params: void
 * @return: void
 * @side-effects: writing sorted array to file and clear the current array 
 */
void Menu::sort_array() {
    if (array.empty()) {
        std::cout << "Array is empty" << std::endl;
        return;
    }
    
    std::chrono::nanoseconds elapsed;

    std::string sorting_algo;
    switch (sa) {
        case SortingAlgorithm::INSERTION_SORT: 
            sorting_algo = "insertion sort"; 
            elapsed = utils::bench_time(algo::sort::insertion_sort<int>, array.begin(), array.end());
            
            break;
        case SortingAlgorithm::BUBBLE_SORT: 
            sorting_algo = "bubble sort"; 
            elapsed = utils::bench_time(algo::sort::bubble_sort<int>, array.begin(), array.end());
            break;
        case SortingAlgorithm::HEAP_SORT: 
            sorting_algo = "heap sort";
            elapsed = utils::bench_time(algo::sort::heap_sort<int>, array.begin(), array.end()); 
            break;
        case SortingAlgorithm::MERGE_SORT: 
            sorting_algo = "merge sort"; 
            elapsed = utils::bench_time(algo::sort::merge_sort_iterative<int>, array.begin(), array.end());
            break;
        case SortingAlgorithm::QUICK_SORT: 
            sorting_algo = "quick sort"; 
            elapsed = utils::bench_time(algo::sort::quick_sort_iterative<int>, array.begin(), array.end());
            break;
        default:
            std::cout << "Sorting algorithm has not been chosen" << std::endl; 
            return;
            break;
    }

    write_array_to_file(sorting_algo, elapsed);
    array.clear();
}



void Menu::print_array() {
    for (const auto &i : array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


void Menu::run_all_algorithms() {
    array.clear();

    ds::array_list<std::pair<int, std::chrono::nanoseconds>> insertion_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> bubble_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> heap_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> merge_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> quick_data;


    ds::array_list<std::pair<std::string, ds::array_list<std::pair<int, std::chrono::nanoseconds>>>> sorting_data;


    std::chrono::nanoseconds elapsed;
    for (int i = 10; i <= 100000; i *= 10) {
        for (int j = 0; j < 5; ++j) {
            input_array_random(i);
            
            switch (j) {
                case 0: 
                    elapsed = utils::bench_time(algo::sort::insertion_sort<int>, array.begin(), array.end()); 
                    insertion_data.push_back(std::make_pair(i, elapsed));
                break;
                case 1: 
                    elapsed = utils::bench_time(algo::sort::bubble_sort<int>, array.begin(), array.end()); 
                    bubble_data.push_back(std::make_pair(i, elapsed));
                break;
                case 2: 
                    elapsed = utils::bench_time(algo::sort::heap_sort<int>, array.begin(), array.end()); 
                    heap_data.push_back(std::make_pair(i, elapsed));
                break;
                case 3: 
                    elapsed = utils::bench_time(algo::sort::merge_sort_iterative<int>, array.begin(), array.end()); 
                    merge_data.push_back(std::make_pair(i, elapsed));
                break;
                case 4: 
                    elapsed = utils::bench_time(algo::sort::quick_sort_iterative<int>, array.begin(), array.end()); 
                    quick_data.push_back(std::make_pair(i, elapsed));
                break;
                default: break;
            }

            
            array.clear();
        }

    }

    sorting_data.push_back(std::make_pair("INSERTION", insertion_data));
    sorting_data.push_back(std::make_pair("BUBBLE", bubble_data));
    sorting_data.push_back(std::make_pair("HEAP", heap_data));
    sorting_data.push_back(std::make_pair("MERGE", merge_data));
    sorting_data.push_back(std::make_pair("QUICK", quick_data));

    
    for (auto &elem : sorting_data) {
        std::cout << elem.first << std::endl;
        for (auto &j : elem.second) {
            std::cout << "\tSize: " <<  j.first;
            std::cout << "\tTime: " << j.second.count() << " ns" << std::endl; 
        }
    }

    array.clear();
}


/* 
 * Create 5 files
 */
void Menu::generate_data_for_report() {
    array.clear();

    ds::array_list<std::pair<int, std::chrono::nanoseconds>> insertion_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> bubble_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> heap_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> merge_data;
    ds::array_list<std::pair<int, std::chrono::nanoseconds>> quick_data;


    ds::array_list<std::pair<std::string, ds::array_list<std::pair<int, std::chrono::nanoseconds>>>> sorting_data;


    std::chrono::nanoseconds elapsed;
    for (int i = 10; i <= 100000; i *= 10) {
        for (int j = 0; j < 5; ++j) {
            input_array_random(i);
            
            switch (j) {
                case 0: 
                    elapsed = utils::bench_time(algo::sort::insertion_sort<int>, array.begin(), array.end()); 
                    insertion_data.push_back(std::make_pair(i, elapsed));
                break;
                case 1: 
                    elapsed = utils::bench_time(algo::sort::bubble_sort<int>, array.begin(), array.end()); 
                    bubble_data.push_back(std::make_pair(i, elapsed));
                break;
                case 2: 
                    elapsed = utils::bench_time(algo::sort::heap_sort<int>, array.begin(), array.end()); 
                    heap_data.push_back(std::make_pair(i, elapsed));
                break;
                case 3: 
                    elapsed = utils::bench_time(algo::sort::merge_sort_iterative<int>, array.begin(), array.end()); 
                    merge_data.push_back(std::make_pair(i, elapsed));
                break;
                case 4: 
                    elapsed = utils::bench_time(algo::sort::quick_sort_iterative<int>, array.begin(), array.end()); 
                    quick_data.push_back(std::make_pair(i, elapsed));
                break;
                default: break;
            }

            
            array.clear();
        }

    }

    sorting_data.push_back(std::make_pair("insertion", insertion_data));
    sorting_data.push_back(std::make_pair("bubble", bubble_data));
    sorting_data.push_back(std::make_pair("heap", heap_data));
    sorting_data.push_back(std::make_pair("merge", merge_data));
    sorting_data.push_back(std::make_pair("quick", quick_data));

    for (auto i = 0; i < sorting_data.size(); ++i) {
        std::ofstream file(sorting_data[i].first + ".txt", std::ios::out);

        if (file.is_open()) {
            for (auto &elem: sorting_data[i].second) {
                file << elem.first << " " << elem.second.count() << std::endl;
            }
            file.close();
        } else {
            std::cout << "Can not open file" << std::endl;
        }
    }
}


int Menu::get_choice() {
    return choice;
}

int Menu::get_im() {
    return static_cast<int>(im);
}

int Menu::get_sa() {
    return static_cast<int>(sa);
}