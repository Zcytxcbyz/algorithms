#include "gcmath.h"
#include <cstdlib>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	gcnum a = "34324343243243252335325";
	gcnum b = "94858";
	gcnum quo, rem;
	a.INTDIV(b, quo, rem);
	cout << a << endl;
	cout << b << endl << endl;
	cout << quo << endl;
	cout << rem << endl;
	system("pause");
}