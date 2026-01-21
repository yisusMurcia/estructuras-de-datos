#ifndef ORDERTREE_H
#define ORDERTREE_H

#include <stdexcept>
#include <iostream>
#include "../stack.h"
#include "../queue.h"

using namespace std;

template <class T>

class Tree{
    private:
    struct Node{
        T data;
        int leftChild;
        int rightChild;
        Node(const T &value) : data(value), leftChild(0), rightChild(0){};
        Node() : leftChild(0), rightChild(0){};
    };

    Node** arr;
    int size;
    Node* head;

    public:
    Tree(int lenght = 50){
        size = lenght;
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
    ~Tree(){
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
            int current = head->leftChild;
            int parent = 0;
            
            while (current != 0) {
                parent = current;
                current = value > arr[current]->data? arr[current]->rightChild : arr[current]->leftChild;
            }
            if (value > arr[parent]->data)
                arr[parent]->rightChild = indexFree;
            else
                arr[parent]->leftChild = indexFree;
        };
    };

    bool remove(T value){
        bool finded = false;
        int index = head->leftChild;
        int fatherIndex = 0;
        do{
            if(arr[index]->data == value)
                finded = true;
            else{
                fatherIndex = index;
                index = arr[index]->data < value? arr[index]->rightChild : arr[index] ->leftChild;
            }
            if(index == 0)return false;//Value not in tree
        }while (!finded);

        Node* toDelete = arr[index];
        int childNodes =(toDelete->leftChild != 0) + (toDelete->rightChild != 0);

        int childNode = index;

        if(childNodes == 0){//Leaf
            if(fatherIndex == 0)//Es la raíz
                head->leftChild = 0;
            else
                if(arr[fatherIndex]->leftChild == index)
                    arr[fatherIndex]->leftChild = 0;
                else
                    arr[fatherIndex]->rightChild = 0;
            
        }else if(childNodes == 1){//One child
            childNode = toDelete->leftChild == 0? toDelete->rightChild : toDelete->leftChild;
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
            int successor = arr[index]->rightChild;
            int successorFather = index;
            
            while(arr[successor]->leftChild != 0){
                successorFather = successor;
                successor = arr[successor]->leftChild;
            }

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

        arr[index]->rightChild = head->rightChild;
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

        cout << endl;
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