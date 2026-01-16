
#include <iostream>
#include "binaryTree.h"

using namespace std;

int main(){
    Tree<int> tree;
    tree.add(10);
    tree.add(12);
    tree.add(5);

    int* arr = tree.getTreeInorden();
    for(int i = 0; i < 3; i++) cout << arr[i] << ", ";
    cout << endl;

    arr = tree.getTreePostOrden();
    for(int i = 0; i < 3; i++) cout << arr[i] << ", ";
    cout << endl;

    arr = tree.getTreePreorden();
    for(int i = 0; i < 3; i++) cout << arr[i] << ", ";
    cout << endl;

    tree.remove(10);

    arr = tree.getTreePreorden();
    for(int i = 0; i < 2; i++) cout << arr[i] << ", ";
    cout << endl;
}