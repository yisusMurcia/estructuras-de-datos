#include <iostream>
#include "arrayTrees/heap.h"

using namespace std;

int main() {

    cout << "==========================================\n";
    cout << "        HEAP COMPREHENSIVE TEST\n";
    cout << "==========================================\n\n";

    // Test 1: Constructor and isEmpty
    cout << "Test 1: Constructor and getSize()\n";
    cout << "-----------------------------------\n";
    Heap<int> heap;
    cout << "Created empty heap\n";
    cout << "getSize(): " << heap.getSize() << "\n\n";

    // Test 2: Single add() operation
    cout << "Test 2: Single add() operation\n";
    cout << "-----------------------------------\n";
    heap.add(50);
    cout << "add(50) - Size: " << heap.getSize() << endl;
    cout << "Expected root: 50\n\n";

    // Test 3: Multiple adds - building max heap
    cout << "Test 3: Multiple add() operations\n";
    cout << "-----------------------------------\n";
    heap.add(30);
    cout << "add(30) - Size: " << heap.getSize() << endl;
    
    heap.add(20);
    cout << "add(20) - Size: " << heap.getSize() << endl;
    
    heap.add(15);
    cout << "add(15) - Size: " << heap.getSize() << endl;
    
    heap.add(10);
    cout << "add(10) - Size: " << heap.getSize() << endl;
    
    heap.add(8);
    cout << "add(8) - Size: " << heap.getSize() << endl;
    
    heap.add(16);
    cout << "add(16) - Size: " << heap.getSize() << "\n";
    
    heap.add(70);
    cout << "add(70) - Size: " << heap.getSize() << endl;
    cout << "Elements added: 50, 30, 20, 15, 10, 8, 16, 70\n\n";

    // Test 4: Adding value that bubbles to top
    cout << "Test 4: Adding value that should bubble to top\n";
    cout << "-----------------------------------\n";
    cout << "Current size: " << heap.getSize() << endl;
    heap.add(100);
    cout << "add(100) - Size: " << heap.getSize() << endl;
    cout << "Expected: 100 should be the new max at root\n\n";

    // Test 5: pop() operation - single pop
    cout << "Test 5: pop() operation\n";
    cout << "-----------------------------------\n";
    cout << "Current size before pop: " << heap.getSize() << endl;
    int popped = heap.pop();
    cout << "pop() returns: " << popped << " (expected: 100)\n";
    cout << "Size after pop: " << heap.getSize() << "\n\n";

    // Test 6: Multiple pops - verify max heap property
    cout << "Test 6: Multiple pops - verify max heap property\n";
    cout << "-----------------------------------\n";
    cout << "Current size: " << heap.getSize() << endl;
    cout << "Popping all elements (should be in descending order):\n";
    int prevVal = INT_MAX;
    int popCount = 0;
    while (heap.getSize() > 0) {
        int val = heap.pop();
        cout << "pop() #" << (++popCount) << ": " << val << " | Remaining size: " << heap.getSize();
        if (val > prevVal) {
            cout << " [ERROR: Heap property violated!]";
        }
        cout << endl;
        prevVal = val;
    }
    cout << "\n";

    // Test 7: Exception handling - pop on empty heap
    cout << "Test 7: Exception handling - pop on empty heap\n";
    cout << "-----------------------------------\n";
    try {
        heap.pop();
        cout << "ERROR: Should have thrown exception!\n";
    } catch (const char* e) {
        cout << "Caught expected exception: " << e << "\n\n";
    }

    // Test 8: Stress test with many elements
    cout << "Test 8: Stress test with 20 random elements\n";
    cout << "-----------------------------------\n";
    Heap<int> heap2;
    int testValues[] = {45, 23, 67, 12, 89, 34, 56, 78, 90, 11, 
                        22, 33, 44, 55, 66, 77, 88, 99, 21, 43};
    
    cout << "Adding elements: ";
    for (int i = 0; i < 20; i++) {
        heap2.add(testValues[i]);
        cout << testValues[i] << " ";
    }
    cout << "\nSize after adding: " << heap2.getSize() << endl;
    cout << "Popping all (should be in descending order):\n";
    
    prevVal = INT_MAX;
    popCount = 0;
    while (heap2.getSize() > 0) {
        int val = heap2.pop();
        cout << val << " ";
        if (val > prevVal) {
            cout << "[ERROR] ";
        }
        prevVal = val;
        popCount++;
    }
    cout << "\nTotal elements popped: " << popCount << "\n\n";

    // Test 9: Heap with double type
    cout << "Test 9: Heap with double type\n";
    cout << "-----------------------------------\n";
    Heap<double> doubleHeap;
    doubleHeap.add(3.14);
    doubleHeap.add(2.71);
    doubleHeap.add(1.41);
    doubleHeap.add(5.0);
    doubleHeap.add(2.5);
    cout << "Added: 3.14, 2.71, 1.41, 5.0, 2.5\n";
    cout << "Size: " << doubleHeap.getSize() << endl;
    cout << "Popping all:\n";
    while (doubleHeap.getSize() > 0) {
        cout << doubleHeap.pop() << " ";
    }
    cout << "\n(expected descending order)\n\n";

    // Test 10: Custom size heap
    cout << "Test 10: Custom size heap (length=10)\n";
    cout << "-----------------------------------\n";
    Heap<int> smallHeap(10);
    for (int i = 1; i <= 10; i++) {
        smallHeap.add(i * 5);
    }
    cout << "Added 10 elements (5, 10, 15, ..., 50) to heap with capacity 10\n";
    cout << "Size: " << smallHeap.getSize() << endl;
    cout << "Popping all:\n";
    while (smallHeap.getSize() > 0) {
        cout << smallHeap.pop() << " ";
    }
    cout << "\n\n";

    cout << "==========================================\n";
    cout << "         ALL TESTS COMPLETED\n";
    cout << "==========================================\n";

    return 0;
}
