#include <stdio.h>
 
int main()
{
    unsigned int num_casos;
    scanf("%d\n", &num_casos);
 
    unsigned int fib_rec[40];
    unsigned int fib_valor[40];
    fib_rec[0] = 0;
    fib_rec[1] = 0;
    fib_valor[0] = 0;
    fib_valor[1] = 1;
 
    unsigned int i;
    for (i = 2; i < 40; ++i)
    {
        fib_rec[i] = fib_rec[i-1] + fib_rec[i-2] + 2;
        fib_valor[i] = fib_valor[i-1] + fib_valor[i-2];
    }
 
    for (i = 0; i < num_casos; ++i)
    {
        unsigned int n;
        scanf("%d\n", &n);
        printf("fib(%d) = %d calls = %d\n", n, fib_rec[n], fib_valor[n]);
    }
}