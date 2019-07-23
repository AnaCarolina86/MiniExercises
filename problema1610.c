#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ESTRUTURAS E FUNÇÕES PARA LISTA ENCADEADA */

typedef struct nodo
{
	int vertice;
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

void insere(Lista* l, int vertice)
{
	if (l->primeiro == NULL)
	{
		l->primeiro = (Nodo*) malloc(sizeof(Nodo));
		l->primeiro->vertice = vertice;
		l->primeiro->prox = NULL;
	}
	else
	{
		Nodo* atual = l->primeiro;
		while (atual->prox != NULL)
			atual = atual->prox;
		atual->prox = (Nodo*) malloc(sizeof(Nodo));
		atual->prox->vertice = vertice;
		atual->prox->prox = NULL;
	}
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

int DFS(unsigned int v, Lista* adj, unsigned int* visitados)
{
	visitados[v] = 1;
	Nodo* atual = adj[v].primeiro;
	while (atual != NULL)
	{
		if (visitados[atual->vertice] == 1)
			return -1;
		if (visitados[atual->vertice] == 0)
		{
			if (DFS(atual->vertice, adj, visitados) == -1)
				return -1;
		}
		atual = atual->prox;
	}
	visitados[v] = 2;
	return 1;
}

int main()
{
	int num_casos = 2;
	scanf("%d", &num_casos);

	unsigned int i, j;
	for (i = 0; i < num_casos; ++i)
	{
		int num_vertices, num_arestas;
		num_vertices = 2;
		num_arestas = 1;
		scanf("%d %d", &num_vertices, &num_arestas);

		Lista adj[num_vertices];
		for (j = 0; j < num_vertices; ++j)
			inicializa_lista(&adj[j]);

		for (j = 0; j < num_arestas; ++j)
		{
			int origem, destino;
			scanf("%d %d", &origem, &destino);
			insere(&adj[origem-1], destino-1);
		}

		unsigned int visitados[num_vertices];
		for (j = 0; j < num_vertices; ++j)
			visitados[j] = 0;
		for (j = 0; j < num_vertices; ++j)
		{
			if (visitados[j] == 0)
			{
				if (DFS(j, adj, visitados) == -1)
				{
					printf("SIM\n");
					break;
				}
			}
		}
		if (j == num_vertices)
			printf("NAO\n");

		for (j = 0; j < num_vertices; ++j)
			destroi(&adj[j]);
	}
}
