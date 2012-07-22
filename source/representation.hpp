#import "vec.hpp"
#import "ciecam02.h"

namespace colour {

struct RGB;
struct HSL;
struct HSB;
struct XYZ;
struct LAB;
struct LCH;
struct CIECAM;

/*
 * RGB is bog standard sRGB.
 * HSL is Hue Saturation Lightness.
 * HSB is Hue Saturation Brightness aka Hue Saturation Value. A stupid colour model that is unfortunately used in many programs (including OS X).
 * (CIE)XYZ is a transitional colour space between RGB and LAB. There's not much use for it.
 * (CIE)LAB is a perceptually linear colour space.
 * LCH is CIELch. Lightness, Chroma, Hue. We reverse it to match the order of HSL.
 * CIECAM is an advanced colour space that is more perceptually linear than CIELAB, though less common.
 */

struct HCL {
    
    HCL(double h, double s, double l)
      : hue(h), saturation(s), lightness(l) { }
    
    double hue;
    double saturation;
    double lightness;
    double a;
};

struct RGB : Vec4 {
    RGB(double r, double g, double b, double a = 1.0)
      : Vec4(r, g, b, a) { }
    
    RGB(RGB const & v) : Vec4(v) { }
    RGB(HSL);
    RGB(HSB);
    RGB(XYZ);
    // RGB(LAB v) : RGB(XYZ(v)) { }
    // RGB(LCH v) : RGB(XYZ(LAB(v))) { }
    // RGB(CIECAM v) : RGB(XYZ(LAB(v))) { }
    
    double& red() { return x; }
    double& green() { return y; }
    double& blue() { return z; }
};

struct HSL : Vec4 {
    HSL(double h, double s, double l, double a = 1.0)
      : Vec4(h, s, l, a) { }
    
    HSL(RGB v);
    HSL(HSL const &v) : Vec4(v) { }
    // HSL(HSB v) : HSL(RGB(v));
    // HSL(XYZ v) : HSL(RGB(v));
    // HSL(LAB v) : HSL(RGB(XYZ(v))) { }
    // HSL(LCH v) : HSL(RGB(XYZ(LAB(v)))) { }
    // HSL(CIECAM v) : HSL(RGB(XYZ(LAB(v)))) { }

    double& hue() { return x; }
    double& saturation() { return y; }
    double& lightness() { return z; }
};

struct HSB : Vec4 {
    HSB(double h, double s, double v, double a = 1.0)
      : Vec4(h, s, v, a) { }

    HSB(RGB v);
    // HSB(HSL v) : HSB(RGB(v));
    HSB(HSB const &v) : Vec4(v) { }
    // HSB(XYZ v) : HSB(RGB(v));
    // HSB(LAB v) : HSB(RGB(XYZ(v))) { }
    // HSB(LCH v) : HSB(RGB(XYZ(LAB(v)))) { }
    // HSB(CIECAM v) : HSB(RGB(XYZ(LAB(v)))) { }

    double& hue() { return x; }
    double& saturation() { return y; }
    double& brightness() { return z; }
};

struct XYZ : Vec4 {
    XYZ(double x, double y, double z, double a = 1.0)
      : Vec4(x, y, z, a) { }

    XYZ(RGB v);
    // XYZ(HSL v) : XYZ(RGB(v));
    // XYZ(HSB v) : XYZ(RGB(v));
    XYZ(XYZ const &v) : Vec4(v) { }
    XYZ(LAB v);
    // XYZ(LCH v) : XYZ(LAB(v)) { }
    XYZ(CIECAM v); // : XYZ(LAB(v)) { }
};

struct LAB : Vec4 {
    LAB(double l, double astar, double bstar, double a = 1.0)
      : Vec4(l, astar, bstar, a) { }
    
    // LAB(RGB v) : LAB(XYZ(v));
    // LAB(HSL v) : LAB(XYZ(RGB(v)));
    // LAB(HSB v) : LAB(XYZ(RGB(v)));
    LAB(XYZ v);
    LAB(LAB const &v) : Vec4(v) { }
    LAB(LCH v);
    // LAB(CIECAM v);

    double& lightness() { return x; }
    double& astar() { return y; }
    double& bstar() { return z; }
};

struct LCH : Vec4 {
    LCH(double hue, double chroma, double lightness, double a = 1.0)
      : Vec4(hue, chroma, lightness, a) { }

    // LCH(RGB v) : LCH(LAB(XYZ(v)));
    // LCH(HSL v) : LCH(LAB(XYZ(RGB(v))));
    // LCH(HSB v) : LCH(LAB(XYZ(RGB(v))));
    // LCH(XYZ v) : LCH(LAB(v));
    LCH(LAB v);
    LCH(LCH const &v) : Vec4(v) { }
    // LCH(CIECAM v) : LCH(LAB(v));

    double& hue() { return x; }
    double& chroma() { return y; }
    double& lightness() { return z; }
};

struct CIECAM : Vec4 {
    CIECAM(double lightness, double chroma, double hue, double a = 1.0)
      : Vec4(hue, chroma, lightness, a) { }
    
    CIECAM() : Vec4() { }
    // CIECAM(RGB v) : CIECAM(LAB(XYZ(v)));
    // CIECAM(HSL v) : CIECAM(LAB(XYZ(RGB(v))));
    // CIECAM(HSB v) : CIECAM(LAB(XYZ(RGB(v))));
    CIECAM(XYZ v);
    // CIECAM(LAB v) : CIECAM(XYZ(v));
    // CIECAM(LCH v) : CIECAM(LAB(v));
    CIECAM(CIECAM const &v) : Vec4(v) { }

    double& lightness() { return x; }
    double& chroma() { return y; }
    double& hue() { return z; }
    
    // Additional information
    typedef struct {
        double brightness;
        double colourfulness;
        double saturation;
    } Extras;
    
    Extras extras();
    double brightness() { return extras().brightness; }
    double colourfulness() { return extras().colourfulness; }
    double saturation() { return extras().saturation; }
};

}
