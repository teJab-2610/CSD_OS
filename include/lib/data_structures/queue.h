#ifndef QUEUE_H
#define QUEUE_H

struct Node {
    int data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    Queue();
    ~Queue();

    void enqueue(int value);
    int dequeue();
    int peek();
    bool empty() const;
    int get_size() const;
    void clear();
    void print() const;
};

#endif // QUEUE_H
