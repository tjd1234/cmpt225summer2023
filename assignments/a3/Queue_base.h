// Queue_base.h

//
// Dont't change this file in any way!
//

#pragma once

#include <string>

using namespace std;

//
// Abstract data type for a queue.
//

template <typename T>
class Queue_base
{
public:
    //
    // C++ bases classes should always have a virtual destructor so that
    // destructor of inheriting classes will be called correctly.
    //
    virtual ~Queue_base() {}

    //
    // Returns the number of items currently in the queue.
    //
    // Performance: O(1) in the worst case
    //
    virtual int size() const = 0;

    //
    // Add an item to the back of the queue.
    //
    // Performance: O(1) in the worst case
    //
    virtual void enqueue(const T &item) = 0;

    //
    // Return a constant reference to the item at the front of the queue. 
    //
    // If the queue is empty it throws a runtime_error exception like this:
    //
    //     throw runtime_error("front: queue is empty");
    //
    // Performance: O(1) in the worst case
    //
    virtual const T &front() const = 0;

    //
    // Remove the item at the front of the queue.
    //
    // If the queue is empty it throws a runtime_error exception like this:
    //
    //     throw runtime_error("dequeue: queue is empty");
    //
    // Performance: O(1) in the worst case
    //
    virtual void dequeue() = 0;

}; // class Queue_base
