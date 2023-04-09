// a1.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <put your full name here!>
// St.# : <put your full SFU student number here>
// Email: <put your SFU email address here>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement the singly-linked list for the word list. You
    // can *add* extra variables/methods/features to this struct if you like,
    // but you must keep its name the same, and also keep the word, count, and
    // next variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *next;
    };

    //
    // ... your code goes here ...
    //

    //
    // ... you can write helper methods if you need them ...
    //

    //
    // ... write a default constructor that creates an empty Wordlist ...
    //

}; // class Wordlist

//
// ... you can write helper functions here if you need them ...
//

//
// ... write functions to test every method of Wordlist ...
//

//
// test_read() is a helper function that reads words, one at a time from cin,
// into a Wordlist and print the stats. You can use it to help test your
// Wordlist class, e.g.:
//
//
// > make a1
// g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a1.cpp   -o a1
//
// > ./a1 < tiny_shakespeare.txt
// Number of different words: 25670
//     Total number of words: 202651
//        Most frequent word: the 5437
//      Number of singletons: 14919 (58%)
//       Average word length: 7
//
// void test_read()
// {
//     Wordlist lst;
//     string w;
//     while (cin >> w)
//     {
//         lst.add_word(w);
//     }
//
//     lst.print_stats();
// }

int main()
{
    cout << "Welcome to assignment 1!\n";
    // ... call test functions here ...
}
