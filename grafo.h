#include "lista.h"
#include "fila.h"


typedef struct posicao{
	unsigned int lin, col;
} posicao;

struct cluster{
	int cor;
	int id;
	int tamanho;
	int marcado;
	posicao pos;
	lista vizinhos;

	struct cluster* pai;
	int altura;
	lista v_agm;
};

typedef struct cluster* cluster;

struct grafo{
	cluster primeiro;
	int tamanho;
};


typedef struct grafo* grafo;


void remover_cluster(cluster c);
cluster constroi_cluster(int cor, int id,posicao pos);
grafo constroi_grafo();
void print_grafo(grafo g);
void print_agm(grafo g);
void desmarcar(Fila f);