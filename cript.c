#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char const *argv[]) {
 
    int i = 0, v = 0, i2 = 0, j = 0, op = 0, tam = 0;
    char c[1000] = {'0'}; char d[1000] = {'0'};
 
    scanf("%d\n",&op);
 
    for(j=0;j<op;++j){
         
        gets(c);
         
        tam=strlen(c);
 
        for (i=tam;i>=0;i--){
            v=c[i-1];
            if((v>=65&&v<=90)||(v>=97&&v<=122)){v=v+3;d[i2]=v;i2++;}
            else{d[i2]=v;i2++;}
        }
        tam=strlen(d);
        for (i=(tam/2);i<tam;i++){v=d[i];v=v-1;d[i]=v;}
        printf("%s\n",d);
        i = 0; i2 = 0;
    }
    return 0;
}