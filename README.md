# Data structures

In this repo you´ll find some useful data structures, here are the structures and methods implemented:

# [List](list.h)

A simple dinamyc list, it uses a template (T) for have more versatility, here are the allowed methods:
- Empty constructor and a destructor.
- getSize(): Return the amount of items in the list.
- isEmpty()
- pushFront(T): Add an item at the front of the list.
- popFront(): Delete the first item ind the list, and return if the operation was succesfull.

⚠️The next methods are not efficient as the methods displayed above.

- PushBack(T): add an item at the end of the list
- PopBack(): Remove the item at the end of the list and return, return a boolean indicating if the operation was succesfull.

⚠️The next methods are more inefficient in comparation to the methods displayed above.

- addAtIndex(int, T): Add an item in the given index.
- removeAtIndex(int): Remove the item in the given index, return a boolean indicating if the operation was succesfull.
- Operator [index]: Access the item in the given index

# [DoubleLinkList](doubleLinkedList.h)
A more complex dinamyc list, it's usefull for manage data when is important to know the item bofore other, here are the methods:

- Empty constructor and a destructor.
- getSize(): Return the amount of items in the list.
- isEmpty()
- pushFront(T): Add an item at the front of the list.
- popFront(): Delete the first item ind the list, and return if the operation was succesfull.
- PushBack(T): add an item at the end of the list
- PopBack(): Remove the item at the end of the list and return, return a boolean indicating if the operation was succesfull.

⚠️The next methods are not efficient as the methods displayed above, the index search is optimized in base if the index is nearest to the beginning or the end:

- addAtIndex(int, T): Add an item in the given index.
- removeAtIndex(int): Remove the item in the given index, return a boolean indicating if the operation was succesfull.
- Operator [index]: Access the item in the given index

# [Stack](stack.h)
LIFO (Last in, first out)

- pop(): return the last element added and remove it from the stack.
- push(t): add the item to the stack
- isEmpty(): You know what it returns
- peek(): return the last item added without remove it.
- emptyStack()

# [Queue](queue.h)
FIFO (First in, first out)

- add(t): add an item to the queue.
- attend(): return the first item added and removes fron the queue.
- isEmpty(): You know what it returns

# [OrderList](orderList.h)
Create a list were the items are order (you can change the order in the add function)

- add(t) Insert an item in the given position
- remove(t) Look for the item in the list, if it appears in the list it's deleted, return a boolean indicating the success of the operation

# [Dequeue](deque.h)
Also known as a double linked queue, this structures work as a queue but the values can be added in the front or in the back, so there are the methods.
- pushFront(val)
- pushBack(val)
- front() : return the value in the front
- bakc() : return the value in the back
- popFront() : return the value and also remove it
- popBack() : return the value and also remove it
- clean() : Removes all the values
- isEmpty()
- getSize

# Tree
Binary trees implementations with the following methods

- add(t): Insert an item
- remove(t): Look for the item in the tree, if it appears in,  it's deleted, return a boolean indicating the success of the operation.
- getSize()

Also these has their own methos for display/get the items in the next order:
- Inorder
- Posorder
- Preorder
This methods work with a stack and also some of this use a queue too, so make sure you included in your program

Here are the tree incuded in this library:
 - Binary tree: The classic one, use it when you have all the data in order.
 - AVL tree: Perfect for the most efficient searches but the adding and remove methods has a more complex process balancing the tree, so make sure you priorize search over tree modifications when you implement this tree.
 - Red black tree: Optimizated in cases where the tree add and removes nodes frecuently, this kind of tree balance the tree less often than the AVL implementation without affect the searc complexity, it's the perfect balance between add/remove and search.

## [Dinamic implementations](dinamicTrees)
This implemententions simulate a real binary tree with the correspondient atributtes, use these implementations for simulate in principal memory a tree and his values

## [Array implementations](arrayTrees)
Why use an static implementation in tree?
Becouse with an array implementation you can save the tree in persistence.

Each element of the array is a node in tree, the node has a value and two ints that indicates the left and right child.

### Where is the root?
Simple, the arr[0] indicates where is it, the leftChild indicates the root position, the right child indicates a free node

### Free nodes

The free nodes work as a queue, each free node has as a right child onether free node, every one instead of the last free node, his right child is the control position (arr[0])



# [Sorting algorithms](SortingAlgorithms.h)
In this library you can find some of the most efficients sorting algorithms, these algorithms take an array (or any other data struct if the  operator [] is defined) and modify this structure, don´t return a new one.

- QuickSort: One of the most efficients sorting algorithms, this implementation doesn't use recursion, it uses a stack.
- MergSort: Useful when you work with a semi-ordered array or when the structure may have the worst case posible.
- Insertion: Useful when the list is almost in order or when the length is less than 32.
- Shell sort: Useful when the data number is medium, between 20 and 5000.