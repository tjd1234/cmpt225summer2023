// getline_demo.cpp

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//
// argc is the number of command-line arguments, i.e. the size of argv
//
// argv is an array of strings, where each string is a command-line argument;
//      argv[0] is the program name that is run, e.g. "./getline_demo"
int main(int argc, char *argv[])
{
    // Check that the user provided a filename.
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        //
        // Returning a non-zero value from main indicates the program ended
        // abnormally. We don't care about main return values, but in some cases
        // they are useful. If this program was used as part of a shell script,
        // then the script might check this return value in an if-statement.
        //
        return 1; 
    }

    //
    // Read the contents of the file named by argv[1], and print each line.
    //
    string filename = argv[1];
    cout << "Printing " << filename << " ..." << endl;
    ifstream infile(filename);
    string line;
    int num_lines = 0;
    while (getline(infile, line))
    {
        num_lines++;
        cout << "line " << num_lines << ": " << line << endl;
    }

} // main
