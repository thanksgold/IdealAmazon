#include <fstream>
#include <chrono>
#include "rbtree.h"
#include "maxheap.h"
#include "tsp.h"

int main(int argc, char *argv[]) {
    // argument checks done first
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
                // if compiling the whole program
                if (std::string("-a").compare(argv[1]) == 0) {
                    if (argc < 4)
                        std::cout << "rbTest mxTest files are missing or run '$fileName --help' to see options\n";
                    else {
                        std::cout << "Reading -a: " << argv[2] << ", " << argv[3] << "\n";

                        // initialize all variables
                        RBTree rbtree;
                        Heap heap;
                        TSP tsp;
                        int n, priority, key, quantity, index;
                        float x, y;
                        std::string name;
                        V<RBData> rb;
                        V<Point> suburbs;
                        V<HeapData> mx;

                        // Read red black tree input
                        std::ifstream rbData(argv[2]);
                        rbData >> n >> x >> y >> name;
                        Point warehouse = Point(x, y, name);
                        for (int i = 0; i < n; i++) {
                            rbData >> key >> quantity;
                            rb.push_back({key, quantity});
                        }
                        rbData.close();
                        // insert all elements into the data structure
                        for (int i = 0; i < n; i++)
                            rbtree.RBInsert(rb.at(i));
                        rb.clear(); // to free up the memory

                        // Read heap input
                        std::ifstream heapData(argv[3]);
                        // reading suburbs first
                        heapData >> n;
                        for (int i = 0; i < n; i++) {
                            heapData >> x >> y >> name;
                            suburbs.push_back({x, y, name});
                        }
                        // reading orders next
                        heapData >> n;
                        for (int i = 0; i < n; i++) {
                            heapData >> priority >> key >> quantity >> name >> x >> y >> index;
                            mx.push_back({priority, key, quantity, name, x, y, index});
                        }
                        heapData.close();
                        // build max heap from the list of orders
                        heap.buildMaxHeap(mx);
                        mx.clear(); // to free up the memory
                        // extract elements in priority order and push through
                        // to dynamic programming if successfully processed
                        V<V<Point>> s_orders = V<V<Point>>(suburbs.size());
                        while (!heap.isEmpty()) {
                            HeapData d = heap.extractMax();
                            int r = rbtree.search(d.key, d.quantity);
                            if (r==2) { // successful
                                s_orders[d.index].push_back({d.x, d.y, d.name});
                                std::cout << "Yo " + d.name + ", your order is on the way! Cheers, IdealAmazon\n";
                            }
                        }

                        // solve tsp and output csv files for visualization
                        suburbs.push_back(warehouse);
                        ReturnPath r = tsp.solveTSP(suburbs);
                        // Create an output filestream object
                        // std::string st = std::string(argv[2]).substr(12);
                        // std::ofstream output("testVisualization/"  + st.substr(0, st.find(".")) + ".csv");    
                        std::ofstream output("testVisualization/suburbs.csv");   
                        // Send data to the stream
                        output << "Latitude,Longitude,Name\n";
                        for (int i = 0; i < r.path.size(); ++i) {
                            output << suburbs[r.path[i]].lat << "," << suburbs[r.path[i]].lon 
                                << "," << suburbs[r.path[i]].name << "\n";
                        }
                        // Close the file
                        output.close();
                        // do the same for the orders from these suburbs
                        for (int i = 0; i < s_orders.size(); ++i) {
                            V<Point> tmp = s_orders[i];
                            r = tsp.solveTSP(tmp);
                            // Create an output filestream object
                            std::ofstream output("testVisualization/" + std::to_string(i) + ".csv");    
                            // Send data to the stream
                            output << "Latitude,Longitude,Name\n";
                            for (int i = 0; i < r.path.size(); ++i) {
                                output << tmp[r.path[i]].lat << "," << tmp[r.path[i]].lon 
                                    << "," << tmp[r.path[i]].name << "\n";
                            }
                            // Close the file
                            output.close();
                        }
                        std::cout << "Finished execution!\n\n";
                    }
                // if compiling red black tree functionality
                } else if (std::string("-rb").compare(argv[1]) == 0) {
                    std::cout << "Reading -rb: " << argv[2] << "\n";

                    // initialize variables
                    RBTree rbtree;
                    int n, key, quantity;
                    float lat, lon;
                    std::string name;
                    V<RBData> rb;

                    // Read red black tree input
                    std::ifstream data(argv[2]);
                    data >> n >> lat >> lon >> name;
                    for (int i = 0; i < n; i++) {
                        data >> key >> quantity;
                        rb.push_back({key, quantity});
                    }
                    data.close();

                    // insert all elements into the data structure
                    for (int i = 0; i < n; i++)
                        rbtree.RBInsert(rb.at(i));
                    rb.clear(); // to free up the memory

                    // print out to check correctness
                    std::cout << "Printing the red black tree nodes...\n";
                    rbtree.print();

                    // tell that the execution is finished
                    std::cout << "Finished execution!\n\n";
                // if compiling max heap functionality
                } else if (std::string("-mx").compare(argv[1]) == 0) {
                    std::cout << "Reading -mx: " << argv[2] << "\n";

                    // initialize variables
                    Heap heap;
                    float x, y;
                    std::string name;
                    int n, priority, key, quantity, index;
                    V<Point> suburbs;
                    V<HeapData> list;

                    // Read max heap input
                    std::ifstream data(argv[2]);
                    data >> n;
                    // reading suburbs first
                    for (int i = 0; i < n; i++) {
                        data >> x >> y >> name;
                        suburbs.push_back({x, y, name});
                    }
                    data >> n;
                    // reading orders next
                    for (int i = 0; i < n; i++) {
                        data >> priority >> key >> quantity >> name >> x >> y >> index;
                        list.push_back({priority, key, quantity, name, x, y, index});
                    }
                    data.close();

                    // build max heap from the list of orders
                    heap.buildMaxHeap(list);
                    list.clear(); // to free up the memory

                    // extract elements in order
                    std::cout << "Printing the order priorities in the descending order...\n";
                    while (!heap.isEmpty()) {
                        HeapData d = heap.extractMax();
                        std::cout << d.priority << " ";
                    }
                    std::cout << "\nFinished execution!\n\n";
                // if compiling dynamic programming functionality
                } else {
                    std::cout << "Reading -dp: " << argv[2] << "\n";

                    // initialize variables
                    TSP tsp;
                    float x, y;
                    std::string name;
                    int n;
                    V<Point> list;

                    // Read tsp input
                    std::ifstream data(argv[2]);
                    data >> n;
                    for (int i = 0; i < n; i++) {
                        data >> x >> y >> name;
                        list.push_back({x, y, name});
                    }
                    data.close();

                    // initialize and solve tsp
                    ReturnPath r = tsp.solveTSP(list);
                    tsp.print(r);

                    // Create an output filestream object
                    std::string st = std::string(argv[2]).substr(12);
                    std::ofstream output("testVisualization/"  + st.substr(0, st.find(".")) + ".csv");    
                    // Send data to the stream
                    output << "Latitude,Longitude,Name\n";
                    for (int i = 0; i < r.path.size(); ++i) {
                        output << list[r.path[i]].lat << "," << list[r.path[i]].lon 
                            << "," << list[r.path[i]].name << "\n";
                    }
                    // Close the file
                    output.close();

                    std::cout << "Finished execution!\n\n";
                }
            }
        } else
            std::cout << "Please provide correct input or run '$fileName --help' to see options\n";
    } else
        std::cout << "Please define the run mode or run '$fileName --help' to see options\n";
    return 0;
}