#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ESTRUTURAS E FUNÇÕES PARA LISTA ENCADEADA */

typedef struct nodo
{
	int destino;
	int metros;
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

void insere(Lista* l, int destino, int metros)
{
	if (l->primeiro == NULL)
	{
		l->primeiro = (Nodo*) malloc(sizeof(Nodo));
		l->primeiro->destino = destino;
		l->primeiro->metros = metros;
		l->primeiro->prox = NULL;
	}
	else
	{
		Nodo* atual = l->primeiro;
		while (atual->prox != NULL)
			atual = atual->prox;
		atual->prox = (Nodo*) malloc(sizeof(Nodo));
		atual->prox->destino = destino;
		atual->prox->metros = metros;
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

/* ESTRUTURAS E FUNÇÕES PARA HEAP BINÁRIO */

typedef struct
{
	int valor;
	int vertice;
} Elemento;

void conserta_heap(Elemento* heap, unsigned int len, unsigned int atual, unsigned int* posicoes)
{
	unsigned int esquerda = atual * 2 + 1;
	unsigned int direita = atual * 2 + 2;
	unsigned int menor = atual;

	if (esquerda < len & heap[esquerda].valor < heap[menor].valor)
		menor = esquerda;
	if (direita < len & heap[direita].valor < heap[menor].valor)
		menor = direita;

	// Trocando elementos...
	Elemento temp = heap[atual];
	heap[atual] = heap[menor];
	heap[menor] = temp;

	// Atualizando mapeamento vertice -> posicao do vetor...
	posicoes[heap[atual].vertice] = atual;
	posicoes[heap[menor].vertice] = menor;

	if (menor != atual)
		conserta_heap(heap, len, menor, posicoes);
}

void remover_minimo(Elemento* heap, unsigned int len, unsigned int* posicoes)
{
	Elemento temp = heap[0];
	heap[0] = heap[len - 1];
	heap[len - 1] = temp;
	posicoes[heap[0].vertice] = 0;
	posicoes[heap[len - 1].vertice] = len - 1;
	conserta_heap(heap, len - 1, 0, posicoes);
}

void diminuir_valor(Elemento* heap, unsigned int indice, int valor, unsigned int* posicoes)
{
	heap[indice].valor = valor;
	unsigned int pai = (indice - 1) / 2;
	while (indice > 0 && heap[pai].valor > heap[indice].valor)
	{
		unsigned int i;
		Elemento temp = heap[pai];
		heap[pai] = heap[indice];
		heap[indice] = temp;

		posicoes[heap[pai].vertice] = pai;
		posicoes[heap[indice].vertice] = indice;

		indice = pai;
		pai = (indice - 1) / 2;
	}
}

int main()
{
	// Lendo dimensões do grafo...
	int num_vertices, num_arestas;
	scanf("%d %d\n", &num_vertices, &num_arestas);

	while (num_vertices != 0)
	{
		// Construindo estrutura de adjacência...
		int gasto = 0;
		unsigned int i, j;
		//Lista adj[num_vertices];
		Lista* adj = (Lista*) malloc(sizeof(Lista) * num_vertices);
		for (i = 0; i < num_vertices; ++i)
			inicializa_lista(&adj[i]);
		for (i = 0; i < num_arestas; ++i)
		{
			int x, y, metros;
			scanf("%d %d %d\n", &x, &y, &metros);
			insere(&adj[x], y, metros);
			insere(&adj[y], x, metros);
			gasto += metros;
		}

		// Inicializando min-heap com as distancias parciais...
		//Elemento heap_distancias[num_vertices];
		Elemento* heap_distancias = (Elemento*) malloc(sizeof(Elemento) * num_vertices);
		//unsigned int posicoes[num_vertices];
		unsigned int* posicoes = (unsigned int*) malloc(sizeof(unsigned int) * num_vertices);
		for (i = 0; i < num_vertices; ++i)
		{
			heap_distancias[i].valor = INT_MAX;
			heap_distancias[i].vertice = i;
			posicoes[i] = i;
		}
		heap_distancias[0].valor = 0;


		// ALGORITMO DE PRIM
		int peso = 0;
		for (i = 0; i < num_vertices; ++i)
		{
			// Incluindo aresta na AGM...
			int imin = heap_distancias[0].vertice;
			peso += heap_distancias[0].valor;

			// Extrair minimo...
			remover_minimo(heap_distancias, num_vertices - i, posicoes);

			// Atualizando distancias...
			Nodo* atual = adj[imin].primeiro;
			while (atual != NULL)
			{
				if (posicoes[atual->destino] < (num_vertices - i - 1) && heap_distancias[posicoes[atual->destino]].valor > atual->metros)
					diminuir_valor(heap_distancias, posicoes[atual->destino], atual->metros, posicoes);
				atual = atual->prox;
			}
		}
		printf("%d\n", gasto - peso);

		// Lendo novo caso de teste...
		for (i = 0; i < num_vertices; ++i)
			destroi(&adj[i]);
		free(adj);
		free(heap_distancias);
		free(posicoes);
		scanf("%d %d\n", &num_vertices, &num_arestas);
	}
}
