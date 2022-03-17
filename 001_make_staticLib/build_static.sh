#!/bin/sh
POUT=../002_make_executableFile/src/
#PATH NEED TO MODIFY

$POUT
gcc -c -o obj/get_image.o src/get_image.c
gcc -c -o obj/myFuncts.o src/myFuncts.cpp
gcc -c -o obj/readIni.o src/readIni.cpp
ar -rcs libimage.a obj/get_image.o obj/myFuncts.o obj/readIni.o
cp libimage.a src/get_image.h src/myFuncts.h $POUT
cd ../002_make_executableFile/
