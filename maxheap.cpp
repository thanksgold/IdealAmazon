#include "maxheap.h"

void Heap::maxHeapify(int i) {
    int size = A.size()-1;
    int largest = i;
    int l = i << 1;
    int r = (i << 1) + 1;
    if (l <= size && A.at(l).priority > A.at(largest).priority)
        largest = l;
    if (r <= size && A.at(r).priority > A.at(largest).priority)
        largest = r;
    if (largest != i) {
        std::swap(A.at(i), A.at(largest));
        maxHeapify(largest);
    }
}

void Heap::insertNode(HeapData data) {
    int i = A.size();
    A.push_back(data);
    int p = i >> 1;
    while (i > 1 && A.at(p).priority < A.at(i).priority) {
        p = i >> 1;
        std::swap(A.at(i), A.at(p));
        i = p;
    }
}

bool Heap::is_empty() {
    return A.size() <= 1;
}

HeapData Heap::extractMax() {
    int size = A.size()-1;
    if (size == 0)
        throw std::invalid_argument("heap underflow");
    HeapData max = A.at(1);
    std::swap(A.at(1), A.at(size));
    A.pop_back();
    maxHeapify(1);
    return max;
}

void Heap::buildMaxHeap(std::vector<HeapData> B) {
    A.insert(A.end(), B.begin(), B.end());
    for (int i = i >> 1; i > 0; i--)
        maxHeapify(i);
}