/* SOLUÇÃO PARA PROBLEMA ABREVIAÇÕES */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodo
{
	char palavra[31];
	unsigned int repeticoes;
	struct nodo* prox;
} Nodo;

typedef struct
{
	Nodo* primeiro;
} Lista;

void inicializa_lista(Lista* l)
{
	l->primeiro = NULL;
}

/* Função para inserir nova palavra em lista ou incrementar contador de
   repetições caso a palavra já exista. */
void insere(Lista* l, char* palavra)
{
	Nodo* atual = l->primeiro;
	Nodo* ultimo = NULL;
	while (atual != NULL && strcmp(atual->palavra, palavra) != 0)
	{
		ultimo = atual;
		atual = atual->prox;
	}

	if (atual == NULL)
	{
		if (ultimo != NULL)
		{
			ultimo->prox = (Nodo*) malloc(sizeof(Nodo));
			strcpy(ultimo->prox->palavra, palavra);
			ultimo->prox->repeticoes = 1;
			ultimo->prox->prox = NULL;
		}
		else
		{
			l->primeiro = (Nodo*) malloc(sizeof(Nodo));
			strcpy(l->primeiro->palavra, palavra);
			l->primeiro->repeticoes = 1;
			l->primeiro->prox = NULL;
		}
	}
	else
		++(atual->repeticoes);
}

void destroi(Lista* l)
{
	Nodo* atual = l->primeiro;
	while (atual != NULL)
	{
		Nodo* temp = atual->prox;
		free(atual);
		atual = temp;
	}
}

int main()
{
	char input[10002], copia[10002];
	fgets(input, 10002, stdin);

	// Loop sobre casos de teste...
	while (input[0] != '.')
	{
		strcpy(copia, input);

		// Inicializando listas...
		Lista lista_palavras[26];
		unsigned int i;
		for (i = 0; i < 26; ++i)
			inicializa_lista(&lista_palavras[i]);

		// Contando as repetições de cada palavra...
		char* palavra = strtok(input, " \n");
		while (palavra != NULL)
		{
			insere(&lista_palavras[palavra[0] - 97], palavra);
			palavra = strtok(NULL, " \n");
		}

		// Calculando abreviações para cada letra inicial...
		char abreviacoes[26][31];
		unsigned int contador_abrev = 0;
		for (i = 0; i < 26; ++i)
		{
			Nodo* atual = lista_palavras[i].primeiro;
			abreviacoes[i][0] = '\0';
			int max_economia = 0;
			while (atual != NULL)
			{
				unsigned int tam = strlen(atual->palavra);
				int economia = (tam - 2) * atual->repeticoes;
				if (economia > max_economia)
				{
					max_economia = economia;
					strcpy(abreviacoes[i], atual->palavra);
				}
				atual = atual->prox;
			}
			if (max_economia > 0)
				++contador_abrev;
		}

		// Imprimindo texto abreviado...
		unsigned int primeira = 1;
		palavra = strtok(copia, " \n");
		while (palavra != NULL)
		{
			if (strcmp(palavra, abreviacoes[palavra[0] - 97]) == 0)
			{
				if (primeira == 1)
					printf("%c.", palavra[0]);
				else
					printf(" %c.", palavra[0]);
			}
			else
			{
				if (primeira == 1)
					printf("%s", palavra);
				else
					printf(" %s", palavra);
			}
			palavra = strtok(NULL, " \n");
			primeira = 0;
		}

		// Imprimindo lista de abreviações...
		printf("\n%d\n", contador_abrev);
		for (i = 0; i < 26; ++i)
		{
			if (strlen(abreviacoes[i]) > 0)
				printf("%c. = %s\n", (i+97), abreviacoes[i]);
		}

		// Liberando memória...
		for (i = 0; i < 26; ++i)
			destroi(&lista_palavras[i]);

		// Lendo novo caso de teste...
		fgets(input, 10002, stdin);
	}
}
