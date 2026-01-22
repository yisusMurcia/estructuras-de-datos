#ifndef BLACKREDTREE_H
#define BLACKREDTREE_H

#include <stdexcept>
#include <iostream>
#include "../stack.h"
#include "../queue.h"

using namespace std;

template <class T>
class RedBlackTree{
    private:
    struct Node{
        T data;
        int rightChild, leftChild;
        bool isRed;
        Node (const T &value): data(value), rightChild(0), leftChild(0),  isRed(true){}
        Node ():rightChild(0), leftChild(0),  isRed(true){}
    };

    Node** arr;
    int size;
    Node *head;

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
            if (parentIndex == 0) {
                // nothing
            } else if (arr[parentIndex]->leftChild == xIndex)
                arr[parentIndex]->leftChild = yIndex;
            else
                arr[parentIndex]->rightChild = yIndex;
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
            if (parentIndex == 0) {
                // nothing
            } else if (arr[parentIndex]->leftChild == xIndex)
                arr[parentIndex]->leftChild = yIndex;
            else
                arr[parentIndex]->rightChild = yIndex;
        }

        y->rightChild = xIndex;
    }


    public:
    RedBlackTree(int length = 50){
        size = length;
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
    ~RedBlackTree(){
        for(int i = 0; i<= size; i++) delete arr[i];
        delete [] arr;
    }

    void add(T value){
        int index = head->rightChild;
        if(index == 0)throw out_of_range("The tree is full");

        Node* newNode = arr[index];
        head->rightChild = newNode->rightChild;
        
        newNode->data = value;
        newNode->leftChild = 0;
        newNode-> rightChild = 0;

        if(!head->leftChild){//No hay raiz
            head-> leftChild = index;
        }else{
            int current = head->leftChild;
            Stack<int> fatherStack;
            int parent, grandpa;

            fatherStack.push(0);            
            while (current != 0) {
                fatherStack.push(current);
                current = (value > arr[current]->data)
                    ? arr[current]->rightChild
                    : arr[current]->leftChild;

            }

            parent = fatherStack.pop();

            if (value > arr[parent]->data)
                arr[parent]->rightChild = index;
            else
                arr[parent]->leftChild = index;

            while (fatherStack.peek() != 0 && arr[parent]->isRed) {
                grandpa = fatherStack.pop();

                int uncle = (parent == arr[grandpa]->leftChild)
                    ? arr[grandpa]->rightChild
                    : arr[grandpa]->leftChild;

                if (uncle && arr[uncle]->isRed) { // Case 1
                    arr[parent]->isRed = false;
                    arr[uncle]->isRed = false;
                    arr[grandpa]->isRed = true;

                    index = grandpa;
                    parent = fatherStack.peek();
                } else { // Case 2 & 3
                    if (parent == arr[grandpa]->leftChild) {
                        if (index == arr[parent]->rightChild) {
                            leftRotation(parent, grandpa);
                            parent = index;
                        }
                        arr[parent]->isRed = false;
                        arr[grandpa]->isRed = true;
                        rightRotation(grandpa, fatherStack.peek());
                    } else {
                        if (index == arr[parent]->leftChild) {
                            rightRotation(parent, grandpa);
                            parent = index;
                        }
                        arr[parent]->isRed = false;
                        arr[grandpa]->isRed = true;
                        leftRotation(grandpa, fatherStack.peek());
                    }
                    index = parent;
                    parent = grandpa;
                }
            }

            
        };
        arr[head->leftChild]->isRed = false;
    };

    bool remove(T value){
       bool finded = false;
        int index = head->leftChild;
        Stack<int> parentsStack;
        parentsStack.push(0);
        do{
            if(arr[index]->data == value)
                finded = true;
            else{
                parentsStack.push(index);
                index = arr[index]->data < value? arr[index]->rightChild : arr[index] ->leftChild;
            }
            if(index == 0)return false;//Value not in tree
        }while (!finded);

        Node* toDelete = arr[index];
        int childNodes =(toDelete->leftChild != 0) + (toDelete->rightChild != 0);
        int fatherIndex = parentsStack.pop();
        int nodeToBalance = 0;
        bool needsBalancing = !arr[index]->isRed;
        int successor;

        if(childNodes == 0){//Leaf
            nodeToBalance = 0;
            if(fatherIndex == 0)//Es la raíz
                head->leftChild = 0;
            else
                if(arr[fatherIndex]->leftChild == index)
                    arr[fatherIndex]->leftChild = 0;
                else
                    arr[fatherIndex]->rightChild = 0;
            
        }else if(childNodes == 1){//One child
            int childNode = toDelete->leftChild == 0? toDelete->rightChild : toDelete->leftChild;
            nodeToBalance = childNode;
            
            if(fatherIndex == 0){//Es la raíz
                head->leftChild = childNode;
            }else{
                if(arr[fatherIndex]->leftChild == index)
                    arr[fatherIndex]->leftChild = childNode;
                else
                    arr[fatherIndex]->rightChild = childNode;
            }
        }else{//Two children
            // Encontrar el sucesor (nodo más a la izquierda del subárbol derecho)
            successor = arr[index]->rightChild;
            int successorFather = index;
            
            while(arr[successor]->leftChild != 0){
                successorFather = successor;
                successor = arr[successor]->leftChild;
            }

            nodeToBalance = arr[successor]->rightChild;
            
            // Desconectar el sucesor de su ubicación anterior
            if(successorFather == index){
                // El sucesor es el hijo derecho directo
                arr[index]->rightChild = arr[successor]->rightChild;
            }else{
                // El sucesor está en el subárbol izquierdo del hijo derecho
                arr[successorFather]->leftChild = arr[successor]->rightChild;
            }

            // Reemplazar el nodo a eliminar con el sucesor
            arr[successor]->leftChild = arr[index]->leftChild;
            arr[successor]->rightChild = arr[index]->rightChild;
            
            if(fatherIndex == 0){//Es la raíz
                head->leftChild = successor;
            }else{
                if(arr[fatherIndex]->leftChild == index)
                    arr[fatherIndex]->leftChild = successor;
                else
                    arr[fatherIndex]->rightChild = successor;
            }
        }

        // Add deleted node back to free list
        arr[index]->rightChild = head->rightChild;
        head->rightChild = index;
        arr[index]->leftChild = 0;

        // Perform balancing if needed
        if (needsBalancing && nodeToBalance != head->leftChild) {
            while (nodeToBalance != head->leftChild && !arr[nodeToBalance]->isRed && !parentsStack.isEmpty()) {
                int parent = parentsStack.pop();
                if (parent == 0) break;

                if (arr[parent]->leftChild == nodeToBalance) {
                    int sibling = arr[parent]->rightChild;

                    if (sibling != 0 && arr[sibling]->isRed) {
                        arr[sibling]->isRed = false;
                        arr[parent]->isRed = true;
                        leftRotation(parent, parentsStack.isEmpty() ? 0 : parentsStack.peek());
                        sibling = arr[parent]->rightChild;
                    }

                    if (sibling != 0 && !arr[arr[sibling]->leftChild]->isRed &&
                        !arr[arr[sibling]->rightChild]->isRed) {
                        arr[sibling]->isRed = true;
                        nodeToBalance = parent;
                    } else if (sibling != 0) {
                        if (!arr[arr[sibling]->rightChild]->isRed) {
                            arr[arr[sibling]->leftChild]->isRed = false;
                            arr[sibling]->isRed = true;
                            rightRotation(sibling, parent);
                            sibling = arr[parent]->rightChild;
                        }

                        arr[sibling]->isRed = arr[parent]->isRed;
                        arr[parent]->isRed = false;
                        arr[arr[sibling]->rightChild]->isRed = false;
                        leftRotation(parent, parentsStack.isEmpty() ? 0 : parentsStack.peek());
                        nodeToBalance = head->leftChild;
                    }
                } else {
                    int sibling = arr[parent]->leftChild;

                    if (sibling != 0 && arr[sibling]->isRed) {
                        arr[sibling]->isRed = false;
                        arr[parent]->isRed = true;
                        rightRotation(parent, parentsStack.isEmpty() ? 0 : parentsStack.peek());
                        sibling = arr[parent]->leftChild;
                    }

                    if (sibling != 0 && !arr[arr[sibling]->leftChild]->isRed &&
                        !arr[arr[sibling]->rightChild]->isRed) {
                        arr[sibling]->isRed = true;
                        nodeToBalance = parent;
                    } else if (sibling != 0) {
                        if (!arr[arr[sibling]->leftChild]->isRed) {
                            arr[arr[sibling]->rightChild]->isRed = false;
                            arr[sibling]->isRed = true;
                            leftRotation(sibling, parent);
                            sibling = arr[parent]->leftChild;
                        }

                        arr[sibling]->isRed = arr[parent]->isRed;
                        arr[parent]->isRed = false;
                        arr[arr[sibling]->leftChild]->isRed = false;
                        rightRotation(parent, parentsStack.isEmpty() ? 0 : parentsStack.peek());
                        nodeToBalance = head->leftChild;
                    }
                }
            }
            if (nodeToBalance != 0) arr[nodeToBalance]->isRed = false;
        }
        return true;
    }

    void displayInOrder() {
        Stack<int> stack;          // Stack de índices
        int current = head->leftChild;   // Raíz del árbol

        while (current != 0 || !stack.isEmpty()) {

            // 1. Ir todo hacia la izquierda
            while (current != 0) {
                stack.push(current);
                current = arr[current]->leftChild;
            }

            // 2. Desapilar y visitar
            current = stack.pop();
            cout << arr[current]->data << " ";

            // 3. Ahora explorar el subárbol derecho
            current = arr[current]->rightChild;
        }
        cout << endl;
    }

    void displayPreOrder() {
        Stack<int> stack;
        int root = head->leftChild;

        if (root == 0) return;

        stack.push(root);

        while (!stack.isEmpty()) {
            int index = stack.pop();
            cout << arr[index]->data << " ";

            // Primero derecho (para que el izquierdo salga primero)
            if (arr[index]->rightChild != 0)
                stack.push(arr[index]->rightChild);

            if (arr[index]->leftChild != 0)
                stack.push(arr[index]->leftChild);
        }
        cout << endl;
    }

    void displayPostOrder() {
        Stack<int> stack1, stack2;
        int root = head->leftChild;

        if (root == 0) return;

        stack1.push(root);

        while (!stack1.isEmpty()) {
            int index = stack1.pop();
            stack2.push(index);

            if (arr[index]->leftChild != 0)
                stack1.push(arr[index]->leftChild);

            if (arr[index]->rightChild != 0)
                stack1.push(arr[index]->rightChild);
        }

        // stack2 contiene los nodos en posorden
        while (!stack2.isEmpty()) {
            cout << arr[stack2.pop()]->data << " ";
        }
    }

    void displayByLevels() {
        int root = head->leftChild;   // La raíz del árbol está aquí
        if (root == 0) return;        // Árbol vacío

        Queue<int> queue;
        queue.add(root);

        while (!queue.isEmpty()) {
            int idx = queue.attend();     // Saco índice del nodo actual

            cout << arr[idx]->data << " ";

            if (arr[idx]->leftChild != 0)
                queue.add(arr[idx]->leftChild);

            if (arr[idx]->rightChild != 0)
                queue.add(arr[idx]->rightChild);
        }
        cout << endl;
    }
};
#endif