// cmpt_trace.h

// By defining CMPT_TRACE_H, we avoid including this file more than once: if
// CMPT_TRACE_H is already defined, then the code is *not* included.
#ifndef CMPT_TRACE_H
#define CMPT_TRACE_H

#include <iostream>
#include <string>

namespace cmpt {

////////////////////////////////////////////////////////////////////////////////
//
// Trace is a helper class that prints a message when a function is called, and
// a corresponding message when the function ends. For example:
//
//     #include "cmpt_trace.h"
//     #include <iostream>
//     #include <string>
//
//     using namespace std;
//
//     int fib(int n) {
//         cmpt::Trace trace("fib(" + to_string(n) + ")");
//         if (n == 0) return 1;       // base case 1
//         if (n == 1) return 1;       // base case 2
//         return fib(n-1) + fib(n-2); // recursive case
//     }
//
//     int main() {
//         cout << fib(10) << "\n";
//     }
//
// The messages are indented according to how many times the function has been
// called, and the results can give you an idea of stack usage, and the order in
// which functions are called (plus the results can be visually striking).
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

class Trace {
private:
    string start_msg;
    string end_msg;
    int incr;           // indent increment, i.e. amount to indent/de-dent messages

    static int indent;  // indent is static, and so one copy is shared by all
                        // Trace objects

    void print_start() const;

    void print_end() const;
public:
    static const int default_incr = 3;

    Trace(const string& start_msg, const string& end_msg, int indent_size);
    Trace(const string& start_msg, const string& end_msg);
    Trace(const string& msg, int indent_size);
    Trace(const string& msg);

    int get_incr() const;
    void set_incr(int n);

    ~Trace();
}; // class Trace

//
// implementation
//

// static variables are initialized outside their class
int Trace::indent = 0;

void Trace::print_start() const {
    cout << string(indent, ' ') << start_msg << " ...\n";
    indent += incr;
}

void Trace::print_end() const {
    indent -= incr;
    cout << string(indent, ' ') << "... " << end_msg << "\n";
}

Trace::Trace(const string& start_msg, const string& end_msg, int indent_size) 
: start_msg(start_msg), end_msg(end_msg)
{
    set_incr(indent_size);
    print_start();
}

Trace::Trace(const string& start_msg, const string& end_msg) 
: Trace{start_msg, end_msg, default_incr}
{ }

Trace::Trace(const string& msg, int indent_size) 
: Trace{msg, msg, indent_size}
{ }

Trace::Trace(const string& msg) 
: Trace{msg, msg, default_incr}
{ }

int Trace::get_incr() const { return incr; }

void Trace::set_incr(int n) {
    incr = max(0, n);
}

Trace::~Trace() {
    print_end();
}


} // namespace cmpt

#endif
