#import <stdlib.h>
#import <stdio.h>
#import "../source/colours.hpp"

int main(int argc, char *argv[]) {
    
    colour::LAB v = colour::LAB(colour::RGB(0.5, 0.0, 1.0));
    printf("%lf %lf %lf", v.x, v.y, v.z);
    
    return 0;
}
