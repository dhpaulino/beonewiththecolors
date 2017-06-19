#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct {
	int nlinhas;
	int ncolunas;
	int ncores;
	int **mapa;
} tmapa;


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

int main(int argc, char **argv) {
	tmapa m;

	scanf("%d", &m.nlinhas);
	scanf("%d", &m.ncolunas);
	scanf("%d", &m.ncores);

	int i, j, k, pula_cor;

	if (m.ncores % 2 == 0)
		pula_cor = 3;
	else
		pula_cor = 2;

	m.mapa = (int**) malloc(m.nlinhas * sizeof(int*));

	for(i = 0; i < m.nlinhas; i++) {
		m.mapa[i] = (int*) malloc(m.ncolunas * sizeof(int));

		for(j = 0; j < m.ncolunas; j++)
			m.mapa[i][j] = 0;
	}

	for (i = 0; i < m.nlinhas; i++) {
		for (j = 0, k = 1; j < m.ncolunas; j++, k++) {
			if (i != 0 && j == 0)
				k = m.mapa[i - 1][j] + pula_cor;

			if (k > m.ncores)
				k -= m.ncores;

			m.mapa[i][j] = k;
		}
	}

	mostra_mapa_cor(&m);

	return 0;

}