#include <malloc.h>
#include "lista.h"

//---------------------------------------------------------------------------
// nó de lista encadeada cujo conteúdo é um void *

struct no {

  void *conteudo;
  no proximo,  anterior;
};
//---------------------------------------------------------------------------
// lista encadeada

struct lista {
  
  unsigned int tamanho;
  int padding; // só pra evitar warning 
  no primeiro, ultimo;
};

int remove_pelo_conteudo(void* cont, struct lista* l){
  no no_atual = primeiro_no(l);
  void* cont_atual = conteudo(no_atual);

for(;no_atual; no_atual = proximo_no(no_atual)){
   cont_atual = conteudo(no_atual);
    if(cont_atual == cont){
      if(no_atual == l->primeiro){
        l->primeiro = no_atual->proximo;
      } 
      if(no_atual == l->ultimo){
        l->ultimo = no_atual->anterior;
      }
      free(no_atual);

      return 1;
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
// devolve o número de nós da lista l

unsigned int tamanho_lista(lista l) { return l->tamanho; }

//---------------------------------------------------------------------------
// devolve o primeiro nó da lista l,
//      ou NULL, se l é vazia

no primeiro_no(lista l) { return l->primeiro; }

//---------------------------------------------------------------------------
// devolve o conteúdo do nó n
//      ou NULL se n = NULL 

void *conteudo(no n) { return n->conteudo; }

//---------------------------------------------------------------------------
// devolve o sucessor do nó n,
//      ou NULL, se n for o último nó da lista

no proximo_no(no n) { return n->proximo; }

//---------------------------------------------------------------------------
// cria uma lista vazia e a devolve
//
// devolve NULL em caso de falha

lista constroi_lista(void) {

  lista l = malloc(sizeof(struct lista));

  if ( ! l ) 
    return NULL;

  l->primeiro = NULL;
  l->ultimo = NULL;
  l->tamanho = 0;

  return l;
}
//---------------------------------------------------------------------------
// desaloca a lista l e todos os seus nós
// 
// se destroi != NULL invoca
//
//     destroi(conteudo(n)) 
//
// para cada nó n da lista. 
//
// devolve 1 em caso de sucesso,
//      ou 0 em caso de falha

int destroi_lista(lista l, int destroi(void *)) { 
  
  no p;
  int ok=1;

  while ( (p = primeiro_no(l)) ) {
    
    l->primeiro = proximo_no(p);

    if ( destroi )
      ok &= destroi(conteudo(p));

    free(p);
  }

  free(l);

  return ok;
}
//---------------------------------------------------------------------------
// insere um novo nó na lista l cujo conteúdo é p
//
// devolve o no recém-criado 
//      ou NULL em caso de falha

no insere_lista(void *conteudo, lista l) { 

  no novo = malloc(sizeof(struct no));

  if ( ! novo ) 
    return NULL;

  novo->conteudo = conteudo;
  novo->proximo = primeiro_no(l);
  novo->anterior = NULL;
  
  if(l->tamanho == 0){
    l->ultimo = novo;
  }else{
    novo->proximo->anterior = novo;
  }

  ++l->tamanho;
  return l->primeiro = novo;
}


int concatena_lista(struct lista *dest, struct lista* l){
  
  if(l->tamanho > 0){
    no n = l->ultimo;
    if(dest->primeiro){
      dest->primeiro->anterior = n;
      n->proximo = dest->primeiro;
    }
    dest->primeiro = l->primeiro;
    if(dest->tamanho == 0){
      dest->ultimo = n;
    }
  }

  dest->tamanho += l->tamanho;

  return 1;
}

//------------------------------------------------------------------------------
// remove o no de endereço rno de l
// se destroi != NULL, executa destroi(conteudo(rno)) 
// devolve 1, em caso de sucesso
//         0, se rno não for um no de l

int remove_no(struct lista *l, struct no *rno, int destroi(void *)) {
	int r = 1;

	for (no n = primeiro_no(l); n; n = proximo_no(n)) {
		if (n == rno) {
      if (l->primeiro == rno) {
        l->primeiro = rno->proximo;
      }else{
        n->anterior->proximo = rno->proximo;
      }
      if(l->ultimo == rno){
        l->ultimo = rno->anterior;
      }else{
        rno->proximo->anterior = rno->anterior;
      }
			if (destroi != NULL) {
				r = destroi(conteudo(rno));
			}
			free(rno);
			l->tamanho--;
			return r;
		}
	}
	return 0;
}


