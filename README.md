# colours

Colours is a C++ library for working with **colours** (duh). Mathematically.

## Usage

**colours** contains classes for a variety of different colour models. All colours are represented as:

* Three `doubles` in the range of 0 to 1, for the chromatic information.
* One `double` in the range of 0 to 1, for the alpha information.

Numbers are *always* in the range of 0 to 1. That includes hue angles.

## Functionality

Colours is separated into two parts: conversion and algorithms.

1. Colours supports many popular colour models, such as RGB, HSL, CIE Lab and CIECAM.
2. Colours includes functions such as CIEDE2000 and algorithms for manipulating contrast.

If all that sounds complicated, wait until you see the mathematics!

## License

Colours itself is WTFPL (google it). However, it does include other dependencies which have different licenses (nothing more restrictive than BSD).



