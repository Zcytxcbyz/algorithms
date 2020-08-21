#include <iostream>
#include "../libRnpCalc/RnpCalc.h"
using namespace std;
int main(int argc, const char* argv[])
{
	if (argc == 2) cout << calculate(argv[1]) << endl;
	return 0;
}