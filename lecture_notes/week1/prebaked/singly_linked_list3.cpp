// linked_list3.cpp

//
// Like linked_lst3.cpp, but with these methods:
//
// - operator==
// - operator!=
// - contains
// - push_front_new (only adds a string if it's not already on the list)
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

    //
    // Returns true if this list is equal to other, false otherwise.
    //
    bool operator==(const List &other) const
    {
        // lists of different sizes can't be equal
        if (size() != other.size())
        {
            return false;
        }

        // walk along the nodes of each list, comparing values
        Node *p = head;
        Node *q = other.head;
        while (p != nullptr)
        {
            if (p->data != q->data)
            {
                return false;
            }
            p = p->next;
            q = q->next;
        }
        return true;
    }

    //
    // Returns true if this list is equal to other, false otherwise.
    //
    bool operator!=(const List &other) const
    {
        return !(*this == other);
    }

    //
    // Returns true if s is in the list, false otherwise.
    //
    bool contains(const string &s) const
    {
        Node *p = head;
        while (p != nullptr)
        {
            if (p->data == s)
            {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    //
    // Puts s at the front of the list as long as s does not
    // occur anywhere else in the list.
    //
    void push_front_new(const string &s)
    {
        if (!contains(s))
        {
            push_front(s);
        }
    }
}; // List

int main()
{
    List lst1;
    assert(lst1.empty());
    assert(lst1.size() == 0);
    assert(!lst1.contains("hello"));

    List lst2;
    assert(lst1 == lst2);
    assert(lst2 == lst1);
    assert(!(lst1 != lst2));

    lst1.push_front("hello");
    assert(lst1 != lst2);
    assert(lst2 != lst1);
    assert(lst1.contains("hello"));

    lst2.push_front("hello");
    assert(lst1 == lst2);
    assert(lst2 == lst1);
    assert(!(lst1 != lst2));

    lst1.push_front("world");
    assert(lst1.contains("hello"));
    assert(lst1.contains("world"));

    lst2.push_front("whirled");
    assert(lst1 != lst2);
    assert(lst2 != lst1);

    lst1.push_front_new("hello");
    assert(lst1.size() == 2);

    cout << "All tests passed!\n";
} // main
