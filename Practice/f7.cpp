#include <iostream>

int *allocate_array( int m, int n ) {
int index{0};
if (m > n) {
    int *array{new int[m - n + 1]{0}};
    for (int i{m}; i >= n; i--) {
        array[index] = i;
        std::cout <<array[index];
        index++;
    }
    return array;
} else {
    int *array{new int[n - m + 1]{0}};
    for (int i{m}; i <= n; i++) {
        array[index] = i;
        std::cout << array[index];
        index++;
    }
return array;
}
}


int main() {
allocate_array(3, 10);

}