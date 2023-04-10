// a1_main.cpp

#include "Wordlist.h"

//
// test_read() is a helper function that reads words, one at a time from cin,
// into a Wordlist and print the stats. You can use it to help test your
// Wordlist class, e.g.:
//
//    > make a1_main
//    g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a1_main.cpp   -o a1_main
//   
//    > ./a1 < tiny_shakespeare.txt
//    Number of different words: 25670
//        Total number of words: 202651
//           Most frequent word: the 5437
//         Number of singletons: 14919 (58%)
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


//
// test_wordlist() is a helper function that tests individual methods in the
// Wordlist class. You should add your own tests for each method as you go. Call
// it every time you run the program.
//
// void test_wordlist()
// {
//     cout << "test_wordlist() called ...\n";
//     Wordlist lst;
//     assert(lst.num_different_words() == 0);
//     assert(lst.total_words() == 0);
//     assert(lst.is_sorted());
//     assert(!lst.contains("hello"));
//
//     // ... add more tests: test all methods! ...
//
//     cout << "... test_wordlist() done: all tests passed!\n";
// }

int main()
{
    cout << "Welcome to assignment 1!\n";
}
