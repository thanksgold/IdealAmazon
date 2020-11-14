#!/bin/sh

g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
./final -a ./testCases/rb5000.txt ./testCases/mxACT100000.txt
