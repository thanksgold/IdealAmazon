#include <fstream>
#include "rbtree.h"
#include "maxheap.h"
#include "tsp.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (std::string("--help").compare(argv[1]) == 0) {
            std::cout << "'$fileName -a rbTest mxTest' to run auto mode\n";
            std::cout << "'$fileName -rb rbTest'       to test red black functionality\n";
            std::cout << "'$fileName -mx mxTest'       to test max heap functionality\n";
            std::cout << "'$fileName -dp dpTest'       to test dynamic programming functionality\n";
        } else if ( std::string("-a").compare(argv[1])  == 0 ||
                    std::string("-rb").compare(argv[1]) == 0 ||
                    std::string("-mx").compare(argv[1]) == 0 ||
                    std::string("-dp").compare(argv[1]) == 0 ) {
            if (argc < 3)
                std::cout << "Input files are missing or run '$fileName --help' to see options\n";
            else {
                // initialize the functionalities and variables
                RBTree rbtree;
                Heap heap;
                TSP tsp;
                int n, key, x, y, quantity;

                if (std::string("-a").compare(argv[1]) == 0) {
                    if (argc < 4)
                        std::cout << "rbTest mxTest files are missing or run '$fileName --help' to see options\n";
                    else {
                        std::cout << "Reading -a: " << argv[2] << ", " << argv[3] << "\n";
                        // Read red black tree input
                        std::ifstream rbData(argv[2]);
                        rbData >> n;
                        V<RBData> rb;
                        for (int i = 0; i < n; i++) {
                            rbData >> key >> x >> y >> quantity;
                            rb.push_back({key, x, y, quantity});
                        }
                        rbData.close();

                        // print
                        for (int i = 0; i < n; i++) {
                            rbtree.RBInsert(rb.at(i));
                        }
                        rb.clear(); // to free up the memory
                        std::cout << "Printing the red black tree nodes\n\n";
                        rbtree.print();
                        
                        // Read heap input
                        std::ifstream heapData(argv[3]);
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

                        // extract elements in order
                        heap.buildMaxHeap(h);
                        h.clear(); // to free up the memory
                        std::cout << "\nPrinting the order results in the descending order \n\n";
                        while (!heap.isEmpty()) {
                            HeapData d = heap.extractMax();

                            int r = rbtree.search(d.key, d.quantity);
                            if (r==0)
                                std::cout << "Yo " + d.name + ", your order is not found. Sorry, IdealAmazon\n";
                            else if (r==2)
                                std::cout << "Yo " + d.name + ", your order is on the way! Cheers, IdealAmazon\n";
                            else
                                std::cout << "Yo " + d.name + ", not enough quantity available for your order :( Apologies, IdealAmazon\n";
                        }
                        std::cout << "\n";

                        std::cout << argv[3] << "\n";


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
                } else if (std::string("-rb").compare(argv[1]) == 0) {
                    std::cout << "Reading -rb: " << argv[2] << "\n";
                    // Read red black tree input
                    std::ifstream rbData(argv[2]);
                    rbData >> n;
                    V<RBData> rb;
                    for (int i = 0; i < n; i++) {
                        rbData >> key >> x >> y >> quantity;
                        rb.push_back({key, x, y, quantity});
                    }
                    rbData.close();

                    // print
                    for (int i = 0; i < n; i++) {
                        rbtree.RBInsert(rb.at(i));
                    }
                    rb.clear(); // to free up the memory
                    std::cout << "Printing the red black tree nodes\n\n";
                    rbtree.print();
                } else if (std::string("-mx").compare(argv[1]) == 0) {
                    std::cout << "Reading -mx: " << argv[2] << "\n";
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

                    // extract elements in order
                    heap.buildMaxHeap(h);
                    h.clear(); // to free up the memory
                    std::cout << "\nPrinting the order results in the descending order \n\n";
                    while (!heap.isEmpty()) {
                        HeapData d = heap.extractMax();

                        int r = rbtree.search(d.key, d.quantity);
                        if (r==0)
                            std::cout << "Yo " + d.name + ", your order is not found. Sorry, IdealAmazon\n";
                        else if (r==2)
                            std::cout << "Yo " + d.name + ", your order is on the way! Cheers, IdealAmazon\n";
                        else
                            std::cout << "Yo " + d.name + ", not enough quantity available for your order :( Apologies, IdealAmazon\n";
                    }
                } else {
                    std::cout << "Reading -dp: " << argv[2] << "\n";

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
            }
        } else
            std::cout << "Please provide correct input or run '$fileName --help' to see options\n";
    } else
        std::cout << "Please define the run mode or run '$fileName --help' to see options\n";
    return 0;
}