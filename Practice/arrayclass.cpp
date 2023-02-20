#include <iostream>

class array {

    public:
        array(double cap, double initial);
        ~array();
        int get_capacity(int n);
        double get_value_at_index(int n);
        void set_value_at_index(int index, int value);

    private:
        double capacity;
        double def{0.0};
        double *p_array;

};

array::array(double cap, double initial): capacity{cap}, def{initial} {
    p_array = new double[capacity]{def};
} 

array::~array() {
    delete[] p_array;
    p_array = nullptr;
}

int array::get_capacity(int n) {
    return capacity;
}

double array::get_value_at_index(int n) {
    if (n > capacity || n < 0) {
        return def;
    } else {
        return p_array[n];
    }
}

void array::set_value_at_index(int index, int value) {
    if (index > capacity || index < 0) {
        double *new_array{new double[index]{def}};
        for (int i{0}; i < capacity; i++) {
            new_array[i] = p_array[i];
        }
        delete[] p_array;
        p_array = new_array;
        new_array = nullptr;
    } else {
        p_array[index] = value;
    }
}





int main() {

}