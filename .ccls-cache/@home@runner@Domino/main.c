#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jogador.h"
#include "jogo.h"

int main() {

  PecaDomino pecas[28];
  PecaDomino pecaDesempilhada;
  tp_pilha pilha;

  int num_jogadores;
  int permitido = 0;

  interface();

  do {
    printf("\nQuantos jogadores deseja criar? ");
    scanf("%d", &num_jogadores);
    permitido = verificar_qntd_jogadores(num_jogadores);
  } while (permitido == 0);

  Jogador *jogadores = criar_jogadores(num_jogadores);
  listar_jogadores(num_jogadores, jogadores);

  tp_listad *maoJogador[num_jogadores];
  for (int i = 0; i < num_jogadores; i++) {
    maoJogador[i] = inicializa_listad();
  }

  // Criação de todas as peças
  inicializa_pecas(pecas);
  embaralha_pecas(pecas);

  // Inicializa a pilha do cava
  inicializa_pilha(&pilha);
  // Empilha as peças no cava
  empilhar_pecas(&pilha, pecas);

  // Distribui as peças para as mãos dos jogadores
  for (int i = 0; i < num_jogadores; i++) {
    printf("\nMão Jogador %s\n", jogadores[i].nome);
    distribuirNaMao(&pilha, &pecaDesempilhada, maoJogador[i]);
    imprime_listad(maoJogador[i], 1);
  }

  // Imprime o cava
  printf("\nCava");
  imprime_pilha(pilha);
  printf("\n");

  // Decidir a jogada - Feito
  // escolhar a peça - Feito
  // jogar na mesa
  int jogadorDaVez = 0;
  int pecaRemovida = 0;
  for (int i = 0; i < 27; i++) {
    printf("\nVez do jogador %s\n", jogadores[jogadorDaVez].nome);
    imprime_listad(maoJogador[jogadorDaVez], 1);
    printf(" \n");
    do{
      printf("Qual é a peça que você quer jogar?");
      scanf("%d%d", &pecaDesempilhada.lado_esq, &pecaDesempilhada.lado_dir);
      pecaRemovida = remove_listad(maoJogador[jogadorDaVez], pecaDesempilhada);
      if(pecaRemovida == 0){
        printf("\nPeça inválida, tente novamente\n");
      }
    }while(pecaRemovida == 0);
    jogadorDaVez = (jogadorDaVez + 1) % num_jogadores;
  }

  for (int i = 0; i < num_jogadores; i++) {
    maoJogador[i] = Destroi_listad(maoJogador[i]);
  }

  free(jogadores);

  return 0;
}