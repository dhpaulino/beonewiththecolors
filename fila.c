

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

Fila constroi_fila(void){
  Fila fila = malloc(sizeof(struct Fila));
  if(!fila)
  	return NULL;
  fila->frente = NULL;
  fila->final = NULL;
  return fila;
}

int vaziaFila(Fila fila){
  if(!fila->frente)
    return 1;
  return 0;
}

int enfileira(void* conteudo, Fila fila){
  ElementoFila ef = malloc(sizeof(struct ElementoFila));
  if(!ef)
    return 0;
  ef->conteudo = conteudo;
  ef->proximo = NULL;
  if(vaziaFila(fila)){
    ef->anterior = NULL;
    fila->frente = ef;
    fila->final = ef;
  }else{
    fila->final->proximo = ef;
    ef->anterior = fila->final;
    fila->final = ef;
  }
  return 1;
  
}

void* desenfileira(Fila fila){
  if(vaziaFila(fila))
    return NULL;
  void* conteudo = fila->frente->conteudo;

  ElementoFila frente = fila->frente;
  fila->frente = fila->frente->proximo;
  if(fila->frente){
    fila->frente->anterior=NULL;
  }else{//TAMANHO 1
    fila->final=NULL;//FRENTE == FILA->FINAL
  }
  free(frente);
  return conteudo;
}

void destroi_fila(Fila fila){
  ElementoFila ef;
  while((ef=fila->frente)){
    fila->frente = ef->proximo;
    free(ef);
  }
  free(fila);
}

ElementoFila encontrar_conteudo(void* conteudo,Fila fila){
  ElementoFila ef;
  for(ef=fila->frente;ef;ef=ef->proximo){
    if(ef->conteudo==conteudo)
      return ef;
  }
  return NULL;
}

void aumentar_prioridade(void *conteudo,int maior(void*,void*),Fila fila){

  ElementoFila ef = encontrar_conteudo(conteudo,fila);
  if(!ef)
    return;
  ElementoFila aux;
  int eh_maior = 1;
  for(aux=ef;aux->anterior && eh_maior;){
    aux=aux->anterior;//aux nunca é null
    eh_maior = maior(conteudo,aux->conteudo);//será maior se aux é a frente(não é "e somente se")
  }
  if(aux!=ef){
    if(eh_maior){
      adicionar_antes(ef,aux,fila);
    }else if(aux->proximo!=ef){
      adicionar_depois(ef,aux,fila);
    }
  }
}

void adicionar_antes(ElementoFila elemento,ElementoFila pivo,Fila fila){
  if(elemento->anterior)
    elemento->anterior->proximo = elemento->proximo;
  if(elemento->proximo)
    elemento->proximo->anterior = elemento->anterior;
  elemento->anterior = pivo->anterior;
  elemento->proximo = pivo;
  
  if(fila->frente==pivo){
    fila->frente=elemento;
  }
  else{
    pivo->anterior->proximo = elemento;
  }
  pivo->anterior = elemento;
}

void adicionar_depois(ElementoFila elemento,ElementoFila pivo,Fila fila){
  if(elemento->anterior)
    elemento->anterior->proximo = elemento->proximo;
  if(elemento->proximo)
    elemento->proximo->anterior = elemento->anterior;
  elemento->anterior=pivo;
  elemento->proximo=pivo->proximo;
  
  if(fila->final==pivo)
    fila->final=elemento;
  else
    pivo->proximo->anterior = elemento;

  pivo->proximo=elemento;
}