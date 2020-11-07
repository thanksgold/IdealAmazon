# COMP3600/6466 Algorithms
## Final Project - IdealAmazon

The software that is being developed for the Final Project of this  course is an inventory management system, e.g. Amazon. It contains a number of data structures that are separated into specification and implementation parts. The code is developed in C++ for both Windows and Linux operating systems.

## Getting Started

This readme file contains instructions on running the project on your local machine.

The prerequisites for this software are the following:

```
1. g++
2. c++11
```

The project can be compiled by using the following command:

```
$ g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp -o fileName
```
where **fileName** is the name of application file that will be used to run test cases. Example:

```
$ g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp -o final
```

## Running the tests

A simple test case was provided with its expected output in **testCases** folder in the **root** directory. This test case includes two input files named **rbSimple.txt** and **heapSimple.txt**. The output should look like as in **outputExpectedSimple.txt** file. Please note that the functionalities are partially implemented and, therefore, the output might change in further revisions.

There are two ways for running test cases:

1. Run the program and print the ouput to the terminal

```
$ .\fileName.exe .\testCases\fileRB.txt .\testCases\fileHeap.txt
```
where **fileName** is the name of application file specified in the previous section, **fileRB** is the Red Black Tree data structure test file, and **fileHeap** is the Max Heap data structure test file. Example:

```
$ .\final.exe .\testCases\rbSimple.txt .\testCases\heapSimple.txt
```

2. Run the program and print the ouput to a file

```
$ .\final.exe .\testCases\fileRB.txt .\testCases\fileHeap.txt > .\testCases\outputFile.txt
```

where **fileName**, **fileRB**, and **fileHeap** are the same files as specificed in the first instuction, while **outputFile** is the output file name. Example:

```
$ .\final.exe .\testCases\rbSimple.txt .\testCases\heapSimple.txt > .\testCases\output.txt
```

## Author

* **Rakhmatilla Bakhodirov** - *u6457384*

## Acknowledgments

* [Helped to created markdown file](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
* [Used pseudo-code from CLRS textbook](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf)
* [Looked at RBTree implementation for debugging purposes](https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp)
* [Looked at MaxHeap implementation for debugging purposes](https://gist.github.com/aleksmitov/8d8577d4aa64ba3d7965)