#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "grafo.h"
#define N_CORES 4



grafo constroi_grafo(){
	grafo g = malloc(sizeof(struct grafo));
	if(!g)
		return NULL;
	g->tamanho = 0;
	return g;
}

cluster constroi_cluster(int cor,posicao pos, grafo g){
	cluster c = malloc(sizeof(struct cluster));
	if(!c)
		return NULL;
	c->tamanho = 0;
	c->cor = cor;
	c->pos = pos;
	c->vizinhos = constroi_lista();

	if(!g->primeiro){
		g->primeiro = c;
	}
	g->tamanho++;
	return c;
}



void remover_cluster(cluster c){
	
	no no_v = primeiro_no(c->vizinhos);
	cluster v = conteudo(no_v);
	
	for(;no_v; no_v = proximo_no(no_v), v = conteudo(no_v) ){
		remove_pelo_conteudo(c, v->vizinhos);
	}
}
