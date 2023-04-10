// Wordlist.h

#pragma once

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
// ... you can write helper functions here (or before Wordlist) if you need them
// ...
//

//
// ... write functions to test every method of Wordlist ...
//
