#include <iostream>

int* remove_elements(int * & original_array, std::size_t original_capacity,
int * & remove_array, std::size_t remove_capacity) {
    std::size_t new_capacity = original_capacity - remove_capacity;
    int *new_array{new int[new_capacity]{0}};
    int save{0};

    for (int i{0}; i < original_capacity; i++) {
        for (int k{0}; k < remove_capacity; k++) {
            if (original_array[i] == remove_array[k] ) {
                save++;
            } 
        }
        if (save == 0) {
            new_array[i] = original_array[i];
            std::cout << new_array[i] << std::endl;
        }
        save = 0;
    }

    delete[] original_array;
    delete[] remove_array;
    original_array = nullptr;
    remove_array = nullptr;
    return new_array;
}

int main () {
int *p_array = new int[8]{1,2,3,4,5,6,7,8};
int *p_remove = new int[4]{1,4,5,3};

std::cout << remove_elements(p_array, 8, p_remove, 4);


}