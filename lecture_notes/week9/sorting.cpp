// sorting.cpp

#include "test.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//
// helper functions
//

//
// Returns true if v is in ascending sorted order, and false otherwise. An empty
// vector is considered to be sorted.
//
template <typename T>
bool is_sorted(const vector<T> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i - 1] > v[i])
        {
            return false;
        }
    }
    return true;
}

void test_is_sorted()
{
    Test("test_is_sorted");
    vector<int> v;
    assert(is_sorted(v));
    v.push_back(1);
    assert(is_sorted(v));
    v.push_back(2);
    assert(is_sorted(v));
    swap(v[0], v[1]);
    assert(!is_sorted(v));
    v = {1, 2, 9};
    assert(is_sorted(v));
    v = {9, 2, 1};
    assert(!is_sorted(v));
    v = {9};
    assert(is_sorted(v));
    v = {9, 9};
    assert(is_sorted(v));
    v = {9, 9, 9};
    assert(is_sorted(v));
    v = {9, 9, 1, 9};
    assert(!is_sorted(v));
    v = {-19, -9, 1, 9, 402, 1000};
    assert(is_sorted(v));
    v = {};
    for (int i = 0; i < 100; i++)
    {
        v.push_back(i);
    }
    assert(is_sorted(v));
}

// Returns a random int in the range [min, max].
int rand_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

//
// Returns a random vector of size elements, where each element is in the range
// [min, max].
//
vector<int> make_rand_vector(int size, int min, int max)
{
    vector<int> v;
    for (int i = 0; i < size; i++)
    {
        v.push_back(rand_int(min, max));
    }
    return v;
}

vector<string> make_rand_string_vector(int size, int min, int max)
{
    vector<string> v;
    for (int i = 0; i < size; i++)
    {
        v.push_back(to_string(rand_int(min, max)));
    }
    return v;
}

void test_make_rand_vector()
{
    Test("test_make_rand_vector");
    vector<int> v = make_rand_vector(10, 10, 100);
    assert(v.size() == 10);
    for (int n : v)
    {
        assert(n >= 10 && n <= 100);
    }
    sort(v.begin(), v.end());
    assert(is_sorted(v));
}

//
// Data for timing code.
//

const string TIMING_FILE = "tiny_shakespeare.txt";

vector<string> get_words(const string &fname)
{
    ifstream infile(fname);
    vector<string> v;
    string word;
    while (infile >> word)
    {
        v.push_back(word);
    }
    return v;
}

const vector<string> TIMING_WORDS = get_words(TIMING_FILE);

struct Sort_tester
{
    virtual ~Sort_tester() {}

    virtual string sort_name() const = 0;
    virtual void sort(vector<string> &vec) = 0;

    void run_all(const vector<string> &data)
    {
        test_sort();
        time_sort(data);
    }

    void time_sort(vector<string> data)
    {
        clock_t start = clock();
        sort(data);
        clock_t end = clock();

        double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
        cout << sort_name() << " on " << data.size() << " words from " << TIMING_FILE << "\n"
             << "   " << elapsed_cpu_time_sec << " seconds" << endl;
        if (!is_sorted(data))
        {
            cout << "   ERROR: not sorted" << endl;
        }
    }

    void test_sort()
    {
        Test("test: " + sort_name());
        vector<string> v;
        sort(v);
        assert(is_sorted(v));
        v = {"1"};
        sort(v);
        assert(is_sorted(v));
        v = {"2", "1"};
        sort(v);
        assert(is_sorted(v));
        v = {"1", "2"};
        sort(v);
        assert(is_sorted(v));
        v = {"2", "2"};
        sort(v);
        assert(is_sorted(v));

        for (int i = 0; i < 100; i++)
        {
            int r = rand_int(1, 1000);
            v = make_rand_string_vector(r, 0, 10000);
            sort(v);
            assert(is_sorted(v));
        }
    }
}; // class Sort_tester

//
// Permutation sort
//
// Generate each permutations of v, one at a time, stopping when a sorted one is
// found.
//
// Simple but very slow: O(n*n!) worst case running time.
//
template <typename T>
void permutation_sort(vector<T> &v)
{
    while (!is_sorted(v))
    {
        next_permutation(v.begin(), v.end());
    }
}

void test_permutation_sort()
{
    Test("test_permutation_sort");
    vector<int> v;
    permutation_sort(v);
    assert(is_sorted(v));
    v = {1};
    permutation_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    permutation_sort(v);
    assert(is_sorted(v));
    v = {1, 2};
    permutation_sort(v);
    assert(is_sorted(v));
    v = {2, 2};
    permutation_sort(v);
    assert(is_sorted(v));

    for (int i = 0; i < 100; i++)
    {
        int r = rand_int(1, 5);
        v = make_rand_vector(r, 0, 10000);
        permutation_sort(v);
        assert(is_sorted(v));
    }
}

//
// Randomized permutation sort
//
// Repeatedly shuffles v until a sorted permutation is found.
//
// Simple but very slow: O(n*n!) worst case running time.
//
template <typename T>
void randomized_permutation_sort(vector<T> &v)
{
    while (!is_sorted(v))
    {
        random_shuffle(v.begin(), v.end());
    }
}

void test_randomized_permutation_sort()
{
    Test("test_randomized_permutation_sort");
    vector<int> v;
    randomized_permutation_sort(v);
    assert(is_sorted(v));
    v = {1};
    randomized_permutation_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    randomized_permutation_sort(v);
    assert(is_sorted(v));
    v = {1, 2};
    randomized_permutation_sort(v);
    assert(is_sorted(v));
    v = {2, 2};
    randomized_permutation_sort(v);
    assert(is_sorted(v));

    for (int i = 0; i < 100; i++)
    {
        int r = rand_int(1, 5);
        v = make_rand_vector(r, 0, 10000);
        randomized_permutation_sort(v);
        assert(is_sorted(v));
    }
}

//
// Bubble sort
//
// Simple but very slow: O(n^2) worst case running time.
//
// Works by repeatedly swapping adjacent elements that are out of order.
//
template <typename T>
void bubble_sort(vector<T> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

class Bubble_sort_tester : public Sort_tester
{
    string sort_name() const
    {
        return "bubble sort";
    }

    void sort(vector<string> &v)
    {
        bubble_sort(v);
    }
};

//
// This merges two vectors.
//
template <typename T>
vector<T> merge(vector<T> &v1, vector<T> &v2)
{
    vector<T> v;
    int i = 0;
    int j = 0;
    while (i < v1.size() && j < v2.size())
    {
        if (v1[i] < v2[j])
        {
            v.push_back(v1[i]);
            i++;
        }
        else
        {
            v.push_back(v2[j]);
            j++;
        }
    }
    while (i < v1.size())
    {
        v.push_back(v1[i]);
        i++;
    }
    while (j < v2.size())
    {
        v.push_back(v2[j]);
        j++;
    }
    return v;
}

//
// Merge sort
//
// Performance: O(n log n) in the worst case.
//
// Not the most efficient implementation, i.e. v1 and v2 are copied. But it's
// relatively easy to understand and still very fast. You can use it as a base
// for building a more efficient implementation.
//
template <typename T>
void merge_sort(vector<T> &v)
{
    if (v.size() <= 1)
    {
        return;
    }
    int mid = v.size() / 2;
    vector<T> v1(v.begin(), v.begin() + mid);
    vector<T> v2(v.begin() + mid, v.end());
    merge_sort(v1);
    merge_sort(v2);
    v = merge(v1, v2);
}

class Merge_sort_tester : public Sort_tester
{
    string sort_name() const
    {
        return "merge sort";
    }

    void sort(vector<string> &v)
    {
        merge_sort(v);
    }
};

//
// Partitions a sub-vector of vector (for quick_sort).
//
// The pivot is the last element in the sub-vector.
//
// Returns the index of the pivot.
//
template <typename T>
int partition(vector<T> &v, int start, int end)
{
    T pivot = v[end];
    int i = start;
    for (int j = start; j < end; j++)
    {
        if (v[j] < pivot)
        {
            swap(v[i], v[j]);
            i++;
        }
    }
    swap(v[i], v[end]);
    return i;
}

//
// Quicksort
//
// Performance: O(n log n) on average, O(n^2) in the worst case.
//
template <typename T>
void quick_sort(vector<T> &v, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int pivot = partition(v, start, end);
    quick_sort(v, start, pivot - 1);
    quick_sort(v, pivot + 1, end);
}

template <typename T>
void quick_sort(vector<T> &v)
{
    quick_sort(v, 0, v.size() - 1);
}

class Quick_sort_tester : public Sort_tester
{
    string sort_name() const
    {
        return "quick sort";
    }

    void sort(vector<string> &v)
    {
        quick_sort(v);
    }
};


//
// Same as quick_sort, but randomly shuffles the input vector first.
//
template <typename T>
void quick_sort_randomized(vector<T> &v)
{
    random_shuffle(v.begin(), v.end());
    quick_sort(v, 0, v.size() - 1);
}

class Quick_sort_randomized_tester : public Sort_tester
{
    string sort_name() const
    {
        return "quick sort randomized";
    }

    void sort(vector<string> &v)
    {
        quick_sort_randomized(v);
    }
};


//
// Quicksort using std::partition from
// https://en.cppreference.com/w/cpp/algorithm/partition
//
// The std::partition function is a C++ standard library function that
// partitions a range of elements [first, last) around a pivot element, such
// that all elements for which the predicate p returns true precede all elements
// for which predicate p returns false. The iterator returned points to the
// first element of the second group.
//
// This implementation is flexible and efficient, competitive with std::sort.
//

template <class ForwardIt>
void quick_sort2(ForwardIt first, ForwardIt last)
{
    if (first == last)
        return;

    auto pivot = *std::next(first, std::distance(first, last) / 2);

    // [pivot](const auto &em) { return em < pivot; } is an example of a
    // function with a no name, i.e. a "lambda function"; lambda function are
    // handy when you want to pass a function as a parameter, as is done here
    // with std::partition.
    auto middle1 = std::partition(first, last, [pivot](const auto &em)
                                  { return em < pivot; });
    auto middle2 = std::partition(middle1, last, [pivot](const auto &em)
                                  { return !(pivot < em); });

    quick_sort2(first, middle1);
    quick_sort2(middle2, last);
}

template <typename T>
void quick_sort2(vector<T> &v)
{
    quick_sort2(v.begin(), v.end());
}

class Quick_sort2_tester : public Sort_tester
{
    string sort_name() const
    {
        return "quick sort 2";
    }

    void sort(vector<string> &v)
    {
        quick_sort2(v);
    }
};


class Std_sort_tester : public Sort_tester
{
    string sort_name() const
    {
        return "std::sort";
    }

    void sort(vector<string> &v)
    {
        std::sort(v.begin(), v.end());
    }
};


int main()
{
    //
    // set random seed based on time; if you want repeatable random numbers, set
    // the seed to be a fixed value
    //
    srand(time(0));

    test_is_sorted();
    test_make_rand_vector();

    test_permutation_sort();
    test_randomized_permutation_sort();

    Merge_sort_tester().time_sort(TIMING_WORDS);
    Quick_sort_tester().time_sort(TIMING_WORDS);
    Quick_sort_randomized_tester().time_sort(TIMING_WORDS);
    Quick_sort2_tester().time_sort(TIMING_WORDS);
    Std_sort_tester().time_sort(TIMING_WORDS);
    Bubble_sort_tester().time_sort(TIMING_WORDS);

} // main

/* timing results on my desktop computer (no optimizations):

std::sort on 202651 words from tiny_shakespeare.txt
   0.067464 seconds
merge_sort on 202651 words from tiny_shakespeare.txt
   0.461179 seconds
quick_sort on 202651 words from tiny_shakespeare.txt
   0.569136 seconds
quick_sort_randomized on 202651 words from tiny_shakespeare.txt
   0.597902 seconds
bubble_sort on 202651 words from tiny_shakespeare.txt
   563.223 seconds

*/

/* timing results on my desktop computer (-O3 optimizations):

std::sort on 202651 words from tiny_shakespeare.txt
   0.026834 seconds
merge_sort on 202651 words from tiny_shakespeare.txt
   0.11282 seconds
quick_sort on 202651 words from tiny_shakespeare.txt
   0.258864 seconds
quick_sort_randomized on 202651 words from tiny_shakespeare.txt
   0.268925 seconds
bubble_sort on 202651 words from tiny_shakespeare.txt
   254.879 seconds

*/
