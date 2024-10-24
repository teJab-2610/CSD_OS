#ifndef HEAP_H
#define HEAP_H

#include <vector>

class MinHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap();

    void insert(int value);
    int extractMin();
    int peekMin() const;
    bool isEmpty() const;
    int size() const;
};

#endif // HEAP_H
