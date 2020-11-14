#!/bin/sh

g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
./final -dp ./testCases/dpACT5.txt
./final -dp ./testCases/dpSA12.txt
./final -dp ./testCases/dpNSW16.txt
./final -dp ./testCases/dpQLD20.txt