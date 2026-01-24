#include <iostream>
#include "dinamicTrees/heap.h"

using namespace std;

int main() {

    cout << "==========================================\n";
    cout << "   DYNAMIC HEAP COMPREHENSIVE TEST\n";
    cout << "==========================================\n\n";

    // Test 1: Constructor and isEmpty
    cout << "Test 1: Constructor and isEmpty()\n";
    cout << "-----------------------------------\n";
    Heap<int> heap;
    cout << "Created empty heap\n";
    cout << "isEmpty(): " << (heap.isEmpty() ? "true" : "false") << endl;
    cout << "getSize(): " << heap.getSize() << "\n\n";

    // Test 2: Constructor with single value
    cout << "Test 2: Constructor with single value\n";
    cout << "-----------------------------------\n";
    Heap<int> heap2(50);
    cout << "Created heap with value 50\n";
    cout << "isEmpty(): " << (heap2.isEmpty() ? "true" : "false") << endl;
    cout << "getSize(): " << heap2.getSize() << "\n\n";

    // Test 3: Single add() operation
    cout << "Test 3: Single add() operation\n";
    cout << "-----------------------------------\n";
    heap.add(50);
    cout << "add(50) - Size: " << heap.getSize() << endl;
    cout << "isEmpty(): " << (heap.isEmpty() ? "true" : "false") << "\n\n";

    // Test 4: Multiple adds - building max heap
    cout << "Test 4: Multiple add() operations\n";
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
    cout << "add(16) - Size: " << heap.getSize() << endl;
    
    heap.add(70);
    cout << "add(70) - Size: " << heap.getSize() << endl;
    cout << "Elements added: 50, 30, 20, 15, 10, 8, 16, 70\n";

    // Test 5: Adding value that should bubble to top (if bubble-up was implemented)
    cout << "Test 5: Adding large value (should bubble if implemented)\n";
    cout << "-----------------------------------\n";
    cout << "Current size: " << heap.getSize() << endl;
    heap.add(100);
    cout << "add(100) - Size: " << heap.getSize() << endl;

    // Test 6: pop() operation - single pop
    cout << "Test 6: pop() operation\n";
    cout << "-----------------------------------\n";
    cout << "Current size before pop: " << heap.getSize() << endl;
    try {
        int popped = heap.pop();
        cout << "pop() returns: " << popped << endl;
        cout << "Size after pop: " << heap.getSize() << "\n\n";
    } catch (const char* e) {
        cout << "Exception caught: " << e << "\n\n";
    }

    // Test 7: Multiple pops - verify max heap property
    cout << "Test 7: Multiple pops - verify max heap property\n";
    cout << "-----------------------------------\n";
    cout << "Current size: " << heap.getSize() << endl;
    cout << "Popping all elements:\n";
    int prevVal = INT_MAX;
    int popCount = 0;
    while (heap.getSize() > 0) {
        try {
            int val = heap.pop();
            cout << "pop() #" << (++popCount) << ": " << val << " | Remaining size: " << heap.getSize();
            if (val > prevVal) {
                cout << " [ERROR: Heap property violated!]";
            }
            cout << endl;
            prevVal = val;
        } catch (const char* e) {
            cout << "Exception: " << e << endl;
            break;
        }
    }
    cout << "\n";

    // Test 8: Exception handling - pop on empty heap
    cout << "Test 8: Exception handling - pop on empty heap\n";
    cout << "-----------------------------------\n";
    try {
        heap.pop();
        cout << "ERROR: Should have thrown exception!\n";
    } catch (const char* e) {
        cout << "Caught expected exception: " << e << "\n\n";
    }

    // Test 9: Stress test with many elements
    cout << "Test 9: Stress test with 15 elements\n";
    cout << "-----------------------------------\n";
    Heap<int> heap3;
    int testValues[] = {45, 23, 67, 12, 89, 34, 56, 78, 90, 11, 
                        22, 33, 44, 55, 66};
    
    cout << "Adding elements: ";
    for (int i = 0; i < 15; i++) {
        heap3.add(testValues[i]);
        cout << testValues[i] << " ";
    }
    cout << "\nSize after adding: " << heap3.getSize() << endl;
    cout << "Popping all:\n";
    
    prevVal = INT_MAX;
    popCount = 0;
    while (heap3.getSize() > 0) {
        try {
            int val = heap3.pop();
            cout << val << " ";
            if (val > prevVal) {
                cout << "[ERROR] ";
            }
            prevVal = val;
            popCount++;
        } catch (const char* e) {
            cout << "\nException: " << e << endl;
            break;
        }
    }
    cout << "\nTotal elements popped: " << popCount << "\n\n";

    // Test 10: Heap with double type
    cout << "Test 10: Heap with double type\n";
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
        try {
            cout << doubleHeap.pop() << " ";
        } catch (const char* e) {
            cout << "\nException: " << e << endl;
            break;
        }
    }
    cout << "\n(expected descending order if heap property maintained)\n\n";

    // Test 11: Tree structure test (perfect binary tree)
    cout << "Test 11: Perfect binary tree structure (7 elements)\n";
    cout << "-----------------------------------\n";
    Heap<int> perfectHeap;
    for (int i = 7; i >= 1; i--) {
        perfectHeap.add(i);
    }
    cout << "Added elements 7, 6, 5, 4, 3, 2, 1\n";
    cout << "Size: " << perfectHeap.getSize() << endl;
    cout << "Popping all:\n";
    while (perfectHeap.getSize() > 0) {
        try {
            cout << perfectHeap.pop() << " ";
        } catch (const char* e) {
            cout << "\nException: " << e << endl;
            break;
        }
    }
    cout << "\n\n";

    cout << "==========================================\n";
    cout << "        ALL TESTS COMPLETED\n";

    return 0;
}