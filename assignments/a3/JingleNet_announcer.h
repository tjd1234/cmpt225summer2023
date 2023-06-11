// JingleNet_announcer.h

//
// Do not make any changes to this file!
//

#pragma once

#include "Announcement.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const string outfile_name = "announcements.txt";

class JingleNet_announcer
{
    ofstream outfile;
    static int announcement_count;
    static bool created;

public:
    JingleNet_announcer()
    {
        if (created)
        {
            throw runtime_error("JingleNet_announcer already created");
        }
        else
        {
            outfile = ofstream(outfile_name, std::ofstream::out);
            created = true;
        }
    }
    // singletons should not be copyable
    JingleNet_announcer(JingleNet_announcer &other) = delete;

    // singletons should not be assignable
    void operator=(const JingleNet_announcer &) = delete;

    void announce(const Announcement &m)
    {
        announcement_count++;
        outfile << announcement_count << ": "
                << m.to_string() << endl;
    }

    ~JingleNet_announcer()
    {
        outfile.close();
        cout << announcement_count << " announcements written to "
             << outfile_name << endl;
    }
}; // class JingleNet_announcer

// static variables must be initialized outside the class definition
int JingleNet_announcer::announcement_count = 0;
bool JingleNet_announcer::created = false;

// jnet is a global variable that can be used in any program that includes this
// file
JingleNet_announcer jnet;
