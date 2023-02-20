#include <iostream>



int main() {

int input;
std::cout << "enter" << std::endl;
std::cin >> input;
int pyramid{1};

for (int column{input+1}; column > 0; column--) {
    for (int space{input}; space > 0; space--) {
        std::cout << " ";
    }
    for (int row{0}; row < pyramid; row++) {
        std::cout << input;
    }

    std::cout << std::endl;
    pyramid = pyramid + 2;
    input--;
}

}