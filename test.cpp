
#include <iostream>
#include "quickSort.h"

int main(){
    int *arr = new int[10];
    for(int i = 0; i < 10; i++) arr[i] = 100-i;
    quickSort(arr, 0, 9);
    for(int i = 0; i < 10; i++) cout << arr[i]<< ", " << endl;
    delete arr;
}