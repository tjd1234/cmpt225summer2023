// queues.cpp

// Based on chp 5 of textbook.

#include "test.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//
// T is the type of the elements in the queue. T should have a copy constructor.
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

    // always include a virtual destructor in a base class
    virtual ~Queue_base() {}

    // return a string representation of the queue
    virtual string to_string() const = 0;
}; // class Queue_base

//
// Testing for queues.
//
void test_queue(Queue_base<int> *q)
{
    assert(q->empty());
    assert(q->size() == 0);
    assert(q->to_string() == "empty queue");
    cout << "q: " << q->to_string() << endl;

    q->enqueue(1);
    assert(!q->empty());
    assert(q->size() == 1);
    assert(q->front() == 1);
    cout << q->to_string() << endl;
    assert(q->to_string() == "{1} (front)");

    assert(q->dequeue() == 1);
    assert(q->empty());
    assert(q->size() == 0);
    assert(q->to_string() == "empty queue");

    q->enqueue(1);
    q->enqueue(8);
    assert(!q->empty());
    assert(q->size() == 2);
    assert(q->front() == 1);
    assert(q->dequeue() == 1);
    assert(q->size() == 1);
    assert(q->front() == 8);
    assert(q->dequeue() == 8);
    assert(q->empty());
    assert(q->size() == 0);
    assert(q->to_string() == "empty queue");

    q->enqueue(1);
    q->enqueue(8);
    q->enqueue(3);
    assert(q->front() == 1);
    cout << "queue: " << q->to_string() << endl;
    assert(q->to_string() == "{1, 8, 3} (front)");

    cout << "queue: " << q->to_string() << endl;
    cout << " size: " << q->size() << endl;
    cout << "front: " << q->front() << endl;

    assert(q->dequeue() == 1);
    assert(q->to_string() == "{8, 3} (front)");
    assert(q->front() == 8);
    cout << endl;
    cout << "queue: " << q->to_string() << endl;
    cout << " size: " << q->size() << endl;
    cout << "front: " << q->front() << endl;
    assert(q->to_string() == "{8, 3} (front)");
} // test_queue

//
// vector<int> implementation
//
template <typename T>
class Queue_vec : public Queue_base<int>
{
private:
    vector<T> v;

public:
    // put x on the back of the queue
    //
    // This implementation is inefficient because it requires shifting all the
    // elements in the vector to the right, which takes O(n) time. This makes
    // this implementation not very useful in practice: it shouldn't take O(n)
    // time to enqueue an element.
    void enqueue(const T &x)
    {
        v.insert(begin(v), x);
    }

    // remove and return the front element; error if queue is empty
    T dequeue()
    {
        assert(!empty());
        T x = v.back();
        v.pop_back();
        return x;
    }

    // return a reference to the front element; error if queue is empty
    const T &front() const
    {
        assert(!empty());
        return v.back();
    }

    // return true if stack is empty; default implementation is to check if
    // size() is 0
    virtual bool empty() const
    {
        return size() == 0;
    }

    // return the number of elements in the queue
    virtual int size() const
    {
        return v.size();
    }

    string to_string() const
    {
        if (empty())
            return "empty queue";
        int n = v.size();
        string s = "{" + std::to_string(v[n - 1]);
        for (int i = 1; i < v.size(); i++)
        {
            s += ", " + std::to_string(v[n - i - 1]);
        }
        s += "} (front)";
        return s;
    }
}; // class Queue_vec

void test_vec_queue()
{
    Test("test_vec_queue");
    Queue_vec<int> q;
    test_queue(&q);
} // test_vec_queue

//
// Singly linked list implementation
//
template <typename T>
class Queue_list : public Queue_base<T>
{
    struct Node
    {
        T data;
        Node *next;
    };

    Node *head = nullptr; // always points to the front node of queue
    Node *tail = nullptr; // always points to the back node of queue
    int num_elements = 0;

public:
    // put x on the back of the queue
    void enqueue(const T &x)
    {
        if (empty())
        {
            head = new Node{x, nullptr};
            tail = head;
        }
        else
        {
            tail->next = new Node{x, nullptr};
            tail = tail->next;
        }
        num_elements++;
    }

    // remove and return the front element; error if queue is empty
    T dequeue()
    {
        assert(!empty());
        if (head == tail)
        {
            tail = nullptr;
        }
        T result = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;

        num_elements--;
        return result;
    }

    // return a reference to the front element; error if queue is empty
    const T &front() const
    {
        assert(!empty());
        return head->data;
    }

    // return true if stack is empty; default implementation is to check if
    // size() is 0
    bool empty() const { return size() == 0; }

    // return the number of elements in the queue
    int size() const { return num_elements; }

    ~Queue_list()
    {
        while (!empty())
            dequeue();
    }

    string to_string() const
    {
        if (empty())
        {
            return "empty queue";
        }
        else
        {
            vector<string> values = {std::to_string(head->data)};
            Node *p = head->next;
            while (p != nullptr)
            {
                values.push_back(std::to_string(p->data));
                p = p->next;
            }
            string result = "{";
            for (int i = 0; i < values.size(); i++)
            {
                result += values[i];
                if (i < values.size() - 1)
                {
                    result += ", ";
                }
            }
            return result + "} (front)";
        }
    }
}; // class Queue_list

void test_list_queue()
{
    Test("test_list_queue");
    Queue_list<int> q;
    test_queue(&q);
} // test_list_queue

//
// Circular array implementation of queue.
//
// This treats the underlying array as circular, which allows the front_index
// back_index to wrap around the array. This makes enqueue and dequeuing both
// O(1) operations.
//
template <typename T>
class Queue_circular : public Queue_base<T>
{
    T *arr;          // pointer to the array
    int front_index; // index of the current front element
    int back_index;  // index of where the next back element will go
    int n;           // current number of elements

public:
    const int max_size = 0;

    // constructor
    Queue_circular(int max_size) : max_size(max_size)
    {
        arr = new T[max_size];
        front_index = 0;
        back_index = 0;
        n = 0;
    }

    // put x on the back of the queue
    void enqueue(const T &x)
    {
        assert(n < max_size);
        arr[back_index] = x;
        back_index = (back_index + 1) % max_size;
        n++;
    }

    // remove and return the front element; error if queue is empty
    T dequeue()
    {
        assert(!empty());
        // T result = arr[front_index];
        front_index = (front_index + 1) % max_size;
        n--;
        return result;
    }

    // return a reference to the front element; error if queue is empty
    const T &front() const
    {
        assert(!empty());
        return arr[front_index];
    }

    // return true if stack is empty; default implementation is to check if
    // size() is 0
    bool empty() const
    {
        return size() == 0;
    }

    // return the number of elements in the queue
    int size() const
    {
        return n;
    }

    ~Queue_circular()
    {
        delete[] arr;
    }

    string to_string() const
    {
        if (empty())
            return "empty queue";
        string s = "{" + std::to_string(arr[front_index]);
        for (int i = 1; i < size(); i++)
        {
            int loc = (front_index + i) % max_size;
            s += ", " + std::to_string(arr[loc]);
        }
        s += "} (front)";
        return s;
    }
}; // class Queue_circular

void test_Queue_circular()
{
    Test("test_Queue_circular");
    Queue_circular<int> q(100);
    test_queue(&q);
} // test_Queue_circular

int main()
{
    test_vec_queue();
    test_list_queue();
    test_Queue_circular();
}
