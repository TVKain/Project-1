#include "sort.hpp"
#include "array_list.hpp"
#include "menu.hpp"
#include "heap.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>

#include <string>


int main() {
    Menu menu;
    
    for (;;) {
        menu.print_menu();
        
        do {
            menu.input_choice();
            if (menu.get_choice() < 1 || menu.get_choice() > 5) {
                std::cout << "Invalid choice" << std::endl;
            }
        } while (menu.get_choice() < 1 || menu.get_choice() > 5);

        if (menu.get_choice() == 5) {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        if (menu.get_choice() == 1) {
            menu.print_input_methods();
            
            do {
                menu.input_input_method();
                if (menu.get_im() < 1 || menu.get_im() > 4) {
                    std::cout << "Invalid choice" << std::endl;
                }
            } while (menu.get_im() < 1 || menu.get_im() > 4);

            if (menu.get_im() == 1) {
                menu.input_array_keyboard();
            } else if (menu.get_im() == 2) {
                menu.input_array_file();
            } else if (menu.get_im() == 3) {
                menu.input_array_random(utils::generate_random_num(10, 100));
                std::cout << "Generated random array" << std::endl;
            }

        } else if (menu.get_choice() == 2) {
            menu.print_sorting_algorithms();

            do {
                menu.input_sorting_algorithm();
                if (menu.get_sa() < 1 || menu.get_sa() > 6) {
                    std::cout << "Invalid choice" << std::endl;
                }
            } while (menu.get_sa() < 1 || menu.get_sa() > 6);

        } else if (menu.get_choice() == 3) {
            menu.sort_array();
        } else if (menu.get_choice() == 4) {
            menu.run_all_algorithms();
        }

    }   
  

    return 0;
}