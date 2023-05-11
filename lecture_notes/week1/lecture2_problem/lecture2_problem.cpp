// lecture2_problem.cpp

#include <iostream>

using namespace std;

//
// Make an array of 3000 integers, and initialize with 4, 5, 9 repeated like
// this:
//
//     4, 5, 9, 4, 5, 9, 4, 5, 9, ..., 4, 5, 9
//     ^                                     ^
//     |                                     |
//    index 0                            index 2999
//

void solution1()
{
    // using a constant makes it easy to change the array size
    const int N = 3000;

    // make the array
    int arr[N];

    // initialize the array
    for (int i = 0; i < N; i++)
    {
        if (i % 3 == 0)
        {
            arr[i] = 4;
        }
        else if (i % 3 == 1)
        {
            arr[i] = 5;
        }
        else
        {
            arr[i] = 9;
        }
    }

    // print the results
    for (int i = 0; i < N; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

void solution2()
{
    // using a constant makes it easy to change the array size
    const int N = 9;

    // make the array
    int arr[N];

    // initialize the array
    for (int i = 0; i < N; i += 3)
    {
        arr[i] = 4;
        arr[i + 1] = 5;
        arr[i + 2] = 9;
    }

    // print the results
    for (int i = 0; i < N; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

// arr is an array of size N, where N is a multiple of 3
// i is the index we are initializing: 0 <= i < N
void recursive_init(int *arr, int N, int i)
{
    if (i < N)
    {
        if (i % 3 == 0)
        {
            arr[i] = 4;
        }
        else if (i % 3 == 1)
        {
            arr[i] = 5;
        }
        else
        {
            arr[i] = 9;
        }
        recursive_init(arr, N, i + 1);
    }
}

// uses recursion
void solution3()
{
    const int N = 9;
    int arr[N];
    recursive_init(arr, N, 0);

    // print the results
    for (int i = 0; i < N; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

int main()
{
    // solution1();
    // solution2();
    // solution3();
}
