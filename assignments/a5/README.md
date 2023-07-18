## Assignment 5: Word Lists Re-visited

In this assignment, your task is to re-implement the `Wordlist` class from
Assignment 1, this time using an **AVL tree** as its underlying representation.
Vectors, arrays, linked lists, or other container data structures are *not*
allowed.

Recall that the `Wordlist` class stores a count of how many time words appear in
a file.

When it's done, you'll be able to write code like this:

```cpp
Wordlist lst("tiny_shakespeare.txt");
lst.print_stats();
```

Which prints:

```
Number of different words: 25670
    Total number of words: 202651
       Most frequent word: the 5437
     Number of singletons: 14919 (58%)
```


## Getting Started

All the code you'll submit for this assignment goes in [Wordlist.h](Wordlist.h).
*Don't* put `main` in [Wordlist.h](Wordlist.h). Instead, put `main` in
[a5_main.cpp](a5_main.cpp), along with all the code you need to test your
`Wordlist` class. 

Be sure to thoroughly test your code before submitting it!
 
> **Note** You can download all the files for this assignment in a single .zip
> archive from the [Github repository for the course](https://github.com/tjd1234/cmpt225summer2023). 
> Click on the green "Code" button, and then click on "Download ZIP".


### Implement the Methods in Wordlist_base

[Wordlist.h](Wordlist.h) contains the class `Wordlist` where you should
implement all the virtual methods listed in the `Wordlist_base` class in
[Wordlist_base.h](Wordlist_base.h). 

Most of the methods in `Wordlist_base` are *virtual* and *abstract*, and so you
*must* write your own version of them in `Wordlist`. A couple of methods, such
as `print_stats`, are *not* `virtual` and have implementations that you *can't*
change, i.e. your `Wordlist` class must work correctly with them as given.

Do **not** change [Wordlist_base.h](Wordlist_base.h) in any way: keep it as-is.

Put your implementation of `Wordlist` in [Wordlist.h](Wordlist.h). It must
publicly inherit from `Wordlist_base`, and use the `Node` `struct` (given in
`Wordlist`) to implement an AVL tree.

> **Don't** use vectors, arrays, linked lists or any other container data
> structures in [Wordlist.h](Wordlist.h).


### Implement Constructors, and a Destructor

In addition to the methods listed in `Wordlist_base`, in `Wordlist` write a
*default constructor* that takes no parameters and creates an empty `Wordlist`
object:

```cpp
Wordlist lst;

// ... lst is an empty Wordlist object ...
```

Also, write a *constructor* that takes the name of a file as input, and adds all
the words in that file to the `Wordlist` object. Read the words from the file
using C++'s standard `<<` operator. When implemented, you'll be able to write
code like in the example above:

```cpp
Wordlist lst("tiny_shakespeare.txt");
lst.print_stats();
```

Write a destructor for `Wordlist` that de-allocates all the nodes in the list.
In `Wordlist_base`, the destructor is called `~Wordlist_base()`, and the one you
write for `Wordlist` should be called `~Wordlist()`.


### Testing Your Code

You can use the `test_read()` function in [a5_main.cpp](a5_main.cpp) to test
your code. For example, [small.txt](small.txt) contains the following text:

```
This is
a test
or is this 
a test?

```

When you run this code:

```cpp
// ...

void test_read()
{
    Wordlist lst;
    string w;
    while (cin >> w)
    {
        lst.add_word(w);
    }

    lst.print_words();
    cout << endl;
    lst.print_stats();
}

int main() 
{
    test_read();
}
```

The output is:

```
❯ ./a5_main < small.txt
1. {"This", 1}
2. {"a", 2}
3. {"is", 2}
4. {"or", 1}
5. {"test", 1}
6. {"test?", 1}
7. {"this", 1}

Number of different words: 7
    Total number of words: 9
       Most frequent word: a 2
     Number of singletons: 5 (71%)
```

Notice that *case matters*, e.g. `"This"` and `"this"` are counted as
*different* words. Also, punctuation *matters*, e.g. `"test"` and `"test?"` are
counted as different.

> **Note** Real life programs would likely strip out punctuation and ignore
> letter case, but in this assignment we want to count every word exactly as it
> appears in the file. This makes the code a littler simpler to implement.

Here's another example using the larger file
[tiny_shakespeare.txt](tiny_shakespeare.txt):

```cpp
❯ ./a5_main < tiny_shakespeare.txt >tiny_shakespeare_out
```

On average computer, this should run in a couple of seconds.

There's more than 25,000 lines of output, and so the example uses
`>tiny_shakespeare_out` to re-direct the output to the file
[tiny_shakespeare_out](tiny_shakespeare_out):

```
1. {"&C:", 2}
...
25670. {"zodiacs", 1}

Number of different words: 25670
    Total number of words: 202651
       Most frequent word: the 5437
     Number of singletons: 14919 (58%)
```

One way to test your program is to use the Linux `diff` command to compare your
output to this expected output:

```bash
> ./a5_main < tiny_shakespeare.txt >out

❯ diff out tiny_shakespeare_out

```

If `diff` prints nothing, then the two files are identical. Otherwise, it prints
each pair of different lines.


## What to Submit

When you're done, submit just your [Wordlist.h](Wordlist.h) on Canvas. Don't
submit anything else. A copy of [Wordlist_base.h](Wordlist_base.h) will be in
the same folder as your [Wordlist.h](Wordlist.h) when it's compiled.

The marker will use their own `a5_main.cpp` that will include your
[Wordlist.h](Wordlist.h) and will test the methods in it using their own test
cases. They will compile your code on Ubuntu Linux using [makefile](makefile),
which runs this command:

```bash
> make a5_main
g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g a5_main.cpp -o a5_main
```

This is a very strict compilation command! No warnings or errors are allowed!
Make sure that your code compiles with this command before submitting it.


## Grading

The marker will test the correctness of your code on at least one text file you
have not seen before, and they will also test individual method calls using test
functions and inputs you have not seen.

Your program will also be run with `valgrind` to check for memory leaks, and
other memory errors, e.g.:

```bash
> valgrind ./a5_main
==13731== Memcheck, a memory error detector
==13731== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==13731== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==13731== Command: ./a5_main
==13731== 
1. {"This", 1}
2. {"a", 2}
3. {"is", 2}
4. {"or", 1}
5. {"test", 1}
6. {"test?", 1}
7. {"this", 1}

Number of different words: 7
    Total number of words: 9
       Most frequent word: a 2
     Number of singletons: 5 (71%)
==13731== 
==13731== HEAP SUMMARY:
==13731==     in use at exit: 0 bytes in 0 blocks
==13731==   total heap usage: 10 allocs, 10 frees, 78,160 bytes allocated
==13731== 
==13731== All heap blocks were freed -- no leaks are possible
==13731== 
==13731== For lists of detected and suppressed errors, rerun with: -s
==13731== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

`valgrind` should report "no leaks are possible", and should *not* print any
other errors.

Be sure to test your program, and run it with `valgrind`, before submitting it.


## Marking Scheme

### Methods: 20 marks

- **2 marks** for each of the 8 virtual methods in `Wordlist_base` that is
  implemented correctly. `is_sorted` is *not* included in the marking because it
  always returns `true`.
- **2 marks** for a default constructor that creates an empty `Wordlist` object.
- **2 marks** for a constructor that takes the name of a file as input, and adds
  all the words in that file to the `Wordlist`. Read the words from the file
  using C++'s standard `<<` operator (the first example at the top of this
  assignment shows how this constructor should work, and what its output ought
  to be).

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

- at least **-5 marks** for any memory leaks, or other errors, reported by
  `valgrind`.
- at least **-1 mark** if your file has an incorrect name, or you submit it in
  the incorrect format, etc.
- up to **-3 marks** if you do not include your full name, email, and SFU ID in
  the header of your file.
- **a score of 0** if you do any of the following:
  - change `Node` in ways that are not allowed, if you modify anything in
    `Wordlist_base`, or if you use a vector, array, or any other data structure
    other than an AVL tree.
  - don't include the "statement of originality, or its modified in any way.
  - submit a "wrong" non-working file, and then *after the due date* submit the
    "right" file. If you can provide evidence that you finished the assignment
    on time, then it may be marked.

## Differences from Assignment 1

You can think of the AVL tree as storing the words in alphabetical order. So,
the tie-breaking rule for the `most_frequent()` is to return the word that comes
first alphabetically. 

Also, the `is_sorted()` method should return `true` if the AVL tree is a BST
(binary search tree), and `false` otherwise. In a working version of this
assignment it should always return `true`: if ever your AVL tree is not a BST,
then you have a serious problem!
