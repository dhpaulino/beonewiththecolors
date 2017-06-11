#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "fila.c"

#define N 10


typedef struct posicao {
	unsigned int lin, col;
} posicao;

typedef struct {
	int nlinhas;
	int ncolunas;
	int ncores;
	int **mapa;
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

// verifica qual cor ainda precisa ser resolvida
// cores[0] indica se o mapa esta completo
void verifica_cores_mapa(tmapa *m, bool *cores) {
	int fundo = m->mapa[0][0], n_cores = m->ncores + 1;

	for (int i = 0; i < n_cores; i++)
		cores[i] = false;

	cores[fundo] = true;

	for (int l = 0; l < m->nlinhas; l++)
		for (int c = 0; c < m->ncolunas; c++)
			if (m->mapa[l][c] != fundo) {
				cores[m->mapa[l][c]] = true;
				cores[0] = true;
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

int conta_fundo(tmapa* m) {

	Fila proximas_pos = constroi_fila();
	int cor, count = 1;

	posicao* atual = malloc(sizeof(posicao));
	atual->lin = 0;
	atual->col = 0;
	enfileira(atual, proximas_pos);
	cor = m->mapa[atual->lin][atual->col];
	m->mapa[atual->lin][atual->col] = 0;

	//printf("Cluster: %i,%i\n", atual->lin, atual->col);
	while((atual = desenfileira(proximas_pos))) {
		//printf("atual: %i,%i\n", atual->lin, atual->col);

		//vizinho esquerda
		if(atual->col != 0 && m->mapa[atual->lin][atual->col - 1] == cor) {
			count++;
			m->mapa[atual->lin][atual->col - 1] = 0;
			posicao* viz_esq = malloc(sizeof(posicao));
			viz_esq->lin = atual->lin;
			viz_esq->col = atual->col - 1;
			enfileira(viz_esq, proximas_pos);
		}

		//vizinho direita
		if(atual->col != m->ncolunas - 1 && m->mapa[atual->lin][atual->col + 1] == cor) {
			count++;
			m->mapa[atual->lin][atual->col + 1] = 0;
			posicao* viz_dir = malloc(sizeof(posicao));
			viz_dir->lin = atual->lin;
			viz_dir->col = atual->col + 1;
			enfileira(viz_dir, proximas_pos);
		}

		//vizinho baixo
		if(atual->lin != m->nlinhas - 1 && m->mapa[atual->lin + 1][atual->col] == cor) {
			count++;
			m->mapa[atual->lin + 1][atual->col] = 0;
			posicao* viz_baixo = malloc(sizeof(posicao));
			viz_baixo->lin = atual->lin + 1;
			viz_baixo->col = atual->col;
			enfileira(viz_baixo, proximas_pos);
		}

		//vizinho cima
		if(atual->lin != 0 && m->mapa[atual->lin - 1][atual->col] == cor) {
			count++;
			m->mapa[atual->lin - 1][atual->col] = 0;
			posicao* viz_cima = malloc(sizeof(posicao));
			viz_cima->lin = atual->lin - 1;
			viz_cima->col = atual->col;
			enfileira(viz_cima, proximas_pos);
		}

		free(atual);
	}

	return count;

}

int escolha_gulosa_por_heuristica(tmapa *m, tmapa *testa_passo, bool *cores) {
	int n_cores = m->ncores + 1, fundo = m->mapa[0][0], aux, maior = 1, escolha;

	for (int i = 1; i < n_cores; i++) {
		// nao considere pintar com cores eliminadas ou a cor do fundo, evita calculos inuteis
		if (!cores[i] || i == fundo) {
			continue;
		}

		// copia mapa atual para testar a cor i
		copia_mapa(m, testa_passo);

		// testa a cor i
		pinta_mapa(testa_passo, i);

		// calcula o tamanho do fundo
		aux = conta_fundo(testa_passo);

		// guarda o maior e a cor
		if (aux > maior) {
			maior = aux;
			escolha = i;
		}
	}

	return escolha;

}

int main(int argc, char **argv) {
	tmapa m, testa_passo;

	m.nlinhas = N;
	m.ncolunas = N;
	m.ncores = N;

	testa_passo.nlinhas = m.nlinhas;
	testa_passo.ncolunas = m.ncolunas;
	testa_passo.ncores = m.ncores;

	int index_passos, passos[m.nlinhas * m.ncolunas], passo;
	bool cores[N + 1];

	testa_passo.mapa = (int**) malloc(testa_passo.nlinhas * sizeof(int*));

	for(int i = 0; i < m.nlinhas; i++) {
		testa_passo.mapa[i] = (int*) malloc(testa_passo.ncolunas * sizeof(int));
	}

	gera_mapa(&m, -1);

	// verifica a existencia de cada cor no mapa
	verifica_cores_mapa(&m, cores);

	for(index_passos = 0; cores[0]; index_passos++) {
		//mostra_mapa_cor(&m);

		//printf("\n");

		// calcula proximo passo usando um mapa de teste copiado do mapa atual
		passo = escolha_gulosa_por_heuristica(&m, &testa_passo, cores);

		// salva para imprimir no final
		passos[index_passos] = passo;

		// altera mapa atual executando o passo
		pinta_mapa(&m, passo);

		// verifica a existencia de cada cor no mapa
		verifica_cores_mapa(&m, cores);
	}

	//mostra_mapa_cor(&m);

	//printf("\n");

	// tamanho da solucao
	printf("%d\n", index_passos);

	// impressao da solucao
	for (int i = 0; i < index_passos; i++) {
		printf("%d ", passos[i]);
	}

	printf("\n");

	return 0;

}