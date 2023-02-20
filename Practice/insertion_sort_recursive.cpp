#include <iostream>

void insertion_sort(int array[], int capacity) {
    if (capacity <= 1) {
        return;
    } else {
        
        if (array[capacity] < array[capacity -1]) {
            std::swap(array[capacity], array[capacity-1]);
        }
        
        insertion_sort(array, capacity -1);
    }
}



int main() {

}