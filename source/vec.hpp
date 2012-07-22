#import <math.h> // I spit on your "cmath"!
#import <assert.h>

namespace colour {

struct Vec4 {
    double x;
    double y;
    double z;
    double a; // Alpha
    double& alpha() { return a; }
    
    Vec4()
      : x(), y(), z(), a() { }
    Vec4(double x, double y, double z, double a = 1.0)
      : x(x), y(y), z(z), a(a) { }
};

Vec4 operator + (Vec4 v, Vec4 w) {
    assert(fabs(v.a - w.a) < 0.001 && "Trying to add colours of different alpha.");
    
    return Vec4(
        v.x + w.x,
        v.y + w.y, 
        v.z + w.z, 
        v.a);
}

Vec4 operator - (Vec4 v, Vec4 w) {
    assert(fabs(v.a - w.a) < 0.001 && "Trying to subtract colours of different alpha.");
    
    return Vec4(
        v.x - w.x,
        v.y - w.y, 
        v.z - w.z, 
        v.a);
}

Vec4 operator * (double val, Vec4 w) {
    return Vec4(
        val * w.x,
        val * w.y, 
        val * w.z, 
        w.a);
}

Vec4 operator * (Vec4 v, double val) {
    return Vec4(
        v.x * val,
        v.y * val, 
        v.z * val, 
        v.a);
}

}