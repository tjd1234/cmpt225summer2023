// announcement_demo.cpp

#include "Announcement.h"
#include <iostream>

using namespace std;

int main()
{
    Announcement a1("yumyum", Rank::SANTA, "I love Christmas!");
    cout << a1 << endl; // prints: {yumyum, santa, "I love Christmas!"}

    // copy another Announcement
    Announcement a2(a1);
    cout << a2 << endl; // prints: {yumyum, santa, "I love Christmas!"}

    // parse a string of the form "sender_name rank text"
    Announcement a3("yumyum santa I love Christmas!");
    cout << a3 << endl; // prints: {yumyum, santa, "I love Christmas!"}
}