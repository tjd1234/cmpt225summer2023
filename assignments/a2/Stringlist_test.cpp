// Stringlist_test.cpp

#include "Stringlist.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

struct Test
{
    string name;
    Test(const string &name)
        : name(name)
    {
        cout << "Calling " << name << " ...\n";
    }

    ~Test()
    {
        cout << "... " << name << " done: all tests passed\n";
    }
}; // struct Test

void test_default_constructor()
{
    Test("test_default_constructor");
    Stringlist lst;
    assert(lst.empty());
    assert(lst.size() == 0);
    assert(lst.to_string() == "{}");
}

void test_copy_constructor()
{
    Test("test_copy_constructor");
    Stringlist lst;
    Stringlist lst2(lst);
    assert(lst == lst2);

    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    assert(lst.size() == 3);
    assert(lst.get(0) == "A");
    assert(lst.get(1) == "B");
    assert(lst.get(2) == "C");
    assert(lst.to_string() == "{\"A\", \"B\", \"C\"}");
    Stringlist lst3(lst);
    assert(lst == lst3);
}

void test_assignment_operator()
{
    Test("test_assignment_operator");
    Stringlist lst;
    Stringlist lst2;
    // lst2 = lst;
    assert(lst == lst2);
    assert(lst.empty());
    assert(lst2.empty());

    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    assert(lst.size() == 3);
    assert(lst.get(0) == "A");
    assert(lst.get(1) == "B");
    assert(lst.get(2) == "C");
    assert(lst.to_string() == "{\"A\", \"B\", \"C\"}");

    lst2 = lst;
    assert(lst == lst2);
    assert(lst2.size() == 3);
    assert(lst2.get(0) == "A");
    assert(lst2.get(1) == "B");
    assert(lst2.get(2) == "C");
    assert(lst2.to_string() == "{\"A\", \"B\", \"C\"}");
}

void test_size_empty()
{
    Test("test_size_empty");
    Stringlist lst;
    assert(lst.empty());
    assert(lst.size() == 0);
    lst.insert_back("A");
    assert(!lst.empty());
    assert(lst.size() == 1);
    lst.insert_back("B");
    assert(!lst.empty());
    assert(lst.size() == 2);
    lst.insert_back("C");
    assert(!lst.empty());
    assert(lst.size() == 3);

    for (int i = 0; i < 10; i++)
    {
        lst.insert_back("D");
    }
    assert(!lst.empty());
    assert(lst.size() == 13);
}

void test_get()
{
    Test("test_get");
    Stringlist lst;
    lst.insert_front("A");
    lst.insert_front("B");
    lst.insert_front("C");
    assert(lst.get(0) == "C");
    assert(lst.get(1) == "B");
    assert(lst.get(2) == "A");
    lst.remove_at(1);
    assert(lst.get(0) == "C");
    assert(lst.get(1) == "A");
    lst.remove_at(0);
    assert(lst.get(0) == "A");
}

void test_index_of()
{
    Test("test_index_of");
    Stringlist lst;
    assert(lst.index_of("A") == -1);
    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    assert(lst.index_of("A") == 0);
    assert(lst.index_of("B") == 1);
    assert(lst.index_of("C") == 2);
    assert(lst.index_of("D") == -1);
    lst.remove_at(1);
    assert(lst.index_of("A") == 0);
    assert(lst.index_of("C") == 1);
    assert(lst.index_of("B") == -1);
    assert(lst.index_of("D") == -1);
    lst.remove_at(0);
    assert(lst.index_of("C") == 0);
    assert(lst.index_of("A") == -1);
    assert(lst.index_of("B") == -1);
    assert(lst.index_of("D") == -1);
}

void test_contains()
{
    Test("test_contains");
    Stringlist lst;
    assert(!lst.contains("A"));
    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C"); // lst == {"A", "B", "C"}
    assert(lst.contains("A"));
    assert(lst.contains("B"));
    assert(lst.contains("C"));
    assert(!lst.contains("D"));
    lst.remove_at(1); // lst == {"A", "C"}
    assert(lst.contains("A"));
    assert(lst.contains("C"));
    assert(!lst.contains("B"));
    assert(!lst.contains("D"));
    lst.remove_at(0); // lst == {"C"}
    assert(lst.contains("C"));
    assert(!lst.contains("A"));
    assert(!lst.contains("B"));
    assert(!lst.contains("D"));
}

void test_set()
{
    Test("test_set");
    Stringlist lst;
    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    assert(lst.to_string() == "{\"A\", \"B\", \"C\"}");
    lst.set(0, "D");
    assert(lst.to_string() == "{\"D\", \"B\", \"C\"}");
    lst.set(1, "E");
    assert(lst.to_string() == "{\"D\", \"E\", \"C\"}");
    lst.set(2, "F");
    assert(lst.to_string() == "{\"D\", \"E\", \"F\"}");
}

void test_insert_before()
{
    Test("test_insert_before");
    Stringlist lst;
    lst.insert_before(0, "A");
    assert(lst.to_string() == "{\"A\"}");
    lst.insert_before(0, "B");
    assert(lst.to_string() == "{\"B\", \"A\"}");
    lst.insert_before(1, "C");
    assert(lst.to_string() == "{\"B\", \"C\", \"A\"}");
    lst.insert_before(3, "D");
    assert(lst.to_string() == "{\"B\", \"C\", \"A\", \"D\"}");
}

void test_insert_back()
{
    Test("insert_back");
    Stringlist lst;
    lst.insert_back("A");
    assert(lst.to_string() == "{\"A\"}");
    lst.insert_back("B");
    assert(lst.to_string() == "{\"A\", \"B\"}");
    lst.insert_back("C");
    assert(lst.to_string() == "{\"A\", \"B\", \"C\"}");
}

void test_insert_front()
{
    Test("insert_front");
    Stringlist lst;
    lst.insert_front("A");
    assert(lst.to_string() == "{\"A\"}");
    lst.insert_front("B");
    assert(lst.to_string() == "{\"B\", \"A\"}");
    lst.insert_front("C");
    assert(lst.to_string() == "{\"C\", \"B\", \"A\"}");
}

void test_remove_at()
{
    Test("remove_at");
    Stringlist lst;
    lst.insert_back("A");
    lst.remove_at(0);
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.insert_back("A");
    lst.insert_back("B");
    lst.remove_at(0);
    assert(lst.get(0) == "B");
    assert(lst.to_string() == "{\"B\"}");
    lst.remove_at(0);
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    lst.remove_at(1);
    assert(lst.to_string() == "{\"A\", \"C\"}");

    lst.remove_all();
    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    lst.remove_at(2);
    assert(lst.to_string() == "{\"A\", \"B\"}");

    lst.remove_all();
    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    lst.remove_at(0);
    assert(lst.to_string() == "{\"B\", \"C\"}");
}

void test_remove_all()
{
    Test("remove_all");
    Stringlist lst;
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.insert_back("A");
    lst.remove_all();
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.insert_back("A");
    lst.insert_back("B");
    lst.remove_all();
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    lst.remove_all();
    assert(lst.empty());
    assert(lst.to_string() == "{}");
}

void test_remove_first()
{
    Test("remove_first");
    Stringlist lst;
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.remove_first("A");
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.insert_back("A");
    lst.remove_first("A");
    assert(lst.empty());
    assert(lst.to_string() == "{}");

    lst.insert_back("A");
    lst.remove_first("B");
    assert(lst.size() == 1);
    assert(lst.to_string() == "{\"A\"}");

    lst.remove_all();
    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("A");
    lst.remove_first("A");
    assert(lst.size() == 2);
    assert(lst.to_string() == "{\"B\", \"A\"}");
}

void test_to_string()
{
    Test("to_string");
    Stringlist lst;
    assert(lst.to_string() == "{}");
    lst.insert_back("A");
    assert(lst.to_string() == "{\"A\"}");
    lst.insert_back("B");
    assert(lst.to_string() == "{\"A\", \"B\"}");
    lst.insert_back("C");
    assert(lst.to_string() == "{\"A\", \"B\", \"C\"}");
}

void test_equals()
{
    Test("equals");
    Stringlist lst1;
    Stringlist lst2;
    assert(lst1 == lst2);
    assert(lst2 == lst1);

    lst1.insert_back("A");
    assert(lst1 != lst2);
    assert(lst2 != lst1);

    lst2.insert_back("A");
    assert(lst1 == lst2);
    assert(lst2 == lst1);

    lst1.insert_back("B");
    assert(lst1 != lst2);
    assert(lst2 != lst1);

    lst2.insert_back("B");
    assert(lst1 == lst2);
    assert(lst2 == lst1);
}

int main()
{
    test_default_constructor();
    test_assignment_operator();
    test_size_empty();
    test_get();
    test_index_of();
    test_contains();
    test_set();
    test_insert_before();
    test_insert_back();
    test_insert_front();
    test_remove_at();
    test_remove_all();
    test_remove_first();
    test_to_string();
    test_equals();

    cout << "\nAll Stringlist tests passed!\n";
} // main
