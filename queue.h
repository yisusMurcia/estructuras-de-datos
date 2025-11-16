#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <class t>
class Queue {
    private:
        struct Node {
            t data;
            Node* next;
        };
        Node *head, *tail;
        int size;
    public:
        int getSize(){ return size; }
        Queue(){
            head = new Node();
            tail = new Node();
            head->next = tail;
            head->before = head;
            tail->next = tail;
            tail->before = head;
            size = 0;
        }
        ~Queue() {
            while (!isEmpty()) {
                attend();
            }
            delete head;
            delete tail;
        }
        bool isEmpty() const {
            return size == 0;
        }

        void add(t value) {
            Node* newNode = new Node();
            newNode->data = value;
            newNode->next = tail;
            newNode->before = tail->before;
            tail->before->next = newNode;
            tail->before = newNode;
            size++;
        }

        void attend(){
            if (isEmpty()) {
                throw std::out_of_range("Queue empty");
            }
            Node* toDelete = head->next;
            head->next = toDelete->next;
            toDelete->next->before = head;
            delete toDelete;
            size--;
        }
};
#endif