#ifndef LISTADEMESA_H
#define LISTADEMESA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int lado_esq;
  int lado_dir;
} PecaDomino;

typedef struct {
  PecaDomino lado_esq;
  PecaDomino lado_dir;
} Mesa;

typedef Mesa tp_item_mesa;

// Estrutura que representa um nó da lista duplamente encadeada para a mesa
typedef struct tp_no_mesa_aux {
  struct tp_no_mesa_aux *ant;
  tp_item_mesa info;
  struct tp_no_mesa_aux *prox;
} tp_no_mesa;

// Estrutura que representa o descritor da lista para a mesa
typedef struct {
  tp_no_mesa *ini;
  tp_no_mesa *fim;
  // int tamanho;
} tp_listad_mesa;

// Inicializa a lista duplamente encadeada para a mesa
tp_listad_mesa *inicializa_listad_mesa() {
  tp_listad_mesa *lista = (tp_listad_mesa *)malloc(sizeof(tp_listad_mesa));
  lista->ini = NULL;
  lista->fim = NULL;
  // lista->tamanho = 0;
  return lista;
}

// Verifica se a lista da mesa está vazia
int listad_mesa_vazia(tp_listad_mesa *lista) { return (lista->ini == NULL); }

// Aloca um novo nó para a lista da mesa
tp_no_mesa *aloca_mesa() {
  tp_no_mesa *pt = (tp_no_mesa *)malloc(sizeof(tp_no_mesa));
  return pt;
}

// Insere um novo nó no fim da lista da mesa
int insere_listad_mesa_no_fim(tp_listad_mesa *lista, tp_item_mesa e) {
  tp_no_mesa *novo = aloca_mesa();
  if (!novo)
    return 0;
  novo->info = e;
  if (listad_mesa_vazia(lista)) { // Se for o primeiro elemento da lista
    novo->prox = NULL;
    novo->ant = NULL;
    lista->ini = lista->fim = novo;
  } else {
    novo->prox = NULL;
    novo->ant = lista->fim;
    lista->fim->prox = novo;
    lista->fim = novo;
  }
  // lista->tamanho++;
  return 1;
}

// Imprime os conteúdos da lista da mesa (de frente para trás ou de trás para
// frente)
void imprime_listad_mesa(tp_listad_mesa *lista, int ordem) {
  if (lista == NULL) {
    printf("Lista não inicializada");
  } else {
    tp_no_mesa *atu;
    switch (ordem) {
    case 1:
      atu = lista->ini;
      while (atu != NULL) {
        printf("[%d|%d] ", atu->info.lado_esq.lado_esq,
               atu->info.lado_esq.lado_dir);
        atu = atu->prox;
      }
      break;
    case 2:
      atu = lista->fim;
      while (atu != NULL) {
        printf("[%d|%d] ", atu->info.lado_esq.lado_esq,
               atu->info.lado_esq.lado_dir);
        atu = atu->ant;
      }
      break;
    default:
      printf("código inválido");
    }
  }
  printf("\n");
}

// Remove um elemento da lista da mesa
int remove_listad_mesa(tp_listad_mesa *lista, tp_item_mesa e) {
  tp_no_mesa *atu = lista->ini;
  while (atu != NULL && (atu->info.lado_esq.lado_esq != e.lado_esq.lado_esq ||
                         atu->info.lado_esq.lado_dir != e.lado_esq.lado_dir)) {
    atu = atu->prox;
  }
  if (atu == NULL)
    return 0;
  if (lista->ini == lista->fim) { // Se for o único elemento da lista
    lista->ini = lista->fim = NULL;
  } else {
    if (lista->ini == atu) { // Se for o primeiro elemento da lista
      lista->ini = atu->prox;
      atu->prox->ant = NULL;
    } else if (lista->fim == atu) { // Se for o último nó da lista
    
      }
  }