#include <iostream> 

void selection_sort(int array[], std::size_t capacity) {

if (capacity <= 1) {
    return;
} else {
    int max_index{0};

    for(int k{1}; k < capacity-1; k++) {
        if (array[k] > array[max_index]) {
            max_index = k;
        }
    }

    if (array[max_index] > array[capacity - 1]) {
        std::swap(array[capacity-1], array[max_index]);
    }

    selection_sort(array, capacity - 1);
}
}


int main() {

}