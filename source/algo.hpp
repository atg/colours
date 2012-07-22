#import "representation.hpp"

namespace Colour {

// CIEDE2000
template<T>
double distance(T a, T b);

// Darken or lighten a colour. 0 is black, 1 is white, 0.5 is stay the same.
template<T>
T lighten(T colour, double amount);

// Make light colours dark and dark colours light
template<T>
T flipLightness(T colour);

// Intensify a colour. 0 is gray, 1 is acid trip, 0.5 is stay the same.
template<T>
T intensify(T colour, double amount);

// Find the contrast of several colours on a background
template<T>
double contrast(T background, std::vector<T> foreground);

}