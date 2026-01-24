#ifndef HEAD_H
#define HEAD_H

template <class T>
class Heap{
    private:

    int size;
    T* arr;
    int numOfNodes;//Also indicates where the new node'll added


    public:
    Heap(int length = 50){
        size = length;
        numOfNodes = 0;
        arr = new T[size];
    }

    ~Heap(){
        delete arr;
    }

    void add(T val){
        int index = numOfNodes;   // new leaf

        while(index > 0 && arr[(index - 1) / 2] < val){
            arr[index] = arr[(index - 1) / 2];  // Move father
            index = (index - 1)/2;
        }

        arr[index] = val;
        numOfNodes++;
    }

    T pop(){
        if(numOfNodes == 0)
            throw "Heap is empty";
        T val = arr[0];
        T last = arr[--numOfNodes];

        int parent = 0;
        bool added = false;

        while(!added && 2*parent + 1 < numOfNodes){
            int left = 2*parent + 1;
            int right = left + 1;

            int maxChild = left;
            if(right < numOfNodes && arr[right] > arr[left])
                maxChild = right;

            if(arr[maxChild] <= last)
                added = true;
            else{
                arr[parent] = arr[maxChild];
                parent = maxChild;
            }
        }

        arr[parent] = last;
        return val;
    }

    int getSize(){
        return numOfNodes;
    }

};

#endif