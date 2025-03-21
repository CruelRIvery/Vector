#include <iostream>
#include "Vector.h"

int main(){
    double d[5] = {1,2,3,4,5};
    Vector v(d, 5);
    Vector vec = Vector(v);
    vec.print();
    return 0;
}