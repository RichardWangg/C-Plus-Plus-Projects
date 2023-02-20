#include <iostream>
#include <cmath>
#include <stdexcept>

class Vector3D {
public:

Vector3D(double x, double y, double z);

~Vector3D();

double *get_values() const;

void set_values(double x, double y, double z);

double get_magnitude() const;

Vector3D cross_product(Vector3D const & other) const;

bool operator<(Vector3D const & other) const;

double operator*(Vector3D const & other) const;

Vector3D operator+(Vector3D const & other) const;

Vector3D operator-(Vector3D const & other) const;

private:

double x;
double y;
double z;

};



int main() {

}