#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define N 10

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

void copia_mapa(tmapa *fonte, tmapa *copia) {
	int i, j;

	for (i = 0; i < fonte->nlinhas; i++)
		for (j = 0; j < fonte->ncolunas; j++) {
			//printf("i: %d\tj: %d\n", i, j);
			//printf("fonte[0][0]: %d\n", fonte->mapa[0][0]);
			//printf("copia[0][0]: %d\n", copia->mapa[0][0]);
			copia->mapa[i][j] = fonte->mapa[i][j];
		}
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

// ele conta mais vezes do que o exato significado de contar os flodados mas serve como heuristica
int conta_flodados(tmapa *m, int l, int c, int fundo, int cor) {
	if (m->mapa[l][c] == fundo) {
		if (l < m->nlinhas - 1 && c < m->ncolunas - 1)
			return 1 + conta_flodados(m, l + 1, c, fundo, cor) + conta_flodados(m, l, c + 1, fundo, cor);
		else
			if (l < m->nlinhas - 1)
				return 1 + conta_flodados(m, l + 1, c, fundo, cor);
			else
				if (c < m->ncolunas - 1)
					return 1 + conta_flodados(m, l, c + 1, fundo, cor);
	}
	else
		if (m->mapa[l][c] == cor)
			conta_borda_flodados(m, l, c, cor);

	return 0;
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

	for (int i = 1; i < n_cores; ++i) {
		// nao considere pintar com a cor do fundo, evita calculos inuteis
		if (i == fundo)
			continue;

		aux = conta_cor(m, i);

		if (aux > maior) {
		 	maior = aux;
		 	escolha = i;

		 	printf("%d blocos de cor %d\n", maior, escolha);
		}
	}

	printf("\n");

	return escolha;
}

int main(int argc, char **argv) {
	tmapa m, testa_passo;

	m.nlinhas = N;
	m.ncolunas = N;
	m.ncores = N;

	testa_passo.nlinhas = N;
	testa_passo.ncolunas = N;
	testa_passo.ncores = N;

	int cor, index_passos, passos[m.nlinhas * m.ncolunas];

	gera_mapa(&m, -1);
	//mostra_mapa(&m);

	testa_passo.mapa = (int**) malloc(testa_passo.nlinhas * sizeof(int*));

	for(int i = 0; i < testa_passo.nlinhas; i++)
		testa_passo.mapa[i] = (int*) malloc(testa_passo.ncolunas * sizeof(int));

	copia_mapa(&m, &testa_passo);

	printf("\n");

	for(index_passos = 0; precisa_resolver_mapa(&m); ++index_passos) {
		// executa heuristica olhando um nivel abaixo apenas
		cor = escolha_gulosa_por_heuristica(&testa_passo, testa_passo.mapa[0][0]);

		passos[index_passos] = cor;

		pinta_mapa(&m, cor);

		//mostra_mapa(&m); // para mostrar sem cores use mostra_mapa(&m);

		printf("\n");

		copia_mapa(&m, &testa_passo);
	}

	printf("tamanho da solução = %d\n", index_passos);

	// impressao da solucao
	for (int i = 0; i < index_passos; ++i)
		printf("%d ", passos[i]);

	// termina a saida com 'pula linha'
	printf("\n");

	return 0;
}