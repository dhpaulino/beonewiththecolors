#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "fila.c"
#include "grafo.h"

#define passei_fundo 6



#define N 4

typedef struct {
	int nlinhas;
	int ncolunas;
	int ncores;
	int **mapa;
	unsigned qtd_flood;
	posicao *boarda;
} tmapa;



void gera_mapa(tmapa *m, int semente) {
	int i, j;

	if(semente < 0)
		srand(time(NULL));
	else
		srand(semente);

	m->mapa = (int**) malloc(m->nlinhas * sizeof(int*));

	for(i = 0; i < m->nlinhas; i++) {
		m->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));

		for(j = 0; j < m->ncolunas; j++)
			m->mapa[i][j] = 1 + rand() % m->ncores;
  }
}

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

	printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);

	for(i = 0; i < m->nlinhas; i++) {
		for(j = 0; j < m->ncolunas; j++) {
			if(m->ncores > 10)
				printf("%s%02d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
			else
				printf("%s%d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
		}

		printf("\n");
  }
}

void pinta(tmapa *m, int l, int c, int fundo, int cor) {
	m->mapa[l][c] = cor;

	if(l < m->nlinhas - 1 && m->mapa[l + 1][c] == fundo)
		pinta(m, l + 1, c, fundo, cor);

	if(c < m->ncolunas - 1 && m->mapa[l][c + 1] == fundo)
		pinta(m, l, c + 1, fundo, cor);

	if(l > 0 && m->mapa[l - 1][c] == fundo)
		pinta(m, l - 1, c, fundo, cor);

	if(c > 0 && m->mapa[l][c - 1] == fundo)
		pinta(m, l, c - 1, fundo, cor);
}

void pinta_mapa(tmapa *m, int cor) {
	if(cor == m->mapa[0][0])
		return;

	pinta(m, 0, 0, m->mapa[0][0], cor);
}

bool precisa_resolver_mapa(tmapa *m) {
	int fundo = m->mapa[0][0];

	for (int l = 0; l < m->nlinhas; ++l)
		for (int c = 0; c < m->ncolunas; ++c)
			if (m->mapa[l][c] != fundo)
				return true;

	return false;
}

int conta_borda_flodados(tmapa *m, int l, int c, int cor) {
	if (l < m->nlinhas - 1 && c < m->ncolunas - 1)
		return 1 + conta_borda_flodados(m, l + 1, c, cor) + conta_borda_flodados(m, l, c + 1, cor);
	else
		if (l < m->nlinhas - 1)
			return 1 + conta_borda_flodados(m, l + 1, c, cor);
		else
			if (c < m->ncolunas - 1)
				return 1 + conta_borda_flodados(m, l, c + 1, cor);
			else
				return 1;
}


void copia_mapa(tmapa *fonte, tmapa *copia) {
	copia->nlinhas = fonte->nlinhas;
	copia->ncolunas = fonte->ncolunas;
	copia->ncores = fonte->ncores;

	for (int i = 0; i < fonte->nlinhas; i++)
		for (int j = 0; j < fonte->ncolunas; j++)
			copia->mapa[i][j] = fonte->mapa[i][j];
}

int conta_cor(tmapa *m, int cor) {
	int count = 0;

	for (int i = 0; i < m->nlinhas; ++i)
		for (int j = 0; j < m->ncolunas; j++)
			if (m->mapa[i][j] == cor)
				count++;

	return count;
		
}

int escolha_gulosa_por_heuristica(tmapa *m, int fundo) {
	int n_cores = m->ncores + 1, maior = 0, aux, escolha;


	tmapa* m_copia = malloc(sizeof(tmapa));

	m_copia->mapa = (int**) malloc(m->nlinhas * sizeof(int*));

	for(int i = 0; i < m->nlinhas; i++) {
		m_copia->mapa[i] = (int*) malloc(m->ncolunas * sizeof(int));
  	}

  
			//conta_flodados(m, fundo);

	printf("\n");

	return escolha;
}

int detecta_clusters(tmapa* m){

  Fila proximas_pos = constroi_fila();
  int cor;
  int qtd_clusters = 0;
  //percorre todas as posições da matriz, ignorando aquelas que estão marcadas com -1
  for(int i=0;i<m->nlinhas;++i){
    for(int j=0;j<m->ncolunas;++j){
      if(m->mapa[i][j] <=0)//tem id
        continue;
      
      posicao* atual = malloc(sizeof(posicao));
      atual->lin = i;
      atual->col = j;
      enfileira(atual, proximas_pos);
      cor = m->mapa[atual->lin][atual->col];
      m->mapa[atual->lin][atual->col] = -1;
      int id = -1*qtd_clusters;

      printf("Cluster: %i,%i  cor:%i\n", atual->lin, atual->col, cor);
      while(atual = desenfileira(proximas_pos)){
        printf("atual: %i,%i\n", atual->lin, atual->col);


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
      qtd_clusters++;
    }
  }

  return qtd_clusters;
}


int marcar_cor(int cor){
  return -1*cor;
}
/*void preenche_vizinho(cluster c, mapa m){

	posicao* atual = malloc(sizeof(posicao));
	atual->lin = c->pos.lin;
	atual->col = c->pos.col;

	enfileira(atual, proximas_pos);
	int cor = m->mapa[atual->lin][atual->col];
  int cor_marcada = marcar_cor(m->mapa[atual->lin][atual->col]);
	m->mapa[atual->lin][atual->col] = cor_marcada;

	printf("Cluster: %i,%i\n", atual->lin, atual->col);
	while(atual = desenfileira(proximas_pos)){
		printf("atual: %i,%i\n", atual->lin, atual->col);


		//vizinho esquerda
		if(atual->col != 0){
			
			if(m->mapa[atual->lin][atual->col-1] == cor){
				//marca como já passado
				m->mapa[atual->lin][atual->col-1] = cor_marcada;
				posicao* viz_esq = malloc(sizeof(posicao));
				viz_esq->lin = atual->lin;
				viz_esq->col = atual->col-1;
				enfileira(viz_esq, proximas_pos);
			}else if(m->mapa[atual->lin][atual->col-1] != cor_marcada){

      }
		}
		//vizinho direita
		if(atual->col != m->ncolunas -1){
			if(m->mapa[atual->lin][atual->col+1] == cor){
				m->mapa[atual->lin][atual->col+1] = cor_marcada;
				posicao* viz_dir = malloc(sizeof(posicao));
				viz_dir->lin = atual->lin;
				viz_dir->col = atual->col+1;
				enfileira(viz_dir, proximas_pos);
			}
		}
		//vizinho baixo
		if(atual->lin != m->nlinhas -1){
			if(m->mapa[atual->lin+1][atual->col] == cor){
				m->mapa[atual->lin+1][atual->col] = cor_marcada;
				posicao* viz_baixo = malloc(sizeof(posicao));
				viz_baixo->lin = atual->lin+1;
				viz_baixo->col = atual->col;
				enfileira(viz_baixo, proximas_pos);
			}
		}
		//vizinho cima
		if(atual->lin != 0){
			if(m->mapa[atual->lin-1][atual->col] == cor){
				m->mapa[atual->lin-1][atual->col] = cor_marcada;
				posicao* viz_cima = malloc(sizeof(posicao));
				viz_cima->lin = atual->lin-1;
				viz_cima->col = atual->col;
				enfileira(viz_cima, proximas_pos);
			}
		}
		free(atual);
	}

}*/
int main(int argc, char **argv) {
	tmapa m, testa_passo;


	m.nlinhas = N;
	m.ncolunas = N;
	m.ncores = 2;

	testa_passo.nlinhas = N;
	testa_passo.ncolunas = N;
	testa_passo.ncores = N;


	int cor, index_passos, passos[m.nlinhas * m.ncolunas];

	gera_mapa(&m, -1);
	//mostra_mapa(&m);
	mostra_mapa_cor(&m);
	detecta_clusters(&m);

	return 0;
}