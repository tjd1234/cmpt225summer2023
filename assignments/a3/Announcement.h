// Announcement.h

//
// Do not make any changes to this file!
//

#pragma once

#include <cassert>
#include <string>

using namespace std;

//
// Each announcement has a rank.
//
enum class Rank
{
    SNOWMAN = 1, // lowest rank
    ELF1 = 2,
    ELF2 = 3,
    REINDEER = 4,
    SANTA = 5 // highest rank
};

//
// Convert a rank to a string.
//
string to_string(Rank r)
{
    switch (r)
    {
    case Rank::SNOWMAN:
        return "snowman";
    case Rank::ELF1:
        return "elf1";
    case Rank::ELF2:
        return "elf2";
    case Rank::REINDEER:
        return "reindeer";
    case Rank::SANTA:
        return "santa";
    default:
        assert(false);
    }
}

//
// Convert a string to a rank.
//
Rank to_rank(const string &s)
{
    if (s == "snowman")
        return Rank::SNOWMAN;
    if (s == "elf1")
        return Rank::ELF1;
    if (s == "elf2")
        return Rank::ELF2;
    if (s == "reindeer")
        return Rank::REINDEER;
    if (s == "santa")
        return Rank::SANTA;
    assert(false);
}

//
// Conveniently print a rank.
//
ostream &operator<<(ostream &out, Rank r)
{
    return out << to_string(r);
}

//
// Return s in ""-marks.
//
string quote(const string &s)
{
    return "\"" + s + "\"";
}

/////////////////////////////////////////////////////////////////////////////

//
// An announcement stores all the information needed for an announcement.
//
// Importantly, Announcement objects are *immutable*. Once an Announcement is
// constructed, it cannot be changed in any way. You can only read its variables
// with getters, or convert it to a string.
//
class Announcement
{
private:
    //
    // The name of the person sending the announcement. This is a a username
    // consisting of one or more letters chosen from A - Z, a - z, and digits
    // 0-9. No other characters are allowed in sender_name.
    //
    string sender_name;

    //
    // The rank of the announcement, e.g. Rank::SNOWMAN is the lowest rank,
    // Rank::SANTA is the highest.
    //
    Rank rank;

    //
    // The contents of the announcement.
    //
    string text;

public:
    //
    // Constructor
    //
    Announcement(const string &sender_name, Rank rank, const string &text)
        : sender_name(sender_name), rank(rank), text(text)
    {
    }

    //
    // Copy constructor
    //
    Announcement(const Announcement &other)
        : sender_name(other.sender_name), rank(other.rank), text(other.text)
    {
    }

    //
    // Read announcements formatted like this:
    //
    //   <sender_name> <rank> <text>
    //
    // For example:
    //
    //   greenie elf2 send candy canes
    //
    Announcement(string line)
    {
        // get the senders name
        size_t pos = line.find(' ');
        sender_name = line.substr(0, pos);
        line = line.substr(pos + 1);

        // get their rank
        pos = line.find(' ');
        rank = to_rank(line.substr(0, pos));
        line = line.substr(pos + 1);

        // get the text
        text = line;
    }

    string to_string() const
    {
        return "{" + sender_name +
               ", " + ::to_string(rank) +
               ", " + quote(text) +
               "}";
    }

    //
    // getters
    //
    string get_sender_name() const { return sender_name; }
    Rank get_rank() const { return rank; }
    string get_text() const { return text; }

    //
    // Test if this announcement is the same as another.
    //
    bool operator==(const Announcement &other) const
    {
        return sender_name == other.sender_name &&
               rank == other.rank &&
               text == other.text;
    }

}; // struct Announcement

//
// Conveniently print announcements.
//
ostream &operator<<(ostream &out, const Announcement &a)
{
    return out << a.to_string();
}
