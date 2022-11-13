#include "Vec3.h"

class Vec3 {
    Vec3() {}

    Vec3(const float x, const float y, const float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    Vec3(const Vec3& vec3) {
        this = vec3;
    }

    Vec3(const Vec3& b, const Vec3& c) {
        this.x = b.x + c.x;
        this.y = b.y + c.y;
        this.z = b.z + c.z;
    }

    float Normalize() {
        return sqrt(x * x + y * y + z * z);
    }

    Vec3 Distance_to(const Vec3& b) {
        return new Vec3(this.x - b.x, this.y - b.y, this.z - b.z);
    }

    float dot_product(const Vec3& b) {
        return this.x * b.x + this.y * b.y + this.z * b.z;
    }

    Vec3 cross_product(const Vec3& b) {
        return new Vec3(this.y * b.z - this.z * b.y, 
            -(this.x * b.z - this.z * b.x),
            this.x * b.y - this.y * b.x)
    }

    float angle_between(const Vec3& b) {
        acos(dot_product(b)/(mag(this)*mag(b)))
    }

    float mag(const Vec3& a) {
        return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }
}