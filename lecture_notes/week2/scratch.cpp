#pragma once

#include <string>

using namespace std;


class List_base {
public:

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual void print() const = 0;

    virtual void push_front(const string &s) = 0;

    virtual string pop_front() = 0;

    virtual string peek_front() const = 0;

    virtual void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    virtual ~List_base() { }

}; // class List_base