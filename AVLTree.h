#ifndef AVLTREE_H
#define AVLTREE_H

#include "stack.h"

template <class T>
class AVLTree{
    private:
    struct Node{
        T value;
        int height;
        Node *leftChild, *rightChild, *father;
        Node(): value(NULL), leftChild(nullptr), rightChild(nullptr), father(nullptr), height(1) {}
        Node(const T &val): value(val), leftChild(nullptr), rightChild(nullptr), father(nullptr), height(1) {}
    };

    Node *root;
    int size;

    int max(int a, int b){
        return a>b? a: b;
    }

    void destroyNode(Node *node){
        if(!node) return;
        destroyNode(node->leftChild);
        destroyNode(node->rightChild);
        delete node;
        size--;
    }

    void leftRotation(Node* node){
        Node* father = node->father;
        Node* rigthChild = node->rightChild;
        Node* newRightChild = rigthChild->leftChild;
        if(father)
            if(father->leftChild == node) father->leftChild = rigthChild;
            else father->rightChild = rigthChild;
        else root = rigthChild;//Root
        
        rigthChild->father = father;

        node->rightChild = newRightChild;
        if(newRightChild) newRightChild->father = node;
        rigthChild->leftChild = node;
        node->father = rigthChild;
        
    }

    void rightRotation(Node* node){
        Node* father = node->father;
        Node* leftChild = node->leftChild;
        Node* newLeftChild = leftChild->rightChild;
        
        if(father)
            if(father->leftChild == node) father->leftChild = leftChild;
            else father ->rightChild = leftChild;
        else root = leftChild; //Root

        leftChild->father = father;

        node->leftChild = newLeftChild;
        if(newLeftChild) newLeftChild->father = node;

        leftChild->rightChild = node;
        node->father = leftChild;
    }

    int height(Node* node){
        return node? node->height: 0;
    }

    int recalulateHeight(Node* node){
        int h = 1 + max(height(node->leftChild), height(node->rightChild));
        node->height = h;
        return h;
    }

    int getBalanceFactor(Node* node){
        return height(node->rightChild) - height(node->leftChild);
    }

    public:
    AVLTree(){
        root = nullptr;
        size = 0;
    }

    AVLTree(T value){
        root = new Node(value);
        size = 1;
    }

    ~AVLTree(){
        destroyNode(root);
    }

    int getSize(){return size;}

    void add(T value){
        Node* newNode = new Node(value);
        if(!root) root= newNode;
        else{
            Node *father, *node;
            int bf;
            father = root;
            do{
                node = value < father->value? father->leftChild: father->rightChild;
                if(node) father = node;
            }while(node);

            newNode-> father = father;
            if(value < father->value)
                father->leftChild = newNode;
            else
                father->rightChild = newNode;

            node = father;
            while(node){
                recalulateHeight(node);
                bf = getBalanceFactor(node);
                if(bf < -1){//Right rotation
                        if(getBalanceFactor(node->leftChild) > 0)//Double rotation
                            leftRotation(node->leftChild);
                        rightRotation(node);
                }else if(bf > 1){//Left rotation
                        if(getBalanceFactor(node->rightChild) < 0)//Double rotation
                            rightRotation(node->rightChild);
                        leftRotation(node);
                }
                node = node->father;
            }
        }
        size++;
    }

    bool remove(T value){
        Node* node = root;
        while(node && node->value != value)
            node = value < node->value ? node->leftChild : node->rightChild;

        if(!node) return false;

        Node* toDelete = node;
        Node* balanceStart = nullptr;

        if(node->leftChild && node->rightChild){
            Node* succ = node->rightChild;
            while(succ->leftChild) succ = succ->leftChild;
            node->value = succ->value;
            toDelete = succ;
        }

        Node* child = toDelete->leftChild ? toDelete->leftChild : toDelete->rightChild;

        if(child) child->father = toDelete->father;

        if(!toDelete->father){
            root = child;
        } else if(toDelete->father->leftChild == toDelete){
            toDelete->father->leftChild = child;
        } else {
            toDelete->father->rightChild = child;
        }

        balanceStart = toDelete->father;
        delete toDelete;
        size--;

        while(balanceStart){
            recalulateHeight(balanceStart);
            int bf = getBalanceFactor(balanceStart);

            if(bf < -1){
                if(getBalanceFactor(balanceStart->leftChild) > 0)
                    leftRotation(balanceStart->leftChild);
                rightRotation(balanceStart);
            }
            else if(bf > 1){
                if(getBalanceFactor(balanceStart->rightChild) < 0)
                    rightRotation(balanceStart->rightChild);
                leftRotation(balanceStart);
            }

            balanceStart = balanceStart->father;
        }

        return true;
    }


    T* getTreeInorden(){
        if (!root || size == 0) return nullptr;
        T* values = new T[size];
        int nodesVisited = 0;
        Stack<Node*> pendingNodes;

        Node* temp = root;

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
        if (!root || size == 0) return nullptr;
        T* values = new T[size];
        int nodesVisited = 0;
        Stack<Node*> pendingNodes;

        Node* temp;
        pendingNodes.push(root);

        while(nodesVisited < size){
            temp = pendingNodes.pop();
            values[size - (++nodesVisited)] = temp->value;

            if(temp->leftChild) pendingNodes.push(temp->leftChild);
            if(temp->rightChild) pendingNodes.push(temp->rightChild);
        }

        return values;
    }

    T* getTreePreorden(){
        if (!root || size == 0) return nullptr;
        T* values = new T[size];
        int nodesVisited = 0;
        Stack<Node*> pendingNodes;

        Node* temp;
        pendingNodes.push(root);

        while(nodesVisited < size && !pendingNodes.isEmpty()){
            temp = pendingNodes.pop();
            values[nodesVisited++] = temp->value;

            if(temp->rightChild) pendingNodes.push(temp->rightChild);
            if(temp->leftChild) pendingNodes.push(temp->leftChild);
        }

        return values;
    }
};
#endif