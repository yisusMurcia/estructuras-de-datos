#include <iostream>
#include "deque.h"

using namespace std;

int main() {

    cout << "==========================================\n";
    cout << "        DEQUE COMPREHENSIVE TEST\n";
    cout << "==========================================\n\n";

    // Test 1: Constructor and isEmpty
    cout << "Test 1: Constructor and isEmpty()\n";
    cout << "-----------------------------------\n";
    Deque<int> deque;
    cout << "Created empty deque\n";
    cout << "isEmpty(): " << (deque.isEmpty() ? "true" : "false") << endl;
    cout << "getSize(): " << deque.getSize() << "\n\n";

    // Test 2: pushFront and pushBack
    cout << "Test 2: pushFront() and pushBack()\n";
    cout << "-----------------------------------\n";
    deque.pushFront(10);
    cout << "pushFront(10) - Size: " << deque.getSize() << endl;
    
    deque.pushBack(20);
    cout << "pushBack(20) - Size: " << deque.getSize() << endl;
    
    deque.pushFront(5);
    cout << "pushFront(5) - Size: " << deque.getSize() << endl;
    
    deque.pushBack(30);
    cout << "pushBack(30) - Size: " << deque.getSize() << "\n";
    
    deque.pushFront(1);
    cout << "pushFront(1) - Size: " << deque.getSize() << "\n";
    
    deque.pushBack(40);
    cout << "pushBack(40) - Size: " << deque.getSize() << "\n\n";

    // Test 3: front() and back()
    cout << "Test 3: front() and back()\n";
    cout << "-----------------------------------\n";
    cout << "front() value: " << deque.front() << endl;
    cout << "back() value: " << deque.back() << "\n\n";

    // Test 4: popFront()
    cout << "Test 4: popFront()\n";
    cout << "-----------------------------------\n";
    cout << "Current size: " << deque.getSize() << endl;
    cout << "popFront() returns: " << deque.popFront() << endl;
    cout << "Size after pop: " << deque.getSize() << endl;
    cout << "New front() value: " << deque.front() << "\n\n";

    // Test 5: popBack()
    cout << "Test 5: popBack()\n";
    cout << "-----------------------------------\n";
    cout << "Current size: " << deque.getSize() << endl;
    cout << "popBack() returns: " << deque.popBack() << endl;
    cout << "Size after pop: " << deque.getSize() << endl;
    cout << "New back() value: " << deque.back() << "\n\n";

    // Test 6: Multiple operations
    cout << "Test 6: Multiple push/pop operations\n";
    cout << "-----------------------------------\n";
    deque.pushFront(100);
    deque.pushFront(200);
    deque.pushBack(50);
    cout << "After pushFront(100), pushFront(200), pushBack(50):\n";
    cout << "Size: " << deque.getSize() << endl;
    cout << "front(): " << deque.front() << endl;
    cout << "back(): " << deque.back() << "\n\n";

    // Test 7: clean()
    cout << "Test 7: clean()\n";
    cout << "-----------------------------------\n";
    cout << "Size before clean: " << deque.getSize() << endl;
    deque.clean();
    cout << "Size after clean: " << deque.getSize() << endl;
    cout << "isEmpty(): " << (deque.isEmpty() ? "true" : "false") << "\n\n";

    // Test 8: Exception handling - popFront on empty deque
    cout << "Test 8: Exception handling - popFront on empty deque\n";
    cout << "-----------------------------------\n";
    try {
        deque.popFront();
        cout << "ERROR: Should have thrown exception!\n";
    } catch (const std::out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << "\n\n";
    }

    // Test 9: Exception handling - popBack on empty deque
    cout << "Test 9: Exception handling - popBack on empty deque\n";
    cout << "-----------------------------------\n";
    try {
        deque.popBack();
        cout << "ERROR: Should have thrown exception!\n";
    } catch (const std::out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << "\n\n";
    }

    // Test 10: Stress test with more elements
    cout << "Test 10: Stress test with multiple elements\n";
    cout << "-----------------------------------\n";
    for (int i = 1; i <= 5; i++) {
        deque.pushBack(i * 10);
    }
    cout << "After pushing 10, 20, 30, 40, 50 to back:\n";
    cout << "Size: " << deque.getSize() << endl;
    cout << "front(): " << deque.front() << endl;
    cout << "back(): " << deque.back() << "\n";
    
    cout << "Popping all elements:\n";
    while (deque.getSize() > 0) {
        cout << "popFront(): " << deque.popFront() << " | Size: " << deque.getSize() << endl;
    }
    cout << "\n\n";

    // Test 11: Test with string type
    cout << "Test 11: Deque with string type\n";
    cout << "-----------------------------------\n";
    Deque<string> stringDeque;
    stringDeque.pushBack("Hello");
    stringDeque.pushFront("World");
    stringDeque.pushBack("!");
    cout << "String deque front(): " << stringDeque.front() << endl;
    cout << "String deque back(): " << stringDeque.back() << endl;
    cout << "String deque size: " << stringDeque.getSize() << "\n\n";

    cout << "==========================================\n";
    cout << "         ALL TESTS COMPLETED\n";
    cout << "==========================================\n";

    return 0;
}
