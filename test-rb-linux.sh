#!/bin/sh

g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
./final -rb ./testCases/rb5.txt
./final -rb ./testCases/rb10.txt
./final -rb ./testCases/rb50.txt