#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
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
	c->v_agm = constroi_lista();
	c->marcado = 0;
	c->altura = 0;
	c->maior_dist_folha = 0;
	c->pai = NULL;

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

	FILE *f = fopen("inteiro_grafo.dot", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	Fila fclusters = constroi_fila();
	Fila marcados = constroi_fila();
	g->primeiro->marcado = 1;
	enfileira(g->primeiro, fclusters);
	cluster atual;

	fprintf(f, "strict graph \"g\" {\n");
	while(atual  = desenfileira(fclusters)){
		enfileira(atual, marcados);

		no no_v = primeiro_no(atual->vizinhos);
		cluster v;	
		for(;no_v; no_v = proximo_no(no_v)){
			v = conteudo(no_v); 
			fprintf(f, "\t\"id:%i cor:%i viz:%i\" -- \"id:%i cor:%i viz:%i\" \n",atual->id, atual->cor, tamanho_lista(atual->vizinhos), v->id, v->cor,tamanho_lista(v->vizinhos));
			if(!v->marcado){
				v->marcado = 1;
				enfileira(v, fclusters);
				
			}
		}
		
	}

	fprintf(f, "}\n");

	while(atual = desenfileira(marcados)){
		atual->marcado = 0;
	}

	destroi_fila(fclusters);
	destroi_fila(marcados);

	fclose(f);
}


void print_agm(grafo g){

	FILE *f = fopen("agm_grafo.dot", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	Fila fclusters = constroi_fila();
	Fila marcados = constroi_fila();
	g->primeiro->marcado = 1;
	enfileira(g->primeiro, fclusters);
	cluster atual;

	fprintf(f, "strict graph \"g\" {\n");
	while(atual  = desenfileira(fclusters)){
		enfileira(atual, marcados);

		no no_v = primeiro_no(atual->v_agm);
		cluster v;	
		for(;no_v; no_v = proximo_no(no_v)){
			v = conteudo(no_v); 
			fprintf(f, "\t\"id:%i cor:%i tam:%i df:%i\" -- \"id:%i cor:%i tam:%i df:%i\" \n",atual->id, atual->cor, atual->tamanho, atual->maior_dist_folha,
						 v->id, v->cor, v->tamanho, v->maior_dist_folha);
			if(!v->marcado){
				v->marcado = 1;
				enfileira(v, fclusters);
				
			}
		}
		
	}

	fprintf(f, "}\n");

	while(atual = desenfileira(marcados)){
		atual->marcado = 0;
	}

	destroi_fila(fclusters);
	destroi_fila(marcados);

	fclose(f);
}

void desmarcar(Fila f){

	cluster atual;
	while(atual = desenfileira(f)){
		atual->marcado = 0;
	}

}