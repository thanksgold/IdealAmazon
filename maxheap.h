#include <iostream>
#include <vector>

using namespace std;

struct HeapData {
    int priority;
    int key;
    int quantity;
    string name;
    int x, y;
};

class Heap {
    private:
        vector<HeapData> A;
        void maxHeapify(int i);
    public:
        Heap() { A.push_back({0,0,0,"a",0,0}); };
        void insertNode(HeapData data);
        bool is_empty();
        HeapData extractMax();
        void buildMaxHeap(vector<HeapData> B);
};
