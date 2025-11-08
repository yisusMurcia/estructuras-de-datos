#ifndef LIST_H
#define LIST_H

#include <stdexcept>
using namespace std;

template <typename T>
class List {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value) : data(value), next(NULL) {}
        };
        Node* head;
        Node* tail;
        int size;
        Node *getNodeAtIndex(int index) {
            if (index < 0 || index >= size) throw out_of_range("Index out of range");
            Node* current= head->next;
                for (int i = 0; i < index; ++i)current = current->next;
            return current;
        }
    public:
        List(){
            head = new Node();
            tail= new Node();
            size = 0;
            head->next = tail;
            tail->next = tail;
        }
        ~List() {
            while (head != tail) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            delete tail;
        }

        void pushBack(const T& value) {
            Node* newNode = new Node(value);
            if (isEmpty()) {
                head -> next = newNode;
                tail = newNode;
            } else {
                Node* temp = head;
                while (temp->next != tail) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->next = tail;
            }
            ++size;
        }

        bool popBack() {
            if (isEmpty()) return false;
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete current;
            --size;
            return true;
        }

        int getSize() const {
            return size;
        }

        bool isEmpty() const {
            return size == 0;
        }

        void pushFront(const T& value) {
            Node* newNode = new Node(value);
            newNode->next = head->next;
            head->next = newNode;
            ++size;
        }

        bool popFront() {
            if (isEmpty()) return false;
            Node* temp = head->next;
            head->next = temp->next;
            delete temp;
            --size;
            return true;
        }

        T operator[](int index) {
            if (index < 0 || index >= size) throw out_of_range("Index out of range");
            Node* current = getNodeAtIndex(index);
            return current->data;
        }

        void addAtIndex(int index, const T& value) {
            if (index < 0 || index > size) throw out_of_range("Index out of range");
            Node* newNode = new Node(value);
            Node* current = getNodeAtIndex(index - 1); 
            newNode->next = current->next;
            current->next = newNode;
            ++size;
        }

        bool removeAtIndex(int index) {
            if (index < 0 || index >= size) return false;
            Node* beforeNode = getNodeAtIndex(index - 1);
            Node* nodeToDelete = beforeNode->next;
            beforeNode->next = nodeToDelete->next;
            delete nodeToDelete;
            --size;
            return true;
        }

};
#endif