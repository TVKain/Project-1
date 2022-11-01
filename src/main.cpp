#include "sort.hpp"
#include "array_list.hpp"
//#include "menu.hpp"
#include <algorithm>
#include <iostream>

#include <string>

int main() {
    ds::array_list<std::string> a;

    a.push_back("Hi");
    a.push_back("Hello");
    a.push_back("Shit");
    a.push_back("hmmm");
    a.push_back("hmmm");
    std::cout << a[0];

    return 0;
}