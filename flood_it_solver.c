#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

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
		       "\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m" };

  if(m->ncores > 15) {
    mostra_mapa(m);
    return;
  }
  printf("%d %d %d\n", m->nlinhas, m->ncolunas, m->ncores);
  for(i = 0; i < m->nlinhas; i++) {
    for(j = 0; j < m->ncolunas; j++)
      if(m->ncores > 10)
	printf("%s%02d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
      else
	printf("%s%d%s ", cor_ansi[m->mapa[i][j]], m->mapa[i][j], cor_ansi[0]);
    printf("\n");
  }
}

void pinta(tmapa *m, int l, int c, int fundo, int cor) {
  m->mapa[l][c] = cor;
  if(l < m->nlinhas - 1 && m->mapa[l+1][c] == fundo)
    pinta(m, l+1, c, fundo, cor);
  if(c < m->ncolunas - 1 && m->mapa[l][c+1] == fundo)
    pinta(m, l, c+1, fundo, cor);
  if(l > 0 && m->mapa[l-1][c] == fundo)
    pinta(m, l-1, c, fundo, cor);
  if(c > 0 && m->mapa[l][c-1] == fundo)
    pinta(m, l, c-1, fundo, cor);
}

void pinta_mapa(tmapa *m, int cor) {
  if(cor == m->mapa[0][0])
    return;
  pinta(m, 0, 0, m->mapa[0][0], cor);
}

bool precisa_resolver_mapa(tmapa *m) {
  int l, c, fundo = m->mapa[0][0];

  for (int l = 0; l < m->nlinhas; ++l)
    for (int c = 0; c < m->ncolunas; ++c)
      if (m->mapa[l][c] != fundo)
        return true;

  return false;
}

int heuristica(tmapa *m) {
  return 0;
}

int main(int argc, char **argv) {
  tmapa m;

  m.nlinhas = 3;
  m.ncolunas = 3;
  m.ncores = 3;

  int cor, index_passos, passos[m.nlinhas * m.ncolunas];
  

  gera_mapa(&m, -1);
  mostra_mapa_cor(&m); 

  printf("\n");

  cor = 1 + rand() % m.ncores;
  passos[0] = cor;

  for(index_passos = 1; precisa_resolver_mapa(&m); ++index_passos) {
    pinta_mapa(&m, cor);
    mostra_mapa_cor(&m); // para mostrar sem cores use mostra_mapa(&m);
    printf("\n");
    cor = 1 + rand() % m.ncores;
    passos[index_passos] = cor;

  }

  index_passos--;

  printf("tamanho da solução = %d\n", index_passos);

  for (int i = 0; i < index_passos; ++i)
  {
    printf("%d ", passos[i]);
  }

  printf("\n");

  return 0;
}