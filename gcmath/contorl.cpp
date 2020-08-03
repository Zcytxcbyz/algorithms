#include "gcmath.h"
#include <cstdlib>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	gcnum a, b; int op;
	while (true)
	{
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;
		cout << "0.+  1.-  2.*  3./  4.%" << endl;
		cout << "operator = ";
		cin >> op;
		switch (op)
		{
		case 0:
			cout << a << " + " << b << " = ";
			cout << (a + b) << endl << endl;
			; break;
		case 1:
			cout << a << " - " << b << " = ";
			cout << (a - b) << endl << endl;
			; break;
		case 2:
			cout << a << " * " << b << " = ";
			cout << (a * b) << endl << endl;
			; break;
		case 3:
			cout << a << " / " << b << " = ";
			cout << (a / b) << endl << endl;
			; break;
		case 4:
			cout << a << " % " << b << " = ";
			cout << (a % b) << endl << endl;
			; break;
		}
	}
}