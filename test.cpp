
#include <iostream>
#include "SortingAlgorithms.h"

int main(){
    int *arr = new int[10];
    for(int i = 0; i < 10; i++) arr[i] = 10-i;
    mergeSort(arr, 10);
    for(int i = 0; i < 10; i++) cout << arr[i]<< ", " << endl;
    delete arr;
}