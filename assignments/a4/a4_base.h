// a4_base.h

#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//
// For conveniently printing vectors.
//
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    int n = v.size();
    os << "{";
    for (int i = 0; i < v.size(); i++)
    {
        os << v[i];
        if (i < n - 1)
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

//
// SortStats stores statistics about one run of a sorting routine.
//

// "ulong" is easier to type than "unsigned long"
typedef unsigned long ulong;

struct SortStats
{
    string sort_name;
    size_t vector_size = 0;
    ulong num_comparisons = 0;
    double cpu_running_time_sec = 0.0;

    string to_csv() const
    {
        return sort_name + ", " + to_string(vector_size) + ", " + to_string(num_comparisons) + ", " + to_string(cpu_running_time_sec);
    }
}; // struct SortStats

//
// For conveniently printing SortStats objects.
//
ostream &operator<<(ostream &os, const SortStats &ss)
{
    os << "SortStats{" << ss.sort_name
       << ", size=" << ss.vector_size
       << ", num_comparisons=" << ss.num_comparisons
       << ", cpu_running_time_sec=" << ss.cpu_running_time_sec
       << "}";
    return os;
}

//
// Returns true if v[0] <= v[1] <= ... <= v[n-1], and false otherwise.
// Returns true if v is empty, i.e. an empty vector is considered sorted.
//
template <typename T>
bool is_sorted(vector<T> &v);

//
// Sorting algorithm headers. Each algorithm implements the named algorithm as
// described in the textbook (iquick sort is described in the assignment), and
// returns a SortStats object containing statistics about the run.
//

template <typename T>
SortStats bubble_sort(vector<T> &v);

template <typename T>
SortStats insertion_sort(vector<T> &v);

template <typename T>
SortStats selection_sort(vector<T> &v);

template <typename T>
SortStats merge_sort(vector<T> &v);

template <typename T>
SortStats quick_sort(vector<T> &v);

template <typename T>
SortStats shell_sort(vector<T> &v);

template <typename T>
SortStats iquick_sort(vector<T> &v);
// See description in assignment.

//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max);
