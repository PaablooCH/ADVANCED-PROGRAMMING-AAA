#include <iostream>
#include <cmath>

using namespace std;

class Vec3 {
    public:
        const float Normalize();
        const Vec3 Distance_to(const Vec3& b);
        const float dot_product(const Vec3& b);
        const Vec3 cross_product(const Vec3& b);
        const float angle_between(const Vec3& b);
    private:
        const 
        float x;
        float y;
        float z;
        float mag(const Vec3& a);
}