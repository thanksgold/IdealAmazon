#!/bin/sh

g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
./final -a ./testCases/rbSimple.txt ./testCases/heapSimple.txt
