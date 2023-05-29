// deques.cpp

// Based on chp 5 of textbook.

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//
// T is the type of the elements in the queue. T should have a copy constructor.
//

template <typename T>
struct Deque_base
{
    // put x on the front of the deque
    virtual void insertFront(const T &x) = 0;

    // put x on the back of the deque
    virtual void insertBack(const T &x) = 0;

    // remove and return the front element; error if deque is empty
    virtual T eraseFront() = 0;

    // remove and return the back element; error if deque is empty
    virtual T eraseBack() = 0;

    // return a reference to the front element; error if queue is empty
    virtual const T &front() const = 0;

    // return a reference to the back element; error if queue is empty
    virtual const T &back() const = 0;

    // return true if stack is empty; default implementation is to check if
    // size() is 0
    virtual bool empty() const
    {
        return size() == 0;
    }

    // return the number of elements in the queue
    virtual int size() const = 0;

    // always include a virtual destructor in a base class
    virtual ~Deque_base() {}
}; // class Deque_base

//
// vector<int> implementation
//
template <typename T>
class Deque_vec : public Deque_base<T>
{
private:
    vector<T> v;

public:
    // put x on the front of the deque
    void insertFront(const T &x)
    {
        v.insert(v.begin(), x);
    }

    // put x on the back of the deque
    void insertBack(const T &x)
    {
        v.push_back(x);
    }

    // remove and return the front element; error if deque is empty
    T eraseFront()
    {
        if (this->empty())
        {
            throw "error: empty deque";
        }
        T x = v[0];
        v.erase(v.begin());
        return x;
    }

    // remove and return the back element; error if deque is empty
    T eraseBack()
    {
        if (this->empty())
        {
            throw "error: empty deque";
        }
        T x = v.back();
        v.pop_back();
        return x;
    }

    // return a reference to the front element; error if queue is empty
    const T &front() const
    {
        if (this->empty())
        {
            throw "error: empty deque";
        }
        return v[0];
    }

    // return a reference to the back element; error if queue is empty
    const T &back() const
    {
        if (this->empty())
        {
            throw "error: empty deque";
        }
        return v.back();
    }

    // return the number of elements in the queue
    int size() const
    {
        return v.size();
    }

    string to_string() const
    {
        if (this->empty())
            return "empty deque";
        string s = "(front) {" + std::to_string(v[0]);
        for (int i = 1; i < v.size(); i++)
        {
            s += ", " + std::to_string(v[i]);
        }
        s += "} (back)";
        return s;
    }
}; // class Deque_vec

void test_vec_deque()
{
    cout << "Calling test_vec_deque()...\n";
    Deque_vec<int> q;
    assert(q.empty());
    assert(q.size() == 0);
    cout << "q: " << q.to_string() << endl;

    q.insertFront(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseFront();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertFront(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertBack(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertBack(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseFront();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertFront(1);
    q.insertFront(2);
    assert(!q.empty());
    assert(q.size() == 2);
    assert(q.front() == 2);
    assert(q.back() == 1);
    q.eraseFront();
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertFront(1);
    q.insertBack(2);
    q.insertBack(3);
    cout << "q: " << q.to_string() << endl;
    assert(!q.empty());
    assert(q.size() == 3);
    assert(q.front() == 1);
    assert(q.back() == 3);
    q.eraseBack();
    assert(!q.empty());
    assert(q.size() == 2);
    assert(q.front() == 1);
    assert(q.back() == 2);
    q.eraseBack();
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    cout << "... test_vec_deque() done: all tests passed\n";
} // test_vec_deque

//
// Doubly linked list implementation.
//

template <typename T>
class Deque_list : public Deque_base<T>
{
    struct Node
    {
        T data;
        Node *next;
        Node *prev;
    };

    Node *front_ptr = nullptr;
    Node *back_ptr = nullptr;
    int count = 0;

public:
    // put x on the front of the deque
    void insertFront(const T &x)
    {
        Node *new_node = new Node;
        new_node->data = x;
        new_node->next = front_ptr;
        new_node->prev = nullptr;
        if (front_ptr != nullptr)
        {
            front_ptr->prev = new_node;
        }
        front_ptr = new_node;
        if (back_ptr == nullptr)
        {
            back_ptr = new_node;
        }
        count++;
    }

    // put x on the back of the deque
    void insertBack(const T &x)
    {
        Node *new_node = new Node;
        new_node->data = x;
        new_node->next = nullptr;
        new_node->prev = back_ptr;
        if (back_ptr != nullptr)
        {
            back_ptr->next = new_node;
        }
        back_ptr = new_node;
        if (front_ptr == nullptr)
        {
            front_ptr = new_node;
        }
        count++;
    }

    // remove and return the front element; error if deque is empty
    T eraseFront()
    {
        if (this->empty())
        {
            throw "error: empty deque";
        }
        else if (size() == 1)
        {
            T data = front_ptr->data;
            delete front_ptr;
            front_ptr = nullptr;
            back_ptr = nullptr;
            count--;
            return data;
        }
        else
        {
            T data = front_ptr->data;
            Node *next = front_ptr->next;
            delete front_ptr;
            front_ptr = next;
            front_ptr->prev = nullptr;
            count--;
            return data;
        }
    }

    // remove and return the back element; error if deque is empty
    T eraseBack()
    {
        if (this->empty())
        {
            throw "error: empty deque";
        }
        else if (size() == 1)
        {
            T data = front_ptr->data;
            delete front_ptr;
            front_ptr = nullptr;
            back_ptr = nullptr;
            count--;
            return data;
        }
        else
        {
            T data = back_ptr->data;
            Node *prev = back_ptr->prev;
            delete back_ptr;
            back_ptr = prev;
            back_ptr->next = nullptr;
            count--;
            return data;
        }
    }

    // return a reference to the front element; error if queue is empty
    const T &front() const
    {
        if (front_ptr == nullptr)
        {
            throw "error: empty deque";
        }
        return front_ptr->data;
    }

    // return a reference to the back element; error if queue is empty
    const T &back() const
    {
        if (back_ptr == nullptr)
        {
            throw "error: empty deque";
        }
        return back_ptr->data;
    }

    // return the number of elements in the queue
    int size() const
    {
        return count;
    }

    // always include a virtual destructor in a base class
    ~Deque_list()
    {
        while (front_ptr != nullptr)
        {
            Node *next = front_ptr->next;
            delete front_ptr;
            front_ptr = next;
        }
    }

    string to_string() const
    {
        if (this->empty())
            return "empty deque";
        string s = "(front) {" + std::to_string(front());
        Node *p = front_ptr->next;
        while (p != nullptr)
        {
            s += ", " + std::to_string(p->data);
            p = p->next;
        }
        s += "} (back)";
        return s;
    }
}; // class Deque_list

void deque_list_test()
{
    Deque_list<int> q;
    assert(q.empty());
    assert(q.size() == 0);

    q.insertBack(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    // memory leak starts here
    q.insertBack(1); // causes memory leak
}

void test_list_deque()
{
    cout << "Calling test_list_deque()...\n";
    Deque_list<int> q;
    assert(q.empty());
    assert(q.size() == 0);
    cout << "q: " << q.to_string() << endl;

    q.insertFront(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseFront();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertFront(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertBack(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    // memory leak starts here
    q.insertBack(1); // causes memory leak
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseFront();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertFront(1);
    q.insertFront(2);
    assert(!q.empty());
    assert(q.size() == 2);
    assert(q.front() == 2);
    assert(q.back() == 1);
    q.eraseFront();
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    q.insertFront(1);
    q.insertBack(2);
    q.insertBack(3);
    cout << "q: " << q.to_string() << endl;
    assert(!q.empty());
    assert(q.size() == 3);
    assert(q.front() == 1);
    assert(q.back() == 3);
    q.eraseBack();
    assert(!q.empty());
    assert(q.size() == 2);
    assert(q.front() == 1);
    assert(q.back() == 2);
    q.eraseBack();
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);
    assert(q.back() == 1);
    q.eraseBack();
    assert(q.empty());
    assert(q.size() == 0);

    srand(time(nullptr));
    int N = 100;
    for (int i = 0; i < N; i++)
    {
        if (rand() % 2 == 0)
        {
            q.insertFront(i);
        }
        else
        {
            q.insertBack(i);
        }
    }
    assert(!q.empty());
    assert(q.size() == 100);

    for (int i = 0; i < N; i++)
    {
        if (rand() % 2 == 0)
        {
            q.eraseFront();
        }
        else
        {
            q.eraseBack();
        }
    }
    assert(q.empty());
    assert(q.size() == 0);

    cout << "... test_list_deque() done: all tests passed\n";
} // test_list_deque

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

    // // remove all elements from the stack; O(n) time
    // virtual void clear() {
    //     while (!empty()) {
    //         pop();
    //     }
    // }

    // always include a virtual destructor in a base class
    virtual ~Stack_base() {}
}; // class Stack_base

//
// Stack made from adapting Deque_list
//
template <typename T>
class Stack_deque : public Stack_base<T>
{
    Deque_list<T> q;

public:
    // put x on top of the stack; O(1) time
    void push(const T &x)
    {
        q.insertBack(x);
    }

    // remove and return the top element; error if stack is empty; O(1) time
    T pop()
    {
        T x = q.back();
        q.eraseBack();
        return x;
    }

    // return a reference to the top element; error if stack is empty; O(1) time
    const T &top() const
    {
        return q.back();
    }

    // return the number of elements in the stack; O(1) time
    int size() const
    {
        return q.size();
    }

    string to_string() const
    {
        return "stack: " + q.to_string();
    }
}; // class Stack_deque

void stack_deque_test()
{
    cout << "Calling stack_deque_test()...\n";
    Stack_deque<int> stack;
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
    cout << "... test_vec_stack() done: all tests passed\n";
    cout << "... stack_deque_test() done: all tests passed\n";
} // stack_deque_test()

//
// Queue made from adapting Deque_list
//

template <typename T>
struct Queue_base
{
    // put x on the back of the queue
    virtual void enqueue(const T &x) = 0;

    // remove and return the front element; error if queue is empty
    virtual T dequeue() = 0;

    // return a reference to the front element; error if queue is empty
    virtual const T &front() const = 0;

    // return true if stack is empty; default implementation is to check if
    // size() is 0
    virtual bool empty() const
    {
        return size() == 0;
    }

    // return the number of elements in the queue
    virtual int size() const = 0;

    // // remove all elements from the queue
    // virtual void clear() {
    //     while (!empty()) {
    //         pop();
    //     }
    // }

    // always include a virtual destructor in a base class
    virtual ~Queue_base() {}
}; // class Queue_base

template <typename T>
class Queue_deque : public Queue_base<T>
{
    Deque_list<T> q;

public:
    // put x on the back of the queue
    void enqueue(const T &x) {
        q.insertBack(x);
    }

    // remove and return the front element; error if queue is empty
    T dequeue() {
        T x = q.front();
        q.eraseFront();
        return x;
    }

    // return a reference to the front element; error if queue is empty
    const T &front() const {
        return q.front();
    }

    // return the number of elements in the queue
    int size() const {
        return q.size();
    }

    string to_string() const {
        return "queue: " + q.to_string();
    }

}; // class Queue_deque

void test_queue_deque()
{
    cout << "Calling test_queue_deque()...\n";
    Queue_deque<int> q;
    assert(q.empty());
    assert(q.size() == 0);
    cout << "q: " << q.to_string() << endl;

    q.enqueue(1);
    assert(!q.empty());
    assert(q.size() == 1);
    assert(q.front() == 1);

    assert(q.dequeue() == 1);
    assert(q.empty());
    assert(q.size() == 0);

    q.enqueue(1);
    q.enqueue(8);
    assert(!q.empty());
    assert(q.size() == 2);
    assert(q.front() == 1);
    assert(q.dequeue() == 1);
    assert(q.size() == 1);
    assert(q.front() == 8);
    assert(q.dequeue() == 8);
    assert(q.empty());
    assert(q.size() == 0);

    q.enqueue(1);
    q.enqueue(8);
    q.enqueue(3);

    cout << "queue: " << q.to_string() << endl;
    cout << " size: " << q.size() << endl;
    cout << "front: " << q.front() << endl;

    assert(q.dequeue() == 1);
    cout << endl;
    cout << "queue: " << q.to_string() << endl;
    cout << " size: " << q.size() << endl;
    cout << "front: " << q.front() << endl;
    cout << "... test_queue_deque() done: all tests passed\n";
} // test_queue_deque

int main()
{
    test_vec_deque();
    test_list_deque();
    // deque_list_test();
    stack_deque_test();
    test_queue_deque();
}
