#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jogador.h"
#include "jogo.h"
#include "listaDE.h"

int main() {
  PecaDomino pecas[28];
  PecaDomino pecaDesempilhada;
  tp_pilha pilha;

  int num_jogadores;
  int permitido = 0;

  do {
    printf("Quantos jogadores deseja criar? ");
    scanf("%d", &num_jogadores);
    permitido = verificar_qntd_jogadores(num_jogadores);
  } while (permitido == 0);

  tp_listad *maoJogador[num_jogadores];

  for (int i = 0; i < num_jogadores; i++) {
    maoJogador[i] = inicializa_listad();
  }

  Jogador *jogadores = criar_jogadores(num_jogadores);
  listar_jogadores(num_jogadores, jogadores);

  // Criação de todas as peças
  inicializa_pecas(pecas);
  embaralha_pecas(pecas);

  // Inicializa a pilha do cava
  inicializa_pilha(&pilha);
  // Empilha as peças no cava
  empilhar_pecas(&pilha, pecas);

  // Distribui as peças para as mãos dos jogadores
  for (int i = 0; i < num_jogadores; i++) {
    printf("Mão Jogador %s\n", jogadores[i].nome);
    distribuirNaMao(&pilha, &pecaDesempilhada, maoJogador[i]);
    imprime_listad(maoJogador[i], 1);
  }

  for (int i = 0; i < num_jogadores; i++) {
    maoJogador[i] = Destroi_listad(maoJogador[i]);
  }

  free(jogadores);

  return 0;
}