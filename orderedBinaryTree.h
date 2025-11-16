#ifndef ORDERTREE_H
#define ORDERTREE_H

#include <stdexcept>
#include <iostream>
#include "stack.h"
#include "queue.h"
using namespace std;

template <class T>

class OrderTree{
    private:
    struct Node{
        T data;
        int leftChild;
        int rightChild;
        Node(const T &value) : data(value), leftChild(0), rightChild(0){};
    };

    Node** arr;
    int size;
    Node* head;

    public:
    OrderTree(int size = 50){
        this.size = size;
        arr = new Node*[size + 1];//0 is for control
        for(int i = 0; i < size; i++){
            Node* node = new Node();
            node->rightChild = i+1;  
            arr[i] = node;          
        }
        head = arr[0];
        arr[size +1] = new Node();
        arr[size +1]->rightChild = 0;
    }
    ~OrderTree(){
        for(int i = 0; i<= size; i++){
            Node* node = arr[i];
            delete node;
        }
    }

    void add(T value){
        int indexFree = head->rightChild;
        if(indexFree == 0)throw out_of_range("The tree is full");

        Node* newNode = arr[indexFree];
        head->rightChild = newNode->rightChild;
        
        newNode->data = value;
        newNode->leftChild = 0;
        newNode-> rightChild = 0;

        if(!head->leftChild){//No hay raiz
            head-> leftChild = indexFree;
        }else{
            Node* child = arr[head->leftChild];
            Node* father = child;
            bool added = false;
            do{
                father = child;
                child = value>father->data? father->rightChild: father->leftChild;

            }while(!added && child != NULL);
            if(father-> data < value)
                father->rightChild = indexFree;
            else
                father->leftChild = indexFree;
        };
    };

    bool remove(T value){
        bool finded = false;
        int index = 1;
        int fatherIndex = 1;
        do{
            if(arr[index]->data == value){
                finded = true;
            }else{
                fatherIndex = index;
                index = arr[index]->data < value? arr[index]->rightChild : arr[index] ->leftChild;
            }
            if(index == 0)return false;//Value not in tree
        }while (!finded);

        Node* toDelete = arr[index];
        int childNodes = toDelete->rightChild + toDelete->leftChild;
        int childNode = index;

        if(childNodes == 0){//Leaf
            childNode = 0; //A leaf has no children
        }else if(childNodes == 1){
            childNode = toDelete->leftChild == 0? toDelete->leftChild: toDelete->rightChild;
            toDelete ->leftChild = 0;
            toDelete->rightChild = head->rightChild;
            head->rightChild = index;
            if(arr[fatherIndex]->leftChild == index)
                arr[fatherIndex]->leftChild = childNode;
            else
                arr[fatherIndex]->rightChild = childNode;
        }else{
            int childIndex = toDelete->rightChild;
            while(toDelete->leftChild == 0){
                toDelete = arr[childIndex];
                childIndex = toDelete->leftChild;
            }
        }
        //Update fatherNode and 
        if(arr[fatherIndex]->leftChild == index)
                arr[fatherIndex]->leftChild = childNode;
            else
                arr[fatherIndex]->rightChild = childNode;
        toDelete -> leftChild = 0;
        toDelete -> rightChild = head->rightChild;
        head->rightChild = index;
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
    }
};

#endif