#import <stdlib.h>
#import <stdio.h>
#import "../source/colours.hpp"

const double delta = 0.01;
const long N = 47;

template<typename From, typename To>
static void test(const char* FromName, const char* ToName) {
    
    for (long x = 0; x <= N; x++) {
        for (long y = 0; y <= N; y++) {
            for (long z = 0; z <= N; z++) {
                for (long a = 0; a <= 3; a++) {
                    
                    From c1 = From(
                      double(x) / double(N),
                      double(y) / double(N),
                      double(z) / double(N),
                      double(a) / 3.0);
                    
                    To c2 = To(c1);
                    From c3 = From(c2);
                    To c4 = To(c3);
                    
                    if (c1 != c3) {
                        printf("A: %ld - %ld - %ld - %ld  --  Not equal %s -> %s {%.5lf, %.5lf, %.5lf, %.5lf} -> {%.5lf, %.5lf, %.5lf, %.5lf} -> {%.5lf, %.5lf, %.5lf, %.5lf}\n",
                            x, y, z, a,
                            FromName,
                            ToName,
                            c1.x, c1.y, c1.z, c1.a,
                            c2.x, c2.y, c2.z, c2.a,
                            c3.x, c3.y, c3.z, c3.a
                        );
                        return;
                    }
                    
                    if (c2 != c4) {
                        printf("B: %ld - %ld - %ld - %ld  --  Not equal %s -> %s {%.5lf, %.5lf, %.5lf, %.5lf} -> {%.5lf, %.5lf, %.5lf, %.5lf} -> {%.5lf, %.5lf, %.5lf, %.5lf}\n",
                            x, y, z, a,
                            ToName,
                            FromName,
                            c2.x, c2.y, c2.z, c2.a,
                            c3.x, c3.y, c3.z, c3.a,
                            c4.x, c4.y, c4.z, c4.a
                        );
                        return;
                    }
                }
            }
        }
    }
    
    printf("Success %s -> %s\n", FromName, ToName);
}

#define DO_TEST(a, b) test<colour::a, colour::b>(#a, #b)

int main(int argc, char *argv[]) {
    
    colour::LAB v = colour::LAB(colour::RGB(0.5, 0.0, 1.0));
    printf("%lf %lf %lf\n", v.x, v.y, v.z);
    
    DO_TEST(RGB, HSL);
    DO_TEST(RGB, HSB);
    DO_TEST(RGB, XYZ);
    DO_TEST(RGB, LAB);
    DO_TEST(RGB, LCH);
    DO_TEST(RGB, CIECAM);
    DO_TEST(HSL, RGB);
    DO_TEST(HSL, HSB);
    DO_TEST(HSL, XYZ);
    DO_TEST(HSL, LAB);
    DO_TEST(HSL, LCH);
    DO_TEST(HSL, CIECAM);
    DO_TEST(HSB, RGB);
    DO_TEST(HSB, HSL);
    DO_TEST(HSB, XYZ);
    DO_TEST(HSB, LAB);
    DO_TEST(HSB, LCH);
    DO_TEST(HSB, CIECAM);
    DO_TEST(XYZ, RGB);
    DO_TEST(XYZ, HSL);
    DO_TEST(XYZ, HSB);
    DO_TEST(XYZ, LAB);
    DO_TEST(XYZ, LCH);
    DO_TEST(XYZ, CIECAM);
    DO_TEST(LAB, RGB);
    DO_TEST(LAB, HSL);
    DO_TEST(LAB, HSB);
    DO_TEST(LAB, XYZ);
    DO_TEST(LAB, LCH);
    DO_TEST(LAB, CIECAM);
    DO_TEST(LCH, RGB);
    DO_TEST(LCH, HSL);
    DO_TEST(LCH, HSB);
    DO_TEST(LCH, XYZ);
    DO_TEST(LCH, LAB);
    DO_TEST(LCH, CIECAM);
    DO_TEST(CIECAM, RGB);
    DO_TEST(CIECAM, HSL);
    DO_TEST(CIECAM, HSB);
    DO_TEST(CIECAM, XYZ);
    DO_TEST(CIECAM, LAB);
    DO_TEST(CIECAM, LCH);
    
    return 0;
}
