// cpu_timer_example.cpp

//
// Example of how to measure CPU time using clock().
//

#include <iostream>
#include <ctime>

using namespace std;

int main() {
    //
    // Simple way to measure CPU time used.
    //
    clock_t start = clock();
    
    string result;
    string s = "this is a test, this is only a test";
    for(int i = 0; i < 10000000; i++) {
        result += s + s;
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    cout << "Elapsed CPU time: " << elapsed_cpu_time_sec << " seconds" << endl;
}
