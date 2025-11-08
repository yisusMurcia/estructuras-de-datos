# Data structures

In this repo you´ll find some useful data structures, here are the structures and methods implemented:

## List

A simple dinamyc list, it uses a template (T) for have more versatility, here are the allowed methods:
- Empty constructor and a destructor.
- PushBack(T): add an item at the end of the list
- PopBack(): Remove the item at the end of the list and return, return a boolean indicating if the operation was succesfull.
- getSize(): Return the amount of items in the list.
- isEmpty()
- pushFront(T): Add an item at the front of the list.
- popFront(): Delete the first item ind the list, and return if the operation was succesfull.
:warning: The next methods are not efficient as the methods displayed above,
- addAtIndex(int, T): Add an item in the given index.
- removeAtIndex(int): Remove the item in the given index, return a boolean indicating if the operation was succesfull.
- Operator [index]: Access the item in the given index