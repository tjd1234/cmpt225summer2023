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

    // Returns a pointer to the first node in the list that contains s. If no
    // node contains s, returns nullptr.
    Node *walk_to(const string &s) const
    {
        Node *p = head;
        while (p != nullptr)
        {
            if (p->data == s)
            {
                return p;
            }
            p = p->next;
        }
        // return nullptr if we didn't find s
        return nullptr;
    }

    // Returns a pointer to the ith node in the list.
    Node *walk_to(int i) const
    {
        Node *p = head;
        for (int j = 0; j < i; j++)
        {
            p = p->next;
        }
        return p;
    }

    // Remove the node after p from the list. Can't delete the first element:
    // use pop_front for that.
    //
    // Assume p points to a valid node in the list.
    void remove_after(Node *p)
    {
        assert(p != nullptr);
        Node *n = p->next;
        p->next = n->next;
        delete n;
    }

public:
    //
    // Tests if the list is empty.
    //
    bool empty() const
    {
        return head == nullptr;
    }

    //
    // Return the number of nodes in the list.
    //
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

    //
    // Print the list to cout.
    //
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
    // Insert a new string at the front of the list.
    //
    void push_front(const string &s)
    {
        Node *n = new Node{s, head};
        head = n;
    }

    //
    // Remove the first node from the list (and return its value).
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
    // Return a copy the string in the first node in the list.
    //
    string peek_front() const
    {
        assert(!empty());
        return head->data;
    }

    //
    // Remove all nodes from the list.
    //
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    //
    // Destructor.
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
        return walk_to(s) != nullptr;
    }

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

    //
    // Puts s at the front of the list as long as s does not occur anywhere else
    // in the list.
    //
    void push_front_new(const string &s)
    {
        if (!contains(s))
        {
            push_front(s);
        }
    }

    //
    // Remove the node at location i.
    //
    void remove(int i)
    {
        assert(i >= 0 && i < size());
        if (i == 0)
        {
            pop_front();
        }
        else
        {
            Node *p = walk_to(i - 1);
            remove_after(p);
        }
    }

    //
    // Reverse the order of the elements of the list.
    //
    void reverse()
    {
        Node *p = head;
        Node *q = nullptr;
        while (p != nullptr)
        {
            Node *r = p->next;
            p->next = q;
            q = p;
            p = r;
        }
        head = q;
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

    // test reverse
    lst1.clear();
    assert(lst1.empty());
    assert(lst1.size() == 0);
    lst1.reverse();
    assert(lst1.empty());
    assert(lst1.size() == 0);

    lst1.push_front("hello");
    assert(lst1.size() == 1);
    assert(lst1.peek_front() == "hello");
    lst1.reverse();
    assert(lst1.size() == 1);
    assert(lst1.peek_front() == "hello");

    lst1.push_front("world");
    lst1.reverse();
    assert(lst1.size() == 2);
    assert(lst1.peek_front() == "hello");
    lst1.pop_front();
    assert(lst1.peek_front() == "world");

    lst1.clear();
    lst1.push_front("A");
    lst1.push_front("B");
    lst1.push_front("C");
    lst1.reverse();
    assert(lst1.size() == 3);
    assert(lst1.peek_front() == "A");
    lst1.pop_front();
    assert(lst1.peek_front() == "B");
    lst1.pop_front();
    assert(lst1.peek_front() == "C");
    lst1.pop_front();
    assert(lst1.empty());

    cout << "All tests passed!\n";
} // main
