// singly_linked_list2.cpp

//
// Like singly_linked_lst1.cpp, but now inside of a class.
//

#include <cassert>
#include <iostream>

using namespace std;

string quote(string s)
{
    return "\"" + s + "\"";
}

class List
{
    // private
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

public:
    // method
    bool empty() const
    {
        return head == nullptr;
    }

    int size() const
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

    void print() const
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

    //
    // remove the first node from the list (and return its value)
    //
    string pop_front()
    {
        assert(!empty());
        string s = head->data;
        Node *p = head;
        head = head->next;
        delete p;
        return s;
    }

    //
    // return a copy the string in the first node in the list
    //
    string peek_front() const
    {
        assert(!empty());
        return head->data;
    }

    //
    // remove all nodes from the list
    //
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    //
    // destructor
    //
    ~List()
    {
        clear();
    }

}; // List

int main()
{
    List lst;

    // add a string
    lst.push_front("hello");
    lst.print();

    // add another string
    lst.push_front("world");
    lst.print();

    string s = lst.pop_front();
    cout << "popped " << quote(s) << endl;
}
