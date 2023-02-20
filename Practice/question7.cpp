#include <iostream>
int main();
// Write your implementation here

int even_sets_odd(int &input) {
int original = input;

    for (int k{0b1}; k < original; k = k << 2) {
        int shift = (k << 1);
        if ((k & input) == 0) {
            input |= shift;
        } else {
            input ^= shift;
        }
    }
    return input;
}

int main() {
int val{0b1110};
std::cout << "Input: " << val << std::endl;
even_sets_odd(val);
std::cout << "Output: " << val << std::endl;
return 0;
}

