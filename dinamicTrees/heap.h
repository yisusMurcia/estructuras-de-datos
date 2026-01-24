#ifndef HEAD_H
#define HEAD_H

using namespace std;

template <class T>
class Heap{
    private:
    struct Node{
        T data;
        Node *leftChild, *rightChild, *father;
        Node(const T &value) : data(value), leftChild(nullptr), rightChild(nullptr), father(nullptr) {};
        Node() : leftChild(nullptr), rightChild(nullptr), father(nullptr) {};
    };

    void destroyNode(Node* node){
        if(node != nullptr){
            destroyNode(node->leftChild);
            destroyNode(node->rightChild);
            delete node;
        }
    }

    unsigned size;
    Node* head;

    public:
    Heap(){
        size = 0;
        head = nullptr;
    }

    Heap(T val){
        size = 1;
        head = new Node(val);
    }

    ~Heap(){
        destroyNode(head);
    }

    int getSize(){
        return size;
    }

    void add(T val){
        Node* newNode = new Node(val);
        size++;
        if(head == nullptr)
            head = newNode;
        else{
            Node* father = head;

            int msb = 31 - __builtin_clz(size);

            for(int i = msb -1; i > 0; --i){
                if(size & (1 << i)){
                    father = father->rightChild;
                }else{
                    father = father->leftChild;
                }
            }

            if(size & 1){
                father->rightChild = newNode;
            }else{
                father->leftChild = newNode;    
            }
            newNode->father = father;

            while(father && val > father->data){
                newNode->data = father->data;
                father->data = val;
                newNode = father;
                father = father->father;
            }
        }

    }

    bool isEmpty(){
        return size == 0;
    }

    T pop(){
        if(size == 0)
            throw "Heap is empty";

        T val = head->data;

        if(size == 1){
            delete head;
            head = nullptr;
            size = 0;
            return val;
        }

        Node* father = head;
        Node* toDelete;
        Node* largerChild;

        int msb = 31 - __builtin_clz(size);
        for(int i = msb - 1; i > 0; --i){
            father = (size & (1 << i))
                ? father->rightChild
                : father->leftChild;
        }

        if(size & 1){
            toDelete = father->rightChild;
            father->rightChild = nullptr;
        }else{
            toDelete = father->leftChild;
            father->leftChild = nullptr;
        }

        father = head;
        while(father->leftChild){
            largerChild = father->leftChild;
            if(father->rightChild && father->rightChild->data > largerChild->data)
                largerChild = father->rightChild;

            if(toDelete->data >= largerChild->data)
                break;

            father->data = largerChild->data;
            father = largerChild;
        }


        father->data = toDelete->data;

        delete toDelete;
        size--;
        return val;
    }

};

#endif