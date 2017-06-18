#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "fila.h"
#include "grafo.h"
#include "lista.h"
#define passei_fundo 6



#define N 3

typedef struct {
	int nlinhas;
	int ncolunas;
	int ncores;
	int **mapa;
	unsigned qtd_flood;
	posicao *boarda;
} tmapa;


void carrega_mapa(tmapa *m) {
	int i, j;

	scanf("%d", &(m->nlinhas));
	scanf("%d", &(m->ncolunas));
	scanf("%d", &(m->ncores));
	m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));

	for(i = 0; i < m->nlinhas; i++) {
		m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));

		for(j = 0; j < m->ncolunas; j++)
			scanf("%d", &(m->mapa[i][j]));
  }
}

void mostra_mapa(tmapa *m) {
	int i, j;

	printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);

	for(i = 0; i < m->nlinhas; i++) {
		for(j = 0; j < m->ncolunas; j++)
			if(m->ncores > 10)
				printf("%02d ", m->mapa[i][j]);
			else
				printf("%d ", m->mapa[i][j]);

		printf("\n");
  }
}
void mostra_mapa_cor(tmapa *m) {
	int i, j;
	char* cor_ansi[] = { "\x1b[0m",
				"\x1b[31m", "\x1b[32m", "\x1b[33m",
				"\x1b[34m", "\x1b[35m", "\x1b[36m",
				"\x1b[37m", "\x1b[30;1m", "\x1b[31;1m",
				"\x1b[32;1m", "\x1b[33;1m", "\x1b[34;1m",
				"\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m"
			};


	if(m->ncores > 15) {
		mostra_mapa(m);

		return;
	}
}



void copia_mapa(tmapa *fonte, tmapa *copia) {
	copia->nlinhas = fonte->nlinhas;
	copia->ncolunas = fonte->ncolunas;
	copia->ncores = fonte->ncores;

	for (int i = 0; i < fonte->nlinhas; i++)
		for (int j = 0; j < fonte->ncolunas; j++)
			copia->mapa[i][j] = fonte->mapa[i][j];
}




Fila detecta_clusters(tmapa* m){

  Fila proximas_pos = constroi_fila();
  Fila clusters = constroi_fila();

  int cor;
  int qtd_clusters = 0;
  //percorre todas as posições da matriz, ignorando aquelas que estão marcadas com -1
  for(int i=0;i<m->nlinhas;++i){
    for(int j=0;j<m->ncolunas;++j){
      if(m->mapa[i][j] < 0)//tem id
        continue;
      
      posicao* atual = malloc(sizeof(posicao));
      atual->lin = i;
      atual->col = j;
      enfileira(atual, proximas_pos);
      cor = m->mapa[atual->lin][atual->col];

      qtd_clusters++;// não quero id == 0
      int id = -1*qtd_clusters;
      m->mapa[atual->lin][atual->col] = id;


      cluster catual = constroi_cluster(id, cor, *atual);
      enfileira(catual, clusters);

      //printf("Cluster: %i,%i  cor:%i\n", atual->lin, atual->col, cor);
      while(atual = desenfileira(proximas_pos)){
        //printf("atual: %i,%i\n", atual->lin, atual->col);


        //vizinho esquerda
        if(atual->col != 0){
          
          if(m->mapa[atual->lin][atual->col-1] == cor){
            //marca como já passado
            m->mapa[atual->lin][atual->col-1] = id;
            posicao* viz_esq = malloc(sizeof(posicao));
            viz_esq->lin = atual->lin;
            viz_esq->col = atual->col-1;
            enfileira(viz_esq, proximas_pos);
          }
        }
        //vizinho direita
        if(atual->col != m->ncolunas -1){
          if(m->mapa[atual->lin][atual->col+1] == cor){
            m->mapa[atual->lin][atual->col+1] = id;
            posicao* viz_dir = malloc(sizeof(posicao));
            viz_dir->lin = atual->lin;
            viz_dir->col = atual->col+1;
            enfileira(viz_dir, proximas_pos);
          }
        }
        //vizinho baixo
        if(atual->lin != m->nlinhas -1){
          if(m->mapa[atual->lin+1][atual->col] == cor){
            m->mapa[atual->lin+1][atual->col] = id;
            posicao* viz_baixo = malloc(sizeof(posicao));
            viz_baixo->lin = atual->lin+1;
            viz_baixo->col = atual->col;
            enfileira(viz_baixo, proximas_pos);
          }
        }
        //vizinho cima
        if(atual->lin != 0){
          if(m->mapa[atual->lin-1][atual->col] == cor){
            m->mapa[atual->lin-1][atual->col] = id;
            posicao* viz_cima = malloc(sizeof(posicao));
            viz_cima->lin = atual->lin-1;
            viz_cima->col = atual->col;
            enfileira(viz_cima, proximas_pos);
          }
        }
        free(atual);
      }
    }
  }

  return clusters;
}



cluster encontrar_pelo_id_fila(int id, Fila clusters){
  ElementoFila ef = clusters->frente;
  while(ef){
    cluster catual = (cluster)ef->conteudo;
    if(catual->id == id){
      return catual;
    }
    ef = ef->proximo;
  }
  return NULL; 
}
cluster encontrar_pelo_id_lista(int id, lista clusters){
  no n = primeiro_no(clusters);
  while(n){
    cluster catual = (cluster)conteudo(n);
    if(catual->id == id){
      return catual;
    }
    n = proximo_no(n);
  }
  return NULL; 
}
grafo obtem_grafo(tmapa* m, Fila fclusters){

  Fila proximas_pos = constroi_fila();
  grafo g = constroi_grafo();
  g->primeiro = (cluster)fclusters->frente->conteudo;
  cluster catual;
  while(catual = desenfileira(fclusters)){


  	posicao* atual = malloc(sizeof(posicao));
  	atual->lin = catual->pos.lin;
  	atual->col = catual->pos.col;


  	enfileira(atual, proximas_pos);
  	int id = catual->id;
    int id_marcado = -1*id;
    //catual->id = id_marcado;//deixa id positivo

  	m->mapa[atual->lin][atual->col] = id_marcado;

  	//printf("Cluster: %i,%i\n", atual->lin, atual->col);
  	while(atual = desenfileira(proximas_pos)){
  		//printf("\natual: %i,%i\n", atual->lin, atual->col);

      //mostra_mapa(m);
  		//vizinho esquerda
  		if(atual->col != 0){
  			
        int id_vizinho = m->mapa[atual->lin][atual->col-1];
  			if(id_vizinho == id){
  				//marca como já passado
  				m->mapa[atual->lin][atual->col-1] = id_marcado;
  				posicao* viz_esq = malloc(sizeof(posicao));
  				viz_esq->lin = atual->lin;
  				viz_esq->col = atual->col-1;
  				enfileira(viz_esq, proximas_pos);
  			}else if(id_vizinho != id_marcado){
          
          cluster cvizinho = encontrar_pelo_id_lista(id_vizinho, catual->vizinhos);
          //não foi processado
          if(!cvizinho){
            cvizinho = encontrar_pelo_id_fila(id_vizinho, fclusters);
            insere_lista(cvizinho, catual->vizinhos);
            insere_lista(catual, cvizinho->vizinhos);
          }
          
        }
  		}
  		//vizinho direita
  		if(atual->col != m->ncolunas -1){
         int id_vizinho = m->mapa[atual->lin][atual->col+1];
  			if(id_vizinho == id){
  				m->mapa[atual->lin][atual->col+1] = id_marcado;
  				posicao* viz_dir = malloc(sizeof(posicao));
  				viz_dir->lin = atual->lin;
  				viz_dir->col = atual->col+1;
  				enfileira(viz_dir, proximas_pos);
  			}else if(id_vizinho != id_marcado){
          
          cluster cvizinho = encontrar_pelo_id_lista(id_vizinho, catual->vizinhos);

          //não foi processado
          if(!cvizinho){
            cvizinho = encontrar_pelo_id_fila(id_vizinho, fclusters);
            insere_lista(cvizinho, catual->vizinhos);
            insere_lista(catual, cvizinho->vizinhos);

            no n = primeiro_no(catual->vizinhos);
            for(;n;n=proximo_no(n)){
              cluster c = conteudo(n);
            }
          }
        }
  		}
  		//vizinho baixo
  		if(atual->lin != m->nlinhas -1){
         int id_vizinho = m->mapa[atual->lin+1][atual->col];
  			if(id_vizinho == id){
  				m->mapa[atual->lin+1][atual->col] = id_marcado;
  				posicao* viz_baixo = malloc(sizeof(posicao));
  				viz_baixo->lin = atual->lin+1;
  				viz_baixo->col = atual->col;
  				enfileira(viz_baixo, proximas_pos);
  			}else if(id_vizinho != id_marcado){
          
          cluster cvizinho = encontrar_pelo_id_lista(id_vizinho, catual->vizinhos);

          //não foi processado
          if(!cvizinho){
            cvizinho = encontrar_pelo_id_fila(id_vizinho, fclusters);

            insere_lista(cvizinho, catual->vizinhos);
            insere_lista(catual, cvizinho->vizinhos);
          }
        }
  		}
  		//vizinho cima
  		if(atual->lin != 0){
         int id_vizinho = m->mapa[atual->lin-1][atual->col];
  			if(id_vizinho == id){
  				m->mapa[atual->lin-1][atual->col] = id_marcado;
  				posicao* viz_cima = malloc(sizeof(posicao));
  				viz_cima->lin = atual->lin-1;
  				viz_cima->col = atual->col;
  				enfileira(viz_cima, proximas_pos);
  			}else if(id_vizinho != id_marcado){
          
          cluster cvizinho = encontrar_pelo_id_lista(id_vizinho, catual->vizinhos);

          //não foi processado
          if(!cvizinho){
            cvizinho = encontrar_pelo_id_fila(id_vizinho, fclusters);

            insere_lista(cvizinho, catual->vizinhos);
            insere_lista(catual, cvizinho->vizinhos);
          }
        }
  		}
  		free(atual);
  	}
    catual->id = id_marcado;
  }

  return g;

}





void mudar_dist_folha(cluster c){
  int dist = 0;
  while(c){ 
    if(dist > c->maior_dist_folha){
      c->maior_dist_folha = dist;
    }
    dist++;
    c = c->pai;
  }

}
cluster marcar_agm(grafo g){

  Fila f = constroi_fila();
  Fila marcados = constroi_fila();
  cluster mais_distante = g->primeiro;
  cluster atual;
  g->primeiro->marcado = 1;
  enfileira(g->primeiro, f);

  while(atual = desenfileira(f)){
    enfileira(atual, marcados);
    if(atual->altura > mais_distante->altura)
      mais_distante = atual;
    int qtd_filhos=0;
    no no_v = primeiro_no(atual->vizinhos);
    for(;no_v;no_v = proximo_no(no_v)){
      cluster cv = conteudo(no_v);
      if(!cv->marcado){
        qtd_filhos++;
        cv->marcado = 1;
        cv->pai = atual;
        cv->altura = atual->altura+1;
        insere_lista(cv, atual->v_agm);
        enfileira(cv, f);
      }
    }
    if(qtd_filhos == 0){//folha
      mudar_dist_folha(atual);
    }
  }

  desmarcar(marcados);
  return mais_distante;
}

void mesclar(cluster raiz, int cor){
    //no no_v = primeiro_no(raiz->vizinhos);
  int nova_maior_distancia_folha = raiz->maior_dist_folha - 1;
  no no_v = primeiro_no(raiz->v_agm);
  for(;no_v;no_v = proximo_no(no_v)){
    cluster cv = conteudo(no_v);
    if(cv->cor == cor){
    //  remove_no(raiz->vizinhos, no_v, NULL);
      //remove_pelo_conteudo(cv, raiz->v_agm);
      //printf("Removido %i\n", cv->id);
      remove_no(raiz->v_agm, no_v, NULL);
      //ARRUMAr
      concatena_lista(raiz->v_agm, cv->v_agm);
      //concatena_lista(raiz->vizinhos, cv->vizinhos);
    }else{
      if(cv->maior_dist_folha ==  raiz->maior_dist_folha - 1){
          nova_maior_distancia_folha = cv->maior_dist_folha+1;
      }
    }
  }
  raiz->maior_dist_folha = nova_maior_distancia_folha;
  raiz->cor = cor;
}
Fila heuristica_mais_longe(grafo g){
  cluster raiz = g->primeiro;

  Fila solucao = constroi_fila();
  while(raiz->maior_dist_folha > 0){
    //printf("==MINHA MAIOR ALTURA: %i==\n", raiz->maior_dist_folha);
    no no_v = primeiro_no(raiz->v_agm);
    cluster prox_cluster = NULL;
    for(;no_v;no_v = proximo_no(no_v)){
      cluster cv = conteudo(no_v);
      
      //printf("pc:%i id:%i\n", cv->maior_dist_folha, cv->id);
      if(cv->maior_dist_folha == raiz->maior_dist_folha-1){
        prox_cluster = cv;
        //printf("entrou\n");
      }
    }
    int* cor_solucao = malloc(sizeof(int));
    *cor_solucao = prox_cluster->cor;
    enfileira(cor_solucao, solucao);
    //printf("PROX_COR:%i id:%i\n\n", prox_cluster->cor, prox_cluster->id);
    mesclar(raiz, prox_cluster->cor);



  }

  return solucao;
}
void print_solucao(Fila solucao){
  fprintf(stdout, "%i\n",solucao->tamanho);
  int* cor;
  cor = (int*)desenfileira(solucao);
  if(cor)
    fprintf(stdout, "%i", *cor);
  while(cor = (int*)desenfileira(solucao)){
    fprintf(stdout, " %i", *cor);
  }
  printf("\n");
}
int main(int argc, char **argv) {
	tmapa m;

  carrega_mapa(&m);


	//mostra_mapa(&m);
	//mostra_mapa_cor(&m);
	Fila fclusters = detecta_clusters(&m);

  //mostra_mapa(&m);
  //printf("OBTEM GRAFO\n");
  grafo g  = obtem_grafo(&m, fclusters);
  //mostra_mapa(&m);
  print_grafo(g);

  cluster mais_distante = marcar_agm(g);
  print_agm(g);
  Fila solucao = heuristica_mais_longe(g);
  print_solucao(solucao);

 

	return 0;
}