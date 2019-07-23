#include <stdio.h>
#include <stdlib.h>
 
int main(){
 
    char letras[27];
    int n, c = 65, cont = 1, i, j, k;
    char aux1, aux2;
     
    while(scanf("%i", &n) && n != 0){
        c = 65;
        for(i = 0; i < 26; i ++){
            letras[i+1] = c;
            c++;
        }
        printf("Instancia %i\n", cont);
        for (j = 0; j < n; j++){
            scanf("%i", &c);
            printf("%c", letras[c]);
            aux1 =  letras[1];
            for (k = 1; k < c; k++){
                aux2 = letras[k+1];
                letras[k+1] = aux1;
                aux1 = aux2;
            }
            letras[1] = aux1;
        }
        printf("\n\n");
        cont++;
    }
 
    return 0;
}