#!/bin/sh

g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
./final.exe -dp ./testCases/dpACT5.txt
./final.exe -dp ./testCases/dpSA12.txt
./final.exe -dp ./testCases/dpNSW16.txt
./final.exe -dp ./testCases/dpQLD20.txt