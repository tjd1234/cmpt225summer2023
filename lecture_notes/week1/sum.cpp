// sum.cpp

//
// sum an array or vector, in 11 different non-recursive ways
// (see recursion.cpp for recursive versions)
//


#include "test.h"
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

//
// In C/C++, basic arrays are passed using a pointer and a size. Basic arrays do
// not store their size!
//
double sum_array1(double *arr, int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total += arr[i];
    }
    return total;
}

void test_sum_array1()
{
    Test("test_sum_array1");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sum_array1(arr, 5) == 15.0);
    assert(sum_array1(arr, 3) == 6.0);
    assert(sum_array1(arr + 2, 3) == 12.0);
    assert(sum_array1(arr + 2, 0) == 0.0);
}

//
// Using a while-loop instead of a for-loop.
//
// Generally, for-loop are preferred over while-loops because they put the loop
// control information in one place at the top of the loop.
//
double sum_array1a(double *arr, int size)
{
    double total = 0;
    int i = 0;
    while (i < size)
    {
        total += arr[i];
        i++;
    }
    return total;
}

void test_sum_array1a()
{
    Test("test_sum_array1a");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sum_array1a(arr, 5) == 15.0);
    assert(sum_array1a(arr, 3) == 6.0);
    assert(sum_array1a(arr + 2, 3) == 12.0);
    assert(sum_array1a(arr + 2, 0) == 0.0);
}

// access array elements using pointer arithmetic
double sum_array1b(double *arr, int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total += *(arr + i);
    }
    return total;
}

void test_sum_array1b()
{
    Test("test_sum_array1b");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sum_array1b(arr, 5) == 15.0);
    assert(sum_array1b(arr, 3) == 6.0);
    assert(sum_array1b(arr + 2, 3) == 12.0);
    assert(sum_array1b(arr + 2, 0) == 0.0);
}

//
// You can use a pointer to iterate through an array.
//
double sum_array2(double *arr, int size)
{
    double total = 0;

    for (double *p = arr; p < arr + size; p++)
    {
        total += *p;
    }
    return total;
}

void test_sum_array2()
{
    Test("test_sum_array2");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sum_array2(arr, 5) == 15.0);
    assert(sum_array2(arr, 3) == 6.0);
    assert(sum_array2(arr + 2, 3) == 12.0);
    assert(sum_array2(arr + 2, 0) == 0.0);
}

//
// Another way to use pointers to iterate through an array. Works on any
// sub-array.
//
// begin points to the first element in the sub-array, and end points to the
// element *after* the last element in the sub-array.
//
double sum_array3(double *begin, double *end)
{
    double total = 0;
    for (double *p = begin; p < end; p++)
    {
        total += *p;
    }
    return total;
}

void test_sum_array3()
{
    Test("test_sum_array3");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sum_array3(arr, arr + 5) == 15.0);
    assert(sum_array3(arr, arr + 3) == 6.0);
    assert(sum_array3(arr + 2, arr + 3) == 3.0);
    assert(sum_array3(arr + 2, arr + 2) == 0.0);
}

//
// The C++ standard library has many helpful functions. The accumulate function
// sums the elements between two iterators (pointers). The third argument is the
// starting value of the sum.
//
double sum_array4(double *arr, int size)
{
    return accumulate(arr, arr + size, 0);
}

void test_sum_array4()
{
    Test("test_sum_array4");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sum_array4(arr, 5) == 15.0);
    assert(sum_array4(arr, 3) == 6.0);
    assert(sum_array4(arr + 2, 3) == 12.0);

    // assert(sum_array4(arr + 2, 0) == 0.0);
}

//
// Another way to use accumulate.
//
double sum_array5(double *begin, double *end)
{
    return accumulate(begin, end, 0);
}

void test_sum_array5()
{
    Test("test_sum_array5");
    double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    assert(sum_array5(arr, arr + 5) == 15.0);
    assert(sum_array5(arr, arr + 3) == 6.0);
    assert(sum_array5(arr + 2, arr + 3) == 3.0);
    assert(sum_array5(arr + 2, arr + 2) == 0.0);
}

//
// In C++, vectors are generally preferred over arrays since they are easier to
// work with. For example, they store their length, can be resized, manage their
// own memory, and have many helper methods.
//
double sum_vec1(const vector<double> &v)
{
    double total = 0;
    for (int i = 0; i < v.size(); i++)
    {
        total += v[i];
    }
    return total;
}

void test_sum_vec1()
{
    Test("test_sum_vec1");
    vector<double> v = {};
    assert(sum_vec1(v) == 0.0);
    v = {1.0};
    assert(sum_vec1(v) == 1.0);
    v = {1.0, 2.0};
    assert(sum_vec1(v) == 3.0);
    v = {1.0, 2.0, 3.0};
    assert(sum_vec1(v) == 6.0);
}

//
// Use the for-each style loop when it makes sense. The code is often shorter
// and simpler.
//
double sum_vec2(const vector<double> &v)
{
    double total = 0;
    for (double x : v)
    {
        total += x;
    }
    return total;
}

void test_sum_vec2()
{
    Test("test_sum_vec2");
    vector<double> v = {};
    assert(sum_vec2(v) == 0.0);
    v = {1.0};
    assert(sum_vec2(v) == 1.0);
    v = {1.0, 2.0};
    assert(sum_vec2(v) == 3.0);
    v = {1.0, 2.0, 3.0};
    assert(sum_vec2(v) == 6.0);
}

//
// The C++ standard library has many help functions. The accumulate function
// sums the elements between two iterators (pointers). The third argument is the
// initial value of the sum.
//
double sum_vec3(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0);
}

void test_sum_vec3()
{
    Test("test_sum_vec3");
    vector<double> v = {};
    assert(sum_vec3(v) == 0.0);
    v = {1.0};
    assert(sum_vec3(v) == 1.0);
    v = {1.0, 2.0};
    assert(sum_vec3(v) == 3.0);
    v = {1.0, 2.0, 3.0};
    assert(sum_vec3(v) == 6.0);
}

//
// Generic (templated) implementation of sum.
//
// std::accumulate works with templated iterators, so it works with any type T
// that has operator+ defined on it.
//
// Note that depending on the version of C++ you're using, sum_generic could be
// quite inefficient on a vector<string>.
//
template <typename T>
T sum_generic(const vector<T> &v)
{
    return accumulate(v.begin(), v.end(),
                      T() // start with an empty object of type T
    );
}

void test_sum_generic()
{
    Test("test_sum_generic");
    vector<double> v = {};
    assert(sum_generic(v) == 0.0);
    v = {1.0};
    assert(sum_generic(v) == 1.0);
    v = {1.0, 2.0};
    assert(sum_generic(v) == 3.0);
    v = {1.0, 2.0, 3.0};
    assert(sum_generic(v) == 6.0);

    vector<string> w = {};
    assert(sum_generic(w) == "");
    w = {"cat"};
    assert(sum_generic(w) == "cat");
    w = {"cat", "dog"};
    assert(sum_generic(w) == "catdog");
    w = {"cat", "dog", "mouse"};
    assert(sum_generic(w) == "catdogmouse");
}

int main()
{
    test_sum_array1();
    test_sum_array1a();
    test_sum_array1b();
    test_sum_array2();
    test_sum_array3();
    test_sum_array4();
    test_sum_array5();

    test_sum_vec1();
    test_sum_vec2();
    test_sum_vec3();

    test_sum_generic();
    cout << "\nAll sum.cpp tests passed!\n";
}
