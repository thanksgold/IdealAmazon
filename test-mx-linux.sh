#!/bin/sh

g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
./final -mx ./testCases/mxNSW100.txt
./final -mx ./testCases/mxVIC500.txt
./final -mx ./testCases/mxWA2500.txt
./final -mx ./testCases/mxNSW5000.txt
./final -mx ./testCases/mxSA10000.txt
./final -mx ./testCases/mxQLD50000.txt