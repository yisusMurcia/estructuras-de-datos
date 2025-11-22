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
        Node (const T &value): data(value), rightChild(0), leftChild(0),  isRed(true){};
        Node (): data(NULL), rightChild(0), leftChild(0),  isRed(true){};
    };

    Node** arr;
    int size;
    Node *head;
    Stack<int> fathersStack;

    void leftRotation(int xIndex) {
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
            int realFatherIndex = fathersStack.peek();
            if (arr[realFatherIndex]->leftChild == xIndex)
                arr[realFatherIndex]->leftChild = yIndex;
            else
                arr[realFatherIndex]->rightChild = yIndex;
        }

        y->leftChild = xIndex;
    }

    void rightRotation(int xIndex) {
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
            int realFatherIndex = fathersStack.peek();
            if (arr[realFatherIndex]->leftChild == xIndex)
                arr[realFatherIndex]->leftChild = yIndex;
            else
                arr[realFatherIndex]->rightChild = yIndex;
        }

        y->rightChild = xIndex;
    }


    public:
    BlackRedTree(int size = 50){
        this.size = size;
        arr = new Node*[size + 1];//0 is for control
        for(int i = 0; i < size; i++){
            Node* node = new Node();
            node->rightChild = i+1;  
            arr[i] = node;          
        }
        head = arr[0];
        arr[size] = new Node();
        arr[size]->rightChild = 0;
    }
    ~BlackRedTree(){
        for(int i = 0; i<= size; i++){
            Node* node = arr[i];
            delete node;
        }
    }

    void add(T value){
        int childIndex = head->rightChild;
        if(childIndex == 0)throw out_of_range("The tree is full");

        Node* newNode = arr[childIndex];
        head->rightChild = newNode->rightChild;
        
        newNode->data = value;
        newNode->leftChild = 0;
        newNode-> rightChild = 0;

        if(!head->leftChild){//No hay raiz
            head-> leftChild = childIndex;
            newNode->isRed = false; //Raiz es negra
        }else{
            int fatherIndex = head->leftChild;
            Node father;
            do{
                fathersStack.push(fatherIndex);
                father = arr[fatherIndex];
                fatherIndex = value>arr[fatherIndex] ->data? father->rightChild: father->leftChild;
            }while(fatherIndex != 0);
            
            fatherIndex = fathersStack.pop();
            if(arr[fatherIndex]-> data < value)
                father->rightChild = childIndex;
            else
                father->leftChild = childIndex;
            //Balancear usamos child y father
            while(!fathersStack.isEmpty() && arr[fatherIndex]->isRed && arr[childIndex]->isRed){
                childIndex = fatherIndex; //Padre
                fatherIndex = fathersStack.pop(); //Abuelo
                int brotherIndex;
                if(arr[fatherIndex]->rightChild == childIndex){//Esta a la derecha
                    brotherIndex = arr[fatherIndex]->leftChild;
                    if(brotherIndex == 0 || !arr[brotherIndex]->isRed){
                        int innerChildIndex = arr[fatherIndex]->leftChild;
                        if(arr[innerChildIndex] == newNode)
                            rightRotation(innerChildIndex);
                        leftRotation(fatherIndex);
                    }else{
                        //Caso 2 (tio rojo)
                        arr[childIndex]-> isRed = false;
                        arr[brotherIndex]->isRed = false;
                        arr[fatherIndex]->isRed = true;
                    };
                }else{
                    brotherIndex = arr[fatherIndex]->rightChild;
                    if(brotherIndex == 0 || !arr[brotherIndex]->isRed){
                        int innerChildIndex = arr[fatherIndex]->rightChild;
                        if(arr[innerChildIndex] == newNode)
                            leftRotation(innerChildIndex);
                        rightRotation(fatherIndex);
                    }else{
                        //Caso 2 (tio rojo)
                        arr[childIndex]-> isRed = false;
                        arr[brotherIndex]->isRed = false;
                        arr[fatherIndex]->isRed = true;
                    }
                }                
                arr[head->leftChild]->isRed = false;//La raiz siempre es negra
            }
        };

        fathersStack.emptyStack();
    }

    bool remove(T value){}
};
#endif