#include <iostream>

char * concat_strings ( char * & string_1, char * & string_2 ) {
    int capacity_1{0};
    int capacity_2{0};
    
    for (int i{0}; string_1[i] != '\0'; i++) {
        capacity_1++;
    }
    for (int i{0}; string_2[i] != '\0'; i++) {
        capacity_2++;
    }

    char *p_concat = {new char[capacity_1+capacity_2+1]{0}};

    for (int i{0}; string_1[i] != '\0'; i++) {
        p_concat[i] = string_1[i];
    }
    p_concat[capacity_1] = {' '};
    for (int i{0}; string_2[i] != '\0'; i++) {
        p_concat[(i+1)+capacity_1] = string_2[i];
    }

    p_concat[capacity_1+capacity_2+2] = '\0';

    for (int i{0}; p_concat[i] != '\0'; i++) {
        std::cout << p_concat[i] << std::endl;
    }

    return p_concat;
}

int main () {
    char *p_string{new char[6]{'H', 'e', 'l', 'l', 'o','\0'}};
    char *p_string2{new char[6]{'W', 'o', 'r', 'l', 'd', '\0'}};
    
    std::cout << concat_strings(p_string, p_string2);
}