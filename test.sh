#!/bin/zsh

clear
cmake -S . -B build \
    -DBUILD_TESTING=OFF \
    -DEXPORT_COMPILE_COMMANDS=ON
cmake --build build --parallel 6
./build/appuntitled
