// test.h

//
// Helper class for printing begin/end messages for test functions
//

#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Test
{
    string name;
    Test(const string &name)
        : name(name)
    {
        cout << "Calling " << name << " ...\n";
    }

    ~Test()
    {
        cout << "... " << name << " done: all tests passed\n";
    }
}; // struct Test
