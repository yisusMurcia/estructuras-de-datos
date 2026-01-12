#ifndef QUICKSORT_H
#define QUICKSORT_H

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
            // push left partition [start, i-1]
            int* leftVals = new int[2];
            leftVals[0] = start;
            leftVals[1] = i - 1;
            stack.push(leftVals);
            // push right partition [i+1, end]
            int* rightVals = new int[2];
            rightVals[0] = i + 1;
            rightVals[1] = end;
            stack.push(rightVals);
        }
    }
    // no additional delete needed: every pushed array is deleted after pop
    // if(start>= end) return;
    // int i = start - 1;
    // int j = end;
    // int pivot = arr[end];
    // for(;;){
    //     while(arr[++i] < pivot);
    //     while(arr[--j] > pivot);
    //     if(i >= j)break;
    //     swap(arr[i], arr[j]);
    // }
    // swap(arr[i], arr[end]);

    // quickSort(arr, start, i -1);
    // quickSort(arr, i +1, end);
}
#endif