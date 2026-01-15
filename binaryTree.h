#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "stack.h"

template <class T>
class Tree{
    private:
    struct Node{
        T value;
        Node *leftChild, *rightChild;
        Node(): value(NULL), leftChild(nullptr), rightChild(nullptr){}
        Node(const T &val): value(val), leftChild(nullptr), rightChild(nullptr){}
    };

    Node *head;
    int size;

    void destroyNode(Node *node){
        if(!node) return;
        destroyNode(node->leftChild);
        destroyNode(node->rightChild);
        delete node;
        size--;
    }

    public:
    Tree(){
        size++;
        head = nullptr;
    }

    Tree(T value){
        head = new Node(value);
        size++;
    }

    ~Tree(){
        destroyNode(head);
    }

    int size(){return size;}

    void add(T value){
        Node* newNode = new Node(value);
        if(!head) head= newNode;
        else{
            Node *father, *node;
            father = head;
            do{
                node = value < father->value? father->leftChild: father->rightChild;
                if(node) father = node;
            }while(node);

            if(value < father->value)
                father->leftChild = newNode;
            else
                father->rightChild = newNode;
        }
        size++;
    }

    bool remove(T value){
        Node* temp = head;
        Node* fatherNode;
        while(temp && temp->value != value){
            fatherNode = temp;
            temp = value < temp->value? temp->leftChild: temp->rightChild;
        }

        if(!temp) return false;

        if(!temp->leftChild || !temp->rightChild){//Leaf
            if(fatherNode->leftChild == temp)
                fatherNode->leftChild = nullptr;
            else
                fatherNode->rightChild = nullptr;
            delete temp;
        }else if(temp->leftChild && temp->rightChild){//Has both childs
            Node* nodeToDelete = temp->rightChild;
            Node* father = temp;
            while(nodeToDelete->leftChild){
                father = nodeToDelete;
                nodeToDelete = nodeToDelete->leftChild;
            }
            temp->value = nodeToDelete->value;
            if(father == temp)
                temp->rightChild = nullptr;
            else
                father->leftChild = nullptr;
            delete nodeToDelete;            
        }else{//There is only one child
            if(fatherNode->leftChild == temp)
                fatherNode->leftChild = temp->leftChild? temp->leftChild: temp->rightChild;
            else
                fatherNode->rightChild = temp->leftChild? temp->leftChild: temp->rightChild;

            delete temp;
        }
        size--;
        return true;
    }

    T* getTreeInorden(){
        if (!head || size == 0) return nullptr;
        T* values = new T[size];
        int nodesVisited = 0;
        Stack<Node*> pendingNodes;

        Node* temp = head;

        while(nodesVisited < size){
            while(temp){
                pendingNodes.push(temp);
                temp = temp->leftChild;
            }

            temp = pendingNodes.pop();
            values[nodesVisited++] = temp->value;

            temp = temp->rightChild;
        }

        return values;
    }

    T* getTreePostOrden(){
        if (!head || size == 0) return nullptr;
        T* values = new T[size];
        int nodesVisited = 0;
        Stack<Node*> pendingNodes;

        Node* temp;
        pendingNodes.push(head);

        while(nodesVisited < size){
            temp = pendingNodes.pop();
            values[size - (++nodesVisited)] = temp->value;

            if(temp->leftChild) pendingNodes.push(temp->leftChild);
            if(temp->rightChild) pendingNodes.push(temp->rightChild);
        }

        return values;
    }

    T* getTreePreorden(){
        if (!head || size == 0) return nullptr;
        T* values = new T[size];
        int nodesVisited = 0;
        Stack<Node*> pendingNodes;

        Node* temp;
        pendingNodes.push(head);

        while(nodesVisited < size && !pendingNodes.empty()){
            temp = pendingNodes.pop();
            values[nodesVisited++] = temp->value;

            if(temp->rightChild) pendingNodes.push(temp->rightChild);
            if(temp->leftChild) pendingNodes.push(temp->leftChild);
        }

        return values;
    }
};
#endif