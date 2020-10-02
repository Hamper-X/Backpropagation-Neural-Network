#!/bin/bash

# if [ "$1" == "-t" ]; then
#     g++ -D test -g -o back.exe \
#         -I utils -I components components/*.cpp utils/*.cpp\
#         back.cpp 
# else
#     g++ -g -o back.exe \
#         -I utils -I components components/*.cpp utils/*.cpp\
#         back.cpp
# fi

case "$1" in
"-t"|"-T") g++ -D test -g -fopenmp -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;

"-p"|"-P") g++ -g -fopenmp -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;

"-o"|"-O") g++ -g -O3 -w -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;

"-tp"|"-TP") g++ -D test -g -fopenmp -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;

"-to"|"-TO") g++ -D test -w -g -O3 -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;

"-po"|"-PO") g++ -g -O3 -w -fopenmp -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;

"-tpo"|"-TPO") \
        g++ -D test -g -O3 -fopenmp -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;

*) g++ -g -o back.exe \
        -I utils -I components components/*.cpp utils/*.cpp\
        back.cpp ;;
esac


