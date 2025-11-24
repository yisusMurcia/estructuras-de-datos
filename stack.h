#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <class T>
class Stack{
private:
    struct Node{ T data; Node *next; };
    Node *head;
    int size;
public:
    Stack () : head(nullptr), size(0) {}
    ~Stack(){
        while(head){ Node *tmp = head; head = head->next; delete tmp; }
    }

    void push(const T &v){ Node *tmp = new Node{v, head}; head = tmp; size++; }

    T peek() const{
        if(!head) throw std::out_of_range("Stack is empty");
        return head->data;
    }

    T pop(){
        if(!head) throw std::out_of_range("Stack is empty");
        Node *tmp = head;
        T val = tmp->data;
        head = head->next;
        delete tmp;
        size--;
        return val;
    }

    void emptyStack(){ while(!isEmpty()) pop(); }

    bool isEmpty() const { return size == 0; }

    int getSize() const { return size; }
};

#endif