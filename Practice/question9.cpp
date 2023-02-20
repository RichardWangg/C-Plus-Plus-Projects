#include <iostream>

int is_sub_array(int arr1[], int cap1, int arr2[], int cap2) {
    int possible_return;
    int checker{0};
    for (int i{0}; i < cap2; i++) {
        if (arr2[i] == arr1[0]) {
            int index_start = i;
            possible_return = i;
            for (int k{0}; k < cap1; k++) {
                if (arr1[k] == arr2[index_start]) {
                    checker++;
                }
                index_start++;
            }
        }
    }

    if (checker = cap1) {
        return possible_return;
    } else {
        return cap2;
    }
}

void remove_entries(int arr[], int cap, int start, int count) {
   int replace = start;

    for (int i{count}; i < cap; i++) {
            arr[start] = arr[i];
            arr[i] = 0;
    }
}

void seek_n_remove(int arr1[], int cap1, int arr2[], int cap2) {
    if (is_sub_array(arr1, cap1, arr2, cap2) != cap2) {
        remove_entries(arr2, cap2, is_sub_array(arr1, cap1, arr2, cap2), cap1);
    } else if (is_sub_array(arr2, cap2, arr1, cap1) != cap1) {
        remove_entries(arr1, cap1, is_sub_array(arr2, cap2, arr1, cap1), cap2);
    }
}


int main() {


int array[10] = {2,3,1,4,1,2,3,4,5,6};

int arrg[3] = {2,3,4};

std::cout << is_sub_array(arrg, 3, array, 10);

}