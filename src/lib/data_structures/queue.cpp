#include <iostream>
#include <stdexcept>

class Queue {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (empty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    int dequeue() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = front;
        int value = front->data;
        front = front->next;
        delete temp;
        size--;
        if (empty()) {
            rear = nullptr;
        }
        return value;
    }

    int peek() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }

    bool empty() const {
        return size == 0;
    }

    int get_size() const {
        return size;
    }

    void clear() {
        while (!empty()) {
            dequeue();
        }
    }

    void print() const {
        Node* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

