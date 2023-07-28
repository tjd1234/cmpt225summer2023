// strings_search.cpp

#include "test.h"
#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Puts quotes around a string.
string quote(const string &s)
{
    return "\"" + string(s) + "\"";
}

//
// Uses strings built-in find method to determine if pattern is in s.
//
bool contains_string(const string &s, const string &pattern)
{
    //
    // If pattern is not in s, then find returns string::npos.
    //
    return s.find(pattern) != string::npos;
}

void contains_string_test()
{
    Test("contains_string_test");

    assert(contains_string("", ""));
    assert(contains_string("a", ""));
    assert(contains_string("a", "a"));
    assert(contains_string("ab", "a"));
    assert(contains_string("ab", "b"));
    assert(contains_string("ab", "ab"));
    assert(contains_string("abc", ""));
    assert(contains_string("abc", "a"));
    assert(contains_string("abc", "b"));
    assert(contains_string("abc", "c"));
    assert(contains_string("abc", "ab"));
    assert(contains_string("abc", "bc"));

    assert(!contains_string("", "a"));
    assert(!contains_string("a", "b"));
    assert(!contains_string("ab", "c"));
    assert(!contains_string("abc", "d"));
    assert(!contains_string("abc", "ac"));
    assert(!contains_string("abc", "abcde"));
    assert(!contains_string("a", "ax"));
    assert(!contains_string("abc", "xyabc"));

    assert(!contains_string("a", "A"));
    assert(!contains_string("A", "a"));
}

//
// Returns true if source contains pattern, and false otherwise.
//
// This code is based on code from GPT-4. Note that it got the correct casting
// of the lengths in the for-loop, and testing suggests it is correct overall.
//
bool contains_gpt4(const string &source, const string &pattern)
{
    if (pattern.empty())
    { // if pattern is an empty string, return true.
        return true;
    }

    // Careful! The string::size method returns an unsigned int, so we need to
    // cast it to an int before we can subtract.
    for (int i = 0; i <= (int)source.size() - (int)pattern.size(); i++)
    {
        int j = 0;
        for (; j < pattern.size(); j++)
        {
            if (source[i + j] != pattern[j])
            {
                break;
            }
        }
        // If loop didn't break early, pattern is found.
        if (j == pattern.size())
        {
            return true;
        }
    }
    return false; // if we get here, then a match was not found.
}

void demo()
{
    string source = "This is a test string";
    string pattern = "test";

    if (contains_gpt4(source, pattern))
    {
        cout << quote(source) << " contains_gpt4 " << quote(pattern) << "\n";
    }
    else
    {
        cout << quote(source) << " does NOT contain " << quote(pattern) << "\n";
    }
}

void contains_gpt4_test()
{
    Test("contains_gpt4_test");

    assert(contains_gpt4("", ""));
    assert(contains_gpt4("a", ""));
    assert(contains_gpt4("a", "a"));
    assert(contains_gpt4("ab", "a"));
    assert(contains_gpt4("ab", "b"));
    assert(contains_gpt4("ab", "ab"));
    assert(contains_gpt4("abc", ""));
    assert(contains_gpt4("abc", "a"));
    assert(contains_gpt4("abc", "b"));
    assert(contains_gpt4("abc", "c"));
    assert(contains_gpt4("abc", "ab"));
    assert(contains_gpt4("abc", "bc"));

    assert(!contains_gpt4("", "a"));
    assert(!contains_gpt4("a", "b"));
    assert(!contains_gpt4("ab", "c"));
    assert(!contains_gpt4("abc", "d"));
    assert(!contains_gpt4("abc", "ac"));
    assert(!contains_gpt4("abc", "abcde"));
    assert(!contains_gpt4("a", "ax"));
    assert(!contains_gpt4("abc", "xyabc"));

    assert(!contains_gpt4("a", "A"));
    assert(!contains_gpt4("A", "a"));
}

//
// Returns true if source contains pattern, and false otherwise.
//
// This code is based on code from the textbook.
//
bool contains_textbook(const string &source, const string &pattern)
{
    int n = source.size();
    int m = pattern.size();
    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m && source[i + j] == pattern[j])
        {
            j++;
        }
        if (j == m)
        {
            return true;
        }
    }
    return false;
}

void contains_textbook_test()
{
    Test("contains_textbook_test");

    assert(contains_textbook("", ""));
    assert(contains_textbook("a", ""));
    assert(contains_textbook("a", "a"));
    assert(contains_textbook("ab", "a"));
    assert(contains_textbook("ab", "b"));
    assert(contains_textbook("ab", "ab"));
    assert(contains_textbook("abc", ""));
    assert(contains_textbook("abc", "a"));
    assert(contains_textbook("abc", "b"));
    assert(contains_textbook("abc", "c"));
    assert(contains_textbook("abc", "ab"));
    assert(contains_textbook("abc", "bc"));

    assert(!contains_textbook("", "a"));
    assert(!contains_textbook("a", "b"));
    assert(!contains_textbook("ab", "c"));
    assert(!contains_textbook("abc", "d"));
    assert(!contains_textbook("abc", "ac"));
    assert(!contains_textbook("abc", "abcde"));
    assert(!contains_textbook("a", "ax"));
    assert(!contains_textbook("abc", "xyabc"));

    assert(!contains_textbook("a", "A"));
    assert(!contains_textbook("A", "a"));
}

vector<int> make_last_function(const string &pattern)
{
    const int N_ASCII = 128;          // number of ASCII characters
    vector<int> last(N_ASCII);        // assume ASCII character set
    for (int i = 0; i < N_ASCII; i++) // initialize array
    {
        last[i] = -1;
    }
    for (int i = 0; i < pattern.size(); i++)
    {
        last[pattern[i]] = i; // (implicit cast to ASCII code)
    }
    return last;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

bool contains_boyer_moore(const string &source, const string &pattern)
{
    vector<int> last = make_last_function(pattern);

    const int m = pattern.size();
    const int n = source.size();

    if (m > n) // check if pattern longer than source
    {
        return false;
    }
    else if (m == 0) // check if pattern is empty
    {
        return true;
    }

    int i = m - 1;
    int j = m - 1;

    do
    {
        if (pattern[j] == source[i])
        {
            if (j == 0)
            {
                return true; // a match!
            }
            else
            {
                i--;
                j--;
            }
        }
        else
        {
            i += m - min(j, 1 + last[source[i]]);
            j = m - 1;
        }
    } while (i <= source.size() - 1);

    return false; // no match
}

void contains_boyer_moore()
{
    Test("contains_boyer_moore");

    assert(contains_boyer_moore("", ""));
    assert(contains_boyer_moore("a", ""));
    assert(contains_boyer_moore("a", "a"));
    assert(contains_boyer_moore("ab", "a"));
    assert(contains_boyer_moore("ab", "b"));
    assert(contains_boyer_moore("ab", "ab"));
    assert(contains_boyer_moore("abc", ""));
    assert(contains_boyer_moore("abc", "a"));
    assert(contains_boyer_moore("abc", "b"));
    assert(contains_boyer_moore("abc", "c"));
    assert(contains_boyer_moore("abc", "ab"));
    assert(contains_boyer_moore("abc", "bc"));

    assert(!contains_boyer_moore("", "a"));
    assert(!contains_boyer_moore("a", "b"));
    assert(!contains_boyer_moore("ab", "c"));
    assert(!contains_boyer_moore("abc", "d"));
    assert(!contains_boyer_moore("abc", "ac"));
    assert(!contains_boyer_moore("abc", "abcde"));
    assert(!contains_boyer_moore("a", "ax"));
    assert(!contains_boyer_moore("abc", "xyabc"));

    assert(!contains_boyer_moore("a", "A"));
    assert(!contains_boyer_moore("A", "a"));
}

void performance_test()
{
    //
    // read the source file in as a big string
    //
    ifstream source_file("tiny_shakespeare.txt");
    stringstream buffer;
    buffer << source_file.rdbuf();
    const string source = buffer.str();
    cout << "read in source text (" << source.size() << " characters)" << endl;

    //
    // read each pattern into a vector
    //
    vector<string> patterns;
    ifstream patterns_file("ospd.txt");
    string p;
    while (patterns_file >> p)
    {
        patterns.push_back(p);
    }
    cout << "read in " << patterns.size() << " patterns" << endl;

    //
    // test the string search function
    //
    int match_count = 0;
    int num = 0;
    clock_t start = clock();
    for (const string &p : patterns)
    {
        num++;
        if (num % 5000 == 0)
        {
            cout << num << "/" << patterns.size() << endl;
        }
        if (contains_string(source, p))
        {
            match_count++;
        }
    }
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    cout << "elapsed time: " << elapsed_cpu_time_sec << " seconds "
         << "(" << match_count << " matches)" << endl;
}

/*

contains_textbook, -O3    : 73.3155 seconds (11442 matches) 
contains_gpt4, -O3        : 65.6916 seconds (11442 matches) 
contains_boyer_moore, -O3 : 51.9195 seconds (11442 matches) 
contains_string, -O3      : 24.6495 seconds (11442 matches)

C++'s built-in find is optimized to run efficiently on modern computers, and so 
it is much faster than the textbook's code. For an example of what a 
std::string::find implementation looks like, see:

https://github.com/gcc-mirror/gcc/commit/fc7ebc4b8d9ad7e2891b7f72152e8a2b7543cd65

*/

int main()
{
    // contains_string_test();
    // contains_gpt4_test();
    // contains_textbook_test();
    // contains_boyer_moore();
    performance_test();
}
