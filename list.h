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
    public:
        List(){
            head<T> = new Node();
            tail<T> = new Node();
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
            if (head->next == tail) {
                head -> next = newNode;
                tail = newNode;
            } else {
                Node<T>* temp = head;
                while (temp->next != tail) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->next = tail;
            }
            ++size;
        }

        bool popBack() {
            if (head->next= tail) return false;
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
            if (head->next == tail) return false;
            Node* temp = head->next;
            head->next = temp->next;
            delete temp;
            --size;
            return true;
        }

        T operator[](int index) {
            if (index < 0 || index >= size) throw out_of_range("Index out of range");
            Node* current = head->next;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->data;
        }

        void addAtIndex(int index, const T& value) {
            if (index < 0 || index > size) throw out_of_range("Index out of range");
            Node* newNode = new Node(value);
            Node* current = List[index - 1];
            newNode->next = current->next;
            current->next = newNode;
            ++size;
        }

        bool removeAtIndex(int index) {
            if (index < 0 || index >= size) return false;
            Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            --size;
            return true;
        }

};
#endif