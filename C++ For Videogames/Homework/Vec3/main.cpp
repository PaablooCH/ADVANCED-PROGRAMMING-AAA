#include <iostream>
#include "Vec3.h"
using namespace std;


int main() {
    Vec3 a = new Vec3();
    Vec3 b = new Vec3(1, 0, 1);
    Vec3 c = new Vec3(b);
    Vec3 d = new Vec3(b, c);

    cout << d.Normalize() << endl << d.dot_product(b) << endl << d.Distance_to(b) << endl << d.cross_product(b) << endl 
        << d.angle_between(b) << endl;
}