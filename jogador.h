#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "listaDE.h"

typedef struct {
  char nome[50];
} Jogador;

Jogador *criar_jogadores(int num_jog) {
  Jogador *jogadores = (Jogador *)malloc(num_jog * sizeof(Jogador));
  for (int i = 0; i < num_jog; i++) {
    printf("Qual eh o nome do jogador %d? ", i + 1);
    scanf("%s", jogadores[i].nome);
  }
  return jogadores;
}

void listar_jogadores(int num_jogadores, Jogador *lista_jogadores) {
  printf("Lista de jogadores:\n");
  for (int i = 0; i < num_jogadores; i++) {
    printf("Jogador %d: %s\n", i + 1, lista_jogadores[i].nome);
  }
}

int verificar_qntd_jogadores(int qntd) {
  if (qntd == 2 || qntd == 4) {
    return 1;
  } else {
    printf("Numero de jogadores invalidos. Apenas 2 ou 4 jogadores\n");
    return 0;
  }
}

void distribuirNaMao(tp_pilha *pilha,PecaDomino *pecaDesempilhada, tp_listad *maoDoJogador){
  for(int i = 0; i < 7; i++){
    pop(pilha, pecaDesempilhada);
    insere_listad_no_fim(maoDoJogador, *pecaDesempilhada);
  }
}