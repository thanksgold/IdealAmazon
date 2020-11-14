# COMP3600/6466 Algorithms
## Final Project - IdealAmazon

The software that is being developed for the Final Project of this  course is an inventory management system, e.g. Amazon. It contains a number of data structures that are separated into specification and implementation parts. The code is developed in C++ for both Windows and Linux operating systems.

## Getting Started

This readme file contains instructions on running the project on your local machine.

The prerequisites for this software are the following:

```
1. g++
2. c++11
3. jupyter notebook
4. geojson
5. geojsonio
6. json
```

The project can be compiled by using the following command:

```
$ g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o fileName
```
where **fileName** is the name of application file that will be used to run test cases. Example:

```
$ g++ -std=c++11 main.cpp rbtree.cpp maxheap.cpp tsp.cpp -o final
```

## Running the software and testing functionalities

A number of test cases were provided in **testCases** folder under the **root** directory. These test cases can be run using the shell scripts provided or compiled severately through the terminal. The corretness of the functionalities can be tested by viewing the outputs printed on the terminal or the output file except the dynamic programming functionality that requires visualization by running `VisualizationCode.ipynb` file. Please note that a few test cases are very big and might require the print operation to be commented out so that the terminal is not overloaded with text.

There are two ways for rinning this software:

1. Run the program through terminal

```
$ .\fileName.exe -a .\testCases\fileRB.txt .\testCases\fileHeap.txt
```
where **fileName** is the name of application file specified in the previous section, **fileRB** is the Red Black Tree data structure test file, and **fileHeap** is the Max Heap data structure test file. Example:

```
$ .\final.exe .\testCases\rb5000.txt .\testCases\mxACT100000.txt
```

2. Run the program by using the shell scripts provided

```
$ .\test-compile-win.sh
or
$ .\test-compile-linux.sh
depending on the operating system.
```

There are two similar ways for testing each functionality:

1. Run the program through terminal

```
$ .\fileName.exe -functionality .\testCases\file.txt
or 
$ .\fileName -functionality .\testCases\file.txt
```

where **fileName** is the name of application file specified while compilation of the software, **functionality** is the functionality that is being tested, and **file** is the test file that the data structure is tested on. The options for the **functionality** are `-a` for the entire programming as specified at the section above, `-rb` to test red black functionality, `-mx` to test max heap functionality, and `-dp` to test dynamic programming functionality. Example:


```
$ .\final.exe -dp .\testCases\dpACT5.txt
or
$ .\final -dp .\testCases\dpACT5.txt
```

2. Run the program by using the shell scripts provided

```
$ .\test-fuctionality-win.sh
or
$ .\test-fuctionality-linux.sh
```

where **fuctionality** is the same as defined above. Example:

```
$ .\test-dp-win.sh
```

## Author

* **Rakhmatilla Bakhodirov** - *u6457384*

## Acknowledgments

* [Helped to created markdown file](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
* [Used pseudo-code from CLRS textbook](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf)
* [Looked at RBTree implementation for debugging purposes](https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp)
* [Looked at MaxHeap implementation for debugging purposes](https://gist.github.com/aleksmitov/8d8577d4aa64ba3d7965)
* [Looked at tsp implementation for debugging purposes](https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/)
* [CLRS textbook referenced in the analysis](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf)
