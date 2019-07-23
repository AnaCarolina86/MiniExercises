#include <stdio.h>
 
int main()
{
    unsigned int num_hab;
    scanf("%d\n", &num_hab);
    while (num_hab != 0)
    {
        long long int comercio[num_hab];
        unsigned int i;
        for (i = 0; i < num_hab; ++i)
            scanf("%lld ", &comercio[i]);
 
        long long int trabalho = 0;
        for (i = 1; i < num_hab; ++i)
        {
            if (comercio[i-1] < 0)
                trabalho -= comercio[i-1];
            else
                trabalho += comercio[i-1];
            comercio[i] += comercio[i-1];
        }
        printf("%lld\n", trabalho);
        scanf("%d\n", &num_hab);
    }
}