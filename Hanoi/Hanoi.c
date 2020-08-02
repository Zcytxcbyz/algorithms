#include <stdlib.h>
#include "gmp.h"
#pragma comment(lib,"libgmp-10.lib")

mpz_t cout, input, temp;
void hanoi(mpz_t n, char a, char b, char c);

void hanoi(mpz_t n, char a, char b, char c)
{
    if (mpz_cmp_ui(n, 1)==0) 
    {
        mpz_add_ui(cout, cout, 1);
    }
    else 
    {
        mpz_sub_ui(temp, n, 1);
        hanoi(temp, a, c, b);
        mpz_add_ui(cout, cout, 1);
        hanoi(temp, b, a, c);
    }
}

int main()
{
    mpz_init(cout);
    mpz_init(input);
    gmp_printf("Count: ");
    gmp_scanf("%Zd", input);
    hanoi(input, 'A', 'B', 'C');
    gmp_printf("Total: ");
    gmp_printf("Zd\n", cout);
    mpz_clear(cout);
    mpz_clear(input);
    system("pause");
    return 0;
}

