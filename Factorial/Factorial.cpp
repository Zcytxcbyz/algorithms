#include "../libgcmath/gcmath.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include<ctime>
using namespace std;
gcnum result = 1;
BOOL complete = false;
void output() 
{
    while (!complete)
    {
        cout << result << endl;
        Sleep(500);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    GCMath_Mulmode = 1;
    ULLONG n;
    clock_t startTime, endTime;
    cout << "n=";
    cin >> n;
    cout << endl;
    thread opt(output);
    startTime = clock();
    for (ULLONG i = 1; i <= n; ++i) {
        result *= gcnum(i);
    }
    endTime = clock();
    complete = true;
	ofstream ofs;
	ofs.open("Factorial_Result.txt");
	ofs << n << "!=" << result;
	ofs.close();
    opt.join();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    cout << endl << n << "!=" << result << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s." << endl;
    cout << "The result has been written to the file \"Factorial_Result.txt\"." << endl;
    cout << "Press any key to continue." << endl;
    getchar();
    getchar();
}
