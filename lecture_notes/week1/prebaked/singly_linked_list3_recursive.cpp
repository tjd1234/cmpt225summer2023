// singly_linked_list3_recursive.cpp

//
// Like singly_linked_list3.cpp, but using recursion instead of loops.
//
// Private helper methods are used with that take starting nodes as parameters.
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

    // Returns the number of nodes in the list starting at p.
    // Uses recursion.
    int size(Node *p) const
    {
        if (p == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + size(p->next);
        }
    }

    // Prints the list starting at p. Uses recursion.
    void print(Node *p) const
    {
        if (p != nullptr)
        {
            cout << quote(p->data) << " ";
            print(p->next);
        }
    }

    // Returns true if the sub-lists starting at a and b are equal.
    bool equals(Node *a, Node *b) const
    {
        if (a == nullptr && b == nullptr)
        {
            return true;
        }
        else if (a == nullptr || b == nullptr)
        {
            return false;
        }
        else
        {
            return a->data == b->data && equals(a->next, b->next);
        }
    }

    // Returns true if one of the nodes, starting at p, contains the string s.
    // Uses recursion.
    bool contains(Node *p, const string &s) const
    {
        if (p == nullptr)
        {
            return false;
        }
        else if (p->data == s)
        {
            return true;
        }
        else
        {
            return contains(p->next, s);
        }
    }

public:
    bool empty() const
    {
        return head == nullptr;
    }

    // int size() const
    // {
    //     int count = 0;
    //     Node *p = head;
    //     while (p != nullptr)
    //     {
    //         count++;
    //         p = p->next;
    //     }
    //     return count;
    // }

    int size() const
    {
        return size(head);
    }

    // void print() const
    // {
    //     cout << "List: ";
    //     Node *p = head;
    //     while (p != nullptr)
    //     {
    //         cout << quote(p->data) << " ";
    //         p = p->next;
    //     }
    //     cout << endl;
    // }

    void print() const
    {
        cout << "List: ";
        print(head);
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
    // void clear()
    // {
    //     while (!empty())
    //     {
    //         pop_front();
    //     }
    // }

    void clear()
    {
        if (empty())
        {
            return;
        }
        else
        {
            pop_front();
            clear();
        }

        // Simpler implementation:
        // if (!empty()) {
        //     pop_front();
        //     clear();
        // }
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
    // bool operator==(const List &other) const
    // {
    //     // lists of different sizes can't be equal
    //     if (size() != other.size())
    //     {
    //         return false;
    //     }

    //     // walk along the nodes of each list, comparing values
    //     Node *p = head;
    //     Node *q = other.head;
    //     while (p != nullptr)
    //     {
    //         if (p->data != q->data)
    //         {
    //             return false;
    //         }
    //         p = p->next;
    //         q = q->next;
    //     }
    //     return true;
    // }

    bool operator==(const List &other) const
    {
        // lists of different sizes can't be equal
        if (size() != other.size())
        {
            return false;
        } else {
            return equals(head, other.head);
        }
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
    // bool contains(const string &s) const
    // {
    //     Node *p = head;
    //     while (p != nullptr)
    //     {
    //         if (p->data == s)
    //         {
    //             return true;
    //         }
    //         p = p->next;
    //     }
    //     return false;
    // }

    bool contains(const string &s) const
    {
        return contains(head, s);
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
