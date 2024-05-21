#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pecas.h"

#define MAX 28

typedef struct {
  int topo;
  PecaDomino item[MAX];
} tp_pilha;

void inicializa_pilha(tp_pilha *p) { p->topo = -1; }

int pilha_cheia(tp_pilha *p) {
  if (p->topo == MAX - 1) {
    return 1;
  } else {
    return 0;
  }
}

int push(tp_pilha *p, PecaDomino e) {
  if (pilha_cheia(p) == 1)
    return 0;
  p->topo++;
  p->item[p->topo] = e;
  return 1;
}

int pilha_vazia(tp_pilha *p) {
  if (p->topo == -1)
    return 1;
  return 0;
}

int pop(tp_pilha *p, PecaDomino *e) {
  if (pilha_vazia(p))
    return 0;
  *e = p->item[p->topo];
  p->topo--;
  return 1;
}

void imprime_pilha(tp_pilha p) {
  PecaDomino e;
  printf("\n");
  while (!pilha_vazia(&p)) {
    pop(&p, &e);
    printf("\n[%d][%d]", e.lado_esq, e.lado_dir);
  }
}

void maracao_criacao_da_pilha() { printf("----- Pilha criada -----"); }

void empilhar_pecas(tp_pilha *p, PecaDomino pecas[]) {
  for (int i = 0; i < MAX; i++) {
    push(p, pecas[i]);
  }
}
