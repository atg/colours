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
      : Vec4(r, g, b, a) { }
    
    RGB(RGB v) : Vec4(v);
    RGB(HSL v);
    RGB(HSV v);
    RGB(XYZ v);
    RGB(LAB v) : RGB(XYZ(v)) { }
    RGB(HCL v) : RGB(XYZ(LAB(v))) { }
    // RGB(CIECAM v) : RGB(XYZ(LAB(v))) { }
    
    double r() { return x; }
    double g() { return y; }
    double b() { return z; }
};

struct HSL : Vec4 {
    HSL(double h, double s, double l, double a = 1.0)
      : Vec4(h, s, l, a) { }
    
    HSL(RGB v);
    HSL(HSL v) : Vec4(v);
    HSL(HSV v) : HSL(RGB(v));
    HSL(XYZ v) : HSL(RGB(v));
    HSL(LAB v) : HSL(RGB(XYZ(v))) { }
    HSL(HCL v) : HSL(RGB(XYZ(LAB(v)))) { }
    // HSL(CIECAM v) : HSL(RGB(XYZ(LAB(v)))) { }

    double hue() { return x; }
    double saturation() { return y; }
    double lightness() { return z; }
};

struct HSV : Vec4 {
    HSV(double h, double s, double v, double a = 1.0)
      : Vec4(h, s, v, a) { }

    HSV(RGB v);
    HSV(HSL v) : HSV(RGB(v));
    HSV(HSV v) : Vec4(v);
    HSV(XYZ v) : HSV(RGB(v));
    HSV(LAB v) : HSV(RGB(XYZ(v))) { }
    HSV(HCL v) : HSV(RGB(XYZ(LAB(v)))) { }
    // HSV(CIECAM v) : HSV(RGB(XYZ(LAB(v)))) { }

    double hue() { return x; }
    double saturation() { return y; }
    double value() { return z; }
};

struct XYZ : Vec4 {
    XYZ(double x, double y, double z, double a = 1.0)
      : Vec4(x, y, z, a) { }

    XYZ(RGB v);
    XYZ(HSL v) : XYZ(RGB(v));
    XYZ(HSV v) : XYZ(RGB(v));
    XYZ(XYZ v) : Vec4(v);
    XYZ(LAB v);
    XYZ(HCL v) : XYZ(LAB(v)) { }
    // XYZ(CIECAM v) : XYZ(LAB(v)) { }
};

struct LAB : Vec4 {
    LAB(double l, double astar, double bstar, double a = 1.0)
      : Vec4(l, astar, bstar, a) { }

    LAB(RGB v) : LAB(XYZ(v));
    LAB(HSL v) : LAB(XYZ(RGB(v)));
    LAB(HSV v) : LAB(XYZ(RGB(v)));
    LAB(XYZ v);
    LAB(LAB v) : Vec4(v);
    LAB(HCL v);
    // LAB(CIECAM v);

    double lightness() { return x; }
    double astar() { return y; }
    double bstar() { return z; }
};

struct HCL : Vec4 {
    HCL(double hue, double chroma, double lightness, double a = 1.0)
      : Vec4(hue, chroma, lightness, a) { }

    HCL(RGB v) : HCL(LAB(XYZ(v)));
    HCL(HSL v) : HCL(LAB(XYZ(RGB(v))));
    HCL(HSV v) : HCL(LAB(XYZ(RGB(v))));
    HCL(XYZ v) : HCL(LAB(v));
    HCL(LAB v);
    HCL(HCL v) : Vec4(v);
    // HCL(CIECAM v) : HCL(LAB(v));

    double hue() { return x; }
    double chroma() { return y; }
    double lightness() { return z; }
};

struct CIECAM : Vec4 {
    HCL(double hue, double chroma, double lightness, double a = 1.0)
      : Vec4(hue, chroma, lightness, a) { }

    CIECAM(RGB v) : CIECAM(LAB(XYZ(v)));
    CIECAM(HSL v) : CIECAM(LAB(XYZ(RGB(v))));
    CIECAM(HSV v) : CIECAM(LAB(XYZ(RGB(v))));
    CIECAM(XYZ v);
    CIECAM(LAB v) : CIECAM(XYZ(v));
    CIECAM(HCL v) : CIECAM(LAB(v));
    CIECAM(CIECAM v) : Vec4(v);

    double hue() { return x; }
    double chroma() { return y; }
    double lightness() { return z; }
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

const double CIECAM_LA = 4.0;
const double CIECAM_YB = 20.0;
const double CIECAM_XW = 95.05;
const double CIECAM_YW = 100.0;
const double CIECAM_ZW = 108.88;

const double CIECAM_F = 1.0;
const double CIECAM_C = 0.690;
const double CIECAM_NC = 1.0;

// CIECAM -> XYZ
XYZ::XYZ(CIECAM v) {
    // ...
}
// XYZ -> CIECAM
CIECAM::CIECAM(XYZ v) {
    
    CIECAM out;
    out.a = v.a;
    xyz2jch_ciecam02(
        &out.z, &out.y, &out.x,
        v.x, v.y, v.z,
        CIECAM_XW, CIECAM_YW, CIECAM_ZW,
        CIECAM_YB, CIECAM_LA,
        CIECAM_F, CIECAM_C, CIECAM_NC
    ); // ???
    
    return out;
}

}