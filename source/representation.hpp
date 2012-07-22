#import "vec.hpp"

namespace colour {

struct RGB, HSL, HSV, XYZ, LAB, HCL, CIECAM;

/*
 * RGB is bog standard sRGB.
 * HSL is Hue Saturation Lightness.
 * HSV is Hue Saturation Value aka Hue Saturation Brightness. A stupid colour model that is unfortunately used in many programs (including OS X).
 * (CIE)XYZ is a transitional colour space between RGB and LAB. There's not much use for it.
 * (CIE)LAB is a perceptually linear colour space.
 * HCL is better known as CIELch. Hue, Chroma, Lightness. We reverse it to match the order of HSL.
 * CIECAM is an advanced colour space that is more perceptually linear than CIELAB, though less common.
 */

struct RGB : Vec4 {
    RGB(double r, double g, double b, double a = 1.0)
      : RGB(r, g, b, a) { }
    
    RGB(RGB v) : Vec4(v);
    RGB(HSL v);
    RGB(HSV v);
    RGB(XYZ v);
    RGB(LAB v) : RGB(XYZ(v)) { }
    RGB(HCL v) : RGB(XYZ(LAB(v))) { }
    RGB(CIECAM v) : RGB(XYZ(LAB(v))) { }
    
    double r() { return x; }
    double g() { return y; }
    double b() { return z; }
};

// HSL -> RGB
RGB::RGB(HSL v) {
    // ...
}
// RGB -> HSL
HSL::HSL(RGB v) {
    // ...
}

// HSV -> RGB
RGB::RGB(HSV v) {
    // ...
}
// RGB -> HSV
HSV::HSV(RGB v) {
    // ...
}

// XYZ -> RGB
RGB::RGB(XYZ v) {
    // ...
}
// RGB -> XYZ
XYZ::XYZ(RGB v) {
    // ...
}

// XYZ -> LAB
LAB::LAB(XYZ v) {
    // ...
}
// LAB -> XYZ
XYZ::XYZ(LAB v) {
    // ...
}

// HCL -> LAB
LAB::LAB(HCL v) {
    // ...
}
// LAB -> HCL
HCL::HCL(LAB v) {
    // ...
}

// CIECAM -> LAB
LAB::LAB(CIECAM v) {
    // ...
}
// LAB -> CIECAM
CIECAM::CIECAM(LAB v) {
    // ...
}

}