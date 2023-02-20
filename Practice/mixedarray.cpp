#include <iostream>

int* mix_array(int * array1, int* array2, std::size_t capacity){

int new_cap = capacity*2;
int tracker{0};
int tracker2{2};
int *mixed{new int[new_cap]{0}};

for (int i{0}; i<capacity; i++) {
    mixed[tracker] = array1[i];
    if (i%2 == 0) {
        tracker++;
    } else {
        tracker = tracker + 3;
    }
}

for (int i{0}; i < capacity; i++) {
    mixed[tracker2] = array2[i];
    if (i%2 == 0) {
        tracker2++;
    } else {
        tracker2 = tracker2 + 3;
    }
}

for (int k{0}; k < new_cap; k++) {
    std::cout << mixed[k] << std::endl;
}

return mixed;










// for (int i{0}; i < new_cap; i = i + 2) {
//     if (whos_turn % 2 == 0) {
//         mixed[i] = array1[whos_turn];
//     } else {
//         mixed[i] = array2[whos_turn];
//     }
//     whos_turn++;
// }

// for (int i{1}; i < new_cap; i = i + 2) {
//     if (whos_turn % 2 == 0) {
//         mixed[i] = array1[whos_turn];
//     } else {
//         mixed[i] = array2[whos_turn];
//     }
//     whos_turn++;
// }

// delete[] array1;
// delete[] array2;
// array1 = nullptr;
// array2 = nullptr;

// for (int k{0}; k < new_cap; k++) {
//     std::cout << mixed[k] << std::endl;
// }

// return mixed;

}



int main() {

int *firstarg{new int[8]{1, 2, 3,4,5,6,7,8}};
int *second{new int[8]{10,11,12,13,14,15,16,17}};
mix_array(firstarg, second, 8);



}