## Assignment 4: Sorting

> The ability to destroy a planet is insignificant next to the power of sorting.
> -- Darth Vader (if he was a computer scientist)

In this assignment, your task is to run performance experiments on 7 sorting
algorithms: *bubble* sort, *insertion* sort, *selection* sort, *merge* sort,
*quick* sort, *shell* sort, and a hybrid algorithm combining quick sort and
insertion sort that we'll call *iquick* sort. You'll create a spreadsheet to
report on your results.

Put your implementations of all the functions in a file named
[a4_sort_implementations.h](a4_sort_implementations.h). Implement each algorithm
as described in the textbook: you can use the code from the textbook, or from
other sources (make sure to cite your sources!). Implement the *exact* function
headers listed in [a4_base.h](a4_base.h). *Don't* change [a4_base.h](a4_base.h)
in any way: all the sorting-related code you write goes in
[a4_sort_implementations.h](a4_sort_implementations.h).

**Important** The *only* #include that
[a4_sort_implementations.h](a4_sort_implementations.h) can use is `#include
"a4_base.h"`. No other #includes are allowed.

*iquick* sort is regular quick sort, except when the sub-vectors being sorted
are shorter than some predetermined threshold length, insertion sort is used instead
of quick sort. If you choose a good threshold length, you can get better
average-time performance than regular quick sort. Do some experimentation to
find the best threshold length for *iquick* sort!

Test your implementations using [test_sorts.cpp](test_sorts.cpp). You can modify
that file in any way you like (it is *not* one of the submitted files for this
assignment).

> **Note** [test_sorts.cpp](test_sorts.cpp) only checks for basic correctness of
> the sorting algorithm, and ignores the `SortStats` objects they return. Feel
> free to add more test cases if you want to test the `SortStats` objects.

Notice that most of the functions in [a4_base.h](a4_base.h) are *template*
functions, i.e. they take a `vector<T>` as input, where `T` is a type of value
that can be sorted.

All the sorts return a `SortStats` object containing their running
time and comparisons counts:

```cpp
typedef unsigned long ulong;

struct SortStats
{
    string sort_name;
    size_t vector_size = 0;
    ulong num_comparisons = 0;
    double cpu_running_time_sec = 0.0;

    string to_csv() const
    {
        return sort_name + ", " 
             + to_string(vector_size) + ", " 
             + to_string(num_comparisons) + ", " 
             + to_string(cpu_running_time_sec);
    }
}; // struct SortStats
```

For this assignment, `num_comparisons` is the number of times `<` or `<=` is
called on the values in the vector. It's declared to be of type `ulong`
(`unsigned long`) because the comparison counts can get very large.

You should modify basic sorting functions to return accurate `SortStats`
objects. You can write helper functions if you like.

### Example: Bubble Sort

For example, you can implement bubble sort like this:

```cpp
template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock(); 

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1])
            {
                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Bubble sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}
```

### Timing Code in C++

As shown in `bubble_sort`, you can measure CPU time using `clock()` like this:

```cpp
#include <ctime>

void timed_experiment() {
    clock_t start = clock();

    //
    // ... do stuff ...
    //

    clock_t end = clock();

    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    cout << "It took " << elapsed_cpu_time_sec << " seconds to do stuff.\n";
}
```

[cpu_timer_example.cpp](cpu_timer_example.cpp) contains a complete example of
some timing code.


## Generating the Experimental Data

When your sorting algorithms are ready, use them to generate the following data:

- For each of the 7 sorting algorithms, do the following:
  - For *N* = 2000, 4000, 6000, ..., 50000 (25 different values of *N*) do the
    following:
    - create a vector of *N* random integers, where the numbers in the vectors
      range from 1 to *N*
    - run the sort on the vector of random integers
    - print the sort name, amount of data being sorted, number of comparisons
      that were done, and the CPU time (in seconds)

Since there are 7 algorithms and 25 values of *N*, you'll end up with $$7 \cdot
25 = 175$$ results. 

If you print the individual results as comma separated values (CSVs), then you
can more easily import them into a spreadsheet. For example, here are 4 calls to
bubble sort printed as comma separated values:

```
Bubble sort, 2000, 3998000, 0.003197
Bubble sort, 4000, 15996000, 0.014169
Bubble sort, 6000, 35994000, 0.035031
Bubble sort, 8000, 63992000, 0.066863
.
.
.
```

If you save this output in a file, the file should be readable by Excel or
Google Sheets as a CSV file.

## Visualizing the Data in a Spreadsheet

Using Excel or Google Sheets, create a table of all the data you generated. Here
is an example of what the first four rows of the table ought to look like (the
numbers in your table might be different):

| **Name**    | **N** | **Comparisons** | **CPU Seconds** |
|-------------|-------|-----------------|-----------------|
| bubble sort |  2000 | 3998000         | 0.003197        |
| bubble sort |  4000 | 15996000        | 0.014169        |
| bubble sort |  6000 | 35994000        | 0.035031        |
| bubble sort |  8000 | 63992000        | 0.066863        |

Please make the table 4 columns, and label each column with the given name, as
shown.

> **Remember** The table will have 175 rows of data.

In addition to this table, **draw four graphs**, where the x-axis of each graph
is *N* (the size of the vector being sorted), and has the values from the data
you generated: N=2000, 4000, 6000, ..., 50000. The four graphs are:

- **Graph 1**: **CPU time** for *bubble* sort, *insertion* sort, and *selection*
  sort. The the y-axis is the CPU time in seconds.

- **Graph 2**: **CPU time** for *merge* sort, *quick* sort, *shell* sort,
  and *iquick* sort. The y-axis is the CPU time in seconds.

- **Graph 3**: **comparison counts** for *bubble* sort, *insertion* sort,
  and *selection* sort. The y-axis is the number of comparisons. 

- **Graph 4**: **comparison counts** for *merge* sort, *quick* sort, *shell*
  sort, and *iquick* sort. The y-axis is the number of comparisons. 

Each graph will have 3 or 4 lines on it, one for each of the sorting algorithms
it is plotting data for.

Make these graphs *beautiful* and *easy to read*. Give them descriptive titles
(**don't** just name them Graph 1, Graph 2, etc.!), clearly labelled x and y
axes, and use colors or textures to distinguish different lines on the same
graph.

> **Note** It's not too hard to make nice-looking graphs in Excel or Google
> Sheets. Spend a bit of time playing with the options.

## What to Submit

When you're done, submit a zip file containing just these two files:

- [a4_sort_implementations.h](a4_sort_implementations.h)
- An Excel or Google Sheets file named **a4.xlsx** that contains the table of
  experimental data and the 4 graphs.

## Grading

The marker will compile and run your program on Ubuntu Linux using
[makefile](makefile) like this:

```bash
> make a4_test
g++ -O3 -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g a4_test.cpp -o a4_test

> ./a4_test
... testing output ...

> valgrind ./a4_test
... valgrind output ...
```

The file `a4_test.cpp` is a test program written by the marker that tests the
correctness of your sorting algorithms. It will #include [a4_base.h](a4_base.h)
and [a4_sort_implementations.h](a4_sort_implementations.h).

Note that the `-O3` flag is one of the options: this asks g++ to optimize the
code for speed.

> **Note** The compilation commands are quite strict! Make sure your program
> compiles with them before submitting it.

## Marking Scheme

- **12 marks** for the correctness of the 6 sorting algorithms (bubble sort is
  not included since it's given in the notes), 2 for each correct sorting
  algorithm. This includes both the correctness of the sorting algorithm itself,
  and the correctness of the `SortStats` object it returns.
- **5 marks** for a nicely-formatted table with 4 columns (all labelled) and 175
  rows of data, as explained above.
- **5 marks** for graphs that are beautiful, easy to read, have good titles,
  have their axes labelled, and clearly label the different plots using color or
  textures. If the graphs look wrong, or have missing data, or plot the wrong
  thing, etc., the highest possible mark for this part will be **2 marks**.

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

- Up to **-3 marks** if you do *not* include your full name, email, and SFU ID
  in the header of your file.
- Up to **-3 marks** if your submitted files don't following the
  naming/formatting conventions given above.
- **A score of 0** if your code *doesn't* compile with the given makefile.
- **A score of 0** if valgrind reports any memory leaks, or other errors.
- **A score of 0** if you *don't* include the "Statement of Originality", or it
  is modified in any way.
- **A score of 0** if you use code from some other source (e.g. the web, the
  textbook, ChatGPT, ...) *without* citing its source.
- **A score of 0** if you submit a "wrong" non-working file, and then *after the
  due date* submit the "right" file. If you can provide evidence that you
  finished the assignment on time, then it may be marked.

There may be other deductions, depending upon the circumstances.
