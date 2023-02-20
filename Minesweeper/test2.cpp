#include <iostream>

int main() {
    int array[8]{};
    int left_column{0};
    int right_column{2};

    for (int i{0}; i < 8; i++) {
        if ((i+1) % 3 == 0) {
            std::cout << "i is about to new line, i = " << i << std::endl;
            left_column = left_column + 3;
            right_column = right_column + 3;
            std::cout << "leftcolumn = " << left_column <<std::endl;
            std::cout << "right column = " << right_column << std::endl;
        } 
    }
}