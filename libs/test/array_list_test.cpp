#include "array_list.hpp"

int main() {
    ds::array_list<int> a = {1,2,3,4};

    if (a.size() != 4) {
        return 1;
    }

    if (a.at(0) != 1) {
        return 1;
    }


    return 0;
}