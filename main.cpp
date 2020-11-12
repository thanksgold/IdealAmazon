#include <fstream>
#include "rbtree.h"
#include "maxheap.h"
#include "tsp.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Please supply the input files for max heap and red black tree\n";
    } 
    else {
		// Read red black tree input
        int n, key, x, y, quantity;
		std::ifstream rbData(argv[1]);
		rbData >> n;
        V<RBData> rb;
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
        std::cout << "Printing the red black tree nodes\n\n";
        rbtree.print();
        
        // Read heap input
		std::ifstream heapData(argv[2]);
		int priority;
        std::string name;
		heapData >> n;
        V<HeapData> h;
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
        std::cout << "\nPrinting the order results in the descending order \n\n";
        while (!heap.is_empty()) {
            HeapData d = heap.extractMax();
            std::cout << rbtree.search(d.key, d.quantity, d.name);
        }
        std::cout << "\n";

        TSP tsp;

        V<Point> points = { Point(-35.282001, 149.128998, "Canberra"),
                            Point(-33.865143, 151.209900, "Sydney"),
                            Point(-37.840935, 144.946457, "Melbourne"),
                            Point(-27.470125, 153.021072, "Brisbane"),
                            Point(-31.953512, 115.857048, "Perth"),
                            Point(-34.921230, 138.599503, "Adelaide"),
                            Point(-42.880554, 147.324997, "Hobart"),
                            Point(-12.462827, 130.841782, "Darwin"),
                        };

        ReturnPath r = tsp.solveTSP(points);

        // Create an output filestream object
        std::ofstream output("output.csv");    
        // Send data to the stream
        output << "Latitude,Longitude,Name\n";
        for (int i = 0; i < r.path.size(); ++i) {
            output << points[r.path[i]].lat << "," << points[r.path[i]].lon 
                << "," << points[r.path[i]].name << "\n";
        }
        // Close the file
        output.close();
    }
    return 0;
}