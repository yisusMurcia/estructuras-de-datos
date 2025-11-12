#ifndef ORDERLIST_H
#define ORDERLIST_H

#include <stdexcept>
using namespace std;

template <class T>
class OrderList{
    private:
    struct Node{
        T data;
        Node *next;
        Node(const T& value) : data(value), next(NULL) {}
    };

    Node* head;
    Node* tail;
    int size;

    public:
    OrderList(){
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->next = tail;
        size = 0;
    }
    ~OrderList(){
        Node* current;
        do{
            current = head;
            head = head->next;
            delete current;
        }while (head != tail);
        delete tail;
    }

    void add(T value){
        Node* newNode = new Node(value);
        Node* current = head;
        while(current->next != tail && current->next->data < value ){
            current = current -> next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    int getSize(){return size;}
    bool isEmpty(){return size == 0;}

    bool remove(T value){
        Node* beforeNode = head;
        Node* toDelete;
        while(beforeNode != tail){
            toDelete = beforeNode->next;
            if(toDelete ->data == value){
                beforeNode->next = toDelete->next;
                size--;
                delete toDelete;
                return true;
            }
            beforeNode = beforeNode->next;
        }
        return false;
    }

    T operator[](int index){
        if(index<0 || index >= size) throw out_of_range("Index out of range");
        Node* current = head->next;
        for(int i = 0; i< index; i++)current = current->next;

        return current->data;
    }
};

#endif