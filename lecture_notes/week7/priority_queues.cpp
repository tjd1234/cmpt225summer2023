// priority_queues.cpp

// Based on chp 8 of textbook.

#include "test.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//
// T is the type of the elements in the queue.
//
// T must implement a total order, i.e. operator< and operator== must be defined
// for T. Mathematically, a total order is a binary relation <= that satisfies
// these properties:
//
//   Reflexive property
//      k <= k
//      (for all values k)
//
//   Antisymmetric property
//      if k1 <= k2 and k2 <= k1, then k1 == k2
//      (for all values k1 and k2)
//
//   Transitive property
//      if k1 <= k2 and k2 <= k3, then k1 <= k3
//      (for all values k1, k2, and k3)
//
// If all values of type T satisfy these properties, then the notion of a min
// value on T is well-defined.
//
// Unlike the priority queue ADT in the textbook, this priority queue ADT does
// not use comparator functions. Instead, it assumes operator<, operator==,
// operator<=, etc. are defined for type T. The books approach is more general,
// but this approach is simpler.
//

template <typename T>
struct Priority_queue_base
{
    //
    // return the number of elements in the priority queue
    //
    virtual int size() const = 0;

    //
    // return true if priority queue is empty
    //
    virtual bool empty() const = 0;

    //
    // adds x to the priority queue
    //
    virtual void insert(const T &x) = 0;

    //
    // returns a reference to an element in the priority queue with the
    // smallest key (does not remove it)
    //
    virtual const T &min() const = 0;

    //
    // remove an element from the priority queue with the smallest key; error if
    // the priority queue is empty
    //
    virtual void remove_min() = 0;

    //
    // always include a virtual destructor in a base class
    //
    virtual ~Priority_queue_base() {}

    //
    // return a string representation of the priority queue
    //
    virtual string to_string() const = 0;
}; // struct Priority_queue_base

template <typename T>
string to_string(const vector<T> &v)
{
    string s = "{";
    for (int i = 0; i < v.size(); i++)
    {
        s += std::to_string(v[i]);
        if (i < v.size() - 1)
        {
            s += ", ";
        }
    }
    s += "}";
    return s;
}

//
// In this implementation, insertion is O(1) and min() and remove_min() are
// O(n). The values are stored in random order, and then an O(n) search is done
// to find the min value.
//
// An alternative way to do this would be to store the values in sorted order,
// and then insertion would be O(n) (in the worst case) and min() and
// remove_min() would be O(1).
//
// For the pq_sort function that follows, both implementations make it O(n^2),
// corresponding to selection sort (when removing the min is O(n)) and insertion
// sorting (when inserting is O(n)).
//
template <typename T>
class Priority_queue_vec : public Priority_queue_base<T>
{
    vector<T> v;

    //
    // returns the index of the min element in v; error if v is empty
    //
    int index_of_min() const
    {
        assert(!empty());
        int smallest_index = 0;
        for (int i = 1; i < size(); i++)
        {
            if (v[i] < v[smallest_index])
            {
                smallest_index = i;
            }
        }
        return smallest_index;
    }

public:
    //
    // make an empty priority queue
    //
    Priority_queue_vec() {}

    //
    // return the number of elements in the priority queue
    //
    // Performance: O(1)
    //
    int size() const
    {
        return v.size();
    }

    //
    // return true if priority queue is empty
    //
    // Performance: O(1)
    virtual bool empty() const
    {
        return size() == 0;
    }

    //
    // adds x to the priority queue
    //
    // Performance: O(1)
    //
    void insert(const T &x)
    {
        v.push_back(x);
    }

    //
    // returns a reference to an element in the priority queue with the smallest
    // key (does not remove it)
    //
    // Performance: O(n)
    //
    const T &min() const
    {
        return v[index_of_min()];
    }

    //
    // remove an element from the priority queue with the smallest key; error if
    // the priority queue is empty
    //
    // Does this by over-writing the smallest element with the last element in
    // the vector and then removing the last element.
    //
    // Performance: O(n)
    //
    void remove_min()
    {
        assert(!empty());
        v[index_of_min()] = v.back();
        v.pop_back();
    }

    //
    // return a string representation of the priority queue
    //
    // Performance: O(n)
    //
    string to_string() const
    {
        return ::to_string(v);
    }
}; // class Priority_queue_vec

//
// pq_sort is variation of selection sort that uses a Priority_queue_vec from
// above to extract the elements in sorted order.
//
template <typename T>
void pq_sort(vector<T> &v)
{
    //
    // add all elements of v to the priority queue
    //
    // O(n), since insert is O(1) and the loop runs n times
    //
    Priority_queue_vec<T> pq;
    for (int i = 0; i < v.size(); i++)
    {
        pq.insert(v[i]);
    }

    //
    // remove all elements from the priority queue and add them back to v in
    // sorted order
    //
    // O(n^2), since min() and remove_min() are both O(n), and the loop runs n
    // times
    //
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = pq.min();
        pq.remove_min();
    }
}

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

void test_Priority_queue_vec()
{
    Test("test_Priority_queue_vec");

    Priority_queue_vec<int> pq;
    assert(pq.empty());
    assert(pq.size() == 0);

    pq.insert(5);
    assert(!pq.empty());
    assert(pq.size() == 1);
    assert(pq.min() == 5);
    pq.remove_min();
    assert(pq.empty());
    assert(pq.size() == 0);

    vector<int> v = {5, 3, 7, 2, 8, 1, 9, 4, 6};
    // cout << "v = " << to_string(v) << endl;
    pq_sort(v);
    // cout << "v = " << to_string(v) << endl;
    assert(is_sorted(v));
}

//
// Min heap implementation of a priority queue
//
// Heap-Order Property: In a min heap T, for every node x other than the root,
// the key associated with x is greater than or equal to the key associated with
// x’s parent.
//
// The heap is also a **complete** tree, i.e. all levels, except possibly the
// last, are completely full, and the last level has all its nodes as far to the
// left as possible.
//
template <typename T>
class Priority_queue_heap : public Priority_queue_base<T>
{
    vector<T> v;

public:
    //
    // return the number of elements in the priority queue
    //
    int size() const
    {
        return v.size();
    }

    //
    // return true if priority queue is empty
    //
    virtual bool empty() const
    {
        return size() == 0;
    }

    //
    // Adds x to the priority queue.
    //
    // The idea is to add x at the end of the vector, and then swap it with its
    // parent until the heap-order property is satisfied. Thus x "floats up" to
    // its correct position in the heap.
    //
    // Since the heap is a complete tree, its height is O(log n), so the number
    // of swaps is at most O(log n).
    //
    void insert(const T &x)
    {
        v.push_back(x);
        int i = size() - 1;
        while (i > 0 && v[i] < v[(i - 1) / 2])
        {
            swap(v[i], v[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    //
    // Returns a reference to the root of priority queue, i.e. an element with a
    // smallest key (does not remove it).
    //
    const T &min() const
    {
        assert(!empty());
        return v[0];
    }

    //
    // Remove the root of the priority queue (the root is an element with a
    // smallest key); error if the priority queue is empty.
    //
    // The idea is to replace the root with the last element in the vector, and
    // then swap it with its smallest child until the heap-order property is
    // satisfied. Thus the root "floats down" to its correct position in the
    // heap.
    //
    // Since the heap is a complete tree, its height is O(log n), so the number
    // of swaps is at most O(log n).
    //
    void remove_min()
    {
        assert(!empty());
        // replace root with last element
        v[0] = v.back();
        v.pop_back();

        int i = 0;
        while (2 * i + 1 < size())
        {
            int j = 2 * i + 1;
            if (j + 1 < size() && v[j + 1] < v[j])
            {
                j++;
            }
            if (v[i] <= v[j])
            {
                break;
            }
            swap(v[i], v[j]);
            i = j;
        }
    }

    //
    // return a string representation of the priority queue
    //
    string to_string() const
    {
        return ::to_string(v);
    }
}; // class Priority_queue_heap

void test_sorted(vector<int> v)
{
    cout << "sorting " << ::to_string(v) << " ... ";
    pq_sort(v);
    assert(is_sorted(v));
    cout << "OK " << ::to_string(v) << endl;
}

void test_Priority_queue_heap()
{
    Test("test_Priority_queue_heap");

    Priority_queue_heap<int> pq;
    assert(pq.empty());
    assert(pq.size() == 0);

    pq.insert(5);
    assert(!pq.empty());
    assert(pq.size() == 1);
    assert(pq.min() == 5);
    pq.remove_min();
    assert(pq.empty());
    assert(pq.size() == 0);

    pq.insert(5);
    pq.insert(4);
    assert(!pq.empty());
    assert(pq.size() == 2);
    assert(pq.min() == 4);
    pq.remove_min();
    assert(!pq.empty());
    assert(pq.size() == 1);
    assert(pq.min() == 5);
    pq.remove_min();
    assert(pq.empty());
    assert(pq.size() == 0);

    pq.insert(5);
    pq.insert(9);
    assert(!pq.empty());
    assert(pq.size() == 2);
    assert(pq.min() == 5);
    pq.remove_min();
    pq.remove_min();
    assert(pq.empty());
    assert(pq.size() == 0);

    // vector<int> v;
    test_sorted({});

    test_sorted({5});

    test_sorted({3, 5});
    test_sorted({5, 3});
    test_sorted({5, 5});

    test_sorted({1, 2, 3});
    test_sorted({3, 2, 1});
    test_sorted({3, 1, 2});

    test_sorted({5, 3, 7, 2, 8, 1, 9, 5, 4, 6});
}

int main()
{
    test_Priority_queue_vec();
    test_Priority_queue_heap();
}
