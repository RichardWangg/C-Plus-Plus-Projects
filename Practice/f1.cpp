#include <iostream>

void mid_term_question( unsigned int n ) {

for ( unsigned int k{1}; k <= n; k++) {
    if (k == 1) {
        for (unsigned int columns{1}; columns <= n; columns++) {
            for (unsigned int rows{1}; rows <= columns; rows++) {
                std::cout << rows;
            }
            std::cout << std::endl;
        }
    } else  {
        for (unsigned int space{k - 1}; space > 0; space--) {
            std::cout << " ";    
        }
        for (unsigned int row{k}; row < k + n; row++) {
            if (row > 9) {
                std::cout << row % 10;
            } else {
            std::cout << row;
            }
        }
        std::cout << std::endl;
    }
}
}




int main() {
mid_term_question(7);
}