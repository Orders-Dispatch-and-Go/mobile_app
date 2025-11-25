#!/bin/zsh
clear && cmake -S . -B build/test -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TESTING=ON && cmake --build build/test --parallel 4 && ./build/test/appuntitled
