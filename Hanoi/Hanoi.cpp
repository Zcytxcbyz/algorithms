#include "../libgcmath/gcmath.h"
#include <iostream>
#include <cstdlib>
using namespace std;

gcnum Hanoi(gcnum n)
{
	if (n == 0) return 0;
	else return 2 * Hanoi(n - 1) + 1;
}
int main()
{
	gcnum n;
	cout << "n=";
	cin >> n;
	gcnum result = Hanoi(n);
	cout << result << endl;
	system("pause");
	return 0;
}
