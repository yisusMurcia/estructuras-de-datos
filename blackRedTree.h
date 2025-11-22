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
        Node (const T &value): data(value), rightChild(0), leftChild(o),  isRed(true){};
    };

    Node** arr;
    int size;
    Node *head;
    Stack<Node> fathersStack;

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
        arr[size +1] = new Node();
        arr[size +1]->rightChild = 0;
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
            Node* father = arr[head->leftChild];
            do{
                fathersStack.push(father);
                father = arr[value>father->data? father->rightChild: father->leftChild];
            }while(father != head);
            //Father es la posición de control
            father = fathersStack.pop();
            if(father-> data < value)
                father->rightChild = childIndex;
            else
                father->leftChild = childIndex;
                //Balancear usamos child y father
                Node* child = newNode;
                while((father->isRed && child->isRed) || fathersStack.isEmpty()){

                    //Balanceo según el caso

                    child = father;
                    father = fathersStack.pop()
                }
        };

        fathersStack.emptyStack();
    }
};
#endif