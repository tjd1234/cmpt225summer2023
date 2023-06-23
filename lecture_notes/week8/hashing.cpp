// hashing.cpp

#include "test.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Map_base
{
public:
    // base classes should always have a virtual destructor
    virtual ~Map_base() {}

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns number of items in the hash table
    //
    virtual int size() const = 0;

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns maximum number of items the hash table can hold
    //
    virtual int max_size() const = 0;

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns load factor of the table
    //
    virtual double load_factor() const = 0;

    // return true if the hash table is empty
    virtual bool empty() const = 0;

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    add (key, value) pair to the hash table; if the key is already in the
    //    hash table, replace the old value with the new value
    //
    virtual void put(const string &key, const string &value) = 0;

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if a pair with the given key is in the hash table
    //
    virtual bool contains(const string &key) const = 0;

    //
    // Pre-condition:
    //    contains(key) is true
    // Post-condition:
    //    returns the value associated with the given key
    //
    virtual string get(const string &key) const = 0;

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    remove the pair with the given key from the hash table; does nothing
    //    if the key is not in the hash table
    //
    virtual void remove(const string &key) = 0;

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    removes all pairs from the hash table, making its size 0
    //
    virtual void clear() = 0;

}; // class Map_base

//
// Map_linear is a hash table that uses linear probing to resolve collisions.
//
class Map_linear : public Map_base
{
    enum class State
    {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Entry
    {
        string key = "";
        string value = "";
        State state = State::EMPTY;
    };

    string to_str(const Entry &e) const
    {
        switch (e.state)
        {
        case State::EMPTY:
            return "EMPTY";
        case State::DELETED:
            return "DELETED";
        case State::OCCUPIED:
            return "(" + e.key + "(" + to_string(hash(e.key)) + "), " + e.value + ")";
        default:
            return "ERROR";
        }
    }

    int num_pairs = 0;
    int cap;
    vector<Entry> arr;

    int hash(const string &s) const
    {
        int h = 0;
        for (int i = 0; i < s.length(); i++)
        {
            h += s[i];
        }
        return abs(h % cap);
    }

    // Returns the index of the pair with the given key. Or, if no pair has key,
    // the index of where it would be put. Could return -1 if the table is full.
    int find_index(const string &key) const
    {
        int i = hash(key);
        for (int count = 0; count < cap; count++)
        {
            if (arr[i].key == key)
            {
                return i;
            }
            else if (arr[i].state == State::EMPTY)
            {
                return i;
            }
            i = (i + 1) % cap;
        }
        return -1;
    }

public:
    //
    // Creates an empty hash table with the given capacity.
    //
    Map_linear(int capacity) : num_pairs(0), cap(capacity), arr(cap)
    {
        assert(cap >= 0);
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns number of items in the hash table
    //
    int size() const
    {
        return num_pairs;
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns maximum number of items the hash table can hold
    //
    int max_size() const
    {
        return cap;
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the load factor of the table
    //
    double load_factor() const
    {
        return (double)size() / max_size();
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    return true if the hash table is empty
    //
    virtual bool empty() const
    {
        return size() == 0;
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    add (key, value) pair to the hash table; if the key is already in the
    //    hash table, replace the old value with the new value
    //
    void put(const string &key, const string &value)
    {
        assert(size() < max_size());
        int i = find_index(key);
        if (arr[i].state == State::EMPTY || arr[i].state == State::DELETED) // add a new pair
        {
            arr[i].key = key;
            arr[i].value = value;
            arr[i].state = State::OCCUPIED;
            num_pairs++;
        }
        else // overwrite the value
        {
            arr[i].value = value;
        }
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if a pair with the given key is in the hash table
    //
    bool contains(const string &key) const
    {
        int i = find_index(key);
        return arr[i].state == State::OCCUPIED;
    }

    //
    // Pre-condition:
    //    contains(key) is true
    // Post-condition:
    //    returns the value associated with the given key
    //
    virtual string get(const string &key) const
    {
        assert(contains(key));
        int i = find_index(key);
        return arr[i].value;
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    remove the pair with the given key from the hash table; does nothing
    //    if the key is not in the hash table
    //
    void remove(const string &key)
    {
        int i = find_index(key);
        if (arr[i].state == State::EMPTY || arr[i].state == State::DELETED)
        {
            return;
        }
        else
        {
            arr[i].state = State::DELETED;
            num_pairs--;
        }
    }

    //
    // Pre-condition:
    //    none
    // Post-condition:
    //    removes all pairs from the hash table, making its size 0
    //
    void clear()
    {
        for (int i = 0; i < cap; i++)
        {
            arr[i].state = State::EMPTY;
        }
        num_pairs = 0;
    }

    string to_str() const
    {
        string result = "{" + to_string(size()) + "/" + to_string(cap) + "=" + to_string(load_factor());
        result += "\n  [";
        for (int i = 0; i < cap; i++)
        {
            result += to_str(arr[i]);
            if (i < cap - 1)
            {
                result += ", ";
            }
        }
        return result + "]}";
    }

}; // class Map_linear

void test_Map_linear()
{
    Test("Map_linear");

    const int N = 10;

    Map_linear map(N);
    assert(map.empty());
    assert(map.size() == 0);
    assert(map.max_size() == N);
    assert(!map.contains("hello"));

    map.put("mary", "doll");
    assert(!map.empty());
    assert(map.size() == 1);
    assert(map.contains("mary"));
    assert(map.get("mary") == "doll");
    assert(!map.contains("scott"));

    map.put("mary", "train");
    assert(!map.empty());
    assert(map.size() == 1);
    assert(map.contains("mary"));
    assert(map.get("mary") == "train");
    assert(!map.contains("scott"));

    map.remove("mary");
    assert(map.empty());
    assert(map.size() == 0);
    assert(!map.contains("mary"));
    assert(!map.contains("scott"));

    map.put("mary", "doll");
    map.put("scott", "doll");
    assert(!map.empty());
    assert(map.size() == 2);
    assert(map.contains("mary"));
    assert(map.get("mary") == "doll");
    assert(map.contains("scott"));
    assert(map.get("scott") == "doll");

    cout << map.to_str() << endl;

    map.remove("mary");
    assert(!map.empty());
    assert(map.size() == 1);
    assert(!map.contains("mary"));
    assert(map.contains("scott"));
    assert(map.get("scott") == "doll");

    map.remove("scott");
    assert(map.empty());
    assert(map.size() == 0);
    assert(!map.contains("mary"));
    assert(!map.contains("scott"));

    map.put("maria", "doll");
    map.put("sam", "doll");
    map.put("dave", "boat");
    map.put("peggy", "ball");
    map.put("ned", "balloon");
    assert(!map.empty());
    assert(map.get("maria") == "doll");
    assert(map.get("sam") == "doll");
    assert(map.get("dave") == "boat");
    assert(map.get("peggy") == "ball");
    assert(map.get("ned") == "balloon");

    cout << map.to_str() << endl;

    map.remove("sam");
    assert(map.get("maria") == "doll");
    // assert(map.get("sam") == "doll");
    assert(map.get("dave") == "boat");
    assert(map.get("peggy") == "ball");
    assert(map.get("ned") == "balloon");

    map.clear();
    for (int i = 0; i < N; i++)
    {
        map.put(to_string(i + 11), to_string(i));
    }
    assert(map.size() == N);
    assert(map.load_factor() == 1.0);
    for (int i = 0; i < N; i++)
    {
        assert(map.contains(to_string(i + 11)));
        assert(map.get(to_string(i + 11)) == to_string(i));
    }
    cout << map.to_str() << endl;
} // test_Map_linear

int main()
{
    test_Map_linear();
}
