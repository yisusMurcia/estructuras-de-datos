#ifndef AVLTREE_H
#define AVLTREE_H

#include "../stack.h"
#include "../queue.h"

template <class T>

class AVLTree{
    private:
    struct Node{
        T data;
        int height, leftChild, rightChild;
        Node(const T &value) : data(value), height(0), leftChild(0), rightChild(0) {};
        Node() : height(0), leftChild(0), rightChild(0) {};
    };

    Node** arr;
    int size;
    Node* head;

    int max(int a, int b){
        return a> b? a: b;
    }

    int height(int i){
        return (i == 0) ? 0 : arr[i]->height;
    }

    void updateHeight(int i){
        arr[i]->height = 1 + max(
            height(arr[i]->leftChild),
            height(arr[i]->rightChild)
        );
    }

    void leftRotation(int node, int fatherNode){
        int rightChild = arr[node]->rightChild;
        int newRightChild = arr[rightChild]->leftChild;

        if(arr[fatherNode]->leftChild == node) arr[fatherNode]->leftChild = rightChild;
        else arr[fatherNode]->rightChild = rightChild;

        arr[node]->rightChild = newRightChild;

        arr[rightChild]->leftChild = node;

        updateHeight(node);
        updateHeight(rightChild);
    }

    void rightRotation(int node, int fatherNode){
        int leftChild = arr[node]->leftChild;
        int newLeftChild = arr[leftChild]->rightChild;

        if(arr[fatherNode]->leftChild == node) arr[fatherNode]->leftChild = leftChild;
        else arr[fatherNode]->rightChild = leftChild;

        arr[node]->leftChild = newLeftChild;

        arr[leftChild]->rightChild = node;

        updateHeight(node);
        updateHeight(leftChild);
    }

    int getBalanceFactor(Node* node){
        return height(node->rightChild) - height(node->leftChild);
    }
    int getBalanceFactor(int i){
        return getBalanceFactor(arr[i]);
    }

    public:
    AVLTree(int length = 50){
        size = length;
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
    ~AVLTree(){
        for(int i = 0; i<= size; i++){
            Node* node = arr[i];
            delete node;
        }
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
            int parent, balanceFactor;

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

            while(!fatherStack.isEmpty()){
                index = parent;
                parent = fatherStack.pop();
                
                updateHeight(index);
                balanceFactor = getBalanceFactor(arr[index]);

                if(balanceFactor < -1){
                    if(getBalanceFactor(arr[index]->leftChild) > 0) leftRotation(arr[index]->leftChild, index);
                    rightRotation(index, parent);
                }else if(balanceFactor > 1){
                    if(getBalanceFactor(arr[index]->rightChild)< 0) rightRotation(arr[index]->rightChild, index);
                    leftRotation(index, parent);
                }
            }
            
        };
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
        int childNode = index;
        int fatherIndex = parentsStack.pop();
        int balanceFactor;

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

            parentsStack.push(successorFather);
        }

        arr[index]->rightChild = head->rightChild;
        head->rightChild = index;
        
        while(fatherIndex != 0 && !parentsStack.isEmpty()){
            index = fatherIndex;
            fatherIndex = parentsStack.pop();

            updateHeight(index);
            balanceFactor = getBalanceFactor(index);

            if(balanceFactor < -1){
                if(getBalanceFactor(arr[index]->leftChild) > 0) leftRotation(arr[index]->leftChild, index);
                rightRotation(index, fatherIndex);
            }else if(balanceFactor > 1){
                if(getBalanceFactor(arr[index]->rightChild)< 0) rightRotation(arr[index]->rightChild, index);
                leftRotation(index, fatherIndex);
            }
            
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