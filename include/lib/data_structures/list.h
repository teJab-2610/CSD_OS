#ifndef LIST_H
#define LIST_H

struct Node {
    int data;
    Node* next;
};

class List {
private:
    Node* head;
    int size;

public:
    List();
    ~List();

    void push_front(int value);
    void push_back(int value);
    void pop_front();
    int front();
    bool empty() const;
    int get_size() const;
    void clear();
    void print() const;
};

#endif // LIST_H
