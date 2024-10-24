#include <iostream>

struct Node {
    int data;
    Node* next;
};

class List {
private:
    Node* head;
    int size;

public:
    List() : head(nullptr), size(0) {}

    ~List() {
        clear();
    }

    void push_front(int value) {
        Node* newNode = new Node{value, head};
        head = newNode;
        size++;
    }

    void push_back(int value) {
        Node* newNode = new Node{value, nullptr};
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    void pop_front() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }

    int front() {
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
            return -1;
        }
        return head->data;
    }

    bool empty() const {
        return size == 0;
    }

    int get_size() const {
        return size;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};
