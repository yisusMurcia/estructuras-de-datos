
#include <iostream>
#include "AVLTree.h"

using namespace std;

int main() {

    AVLTree<int> tree;
    int* arr;

    // ===============================
    // INSERCIONES
    // ===============================

    tree.add(30);
    tree.add(20);
    tree.add(40);
    tree.add(10);
    tree.add(25);
    tree.add(35);
    tree.add(50);

    /*
        Árbol esperado (balanceado):

                30
              /    \
            20      40
           /  \    /  \
         10   25  35   50

        InOrder esperado:
        10 20 25 30 35 40 50
    */

    cout << "InOrder inicial: ";
    arr = tree.getTreeInorden();
    for(int i = 0; i < tree.getSize(); i++){
        cout << arr[i] << ", ";
    }
    cout << endl;


    // ===============================
    // ELIMINAR HOJA
    // ===============================

    tree.remove(10);

    /*
        Eliminar hoja 10

                30
              /    \
            20      40
              \    /  \
              25  35   50

        No requiere rotación
        InOrder esperado:
        20 25 30 35 40 50
    */

    cout << "Después de eliminar 10: ";
    arr = tree.getTreeInorden();
    for(int i = 0; i < tree.getSize(); i++){
        cout << arr[i] << ", ";
    }
    cout << endl;


    // ===============================
    // ELIMINAR NODO CON UN HIJO
    // ===============================

    tree.remove(20);

    /*
        20 tiene solo hijo derecho (25)

                30
              /    \
            25      40
                   /  \
                 35   50

        No requiere rotación
        InOrder esperado:
        25 30 35 40 50
    */

    cout << "Después de eliminar 20: ";
    arr = tree.getTreeInorden();
    for(int i = 0; i < tree.getSize(); i++){
        cout << arr[i] << ", ";
    }
    cout << endl;


    // ===============================
    // ELIMINAR NODO CON DOS HIJOS
    // ===============================

    tree.remove(40);

    /*
        40 tiene dos hijos (35 y 50)
        Se reemplaza por sucesor inorder (50)

                30
              /    \
            25      50
                   /
                 35

        Puede requerir balanceo
        InOrder esperado:
        25 30 35 50
    */

    cout << "Después de eliminar 40: ";
    arr = tree.getTreeInorden();
    for(int i = 0; i < tree.getSize(); i++){
        cout << arr[i] << ", ";
    }
    cout << endl;


    // ===============================
    // ELIMINAR PARA FORZAR ROTACIÓN
    // ===============================

    tree.remove(50);

    /*
        Eliminar 50 provoca desbalance:

            30
           /
         25
           \
           35   (dependiendo de rotaciones previas)

        Se debe aplicar rotación
        Árbol balanceado esperado

        InOrder esperado:
        25 30 35
    */

    cout << "Después de eliminar 50: ";
    arr = tree.getTreeInorden();
    for(int i = 0; i < tree.getSize(); i++){
        cout << arr[i] << ", ";
    }
    cout << endl;


    // ===============================
    // ELIMINAR RAÍZ
    // ===============================

    tree.remove(30);

    /*
        Eliminar raíz

        Árbol final balanceado
        InOrder esperado:
        25 35
    */

    cout << "Después de eliminar 30: ";
    arr = tree.getTreeInorden();
    for(int i = 0; i < tree.getSize(); i++){
        cout << arr[i] << ", ";
    }
    cout << endl;


    return 0;
}