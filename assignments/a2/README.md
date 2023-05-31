## Assignment 2: An Undoable List
 
> The undoing is always more difficult than the doing. -- *Kate DiCamillo*

In this assignment, your task is to add an *undo* feature to a list of strings.

To start, here's a working class called [Stringlist](Stringlist.h) that
implements a simple string list as a dynamic array.
[Stringlist_test.cpp](Stringlist_test.cpp) has tests for all the methods in
[Stringlist](Stringlist.h).

`Stringlist` has one unimplemented method:

```cpp
  //
  // Undoes the last operation that modified the list. Returns true if a
  // change was undone, false otherwise.
  //
  bool undo()
  {
      cout << "Stringlist::undo: not yet implemented\n";
      return false;
  }
```

Your job is to implement `undo`, thus making `Stringlist` an *undoable* list.

Your implementation must follow these rules:

- Do **not** delete any methods, or change the *signatures* of any methods, in
  [Stringlist](Stringlist.h). You **can** change the *implementation* of
  existing methods if necessary. But they should still work the same way: **your
  finished version of `Stringlist` with `undo` implement must still pass all the
  tests in [Stringlist_test.cpp](Stringlist_test.cpp)**.
- You **can** add other helper methods (public or private), functions, and
  classes/structs to [Stringlist.h](Stringlist.h) if you need them.
- You **must** implement `undo()` using a *private stack* that is accessible
  only inside the `Stringlist` class. **Implement the stack yourself as a linked
  list**. Do **not** use arrays, vectors, or any other data structure for your
  stack.
- Do **not** use any other #includes or #pragmas in [Stringlist.h](Stringlist.h)
  other than the ones already there.

When it's done, you'll be able to write code like this:

```cpp
#include "Stringlist.h"
#include <iostream>

using namespace std;

int main() {
    Stringlist lst;
    cout << lst << endl; // {}

    lst.add("one");
    lst.add("two");
    lst.add("three");
    cout << lst << endl; // {"one", "two", "three"}

    lst.undo();
    cout << lst << endl; // {"one", "two"}

    lst.undo();
    cout << lst << endl; // {"one"}

    lst.undo();
    cout << lst << endl; // {}
}
```

## Getting Started with `StringList`

To start, 
[download all the files for this assignment](https://github.com/tjd1234/cmpt225summer2023/tree/main/assignments/a2)
to your computer, and then compile and run
[Stringlist_test.cpp](Stringlist_test.cpp) to make sure it runs without error:

```bash
> make Stringlist_test
g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g Stringlist_test.cpp -o Stringlist_test

> valgrind ./Stringlist_test
... test output ...
```

Running your program with `valgrind` is important, since it will help you find
memory leaks, and other memory-related errors.

> **Note** There should be *no* errors when you run this testing! If you have
> any, double-check that you are running exactly the correct file, and using the
> correct compiler version, correct options, and correct [makefile](makefile).

## Designing the Undo Stack

As mentioned above, you must implement `undo()` using at least one *private
stack* implemented as a linked list inside the `Stringlist` class. You can
modify `Stringlist` only as described at the start of this assignment.

One idea for how undo can work is that every time `Stringlist` is modified by
one of its methods, it *pushes* the *inverse* operation on the top of an undo
stack. When `undo()` is called, it *pops* the top of the stack and applies that
operation to the list, thus undoing the most recent operation.

**Important** All the methods in [Stringlist](Stringlist.h) marked "undoable"
should work with `undo()`. `undo()` cannot be undone: there is no "re-do"
feature in this assignment.

Here are some examples of how specific methods should work.

### Undoing `insert_before`

Suppose `lst` is `{"dog", "cat", "tree"}`, and you call `lst.insert_before(3,
"hat")`, making it `{"dog", "cat", "tree", "hat"}`. It should push the operation
*remove string at index 3* on the undo stack. You could store it as a short
`string` command, e.g. `REMOVE 3`. If you now call `lst.undo()`, the `REMOVE 3`
command on top of the stack is popped and applied to the list, e.g. the string
at index 3 is removed, leaving the list in the state it was in before calling
`insert_before`: `{"dog", "cat", "tree"}`.

In code:

```cpp
// lst == {"dog", "cat", "tree"}

lst.insert_before(3, "hat");
// lst == {"dog", "cat", "tree", "hat"}

lst.undo();
// lst == {"dog", "cat", "tree"}

lst.insert_before(1, "shoe");
// lst == {"dog", "shoe", "cat", "tree"}

lst.undo();
// lst == {"dog", "cat", "tree"}
```

### Undoing `set`

For `set`, suppose that `lst` is `{"yellow", "green", "red", "orange"}`, and so
`lst.get(2)` returns `"red"`. If you call `lst.set(2, "cow")`, then you should
push the operation *set location 2 to `"red"`* onto the undo stack, and then
over-write location 2 with `"cow"`. You could format the operation like `"SET 2
red"`. Calling `lst.undo()` pops the top command of the stack and applies it to
the list, e.g. the string at index 2 is set to `"red"` and the list is in the
state it was in before calling `set`: `{"yellow", "green", "red", "orange"}`.

In code:

```cpp
// lst == {"yellow", "green", "red", "orange"}

lst.set(2, "cow");
// lst == {"yellow", "green", "cow", "orange"}

lst.undo();
// lst == {"yellow", "green", "red", "orange"}
```

### Undoing `remove_at`

For `remove_at`, suppose `lst` is `{"dog", "cat", "tree"}`. If you call
`lst.remove_at(1)`, you should then push the operation *insert `"cat"` at index
1* onto the stack, and then remove the string at index 1 so it becomes `{"dog",
"cat", "tree"}`. You could format the operation as `"INSERT 1 cat"`. If you now
call `lst.undo()`, the command on top of the stack is popped and applied to the
list, e.g. the string `"cat"` is inserted at index 1, and the list is in the
state it was in before calling `remove_at`: `{"dog", "cat", "tree"}`.

In code:

```cpp
// lst == {"dog", "cat", "tree"}

lst.remove_at(1);
// lst == {"dog", "tree"}

lst.undo();
// lst == {"dog", "cat", "tree"}
```


### Undoing `operator=`

For `operator=`, suppose `lst1` is `{"dog", "cat", "tree"}`, and `lst2` is
`{"yellow", "green", "red", "orange"}`. If you call `lst1 = lst2;`, then you
should push the command *set `lst1` to `{"dog", "cat", "tree"}`* onto the stack,
and then assign `lst1` to `lst2`. You could format the command as `"SET lst1 dog
cat tree"`. Calling `lst1.undo()` pops the command on top of the stack and
applies it to the list, e.g. `lst1` is set to the state it was in before calling
`operator=`: `{"dog", "cat", "tree"}`.

In code:

```cpp
// lst1 == {"dog", "cat", "tree"}
// lst2 == {"yellow", "green", "red", "orange"}

lst1 = lst2;
// lst1 == {"yellow", "green", "red", "orange"}
// lst2 == {"yellow", "green", "red", "orange"}

lst1.undo();
// lst1 == {"dog", "cat", "tree"}
// lst2 == {"yellow", "green", "red", "orange"}
```

As this shows, when you undo `operator=`, the *entire* list of strings is
restored in *one* call to `undo()`.

**Important** notes:

- If `lst1` and `lst2` are different objects, then when `lst2` is assigned to
  `lst1` just the underlying string array of `lst2` is copied to `lst1`. The
  `lst1` undo stack is updated so that it can undo the assignment. The undo
  stack of `lst2` is *not* copied, and `lst2` is not modified in any away.

- *Self-assignment* is when you assign a list to itself, e.g. `lst1 = lst1;`. In
  this case, *nothing* happens to `lst1`. Both its string data and undo stack
  are left as-is.

### Undoing `remove_all`

For `remove_all`, suppose `lst` is `{"dog", "cat", "tree"}`. If you call
`lst.remove_all()`, then you should push the operation *set `lst1` to `{"dog",
"cat", "tree"}`* onto the stack, and then remove all the strings from `lst`
(i.e. its size is 0). You could format the command as `"SET lst1 dog cat tree"`.
Calling `lst1.undo()` pops the command on top of the stack and applies it to the
list, e.g. `lst` is set to `{"dog", "cat", "tree"}` and the list is in the state
it was in before calling `remove_all`: `{"dog", "cat", "tree"}`.

In code:

```cpp
// lst == {"dog", "cat", "tree"}

lst.remove_all();
// lst == {}

lst.undo();
// lst == {"dog", "cat", "tree"}
```

Note that it should work the same way when `lst` is empty:

```cpp  
// lst == {}

lst.remove_all();
// lst == {}

lst.undo();
// lst == {}
```

### Undoing Other Methods

`undo()` should undo all the other methods in [Stringlist](Stringlist.h) that
are marked as "undoable" in the source code comments.

As mentioned above, `undo()` is *not* undoable. There is no "re-do" feature in
this assignment.


### Testing Your Code

It's important to test your code as you go. In [a2_test.cpp](a2_test.cpp), write
code to test your `Stringlist` undo method. Compile and run it like this:
  
```bash 
❯ make a2_test
g++  -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a2_test.cpp   -o a2_test

> ./a2_test
... testing output ...
```

You should test *at least* the examples given above, plus every other function
that can be undone. Follow the testing style in
[Stringlist_test.cpp](Stringlist_test.cpp) and use `assert`s or `if`-statements
to test your code.


## What to Submit

When you're done, submit just your [Stringlist.h](Stringlist.h) on Canvas. Don't
submit anything else. 

## Grading

The marker will compile and run your program on Ubuntu Linux using
[makefile](makefile) and a command like this:

```bash
> make a2_test
g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g a2_test.cpp -o a2_test

> ./a2_test
... testing output ...

> valgrind ./a2_test
... valgrind output ...
```

If the marker can't compile your program, then you will get 0 marks for the
assignment.

The markers `a2_test.cpp` will contain their tests (that you have probably not
seen before) to check the correctness of you `Stringlist`. `a2_test.cpp` will
#include your [Stringlist.h](Stringlist.h), and it should run without needing
any other #includes in `a2_test.cpp` (all the #includes your `Stringlist` need
should be in your [Stringlist.h](Stringlist.h).

The marker will also run your [Stringlist.h](Stringlist.h) with
[Stringlist_test.cpp](Stringlist_test.cpp) to ensure that all the original
`Stringlist` functionality still works:

```bash
> make Stringlist_test
g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g Stringlist_test.cpp -o Stringlist_test

> ./Stringlist_test
... testing output ...
```

> **Note** The compilation commands are quite strict! Make sure your program
> compiles with them before submitting it.

## Marking Scheme

- **8 marks** One mark for each method in [Stringlist.h](Stringlist.h) marked
  "undoable" that works correctly with `undo()`. This also includes the correct
  behaviour for the `Stringlist` copy constructor (which should *not* copy the
  undo stack).
- **5 marks** The markers tests run correctly, including with no memory leaks
  according to `valgrind`.
- **5 marks** `Stringlist` passes all tests in
  [Stringlist_test.cpp](Stringlist_test.cpp).

### Overall source code readability: 5 marks

- All code is sensibly and consistently indented, and all lines are 100
  characters in length, or less.
- Whitespace is used to group related pieces of a code to make it easier for
  humans to read. All whitespace has a purpose.
- Variable and function names are self-descriptive.
- Appropriate features of C++ are used, as discussed in class and in the notes.
  **Note** If you use a feature that we haven't discussed in class, **you must
  explain it in a comment**, even if you think it's obvious.
- Comments are used when needed to explain code whose purpose is not obvious
  from the code itself. There should be *no* commented-out code from previous
  versions.

### Deductions

- **-5 marks** if your program does *not* compile with the given
  [makefile](makefile) and the `make` commands given in the assignment. **If the
  marker can't get your program to compile at all, then you will get a score of
  0 for the assignment**.
- **-5 marks** if you change the name of the file or class, or if you change the
  *signatures* of any give methods or functions. Each individual difference is
  -5 marks.
- **-10 marks** if you use arrays, vectors, or other containers to implement the
  private stack in `Stringlist`. You must use a linked list to implement the
  stack.
- up to **-3 marks** if you do not include your full name, email, and SFU ID in
  the header of your file.
- **a score of 0** if you don't include the "Statement of Originality", or it is
  modified in any way.
- **a score of 0** if you submit a "wrong" non-working file, and then *after the
  due date* submit the "right" file. If you can provide evidence that you
  finished the assignment on time, then it may be marked.
