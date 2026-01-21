#include <iostream>
#include "arrayTrees/AVLTree.h"

using namespace std;

int main() {

    AVLTree<int> tree;

    // =========================
    // PRUEBA DE INSERCIÓN
    // =========================
    int values[] = {10, 20, 30, 15, 25, 5, 1, 8};
    int n = sizeof(values) / sizeof(values[0]);

    cout << "Insertando valores:\n";
    for(int i = 0; i < n; i++){
        cout << values[i] << " ";
        tree.add(values[i]);
    }
    cout << "\n\n";

    // =========================
    // RECORRIDOS
    // =========================
    tree.displayInOrder();
    tree.displayPreOrder();
    tree.displayPostOrder();

    // =========================
    // PRUEBA DE ELIMINACIÓN
    // =========================
    int toRemove[] = {1, 20, 10};
    int r = sizeof(toRemove) / sizeof(toRemove[0]);

    for(int i = 0; i < r; i++){
        cout << "Eliminando: " << toRemove[i] << endl;
        tree.remove(toRemove[i]);

        tree.displayInOrder();
        cout << "\n\n";
    }

    // =========================
    // PRUEBA FINAL
    // =========================
    cout << "Inserciones finales:\n";
    tree.add(50);
    tree.add(60);
    tree.add(55);

    tree.displayInOrder();

    return 0;
}
