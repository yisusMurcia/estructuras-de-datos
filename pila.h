#ifndef PILA_H
#define PILA_H

template <class t> 
class Stack{
    private:
    struct Node{t data; Node *next;};
    Node *head, *tail;
    int size;
    public:
    Stack (){
        head = new Node;
        tail=new Node;
        size = 0;
        head->next=tail; tail->next =tail;
    }
    ~Stack(){
    struct Node *temp= head;
    while (temp!=tail){head=temp;  temp= temp->next;  delete head;}
    delete tail;
}

void push (t v){Node *temp=new Node;
 temp->data = v;  temp->next=head->next;
head->next=temp;
size++;
}
    t pop(){
        t x;
    Node *temp = head->siguiente;
    head->siguiente = temp->siguiente; x=temp->data;
    delete temp;
    size--;
    return x;
}
    bool empty(){return size == 0;}
    int getSize(){return size;}
 };
#endif