#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>

template <class T>
class Deque{
    private:
    struct Node{
        T value;
        Node *front, *back;
        Node(const T &val): value(val), front(nullptr), back(nullptr) {};
        Node(): front(nullptr), back(nullptr) {};
    };

    Node *frontNode, *backNode;
    int size;

    public:
    Deque(){
        frontNode = new Node();
        backNode = new Node;

        frontNode->front = frontNode;
        frontNode->back = backNode;

        backNode->back = backNode;
        backNode->front = frontNode;

        size = 0;

    }

    ~Deque(){
        clean();
        delete backNode;
        delete frontNode;
    }

    int getSize(){return size;}

    bool isEmpty(){return size == 0;}

    void pushFront(T val){
        Node* newNode = new Node(val);
        Node* oldFirstNode = frontNode->back;

        newNode->back = oldFirstNode;
        oldFirstNode->front = newNode;

        newNode->front = frontNode;
        frontNode->back = newNode;

        size++;
    }

    void pushBack(T val){
        Node* newNode = new Node(val);
        Node* oldLastNode = backNode->front;

        newNode->front = oldLastNode;
        oldLastNode->back = newNode;

        newNode->back = backNode;
        backNode->front = newNode;

        size++;
    }

    void clean(){
        Node* node = frontNode->back;
        while(node!= backNode){
            Node* temp = node;
            node = node->back;
            delete temp;
        }
        // Restore circular structure
        frontNode->back = backNode;
        backNode->front = frontNode;
        size = 0;
    }

    T front(){
        if (isEmpty()) throw std::out_of_range("Queue empty");
        Node* node = frontNode->back;

        return node->value;
    }

    T back(){
        if (isEmpty()) throw std::out_of_range("Queue empty");
        Node* node = backNode->front;

        return node->value;
    }

    T popFront(){
        if (isEmpty()) throw std::out_of_range("Queue empty");

        Node* node = frontNode->back;
        Node* newFrontNode = node->back;
        T val = node->value;

        newFrontNode->front = frontNode;
        frontNode->back = newFrontNode;

        delete node;
        size--;
        return val;
    }

    T popBack(){
        if (isEmpty()) throw std::out_of_range("Queue empty");

        Node *node = backNode->front;
        Node *newLastNode = node->front;
        T val = node->value;

        newLastNode->back = backNode;
        backNode->front = newLastNode;

        delete node;
        size--;
        return val;
    }
};
#endif