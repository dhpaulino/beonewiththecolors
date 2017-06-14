#include "lista.h"

typedef struct posicao{
	unsigned int lin, col;
} posicao;

struct cluster{
	int cor;
	int tamanho;
	posicao pos;
	lista vizinhos;
};

typedef struct cluster* cluster;

struct grafo{
	cluster primeiro;
	int tamanho;
};


typedef struct grafo* grafo;


void remover_cluster(cluster c);
cluster constroi_cluster(int cor,posicao pos,grafo g);
grafo constroi_grafo();
