#include <iostream>
void g(int x, int *p_y, int &r_x, int *&p_z);
int main();
void g( int x, int *p_y, int &r_x, int *&p_z ) {
x = 4;
*p_y += 1;
r_x = *p_y * x;
p_z = new int{99};
p_y = p_z;
}
int main() {
int v1{2};
int v2{3};
int *p_v1{&v1};
int *p_v2{&v2};
std::cout << v1 << " " << v2 << " " << *p_v1 << " " << *p_v2 << std::endl;
g(v1, p_v2, v2, p_v1);
std::cout << v1 << " " << v2 << " " << *p_v1 << " " << *p_v2 << std::endl;
delete p_v1;
p_v1 = nullptr;
return 0;
}
