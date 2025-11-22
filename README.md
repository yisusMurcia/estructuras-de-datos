# Data structures

In this repo you´ll find some useful data structures, here are the structures and methods implemented:

## List

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

## DoubleLinkList
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

## Stack
LIFO (Last in, first out)

- pop(): return the last element added and remove it from the stack.
- push(t): add the item to the stack
- isEmpty(): You know what it returns
- peek(): return the last item added without remove it.
- emptyStack()

## Queue
FIFO (First in, first out)

- add(t): add an item to the queue.
- attend(): return the first item added and removes fron the queue.
- isEmpty(): You know what it returns

## OrderList
Create a list were the items are order (you can change the order in the add function)

- add(t) Insert an item in the given position
- remove(t) Look for the item in the list, if it appears in the list it´s deleted, return a boolean indicating the success of the operation

## Ordered binary tree

Creat an ordered tree optimizated for search, also it´s represented as an array, so take in count it has a limit.
- add(t): Insert an item
- remove(t): Look for the item in the tree, if it appears in,  it´s deleted, return a boolean indicating the success of the operation.

### Display data methods:
- displayByLevels()
- displayPostOrder()
- displayPreOrder()
- displayInOrder()

It also uses a stack and queue, so make sure to added when you'll use it. 