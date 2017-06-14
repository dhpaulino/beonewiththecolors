/* This file was automatically generated.  Do not edit! */
void adicionar_depois(ElementoFila elemento,ElementoFila pivo,Fila fila);
void adicionar_depois(ElementoFila elemento,ElementoFila pivo,Fila fila);
void adicionar_antes(ElementoFila elemento,ElementoFila pivo,Fila fila);
void adicionar_antes(ElementoFila elemento,ElementoFila pivo,Fila fila);
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
void aumentar_prioridade(void *conteudo,int maior(void *,void *),Fila fila);
void aumentar_prioridade(void *conteudo,int maior(void *,void *),Fila fila);
ElementoFila encontrar_conteudo(void *conteudo,Fila fila);
ElementoFila encontrar_conteudo(void *conteudo,Fila fila);
void destroi_fila(Fila fila);
void destroi_fila(Fila fila);
void *desenfileira(Fila fila);
void *desenfileira(Fila fila);
int enfileira(void *conteudo,Fila fila);
int enfileira(void *conteudo,Fila fila);
int vaziaFila(Fila fila);
int vaziaFila(Fila fila);
Fila constroi_fila(void);
Fila constroi_fila(void);
