// string_view.cpp

//
// A std::string_view can be thought of as a pointer to a character in a string,
// plus a length. It is an efficient way to pass both C++ strings and C-style
// strings as parameters to functions. With C-style strings, there is usually no
// need to convert the string to a C++ string.
//
// A std::string_view cannot be modified, i.e. you cannot change the characters
// of the underlying string. Getting substring with substr() is allowed and is
// very efficient (since characters are not copied).
//
// If you need to modify the string, you can make a convert it to a std::string.
//
// In general, std::string_view is a good choice for replacing const string&
// parameters. It is more flexible, and often faster.
//

#include "test.h"
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

//
// Returns the number of times c appears in s.
//
// count_char("Hello", 'H') == 1
//
int count_char(string_view s, char c)
{
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == c)
        {
            count++;
        }
    }
    return count;
}

//
// Returns true if c is in source, and false otherwise.
//
bool contains(string_view source, char c)
{
    return count_char(source, c) > 0;
}

//
// Returns the number of spaces in s.
//
int count_spaces(string_view s)
{
    return count_char(s, ' ');
}

void test_contains_char()
{
    Test("contains_char");

    // C-style strings
    assert(!contains("", 'H'));
    assert(contains("Hello", 'H'));
    assert(contains("Hello", 'e'));
    assert(contains("Hello", 'o'));

    // C++ strings
    assert(!contains(string(""), 'H'));
    assert(contains(string("Hello"), 'H'));
    assert(contains(string("Hello"), 'e'));
    assert(contains(string("Hello"), 'o'));

    // std::string_view
    assert(!contains(string_view(""), 'H'));
    assert(contains(string_view("Hello"), 'H'));
    assert(contains(string_view("Hello"), 'e'));
    assert(contains(string_view("Hello"), 'o'));
}

//
// Return a string with quotes around it.
//
string quote(string_view s)
{
    // the string_view s must be explicitly convert to a string
    return "\"" + string(s) + "\"";
}

string quote(char c)
{
    return "\'" + string(1, c) + "\'";
}

void test_quote()
{
    Test("quote");

    // C-style strings
    assert(quote("") == "\"\"");
    assert(quote("Hello") == "\"Hello\"");

    // C++ strings
    assert(quote(string("")) == "\"\"");
    assert(quote(string("Hello")) == "\"Hello\"");

    // std::string_view
    assert(quote(string_view("")) == "\"\"");
    assert(quote(string_view("Hello")) == "\"Hello\"");
}

//
// Tries to return a string with quotes around it, but doesn't work.
//
// The returned string is a dangling reference to a temporary string, so the
// returned string_view is invalid.
//
string_view bad_quote(string_view s)
{
    // the string_view s must be explicitly convert to a string
    return "\"" + string(s) + "\"";
}

void test_bad_quote()
{
    Test("bad_quote");

    // C-style strings
    string_view result = bad_quote("");
    cout << quote(result[0]) << " " << quote(result[1]) << endl;
    cout << "result.size(): " << result.size() << endl;
    cout << "bad_quote(\"\"): " << result << endl;
    // assert(result == "\"\"");

    // assert(bad_quote("Hello") == "\"Hello\"");

    // // C++ strings
    // assert(bad_quote(string("")) == "\"\"");
    // assert(bad_quote(string("Hello")) == "\"Hello\"");

    // // std::string_view
    // assert(bad_quote(string_view("")) == "\"\"");
    // assert(bad_quote(string_view("Hello")) == "\"Hello\"");
}

void demo2()
{
    string s = "fold";

    string_view sv(s);
    cout << sv << endl;
    sv = sv.substr(1, 3);  // fast: no characters copied
    cout << sv << endl;

    s = "foldable"; // uh oh: s has changed
    cout << sv << endl; // phew: still "old"

    s = "!"; // uh oh: s has changed again
    cout << quote(sv) << endl;
    cout << "sv.size(): " << sv.size() << endl;
    // prints "ld" for me, but this is undefined behavior because s only has one
    // character; no error reported, not even when run with valgrind!
}

int main()
{
    // test_contains_char();
    // test_quote();
    // test_bad_quote();
    demo2();
}
