// Wordlist_base.h

//
// Don't change this file in any way!
//

#pragma once

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Wordlist_base
{
    //
    // Virtual destructor: de-allocate all memory allocated by the class.
    //
    virtual ~Wordlist_base() {}

    //
    // Returns the number of times w occurs as a word in the word list.
    //
    virtual int get_count(const string &w) const = 0;

    //
    // Returns true if w is in the word list, false otherwise.
    //
    bool contains(const string &w) const
    {
        return get_count(w) > 0;
    }

    //
    // Returns the number of nodes in the word list.
    //
    virtual int num_different_words() const = 0;

    //
    // Returns the total number of words in the word list, i.e. the sum of the
    // word counts.
    //
    virtual int total_words() const = 0;

    //
    // Returns true if the words in the word list are in ascending sorted order,
    // false otherwise.
    //
    // For an AVL implementation, this should return true if the AVL tree is a
    // BST, and false otherwise.
    //
    virtual bool is_sorted() const = 0;

    //
    // Returns a string of the most frequent word in the format "word freq".
    // E.g. if the most frequent word is "the" with count 5437, then "the 5437"
    // is returned. 
    //
    // If there is a tie, the first word in the list is returned. For an AVL
    // implementation, this means return the word that occurs first
    // alphabetically.
    //
    // Assumes the list is not empty.
    //
    virtual string most_frequent() const = 0;

    //
    // Returns the number of nodes with count 1.
    //
    virtual int num_singletons() const = 0;

    //
    // Adds w to the word list. If w is already in the word list, then increment
    // its count. Otherwise add a new Node (with count 1) at the alphabetically
    // correct location for the word.
    //
    virtual void add_word(const string &w) = 0;

    //
    // Prints useful statistics about the word list.
    //
    void print_stats() const
    {
        cout << "Number of different words: " << num_different_words() << endl;
        cout << "    Total number of words: " << total_words() << endl;
        cout << "       Most frequent word: " << most_frequent() << endl;
        cout << "     Number of singletons: " << num_singletons()
             << setprecision(0) << fixed
             << " (" << 100.0 * num_singletons() / num_different_words() << "%)"
             << endl;
    }

    //
    // Prints the words in the word list in alphabetical order by word, along
    // with their counts. The first word is 1, the second 2, and so on, e.g.:
    //
    //   ❯ ./a5_main < small.txt
    //   1. {"This", 1}
    //   2. {"a", 2}
    //   3. {"is", 2}
    //   4. {"or", 1}
    //   5. {"test", 1}
    //   6. {"test?", 1}
    //   7. {"this", 1}
    //
    virtual void print_words() const = 0;

}; // struct Wordlist_base
