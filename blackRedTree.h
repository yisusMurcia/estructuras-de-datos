#ifndef BLACKREDTREE_H
#define BLACKREDTREE_H

#include <stdexcept>
#include <iostream>
#include "stack.h"

using namespace std;

template <class T>
class BlackRedTree{
    private:
    struct Node{
        T data;
        int rightChild, leftChild;
        bool isRed;
        Node (const T &value): data(value), rightChild(0), leftChild(0),  isRed(true){}
        Node (): data(), rightChild(0), leftChild(0),  isRed(true){}
    };

    Node** arr;
    int size;
    Node *head;
    Stack<int> fathersStack;

    void leftRotation(int xIndex, int parentIndex) {
        Node* x = arr[xIndex];
        int yIndex = x->rightChild;

        Node* y = arr[yIndex];

        // B = hijo izquierdo de Y
        int B = y->leftChild;

        // 1. X adopta a B como hijo derecho
        x->rightChild = B;

        if (xIndex == head->leftChild) {
            head->leftChild = yIndex;
        } else {
            int realFatherIndex = parentIndex;
            if (realFatherIndex == 0) {
                // nothing
            } else if (arr[realFatherIndex]->leftChild == xIndex)
                arr[realFatherIndex]->leftChild = yIndex;
            else
                arr[realFatherIndex]->rightChild = yIndex;
        }

        y->leftChild = xIndex;
    }

    void rightRotation(int xIndex, int parentIndex) {
        Node* x = arr[xIndex];
        int yIndex = x->leftChild;

        Node* y = arr[yIndex];

        // B = hijo izquierdo de Y
        int B = y->rightChild;

        // 1. X adopta a B como hijo izquierdo
        x->leftChild = B;

        if (xIndex == head->leftChild) {
            head->leftChild = yIndex;
        } else {
            int realFatherIndex = parentIndex;
            if (realFatherIndex == 0) {
                // nothing
            } else if (arr[realFatherIndex]->leftChild == xIndex)
                arr[realFatherIndex]->leftChild = yIndex;
            else
                arr[realFatherIndex]->rightChild = yIndex;
        }

        y->rightChild = xIndex;
    }


    public:
    BlackRedTree(int size = 50){
        this->size = size;
        arr = new Node*[size + 1]; // 0 is control
        for(int i = 0; i <= size; i++){
            arr[i] = new Node();
        }
        // build free-list in rightChild: 0 -> 1 -> 2 -> ... -> size -> 0
        for(int i = 0; i < size; i++) arr[i]->rightChild = i+1;
        arr[size]->rightChild = 0;
        head = arr[0];
        head->leftChild = 0; // root is empty
        head->isRed = false; // control/nil is black
    }
    ~BlackRedTree(){
        for(int i = 0; i<= size; i++) delete arr[i];
        delete [] arr;
    }

    void add(T value){
        fathersStack.emptyStack();

        int childIndex = head->rightChild;
        if(childIndex == 0) throw out_of_range("The tree is full");

        Node* newNode = arr[childIndex];
        head->rightChild = newNode->rightChild;

        newNode->data = value;
        newNode->leftChild = 0;
        newNode->rightChild = 0;

        if(head->leftChild == 0){ // No root
            head->leftChild = childIndex;
            newNode->isRed = false; // root is black
            return;
        } else {
            int cur = head->leftChild;
            int parent = 0;
            while(cur != 0){
                parent = cur;
                fathersStack.push(parent);
                cur = (value > arr[cur]->data) ? arr[cur]->rightChild : arr[cur]->leftChild;
            }

            // attach
            if(arr[parent]->data < value)
                arr[parent]->rightChild = childIndex;
            else
                arr[parent]->leftChild = childIndex;

            // basic balancing omitted here (kept minimal); ensure root is black
            arr[head->leftChild]->isRed = false;
        }

    }

    int getPosition(T value){//Llena la pila de padres
        fathersStack.emptyStack();
        int currentIndex = head->leftChild;
        while(currentIndex != 0){
            Node* currentNode = arr[currentIndex];
            if(currentNode->data == value)
                return currentIndex;
            // push parent before going down so top of stack is parent of next node
            fathersStack.push(currentIndex);
            if(currentNode->data < value)
                currentIndex = currentNode->rightChild;
            else
                currentIndex = currentNode->leftChild;
        }
        return 0; //No encontrado
    }

    bool remove(T value){
        int index = getPosition(value);
        if(index == 0) return false;

        // parent of node to delete (0 if root)
        int fatherIndex = fathersStack.isEmpty() ? 0 : fathersStack.pop();
        Node* toDelete = arr[index];

        // If node has two children, find successor, copy its data/color and delete successor instead
        if(toDelete->leftChild != 0 && toDelete->rightChild != 0){
            int succParent = index;
            int succ = toDelete->rightChild;
            while(arr[succ]->leftChild != 0){
                succParent = succ;
                succ = arr[succ]->leftChild;
            }
            // copy
            arr[index]->data = arr[succ]->data;
            arr[index]->isRed = arr[succ]->isRed;
            // now delete successor node
            index = succ;
            fatherIndex = succParent;
            toDelete = arr[index];
        }

        // child that will replace toDelete (may be 0)
        int childNode = (toDelete->leftChild == 0) ? toDelete->rightChild : toDelete->leftChild;

        // update parent's pointer
        if(fatherIndex == 0){
            head->leftChild = childNode;
        } else {
            if(arr[fatherIndex]->leftChild == index)
                arr[fatherIndex]->leftChild = childNode;
            else
                arr[fatherIndex]->rightChild = childNode;
        }

        // take node into free-list
        toDelete->leftChild = 0;
        toDelete->rightChild = head->rightChild;
        head->rightChild = index;

        // rebalance if we removed a black node
        if(!toDelete->isRed){
            int x = childNode;
            int parent = fatherIndex;

            while(x != head->leftChild && !(x != 0 && arr[x]->isRed)){
                if(parent == 0){ x = head->leftChild; continue; }
                int w;
                if(x == arr[parent]->leftChild){
                    w = arr[parent]->rightChild;
                    if(w != 0 && arr[w]->isRed){
                        arr[w]->isRed = false;
                        arr[parent]->isRed = true;
                        int parentParent = fathersStack.isEmpty() ? 0 : fathersStack.pop();
                        leftRotation(parent, parentParent);
                        w = arr[parent]->rightChild;
                    }
                    if((w == 0 || !(arr[w]->leftChild != 0 && arr[arr[w]->leftChild]->isRed)) && (w == 0 || !(arr[w]->rightChild != 0 && arr[arr[w]->rightChild]->isRed))){
                        if(w != 0) arr[w]->isRed = true;
                        x = parent;
                        parent = fathersStack.isEmpty() ? 0 : fathersStack.pop();
                        continue;
                    } else {
                        if(w == 0){ x = head->leftChild; continue; }
                        if(!(arr[w]->rightChild != 0 && arr[arr[w]->rightChild]->isRed)){
                            if(arr[w]->leftChild != 0) arr[arr[w]->leftChild]->isRed = false;
                            arr[w]->isRed = true;
                            int parentOfW = parent; // parent of w is parent
                            rightRotation(w, parentOfW);
                            w = arr[parent]->rightChild;
                        }
                        if(w != 0) arr[w]->isRed = arr[parent]->isRed;
                        arr[parent]->isRed = false;
                        if(arr[w]->rightChild != 0) arr[arr[w]->rightChild]->isRed = false;
                        int parentParent = fathersStack.isEmpty() ? 0 : fathersStack.pop();
                        leftRotation(parent, parentParent);
                        x = head->leftChild;
                        continue;
                    }
                } else {
                    // symmetric
                    w = arr[parent]->leftChild;
                    if(w != 0 && arr[w]->isRed){
                        arr[w]->isRed = false;
                        arr[parent]->isRed = true;
                        int parentParent = fathersStack.isEmpty() ? 0 : fathersStack.pop();
                        rightRotation(parent, parentParent);
                        w = arr[parent]->leftChild;
                    }
                    if((w == 0 || !(arr[w]->leftChild != 0 && arr[arr[w]->leftChild]->isRed)) && (w == 0 || !(arr[w]->rightChild != 0 && arr[arr[w]->rightChild]->isRed))){
                        if(w != 0) arr[w]->isRed = true;
                        x = parent;
                        parent = fathersStack.isEmpty() ? 0 : fathersStack.pop();
                        continue;
                    } else {
                        if(w == 0){ x = head->leftChild; continue; }
                        if(!(arr[w]->leftChild != 0 && arr[arr[w]->leftChild]->isRed)){
                            if(arr[w]->rightChild != 0) arr[arr[w]->rightChild]->isRed = false;
                            arr[w]->isRed = true;
                            int parentOfW = parent;
                            leftRotation(w, parentOfW);
                            w = arr[parent]->leftChild;
                        }
                        if(w != 0) arr[w]->isRed = arr[parent]->isRed;
                        arr[parent]->isRed = false;
                        if(arr[w]->leftChild != 0) arr[arr[w]->leftChild]->isRed = false;
                        int parentParent = fathersStack.isEmpty() ? 0 : fathersStack.pop();
                        rightRotation(parent, parentParent);
                        x = head->leftChild;
                        continue;
                    }
                }
            }
            if(x != 0) arr[x]->isRed = false;
        }

        return true;
    }
};
#endif