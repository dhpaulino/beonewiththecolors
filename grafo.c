#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "fila.h"
#define N_CORES 4



grafo constroi_grafo(){
	grafo g = malloc(sizeof(struct grafo));
	if(!g)
		return NULL;
	g->tamanho = 0;
	return g;
}

cluster constroi_cluster(int id, int cor,posicao pos){
	cluster c = malloc(sizeof(struct cluster));
	if(!c)
		return NULL;
	c->tamanho = 0;
	c->id = id;
	c->cor = cor;
	c->pos = pos;
	c->vizinhos = constroi_lista();
	c->marcado = 0;

	/*if(!g->primeiro){
		g->primeiro = c;
	}
	g->tamanho++;*/
	return c;
}

void remover_cluster(cluster c){
	
	no no_v = primeiro_no(c->vizinhos);
	cluster v;
	
	for(;no_v; no_v = proximo_no(no_v)){
		 v = conteudo(no_v);
		remove_pelo_conteudo(c, v->vizinhos);
	}
}


void print_grafo(grafo g){

	Fila fclusters = constroi_fila();
	Fila marcados = constroi_fila();
	g->primeiro->marcado = 1;
	enfileira(g->primeiro, fclusters);
	cluster atual;

	printf("strict graph \"g\" {\n");
	while(atual  = desenfileira(fclusters)){
		enfileira(atual, marcados);

		no no_v = primeiro_no(atual->vizinhos);
		cluster v;	
		for(;no_v; no_v = proximo_no(no_v)){
			v = conteudo(no_v); 
			if(!v->marcado){
				v->marcado = 1;
				enfileira(v, fclusters);
				printf("id:%i,cor:%i -- id:%i,cor:%i \n",atual->id, atual->cor, v->id, v->cor);
			}
		}
		
	}

	printf("}");

	while(atual = desenfileira(marcados)){
		atual->marcado = 0;
	}

	destroi_fila(fclusters);
	destroi_fila(marcados);
}