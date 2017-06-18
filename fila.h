#ifndef _FILA_H
#define _FILA_H



typedef struct Fila* Fila;
typedef struct ElementoFila* ElementoFila;

/**
Elemento da fila, cujo o conteudo é void*
**/
struct ElementoFila{
	void* conteudo;
	ElementoFila proximo,anterior;
};

/*
fila duplamente encadeada
*/
struct Fila{
	int tamanho;
	ElementoFila frente,final;
};

/**
cria uma lista vazia e a devolve
em caso de falha retorna null
*/
Fila constroi_fila(void);
/**
returna 1 se a fila estiver vazia
retorna 0, caso contrário
**/
int vaziaFila(Fila fila);
/**
adiciona um valor(conteudo) a fila
retorna 1 em caso de sucesso
retorna 0 caso contrário
**/
int enfileira(void* conteudo, Fila fila);
/**
	retorna o valor na frente da fila,
	caso a fila esteja vazia retorna null
**/
void* desenfileira(Fila fila);
/**
	remove a fila da memória, porém não o seu conteúdo
**/
void destroi_fila(Fila fila);
/**
	Retorna o ElementoFila correspondente ao valor procurado na fila
	Caso não  encontre retorna NULL
**/
ElementoFila encontrar_conteudo(void* conteudo,Fila fila);
/**
	aumenta a prioridade(diminui a posição) do conteudo, de acordo com a função de maior passada
	O primeiro valor que será passado para a função maior será o conteúdo fornecido, o segundo será um conteúdo qualquer da fila
	Será aumentado apenas o primeiro elemento da fila que casar com o conteúdo fornecido
**/
void aumentar_prioridade(void *conteudo,int maior(void*,void*),Fila fila);
/**
Adiciona o elemento uma posição antes do pivo na fila
**/
void adicionar_antes(ElementoFila elemento,ElementoFila pivo,Fila fila);
/**
Adiciona o elemento uma posição depois do pivo na fila
**/
void adicionar_depois(ElementoFila elemento,ElementoFila pivo,Fila fila);


#endif
