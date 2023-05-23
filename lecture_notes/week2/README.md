## Week 2 Note

- [singly_linked_list0.cpp](singly_linked_list0.cpp) shows how to construct a
  specific 3-element linked list. Good review/overview of pointers, structs, and
  new/delete.

- [singly_linked_list1.cpp](singly_linked_list1.cpp) shows how to implement a
  singly-linked list using functions to basic operaitons. The `head` pointer is
  a global variable.

- [singly_linked_list2.cpp](singly_linked_list2.cpp) shows how to implement a
  singly-linked list using a class: the code from
  [singly_linked_list1.cpp](singly_linked_list1.cpp) is encapsulated into a
  class. The `head` variable and `Node` struct are private members of the class
  so that only code in the class can access them.

  Importantly, the `~List()` destructor is used to automatically de-allocate the
  list nodes when the `List` object goes out of scope, or is deleted. This
  prevents memory leaks and double deletions.

  The resulting code in `main` is simple and easy to use. The user of the `List`
  class doesn't need to know anything about the implementation, i.e. they don't
  need to know about points, or nodes, or new/delete.
