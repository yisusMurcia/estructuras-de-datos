#ifndef BLACKREDTREE_H
#define BLACKREDTREE_H

#include "../stack.h"

template <class T>
class RedBlackTree{
    private:
    struct Node{
        Node *leftChild, *rightChild, *father;
        T value;
        bool isRed;
        Node( const T &val): leftChild(nullptr), rightChild(nullptr), father(nullptr), value(val), isRed(true) {};
    };

    Node* root;
    int size;

    void destroyTree(Node *node){
        if(!node) return;
        destroyTree(node->leftChild);
        destroyTree(node->rightChild);
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

    public:

    RedBlackTree(T val){
        root = new Node(val);
        size = 1;
    }

    RedBlackTree(){
        size = 0;
        root = nullptr;
    }

    ~RedBlackTree(){
        destroyTree(root);
    }

    int getSize(){return size;}


    void add(T val){
        Node* newNode = new Node(val);
        if(!root) root = newNode;
        else{
            Node *father, *temp;
            father = root;
            do{
                temp = val < father->value? father->leftChild : father->rightChild;
                if(temp) father = temp;
            }while(temp);
            
            if(val < father->value) father->leftChild = newNode;
            else father->rightChild = newNode;
            
            newNode->father = father;
            
            // Balanceo del árbol rojo-negro
            Node* current = newNode;
            while (current->father && current->father->isRed) {
                Node* parent = current->father;
                Node* grandpa = parent->father;
                
                if(!grandpa) break;
                
                Node* uncle = (parent == grandpa->leftChild)
                ? grandpa->rightChild
                : grandpa->leftChild;
                
                // CASE 1: Tío es rojo
                if (uncle && uncle->isRed) {
                    parent->isRed = false;
                    uncle->isRed = false;
                    grandpa->isRed = true;
                    current = grandpa;
                }else {
                    // CASE 2 y 3: Tío es negro
                    if (parent == grandpa->leftChild) {
                        if (current == parent->rightChild) {
                            leftRotation(parent);
                            current = parent;
                            parent = current->father;
                        }
                        parent->isRed = false;
                        grandpa->isRed = true;
                        rightRotation(grandpa);
                    } else {
                        if (current == parent->leftChild) {
                            rightRotation(parent);
                            current = parent;
                            parent = current->father;
                        }
                        parent->isRed = false;
                        grandpa->isRed = true;
                        leftRotation(grandpa);
                    }
                }
            }
        }
        root->isRed = false;
        size++;
    }
    
    bool remove(T val){
        Node* node = root;
        while(node && node->value != val)
            node = val < node->value ? node->leftChild : node->rightChild;

        if(!node) return false;

        Node* toDelete = node;
        if(node->leftChild && node->rightChild){
            Node* succ = node->rightChild;
            while(succ->leftChild) succ = succ->leftChild;
            node->value = succ->value;
            toDelete = succ;
        }

        Node* child = toDelete->leftChild ? toDelete->leftChild : toDelete->rightChild;
        Node* father = toDelete->father;

        if(child) child->father = father;

        if(!father){
            root = child;
        } else if(father->leftChild == toDelete){
            father->leftChild = child;
        } else {
            father->rightChild = child;
        }

        Node* x = child;
        Node* brother;

        if(!toDelete->isRed){
            while(x != root && (!x || !x->isRed)){
                if(father->leftChild == x){
                    brother = father->rightChild;

                    if(brother && brother->isRed){
                        brother->isRed = false;
                        father->isRed = true;
                        leftRotation(father);
                        brother = father->rightChild;
                    }

                    if(brother &&
                    (!brother->leftChild || !brother->leftChild->isRed) &&
                    (!brother->rightChild || !brother->rightChild->isRed)){
                        brother->isRed = true;
                        x = father;
                        father = father->father;
                    } else {
                        if(brother && (!brother->rightChild || !brother->rightChild->isRed)){
                            if(brother->leftChild) brother->leftChild->isRed = false;
                            brother->isRed = true;
                            rightRotation(brother);
                            brother = father->rightChild;
                        }

                        if(brother) brother->isRed = father->isRed;
                        father->isRed = false;
                        if(brother && brother->rightChild)
                            brother->rightChild->isRed = false;

                        leftRotation(father);
                        x = root;
                    }
                } else {
                    brother = father->leftChild;
                    if(brother && brother->isRed){
                        brother->isRed = false;
                        father->isRed = true;
                        rightRotation(father);
                        brother = father->leftChild;
                    }
                    if(brother &&
                    (!brother->leftChild || !brother->leftChild->isRed) &&
                    (!brother->rightChild || !brother->rightChild->isRed)){
                        brother->isRed = true;
                        x = father;
                        father = father->father;
                    }else{
                        if(!brother->leftChild || !brother->leftChild->isRed){
                            if(brother->rightChild) brother->rightChild->isRed = false;
                            brother->isRed = true;
                            leftRotation(brother);
                            brother = father->leftChild;
                        }
                        if(brother) brother->isRed = father->isRed;
                        father->isRed = false;
                        if(brother && brother->leftChild)
                            brother->leftChild->isRed = false;
                        rightRotation(father);
                        x = root;
                    }
                }
            }
            if(x) x->isRed = false;
        }

        delete toDelete;
        size--;
        return true;
    }

    T* getTreeInorder(){
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

    T* getTreePostorder(){
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

    T* getTreePreorder(){
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