// List_base.h

//
// An example of how to use an abstract base class to implement a list
//

#pragma once

#include <string>

using namespace std;

//
// List_base is abstract base class. All of its methods are:
//
// - virtual, meaning they can be overridden by a class that inherits from
//   List_base; in C++ this is indicated by the "virtual" keyword
// - abstract, meaning they have no implementation; in C++ this is indicated by
//   putting "= 0" at the end of the method declaration
//
// The purpose of this is to clearly specify the methods a class must implement.
//
class List_base {
public:
    //
    // Returns true if the list is empty, and false otherwise.
    //
    virtual bool empty() const = 0;

    //
    // Returns the number of nodes in the list.
    //
    virtual int size() const = 0;

    //
    // Prints the contents of the list to cout.
    //
    virtual void print() const = 0;

    //
    // Inserts a new string at the front of the list
    //
    virtual void push_front(const string &s) = 0;

    //
    // Remove the first node from the list (and return its value).
    //
    virtual string pop_front() = 0;

    //
    // Return a copy of the string in the first node in the list
    //
    virtual string peek_front() const = 0;

    //
    // Remove all nodes from the list.
    //
    // This particular method can be efficiently written in terms of the other
    // methods in this class, so we give it a body.
    //
    // Since it is virtual, an inheriting class can, if it chooses, to over-ride
    // this implementation and provide its own.
    //
    virtual void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    //
    // Destructor: called automatically when the object goes out of scope, or is
    // deleted.
    //
    // In C++, a base class should always declare a virtual destructor.
    // Otherwise, you can have problems calling the right destructor in
    // inheriting classes.
    //
    virtual ~List_base() { }

}; // class List_base
