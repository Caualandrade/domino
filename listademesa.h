#ifndef LISTADEMESA_H
#define LISTADEMESA_H

#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>

typedef PecaDomino peca;
// Estrutura que representa uma peça de dominó

// Estrutura do nó da lista duplamente encadeada
typedef struct tp_no_auxM {
  struct tp_no_auxM *ant;
  PecaDomino peca; // Peça de dominó
  struct tp_no_auxM *prox;
} tp_noM;

// Estrutura do descritor da lista
typedef struct {
  tp_noM *ini;
  tp_noM *fim;
  // int tamanho; // Opcional
} tp_listadM;

// Inicializa a lista com o descritor
tp_listadM *inicializa_listadM() {
  tp_listadM *lista = (tp_listadM *)malloc(sizeof(tp_listadM));
  lista->ini = NULL;
  lista->fim = NULL;
  // lista->tamanho = 0;
  return lista;
}

// Verifica se a lista está vazia
int listad_vaziaM(tp_listadM *lista) { return (lista->ini == NULL); }

// Aloca um novo nó
tp_noM *alocaM(int lado_esq, int lado_dir) {
  tp_noM *pt = (tp_noM *)malloc(sizeof(tp_noM));
  if (pt != NULL) {
    pt->peca.lado_esq = lado_esq;
    pt->peca.lado_dir = lado_dir;
    pt->prox = NULL;
    pt->ant = NULL;
  }
  return pt;
}

// Insere um novo nó no final da lista
int insere_listad_no_fimM(tp_listadM *lista, int lado_esq, int lado_dir) {
  tp_noM *novo = alocaM(lado_esq, lado_dir);
  if (!novo)
    return 0;
  if (listad_vaziaM(lista)) { // Se for o primeiro elemento da lista
    lista->ini = lista->fim = novo;
  } else {
    novo->ant = lista->fim;
    lista->fim->prox = novo;
    lista->fim = novo;
  }
  // lista->tamanho++;
  return 1;
}

// Insere um novo nó no início da lista
int insere_listad_no_inicioM(tp_listadM *lista, int lado_esq, int lado_dir) {
  tp_noM *novo = alocaM(lado_esq, lado_dir);
  if (!novo)
    return 0;
  if (listad_vaziaM(lista)) { // Se for o primeiro elemento da lista
    lista->ini = lista->fim = novo;
  } else {
    novo->prox = lista->ini;
    lista->ini->ant = novo;
    lista->ini = novo;
  }
  // lista->tamanho++;
  return 1;
}

// Imprime os conteúdos da lista (de frente para trás ou de trás pra frente)
void imprime_listadM(tp_listadM *lista, int ordem) {
  if (lista == NULL) {
    printf("Lista não inicializada\n");
  } else {
    tp_noM *atu;
    switch (ordem) {
    case 1: // Da frente para trás
      atu = lista->ini;
      while (atu != NULL) {
        printf("[%d|%d] ", atu->peca.lado_esq, atu->peca.lado_dir);
        atu = atu->prox;
      }
      break;
    case 2: // De trás para frente
      atu = lista->fim;
      while (atu != NULL) {
        printf("[%d|%d] ", atu->peca.lado_esq, atu->peca.lado_dir);
        atu = atu->ant;
      }
      break;
    default:
      printf("Código inválido\n");
    }
    printf("\n");
  }
}

// Remove um elemento da lista
int remove_listadM(tp_listadM *lista, int lado_esq, int lado_dir) {
  tp_noM *atu = lista->ini;
  while (atu != NULL &&
         (atu->peca.lado_esq != lado_esq || atu->peca.lado_dir != lado_dir)) {
    atu = atu->prox;
  }
  if (atu == NULL)
    return 0;
  if (lista->ini == lista->fim) { // Se for o único elemento da lista
    lista->ini = lista->fim = NULL;
  } else {
    if (lista->ini == atu) { // Se for o primeiro elemento da lista
      lista->ini = atu->prox;
      if (lista->ini != NULL)
        lista->ini->ant = NULL;
    } else if (lista->fim == atu) { // Se for o último nó da lista
      lista->fim = atu->ant;
      if (lista->fim != NULL)
        lista->fim->prox = NULL;
    } else { // Se estiver no meio da lista
      atu->prox->ant = atu->ant;
      atu->ant->prox = atu->prox;
    }
  }
  free(atu);
  // lista->tamanho--;
  return 1;
}

// Retira da memória todos os nós da lista e também o descritor
tp_listadM *Destroi_listadM(tp_listadM *lista) {
  tp_noM *atu = lista->ini;
  while (atu != NULL) {
    lista->ini = atu->prox;
    free(atu);
    atu = lista->ini;
  }
  free(lista);
  return NULL;
}

#endif
