// singly_linked_list1.cpp

#include <cassert>
#include <iostream>

using namespace std;

string quote(string s)
{
    return "\"" + s + "\"";
}

struct Node
{
    string data;
    Node *next;
};

//
// head always points the the first node in the list.
// nullptr means the list is empty.
//
Node *head = nullptr;

bool empty()
{
    return head == nullptr;
}

int size()
{
    int count = 0;
    Node *p = head;
    while (p != nullptr)
    {
        count++;
        p = p->next;
    }
    return count;
}

void print_list()
{
    cout << "List: ";
    Node *p = head;
    while (p != nullptr)
    {
        cout << quote(p->data) << " ";
        p = p->next;
    }
    cout << endl;
}

//
// insert a new string at the front of the list
//
void push_front(const string &s)
{
    Node *n = new Node{s, head};
    head = n;
}

string pop_front()
{
    assert(!empty());
    string s = head->data;
    Node *p = head;
    head = head->next;
    delete p;
    return s;
}

void clear()
{
    while (!empty())
    {
        pop_front();
    }
}

int main()
{
    assert(head == nullptr);
    assert(size() == 0);

    push_front("cat");
    push_front("dog");
    push_front("bird");

    print_list();

    //
    // de-allocate all memory allocated with new
    //
    // clear();
}
