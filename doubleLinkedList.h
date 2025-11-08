#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdexcept>
using namespace std;

template <typename T>
class List {
    private:
        struct Node {
            T data;
            Node *next, *before;
            Node(const T& value) : data(value), next(NULL), before(NULL) {}
        };
        Node* head;
        Node* tail;
        int size;
        Node getNodeAtIndex(int index) {
            if (index < 0 || index >= size) throw out_of_range("Index out of range");
            Node* current;
            if(index < size / 2) {
                current = head->next;
                for (int i = 0; i < index; ++i)current = current->next;
            } else {
                current = tail->before;
                for (int i = size - 1; i > index; --i)current = current->before;
            }
            return current;
        }
    public:
        List(){
            head= new Node();
            tail= new Node();
            size = 0;
            head->next = tail;
            head->before = head;
            tail->before = head;
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
                newNode->next = tail;
                tail->before->next = newNode;
                newNode->before = tail->before;
                tail->before = newNode;
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
            newNode->next->before = newNode;
            newNode->before = head;
            head->next = newNode;
            ++size;
        }

        bool popFront() {
            if (isEmpty()) return false;
            Node* temp = head->next;
            head->next = temp->next;
            head->next->before = head;
            delete temp;
            --size;
            return true;
        }

        T operator[](int index) {
            Node* current = getNodeAtIndex(index);
            return current->data;
        }

        void addAtIndex(int index, const T& value) {
            if (index < 0 || index > size) throw out_of_range("Index out of range");
            Node* newNode = new Node(value);
            Node* beforeNode = getNodeAtIndex(index - 1);
            newNode->next = beforeNode->next;
            newNode->before = beforeNode;
            beforeNode->next->before = newNode;
            beforeNode->next = newNode;
            ++size;
        }

        bool removeAtIndex(int index) {
            if (index < 0 || index >= size) return false;
            Node* nodeTodelete = getNodeAtIndex(index - 1);
            nodeTodelete->before->next = nodeTodelete->next;
            nodeTodelete->next->before = nodeTodelete->before;
            delete nodeTodelete;
            --size;
            return true;
        }

};
#endif