#!/bin/bash

mkdir -p build
clang++ -o build/colours -Ideps test/main.cpp source/*.cpp deps/*.c
