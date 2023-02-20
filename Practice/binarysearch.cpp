#include <iostream>

std::size_t binary_search( double const array[], std::size_t const capacity, double const value ) {

    std::size_t lower_index{0};
    std::size_t upper_index{capacity - 1};

    while ((lower_index <= upper_index) && (upper_index < capacity)) {
        std::size_t avg_index{(upper_index + lower_index)/2};

        if (array[avg_index] == value) {
            return avg_index;
        } else if (array[avg_index] > value) {
            upper_index = avg_index - 1; 
        } else {
            lower_index = avg_index + 1;
        }
    }

    return capacity;
 }


int main () {

}