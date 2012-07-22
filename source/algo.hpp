#import "representation.hpp"
#import <vector>
#import <algorithm>

namespace colour {

// CIEDE2000
template<typename T>
double distance(T a, T b) {
    // ...
}

// Darken or lighten a colour. 0 is black, 1 is white, 0.5 is stay the same.
template<typename T>
T lighten(T colour, double amount) {
    // ...
}

// Make light colours dark and dark colours light
template<typename T>
T flipLightness(T colour) {
    return T(colour.x, colour.y, 1.0 - colour.lightness());
}

// Intensify a colour. 0 is gray, 1 is acid trip, 0.5 is stay the same.
template<typename T>
T intensify(T colour, double amount) {
    // ...
}

// Find the contrast of several colours on a background
template<typename T>
double contrast(T background, std::vector<T> foregrounds) {
    
    double bglightness = background.lightness();
    std::vector<T> lightnesses;
    for (T& v : foregrounds) {
        lightnesses.push_back(v.lightness());
    }
    
    // Sort ascending so that we're numerically stable
    std::sort(lightnesses.begin(), lightnesses.end());
    
    double sum = 0.0;
    for (double& l : lightnesses) {
        sum += (l - bglightness) * (l - bglightness);
    }
    
    return sum / foregrounds.size();
}

}