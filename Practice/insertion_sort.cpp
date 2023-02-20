#include <iostream>

void insert(double array[], std::size_t capacity) {
    
for (std::size_t j{1}; j < capacity; j++) {
    double value = {array[j]};

    std::size_t k;
    for (k = j; array[k-1] > value && k>0; k--) {
        array[k] = array[k-1];
    }
    array[k] = value;
}
}

int main() {
    
}