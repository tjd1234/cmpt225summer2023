// stacks.cpp

// Based on chp 5 of textbook.

#include "test.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//
// T is the type of the elements in the stack. T should have a copy constructor.
//
// An import detail here compared to the textbook is that Stack_bases specifies
// that all its methods run in O(1) time. In other words, all its methods run in
// constant time no matter the size of the stack.
//
template <typename T>
struct Stack_base
{
    // put x on top of the stack; O(1) time
    virtual void push(const T &x) = 0;

    // remove and return the top element; error if stack is empty; O(1) time
    virtual T pop() = 0;

    // return a reference to the top element; error if stack is empty; O(1) time
    virtual const T &top() const = 0;

    // return true if stack is empty; default implementation is to check if
    // size() is 0; O(1) time
    virtual bool empty() const
    {
        return size() == 0;
    }

    // return the number of elements in the stack; O(1) time
    virtual int size() const = 0;

    // always include a virtual destructor in a base class
    virtual ~Stack_base() {}

}; // class Stack_base

//
// Fixed-sized array implementation.
//
template <typename T>
class Stack_array : public Stack_base<T>
{
private:
    T *arr; // pointer to the array
    int n;  // number of elements currently in the stack

public:
    // It's okay to make max_size public because it's const. Users can read it, but
    // they can't change it.
    const int max_size; // max number of elements that can be stored

    //
    // constructor
    //
    // Notice that max_size is initalized in the initialization list, not in the
    // body of the constructor. This is because max_size is const, so it can
    // only be initialized and not assigned to.
    //
    Stack_array(int msize)
        : max_size(msize) // initializer list
    {
        assert(max_size > 0);
        arr = new T[max_size];
        n = 0;
    }

    // put x on top of the stack; O(1) time
    void push(const T &x)
    {
        assert(n < max_size);
        arr[n] = x;
        n++;
    }

    // remove and return the top element; error if stack is empty; O(1) time
    T pop()
    {
        assert(!empty());
        n--;
        return arr[n];
    }

    // return a reference to the top element; error if stack is empty; O(1) time
    const T &top() const
    {
        assert(!empty());
        return arr[n - 1];
    }

    // return true if stack is empty; default implementation is to check if
    // size() is 0; O(1) time
    bool empty() const
    {
        return size() == 0;
    }

    // return the number of elements in the stack; O(1) time
    int size() const
    {
        return n;
    }

    // always include a virtual destructor in a base class
    ~Stack_array()
    {
        delete[] arr;
    }

    // return a string representation of the stack
    string to_string() const
    {
        if (empty())
        {
            return "empty stack (" + std::to_string(max_size) + " max)";
        }
        string s = "{" + std::to_string(arr[0]);
        for (int i = 1; i < size(); i++)
        {
            s += ", " + std::to_string(arr[i]);
        }
        s += "} (top, " + std::to_string(max_size) + " max)";
        return s;
    }
}; // class Stack_array

void test_Stack_array()
{
    Test("test_Stack_array()");
    Stack_array<int> stack(100); // Stack_array needs a max size
    assert(stack.empty());
    assert(stack.size() == 0);
    cout << "stack: " << stack.to_string() << endl;

    stack.push(1);
    assert(!stack.empty());
    assert(stack.size() == 1);
    assert(stack.top() == 1);
    assert(stack.pop() == 1);
    assert(stack.empty());
    assert(stack.size() == 0);

    stack.push(1);
    stack.push(8);
    assert(!stack.empty());
    assert(stack.size() == 2);
    assert(stack.top() == 8);
    assert(stack.pop() == 8);
    assert(stack.size() == 1);
    assert(stack.top() == 1);
    assert(stack.pop() == 1);
    assert(stack.empty());
    assert(stack.size() == 0);

    stack.push(1);
    stack.push(8);
    stack.push(3);

    cout << "stack: " << stack.to_string() << endl;
    cout << " size: " << stack.size() << endl;
    cout << "  top: " << stack.top() << endl;

    assert(stack.pop() == 3);
    cout << endl;
    cout << "stack: " << stack.to_string() << endl;
    cout << " size: " << stack.size() << endl;
    cout << "  top: " << stack.top() << endl;
} // test_list_stack

//
// vector<int> implementation
//
class Stack_vec : public Stack_base<int>
{
private:
    vector<int> v;

public:
    // put x on top of the stack; O(1) time
    void push(const int &x)
    {
        v.push_back(x);
    }

    // remove and return the top element; error if stack is empty; O(1) time
    int pop()
    {
        if (empty())
        {
            throw "Stack_vec::pop: stack is empty";
        }
        int x = v.back();
        v.pop_back();
        return x;
    }

    // return the top element; error if stack is empty; O(1) time
    const int &top() const
    {
        if (empty())
        {
            throw "Stack_vec::top: stack is empty";
        }
        return v.back();
    }

    // return the number of elements in the stack; O(1) time
    int size() const { return v.size(); }

    string to_string() const
    {
        if (empty())
            return "empty stack";
        string s = "{" + std::to_string(v[0]);
        for (int i = 1; i < v.size(); i++)
        {
            s += ", " + std::to_string(v[i]);
        }
        s += "} (top)";
        return s;
    }
}; // class Stack_vec

void test_vec_stack()
{
    Test("test_vec_stack");
    Stack_vec stack;
    assert(stack.empty());
    assert(stack.size() == 0);
    cout << "stack: " << stack.to_string() << endl;

    stack.push(1);
    assert(!stack.empty());
    assert(stack.size() == 1);
    assert(stack.top() == 1);
    assert(stack.pop() == 1);
    assert(stack.empty());
    assert(stack.size() == 0);

    stack.push(1);
    stack.push(8);
    assert(!stack.empty());
    assert(stack.size() == 2);
    assert(stack.top() == 8);
    assert(stack.pop() == 8);
    assert(stack.size() == 1);
    assert(stack.top() == 1);
    assert(stack.pop() == 1);
    assert(stack.empty());
    assert(stack.size() == 0);

    stack.push(1);
    stack.push(8);
    stack.push(3);

    cout << "stack: " << stack.to_string() << endl;
    cout << " size: " << stack.size() << endl;
    cout << "  top: " << stack.top() << endl;

    assert(stack.pop() == 3);
    cout << endl;
    cout << "stack: " << stack.to_string() << endl;
    cout << " size: " << stack.size() << endl;
    cout << "  top: " << stack.top() << endl;

} // test_vec_stack

//
// Stack based on a list
//
template <typename T>
class Stack_list : public Stack_base<T>
{
    struct Node
    {
        T data;
        Node *next;
    };

    Node *head = nullptr;
    int num_elements = 0;

public:
    // put x on top of the stack; O(1) time
    void push(const T &x)
    {
        Node *p = new Node{x, head};
        head = p;
        num_elements++;
    }

    // remove and return the top element; error if stack is empty; O(1) time
    T pop()
    {
        if (this->empty())
        {
            throw "Stack_list::pop: stack is empty";
        }

        T result = head->data; // save the value to return
        Node *p = head;        // save the head node so it can be deleted
        head = head->next;     // move the head pointer to the next node
        delete p;              // delete the old head node
        num_elements--;        // decrement the number of elements
        return result;         // return the value
    }

    // return the top element; error if stack is empty; O(1) time
    const T &top() const
    {
        if (this->empty())
        {
            throw "Stack_list::top: stack is empty";
        }
        return head->data;
    }

    // return the number of elements in the stack; O(1) time
    int size() const
    {
        return num_elements;
    }

    string to_string() const
    {
        if (this->empty())
            return "empty stack";
        string s = "{" + std::to_string(head->data);
        for (Node *p = head->next; p != nullptr; p = p->next)
        {
            s += ", " + std::to_string(p->data);
        }
        s += "} (top)";
        return s;
    }

    ~Stack_list()
    {
        while (head != nullptr)
            pop();
    }
}; // class Stack_list<T>

void test_list_stack()
{
    Test("test_list_stack");
    Stack_list<int> stack;
    assert(stack.empty());
    assert(stack.size() == 0);
    cout << "stack: " << stack.to_string() << endl;

    stack.push(1);
    assert(!stack.empty());
    assert(stack.size() == 1);
    assert(stack.top() == 1);
    assert(stack.pop() == 1);
    assert(stack.empty());
    assert(stack.size() == 0);

    stack.push(1);
    stack.push(8);
    assert(!stack.empty());
    assert(stack.size() == 2);
    assert(stack.top() == 8);
    assert(stack.pop() == 8);
    assert(stack.size() == 1);
    assert(stack.top() == 1);
    assert(stack.pop() == 1);
    assert(stack.empty());
    assert(stack.size() == 0);

    stack.push(1);
    stack.push(8);
    stack.push(3);

    cout << "stack: " << stack.to_string() << endl;
    cout << " size: " << stack.size() << endl;
    cout << "  top: " << stack.top() << endl;

    assert(stack.pop() == 3);
    cout << endl;
    cout << "stack: " << stack.to_string() << endl;
    cout << " size: " << stack.size() << endl;
    cout << "  top: " << stack.top() << endl;
} // test_list_stack

// uses a stack to reverse a vector
template <typename T>
void reverse_with_stack(vector<T> &v)
{
    Stack_list<T> stack;
    for (int i = 0; i < v.size(); i++)
    {
        stack.push(v[i]);
    }
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = stack.pop();
    }
}

void test_reverse_stack()
{
    Test("test_reverse_stack");
    vector<int> v{1, 2, 3, 4, 5};
    reverse_with_stack(v);
    assert(v[0] == 5);
    assert(v[1] == 4);
    assert(v[2] == 3);
    assert(v[3] == 2);
    assert(v[4] == 1);
    cout << "... test_reverse_stack() done: all tests passed\n";
}

// reverse without a stack
template <typename T>
void reverse_basic(vector<T> &v)
{
    int a = 0;
    int b = v.size() - 1;
    while (a < b)
    {
        swap(v[a], v[b]);
        a++;
        b--;
    }
}

void test_reverse_basic()
{
    Test("test_reverse_basic");
    vector<int> v{1, 2, 3, 4, 5};
    reverse_basic(v);
    assert(v[0] == 5);
    assert(v[1] == 4);
    assert(v[2] == 3);
    assert(v[3] == 2);
    assert(v[4] == 1);
}

int main()
{
    test_Stack_array();
    test_vec_stack();
    test_list_stack();
    test_reverse_stack();
    test_reverse_basic();
}
