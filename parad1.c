#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
long long vet[100001];
long long desloca = 0;
int habitantes;
int i; //contador

	for(i=0; i<100001; i++){
		vet[i] = '\0'; //limpo o vetor
	}
	
	while(1){
		scanf("%d", &habitantes);
		if(habitantes == 0){ //condicao de parada
			return 0; 
		}
		for(i=0; i<habitantes; i++){
			scanf("%lld", &vet[i]);//leitura dos valores
		}
		for(i=0; i<habitantes; i++){
			if((i+1) < habitantes){
				vet[i+1] += vet[i]; 
			}
			desloca += abs(vet[i]);
									
		}
		printf("%lld\n", desloca);	
		desloca = 0; //limpo a variavel
		for(i=0; i<habitantes; i++){
			vet[i] = '\0'; //limpo o vetor
		}
	}

return 0;
}