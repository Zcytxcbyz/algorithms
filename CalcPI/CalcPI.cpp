#include "../libgcmath/gcmath.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <ctime>
using namespace std;
gcnum result = 3;

int main()
{
	ios_base::sync_with_stdio(false);
	gcnum n;
	gcnum i = 2;
	int pox = 1;
	clock_t startTime, endTime;
	cout << "n=";
	cin >> n;
	cout << endl;
	GCMath_Accuracy = stoi(n.getstr());
	startTime = clock();
	for (gcnum i = 2; i < n + 2; i += gcnum(2)) {
		result += gcnum(4) / (pox * i * (i + 1) * (i + 2));
		pox = -pox;
		cout << result << endl;
	}
	endTime = clock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << endl << "PI=" << result << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s." << endl;
	cout << "Press any key to continue." << endl;
	getchar();
	getchar();
}
