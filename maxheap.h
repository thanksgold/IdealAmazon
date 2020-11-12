#include <iostream>
#include <vector>

struct HeapData {
    int priority;
    int key;
    int quantity;
    std::string name;
    int x, y;
};

class Heap {
    private:
        std::vector<HeapData> A;
        void maxHeapify(int i);
    public:
        Heap() { A.push_back({0,0,0,"a",0,0}); };
        void insertNode(HeapData data);
        bool is_empty();
        HeapData extractMax();
        void buildMaxHeap(std::vector<HeapData> B);
};
