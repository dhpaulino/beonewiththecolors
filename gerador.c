#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct {
	int nlinhas;
	int ncolunas;
	int ncores;
	int **mapa;
	unsigned qtd_flood;
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


int main(int argc, char **argv) {
	tmapa m;


  if(argc != 4){
    printf("Rode: ./gerador N_LINHAS N_COLUNAS N_CORES\n");
    return -1;
  }

	m.nlinhas = atoi(argv[1]);
	m.ncolunas = atoi(argv[2]);
	m.ncores = atoi(argv[3]);


	gera_mapa(&m, -1);
	
  mostra_mapa(&m);

	return 0;
}