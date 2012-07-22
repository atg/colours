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
    // https://en.wikipedia.org/wiki/HSL_and_HSV#Hue_and_chroma
    
    double max = std::max(std::max(v.r, v.g), v.b);
    double min = std::min(std::min(v.r, v.g), v.b);
    double chroma = max - min;
    
    hue() = 0.0;
    if (v.r > v.g && v.r > v.b) // Red is max
        hue() = fmod((v.g - v.b) / c, 6.0);
    if (v.g > v.r && v.g > v.b) // Green is max
        hue() = (v.b - v.r) + 2.0;
    if (v.b > v.r && v.b > v.g) // Blue is max
        hue() = (v.b - v.g) + 4.0;
    
    hue() /= 6.0;
    
    // https://en.wikipedia.org/wiki/HSL_and_HSV#Lightness
    lightness() = (v.r + v.g + v.b) / 3.0;
    
    // https://en.wikipedia.org/wiki/HSL_and_HSV#Saturation
    if (l <= 0.5)
        saturation() = chroma / (2.0 * l);
    else
        saturation() = chroma / (2.0 - 2.0 * l);
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
    // https://en.wikipedia.org/wiki/HSL_and_HSV#Hue_and_chroma
    
    // https://en.wikipedia.org/wiki/HSL_and_HSV#Hue_and_chroma
    
    double max = std::max(std::max(v.r, v.g), v.b);
    double min = std::min(std::min(v.r, v.g), v.b);
    double chroma = max - min;
    
    hue() = 0.0;
    if (v.r > v.g && v.r > v.b) // Red is max
        hue() = fmod((v.g - v.b) / c, 6.0);
    if (v.g > v.r && v.g > v.b) // Green is max
        hue() = (v.b - v.r) + 2.0;
    if (v.b > v.r && v.b > v.g) // Blue is max
        hue() = (v.b - v.g) + 4.0;
    
    hue() /= 6.0;
    
    // https://en.wikipedia.org/wiki/HSL_and_HSV#Lightness
    brightness() = max;
    
    // https://en.wikipedia.org/wiki/HSL_and_HSV#Saturation
    saturation() = chroma / brightness();
}

static double rgb_linear_to_standard(double x) {
    if (x <= 0.0031308)
        return 12.92 * x;
    return (1 + 0.055) * pow(x, 1.0 / 2.4) - 0.055;
}

static double rgb_standard_to_linear(double x) {
    if (x <= 0.04045)
        return x / 12.92;
    return pow((x + 0.055) / 1.055, 2.4);
}

// XYZ -> RGB
RGB::RGB(XYZ v) {
    // https://en.wikipedia.org/wiki/SRGB#The_forward_transformation_.28CIE_xyY_or_CIE_XYZ_to_sRGB.29

    r() =  3.2406 * x  -  1.5372 * y  -  0.4986 * z;
    g() = -0.9689 * x  +  1.8758 * y  +  0.0415 * z;
    b() =  0.0557 * x  -  0.2040 * y  +  1.0570 * z;
    
    r() = rgb_linear_to_standard(r());
    g() = rgb_linear_to_standard(g());
    b() = rgb_linear_to_standard(b());
}
// RGB -> XYZ
XYZ::XYZ(RGB v) {
    // https://en.wikipedia.org/wiki/SRGB#The_reverse_transformation
    
    v.r = rgb_standard_to_linear(v.r);
    v.g = rgb_standard_to_linear(v.g);
    v.b = rgb_standard_to_linear(v.b);
    
    x() = 0.1805 * v.b  +  0.3576 * v.g  +  0.4124 * v.r;
    y() = 0.0722 * v.b  +  0.7152 * v.g  +  0.2126 * v.r;
    z() = 0.9505 * v.b  +  0.1192 * v.g  +  0.0193 * v.r;
}

static double f(double t) {
    if (t > pow(6.0 / 29.0, 3.0))
        return pow(t, 1.0 / 3.0);
    return (1.0 / 3.0) * pow(29.0 / 6.0, 2.0) * t + (4.0 / 29.0);
}
static double finv(double t) {
    if (t > 6.0 / 29.0)
        return pow(t, 3.0);
    return 3.0 * pow(6.0 / 2.0, 2.0) * (t - 4.0/29.0);
}

// XYZ -> LAB
LAB::LAB(XYZ v) {
    // https://en.wikipedia.org/wiki/Lab_color_space#Forward_transformation
    
    lightness() = 116.0 * f(v.y / Yn) - 16.0;
    astar() = 500.0 * (f(v.x / Xn) - f(v.y / Yn));
    bstar() = 200.0 * (f(v.y / Yn) - f(v.z / Zn));
}
// LAB -> XYZ
XYZ::XYZ(LAB v) {
    // https://en.wikipedia.org/wiki/Lab_color_space#Reverse_transformation
    
    y = Yn * finv((1.0 / 116.0) * (v.lightness() + 16.0));
    x = Xn * finv((1.0 / 116.0) * (v.lightness() + 16.0)
            + (1.0 / 500.0) * v.astar());
    z = Zn * finv((1.0 / 116.0) * (v.lightness() + 16.0)
            + (1.0 / 200.0) * v.bstar());
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
