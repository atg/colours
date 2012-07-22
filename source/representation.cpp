#import "representation.hpp"

namespace colour {

// HSL -> RGB
RGB::RGB(HSL v) {
    // https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSL
    
    double c = (1.0 - fabs(2.0 * v.lightness() - 1.0)) * v.saturation();
    double hprime = hue / 6.0;
    double x = c * (1.0 - fabs(fmod(hprime, 2.0) - 1.0));
    
    if (0 <= hprime && hprime < 1) {
        r() = c; g() = x; b() = 0.0;
    }
    else if (1 <= hprime && hprime < 2) {
        r() = x; g() = c; b() = 0.0;
    }
    else if (2 <= hprime && hprime < 3) {
        r() = 0.0; g() = c; b() = x;
    }
    else if (3 <= hprime && hprime < 4) {
        r() = 0.0; g() = x; b() = c;
    }
    else if (4 <= hprime && hprime < 5) {
        r() = x; g() = 0.0; b() = c;
    }
    else if (5 <= hprime && hprime < 6) {
        r() = c; g() = 0.0; b() = x;
    }
    else {
        r() = 0.0; g() = 0.0; b() = 0.0;
    }
    
    double m = v.lightness() - (c / 2.0);
    r() += m;
    g() += m;
    b() += m;
}
// RGB -> HSL
HSL::HSL(RGB v) {
    // ...
}

// HSV -> RGB
RGB::RGB(HSV v) {
    // https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV

    double c = v.brightness() * v.saturation();
    double hprime = hue / 6.0;
    double x = c * (1.0 - fabs(fmod(hprime, 2.0) - 1.0));

    if (0 <= hprime && hprime < 1) {
        r() = c; g() = x; b() = 0.0;
    }
    else if (1 <= hprime && hprime < 2) {
        r() = x; g() = c; b() = 0.0;
    }
    else if (2 <= hprime && hprime < 3) {
        r() = 0.0; g() = c; b() = x;
    }
    else if (3 <= hprime && hprime < 4) {
        r() = 0.0; g() = x; b() = c;
    }
    else if (4 <= hprime && hprime < 5) {
        r() = x; g() = 0.0; b() = c;
    }
    else if (5 <= hprime && hprime < 6) {
        r() = c; g() = 0.0; b() = x;
    }
    else {
        r() = 0.0; g() = 0.0; b() = 0.0;
    }

    double m = v.brightness() - c;
    r() += m;
    g() += m;
    b() += m;
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

static double f(double t) {
    if (t > pow(6.0 / 29.0, 3.0))
        return pow(t, 1.0 / 3.0);
    return (1.0 / 3.0) * pow(29.0 / 6.0, 2.0) * t + (4.0 / 29.0);
}

// XYZ -> LAB
LAB::LAB(XYZ v) {
    
    lightness() = 116.0 * f(v.y / Yn) - 16.0;
    astar() = 500.0 * (f(v.x / Xn) - f(v.y / Yn));
    bstar() = 200.0 * (f(v.y / Yn) - f(v.z / Zn));
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
