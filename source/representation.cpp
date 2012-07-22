#import "representation.hpp"

namespace colour {

// HSL -> RGB
RGB::RGB(HSL v) {
    double chroma = (1.0 - fabs(2.0 * v.lightness() - 1.0)) * v.saturation();
    double hueprime = hue / 6.0;
    
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

// LCH -> LAB
LAB::LAB(LCH v) {
    
    lightness() = v.lightness();
    astar() = v.chroma() * cos(v.hue() * M_2_PI);
    bstar() = v.chroma() * sin(v.hue() * M_2_PI);
    alpha() = v.alpha();
}
// LAB -> LCH
LCH::LCH(LAB v) {
    
    hue() = atan2(v.astar(), v.bstar()) / M_2_PI;
    chroma() = (v.astar() + v.bstar()) / 2.0;
    lightness() = v.lightness();
    alpha() = v.alpha();
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
    
    a = v.a;
    jch2xyz_ciecam02(
        &x, &y, &z,
        v.lightness(), v.chroma(), v.hue(),
        CIECAM_XW, CIECAM_YW, CIECAM_ZW,
        CIECAM_YB, CIECAM_LA,
        CIECAM_F, CIECAM_C, CIECAM_NC
    );
}
// XYZ -> CIECAM
CIECAM::CIECAM(XYZ v) {
    
    a = v.a;
    xyz2jch_ciecam02(
        &z, &y, &x,
        v.x, v.y, v.z,
        CIECAM_XW, CIECAM_YW, CIECAM_ZW,
        CIECAM_YB, CIECAM_LA,
        CIECAM_F, CIECAM_C, CIECAM_NC
    );
}

CIECAM::Extras CIECAM::extras() {
    CIECAM::Extras ext;
    ext.brightness = 0.0; ext.colourfulness = 0.0; ext.saturation = 0.0;
    XYZ xyz(*this);
    
    xyz2jchqms_ciecam02(NULL, NULL, NULL,
        &ext.brightness, &ext.colourfulness, &ext.saturation,
        xyz.x, xyz.y, xyz.z,
        CIECAM_XW, CIECAM_YW, CIECAM_ZW,
        CIECAM_YB, CIECAM_LA,
        CIECAM_F, CIECAM_C, CIECAM_NC);
    
    return ext;
}

}
