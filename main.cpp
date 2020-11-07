#include <iostream>
#include <fstream>
#include <vector>
#include "rbtree.h"
#include "maxheap.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Please supply the input files for max heap and red black tree\n";
    } 
    else {
		// Read red black tree input
        int n, key, x, y, quantity;
		ifstream rbData(argv[1]);
		rbData >> n;
        vector<RBData> rb;
		for (int i = 0; i < n; i++) {
			rbData >> key >> x >> y >> quantity;
            rb.push_back({key, x, y, quantity});
		}
        rbData.close();

        // initialize rbtree and print
        RBTree rbtree;
        for (int i = 0; i < n; i++) {
            rbtree.RBInsert(rb.at(i));
        }
        rb.clear(); // to free up the memory
        cout << "Printing the red black tree nodes\n\n";
        rbtree.print();
        
        // Read heap input
		ifstream heapData(argv[2]);
		int priority;
        string name;
		heapData >> n;
        vector<HeapData> h;
		for (int i = 0; i < n; i++) {
			heapData >> priority >> key >> quantity >> name >> x >> y;
			// Store requests (heap tree)           
            h.push_back({priority, key, quantity, name, x, y});
		}
        heapData.close();

        // initialize heap and extract elements in order
        Heap heap;
        heap.buildMaxHeap(h);
        h.clear(); // to free up the memory
        cout << "\nPrinting the order results in the descending order \n\n";
        while (!heap.is_empty()) {
            HeapData d = heap.extractMax();
            cout << rbtree.search(d.key, d.quantity, d.name);
        }
        cout << "\n";
    }
    return 0;
}