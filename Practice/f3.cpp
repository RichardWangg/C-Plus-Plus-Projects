#include <iostream>

// An inversion in an array a is any pair of entries a[i] and a[k] where i < k but a[i] > a[k].
// Write the function definition for inversion_count(...), with the function declaration given below,
// which returns the number of inversions in the passed array.
int inversion_count( double a[], std::size_t cap ) {
    int count{0};
    for (int i{0}; i < cap; i++) {
        for (int k{i+1}; k < cap; k++) {
            if (a[i] > a[k]) {
                count++;
            }
        }
    }
    return count;
}



int main() {
double b[4] = {0,5,2, 1};
std::cout << inversion_count(b, 4);


// while (p_head != nullptr) {
//  linked_list temp = p_head;
//  p_head = p_head -> get_next();
//  delete p_head;
///
//}
//
//
//
//
//
//


}