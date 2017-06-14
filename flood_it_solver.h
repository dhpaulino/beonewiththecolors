/* This file was automatically generated.  Do not edit! */
int main(int argc,char **argv);
#if TEST==0
int main(int argc,char **argv);
#endif
#if TEST==1
void main(int argc,char **argv);
#endif
int marcar_cor(int cor);
void *desenfileira(Fila fila);
void *desenfileira(Fila fila);
#if !defined(_LISTA_H)
#define _LISTA_H
#endif
#if !defined(_LISTA_H)
typedef struct no *no;
#endif
void *conteudo(no n);
#if !defined(_LISTA_H)
void *conteudo(no n);
#endif
int enfileira(void *conteudo,Fila fila);
int enfileira(void *conteudo,Fila fila);
Fila constroi_fila(void);
Fila constroi_fila(void);
int detecta_clusters(tmapa *m);
int escolha_gulosa_por_heuristica(tmapa *m,int fundo);
int conta_cor(tmapa *m,int cor);
void copia_mapa(tmapa *fonte,tmapa *copia);
int conta_borda_flodados(tmapa *m,int l,int c,int cor);
bool precisa_resolver_mapa(tmapa *m);
void pinta_mapa(tmapa *m,int cor);
void pinta(tmapa *m,int l,int c,int fundo,int cor);
void mostra_mapa_cor(tmapa *m);
void mostra_mapa(tmapa *m);
void carrega_mapa(tmapa *m);
void gera_mapa(tmapa *m,int semente);
