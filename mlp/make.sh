#!/bin/bash

if [ "$1" == "-t" ]; then
    g++ -D test -g -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp
else
    g++ -g -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp
fi