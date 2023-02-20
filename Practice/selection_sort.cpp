#include <iostream>

void selection_sort( double array[], std::size_t capacity ) {    
    for (std::size_t k{capacity - 1}; k > 0; k--) {

    std::size_t max_index{0};

    for (int i{1}; i<=k ; i++) {
        if (array[i] > array[max_index]) {
            max_index = i;
        }
    }

    if (array[max_index] > array[k]) {
        double tmp{array[k]};
        array[k] = array[max_index];
        array[max_index] = tmp;
    }
}
}


int main () {

}