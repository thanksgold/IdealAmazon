#!/bin/sh

g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
./final.exe -mx ./testCases/mxNSW100.txt
./final.exe -mx ./testCases/mxVIC500.txt
./final.exe -mx ./testCases/mxWA2500.txt
./final.exe -mx ./testCases/mxNSW5000.txt
./final.exe -mx ./testCases/mxSA10000.txt
./final.exe -mx ./testCases/mxQLD50000.txt