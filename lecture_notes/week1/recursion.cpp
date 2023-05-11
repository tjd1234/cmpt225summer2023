// recursion.cpp

//
// Examples of recursive functions.
//

#include "test.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//
// Pre-condition:
//    n >= 0
// Post-condition:
//    returns 0 + 1 + 2 + ... + n
// Note:
//    The recursive idea is that to sum the numbers from 1 to n, first sum the
//    numbers from 0 to n - 1, and then add n.
//
int sum_to(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return n + sum_to(n - 1);
    }
}

void test_sum_to()
{
    Test test("test_sum_to");
    assert(sum_to(0) == 0);
    assert(sum_to(1) == 1);
    assert(sum_to(2) == 3);
    assert(sum_to(3) == 6);
    assert(sum_to(4) == 10);
}

//
// Pre-condition:
//    [begin, end) is a valid range of indices for vec
// Post-condition:
//    returns vec[begin] + vec[begin + 1] + ... + vec[end - 1]
//
int sum_vec(const vector<int> &vec, int begin, int end)
{
    if (begin == end)
    {
        return 0;
    }
    else
    {
        return vec[begin] + sum_vec(vec, begin + 1, end);
    }
}

//
// Returns the sum of all elements in vec.
//
int sum_vec(const vector<int> &vec)
{
    return sum_vec(vec, 0, vec.size());
}

void test_sum_vec()
{
    Test test("test_sum_vec");
    vector<int> vec = {1, 2, 3, 4, 5};
    assert(sum_vec(vec) == 15);
    assert(sum_vec(vec, 0, 3) == 6);
    assert(sum_vec(vec, 2, 5) == 12);
    assert(sum_vec(vec, 2, 2) == 0);

    vec = {};
    assert(sum_vec(vec) == 0);
    assert(sum_vec(vec, 0, 0) == 0);
    vec = {2};
    assert(sum_vec(vec) == 2);
    assert(sum_vec(vec, 0, 1) == 2);
}

//
// Pre-condition:
//    size is the number of elements in arr
//    arr points to a valid array
// Post-condition:
//    returns the sum of all elements in arr
//
double sum_array(double *arr, int size)
{
    if (size == 0)
    {
        return 0;
    }
    else
    {
        return arr[0] + sum_array(arr + 1, size - 1);
    }
}

void test_sum_array()
{
    Test("test_sum_array");
    double arr[] = {1, 2, 3, 4, 5};
    assert(sum_array(arr, 0) == 0);
    assert(sum_array(arr, 1) == 1);
    assert(sum_array(arr, 2) == 3);
    assert(sum_array(arr, 3) == 6);
    assert(sum_array(arr, 4) == 10);
    assert(sum_array(arr, 5) == 15);
}

//
// Pre-condition:
//    none
// Post-condition:
//    returns the number of spaces in s
// Note:
//    The recursive idea is that to count the number of spaces in s, first count
//    the number of spaces in s[1] onward, and then add 1 if s[0] is a space.
//
//    Also, uses s.substr(1) to get the substring of s starting at index 1,
//    which is relatively inefficient for large strings.
//
int count_spaces1(const string &s)
{
    if (s == "")
    {
        return 0;
    }
    else
    {
        return (s[0] == ' ') + count_spaces1(s.substr(1));
    }
}

void test_count_spaces1()
{
    Test("test_count_spaces1");
    assert(count_spaces1("") == 0);
    assert(count_spaces1(" ") == 1);
    assert(count_spaces1("  ") == 2);
    assert(count_spaces1("   ") == 3);
    assert(count_spaces1("a") == 0);
    assert(count_spaces1(" a") == 1);
    assert(count_spaces1("a ") == 1);
    assert(count_spaces1(" a ") == 2);
    assert(count_spaces1("a a") == 1);
    assert(count_spaces1("a  a") == 2);
    assert(count_spaces1("aa") == 0);
}

//
// Pre-condition:
//    begin is a valid index for s
// Post-condition:
//    returns the number of spaces in s
// Note:
//    Passing the begin index of where to start counting spaces avoids the use
//    the (costly) s.substr() function.
//
int count_spaces2(const string &s, int begin)
{
    if (begin == s.size())
    {
        return 0;
    }
    else
    {
        return (s[begin] == ' ') + count_spaces2(s, begin + 1);
    }
}

//
// Returns the number of spaces in s.
//
int count_spaces2(const string &s)
{
    return count_spaces2(s, 0);
}

void test_count_spaces2()
{
    Test("test_count_spaces2");
    assert(count_spaces2("") == 0);
    assert(count_spaces2(" ") == 1);
    assert(count_spaces2("  ") == 2);
    assert(count_spaces2("   ") == 3);
    assert(count_spaces2("a") == 0);
    assert(count_spaces2(" a") == 1);
    assert(count_spaces2("a ") == 1);
    assert(count_spaces2(" a ") == 2);
    assert(count_spaces2("a a") == 1);
    assert(count_spaces2("a  a") == 2);
    assert(count_spaces2("aa") == 0);
}

//
// Pre-condition:
//    none
// Post-condition:
//    returns the number of spaces in s
// Note:
//    string_view is a C++17 standard class. A string_view stores a pointer to
//    the start of a string, and a length. Thus the substr function is
//    relatively efficient. It works with both C-style strings and C++ strings.
//
int count_spaces3(string_view s)
{
    if (s == "")
    {
        return 0;
    }
    else
    {
        return (s[0] == ' ') + count_spaces3(s.substr(1));
    }
}

void test_count_spaces3()
{
    Test("test_count_spaces3");
    assert(count_spaces3("") == 0);
    assert(count_spaces3(" ") == 1);
    assert(count_spaces3("  ") == 2);
    assert(count_spaces3("   ") == 3);
    assert(count_spaces3("a") == 0);
    assert(count_spaces3(" a") == 1);
    assert(count_spaces3("a ") == 1);
    assert(count_spaces3(" a ") == 2);
    assert(count_spaces3("a a") == 1);
    assert(count_spaces3("a  a") == 2);
    assert(count_spaces3("aa") == 0);
}

//
// Pre-condition:
//    begin is a valid index for s
// Post-condition:
//    returns the index of the first occurrence of target in s
//    returns -1 if target does not occur in s
// Note:
//    The recursive idea is that to find the index of the first occurrence of
//    target, first check if the first character of the string is the target. If
//    not, then, if the target is in the string at all, it must be from the
//    second character onward, so recursively check that.
int index_of(const string &s, char target, int begin)
{
    if (begin == s.size())
    {
        return -1;
    }
    else if (s[begin] == target)
    {
        return begin;
    }
    else
    {
        return index_of(s, target, begin + 1);
    }
}

//
// Returns the index of the first occurrence of target in s.
// Returns -1 if target does not occur in s.
//
int index_of(const string &s, char target)
{
    return index_of(s, target, 0);
}

void test_index_of()
{
    Test("test_index_of");
    assert(index_of("", 'a') == -1);
    assert(index_of("a", 'a') == 0);
    assert(index_of("a", 'b') == -1);
    assert(index_of("ab", 'a') == 0);
    assert(index_of("ab", 'b') == 1);
    assert(index_of("ab", 'c') == -1);
    assert(index_of("abc", 'a') == 0);
    assert(index_of("abc", 'b') == 1);
    assert(index_of("abc", 'c') == 2);
    assert(index_of("abc", 'd') == -1);
}


int main()
{
    test_sum_to();
    test_sum_vec();
    test_count_spaces1();
    test_count_spaces2();
    test_count_spaces3();
    test_index_of();
    test_sum_array();
    cout << "All recursion.cpp tests passed!\n";
}
