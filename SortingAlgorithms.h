#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

using namespace std;

#include "stack.h"

template <class T>
void quickSort(T arr[], int start, int end){
    Stack<int*> stack;
    int* values = new int[2];
    values[0] = start;
    values[1] = end;
    stack.push(values);
    int i, j;
    while(!stack.isEmpty()){
        values = stack.pop(); //[start, end]
        start = values[0];
        end = values[1];
        delete[] values;
        if(end > start){
            i = start - 1;
            j = end;
            T pivot = arr[end];
            for(;;){
                while(arr[++i] < pivot);
                while(arr[--j] > pivot);
                if(i >= j) break;
                swap(arr[i], arr[j]);
            }

            swap(arr[i], arr[end]);
            //left partition
            int* leftVals = new int[2];
            leftVals[0] = start;
            leftVals[1] = i - 1;
            stack.push(leftVals);
            //right partition
            int* rightVals = new int[2];
            rightVals[0] = i + 1;
            rightVals[1] = end;
            stack.push(rightVals);
        }
    }
}

template <class T>
void mergeList(T arr[], int start1, int end1, int start2, int end2){//Not use, this functions is called in mergeSort
    int finalStart = start1;
    int finalEnd = end2;
    int index = 0;
    T* result = new T[end2- start1];

    while(start1 <= end1 && start2 <= end2){
        result[index] = arr[start1] < arr[start2]? arr[start1++]: arr[start2++];
        index++;
    }

    if(start1<= end1)
        for(int i = start1; i <= end1; i++) result[index++] = arr[i];
    else
        for(int i= start2; i<=end2; i++) result[index++] = arr[i];

    index = 0;
    for(int i = finalStart; i <= finalEnd; i++) arr[i] = result[index++];
    delete result;
    
}

template <class T>
void mergeSort(T arr[], int size) {

    T* buffer = new T[size];

    for (int length = 1; length < size; length *= 2) {

        for (int l = 0; l < size - 1; l += 2 * length) {

            int start1 = l;
            int end1   = (l + length - 1 < size - 1) ? l + length - 1 : size - 1;
            int start2 = end1 + 1;
            int end2   = (l + 2 * length - 1 < size - 1) ? l + 2 * length - 1 : size - 1;

            int index = l;

            while (start1 <= end1 && start2 <= end2) {
                buffer[index++] =
                    (arr[start1] <= arr[start2]) ? arr[start1++] : arr[start2++];
            }

            while (start1 <= end1)
                buffer[index++] = arr[start1++];

            while (start2 <= end2)
                buffer[index++] = arr[start2++];

            for (int i = l; i <= end2; i++)
                arr[i] = buffer[i];
        }
    }

    delete[] buffer;
}

template <class T>
void insertion(T arr[], int size){
    int i, j;
    T value;
    for(i = 1; i < size; i++){
        j = i;
        value = arr[j];
        while(arr[j -1] > value && j > 0){
            arr[j--] = arr[j - 1];
        }
        arr[j] = value;
    }
}

template <class T>
void shellSort(T arr[], int size){
    int i, j, h;
    T value;
    for(h = 1; h< size/9; h = 3*h+1);
    for(;h>0; h/=3)
        for(i = h; i < size; i++){
            value = arr[i];
            j = i;
            while(j >= h && arr[j-h] > value){
                arr[j] = arr[j - h];
                j-= h;
            }
            arr[j] = value;
        }
}
#endif