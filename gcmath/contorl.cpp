#include "gcmath.h"
#include <cstdlib>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	while (true)
	{
		gcnum a, b; char op;
		cout << "a = ";
		cin >> a;
		cout << "b = ";
		cin >> b;
		cout << "operator = ";
		cin >> op;
		switch (op)
		{
		case '+':
			cout << a << " + " << b << " = ";
			cout << (a + b) << endl << endl;
			; break;
		case '-':
			cout << a << " - " << b << " = ";
			cout << (a - b) << endl << endl;
			; break;
		case '*':
			cout << a << " * " << b << " = ";
			cout << (a * b) << endl << endl;
			; break;
		case '/':
			cout << a << " / " << b << " = ";
			cout << (a / b) << endl << endl;
			; break;
		case '%':
			cout << a << " % " << b << " = ";
			cout << (a % b) << endl << endl;
			; break;
		case '>':
			cout << a << " >> " << b << " = ";
			cout << (a >> b.getnum()) << endl << endl;
			; break;
		case '<':
			cout << a << " << " << b << " = ";
			cout << (a << b.getnum()) << endl << endl;
			; break;
		}
	}
}