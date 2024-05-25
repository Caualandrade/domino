#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jogo.h"
#include "listademesa.h"

int main() {

  PecaDomino pecas[28];
  PecaDomino pecaDesempilhada;
  tp_pilha pilhaCava;

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
  inicializa_pilha(&pilhaCava);
  // Empilha as peças no cava
  empilhar_pecas(&pilhaCava, pecas);

  // Distribui as peças para as mãos dos jogadores
  for (int i = 0; i < num_jogadores; i++) {
    printf("\nMão Jogador %s\n", jogadores[i].nome);
    distribuirNaMao(&pilhaCava, &pecaDesempilhada, maoJogador[i]);
    imprime_listad(maoJogador[i], 1);
  }

  // Decidir a jogada - Feito
  // escolhar a peça - Feito
  // jogar na mesa - feito

  tp_listadM *mesa = inicializa_listadM();

  int jogadorDaVez = 0;
  int pecaRemovida = 0;
  int resposta = 0;
  for (int i = 0; i < 27; i++) {
    printf("\nJogada: %d\n", i + 1);
    printf("\nVez do jogador %s\n", jogadores[jogadorDaVez].nome);
    imprime_listad(maoJogador[jogadorDaVez], 1);
    printf(" \n");
    do {
      printf("1 - Jogar Peça\n2 - Cavar peça\n");
      scanf("\n%d", &resposta);
    } while (resposta != 1 && resposta != 2);
    if (resposta == 1) {
      do {
        printf("Qual é a peça que você quer jogar?");
        scanf("%d%d", &pecaDesempilhada.lado_esq, &pecaDesempilhada.lado_dir);
        pecaRemovida = remove_listad(maoJogador[jogadorDaVez], pecaDesempilhada);
        if (pecaRemovida == 0) {
          printf("\nPeça inválida, tente novamente\n");
        }
      } while (pecaRemovida == 0);
      if (i == 0) {
        insere_listad_no_inicioM(mesa, pecaDesempilhada.lado_esq,
                                 pecaDesempilhada.lado_dir);
      }
      if (i > 0) {
        printf("Você deseja jogar no esquerda (0) ou na direita (1)?");
        scanf("%d", &resposta);
        if (resposta == 0) {
          printf("Você deseja virar a peça? NAO(0) SIM (1) ");
          scanf("%d", &resposta);
          if (resposta == 0) {
            insere_listad_no_inicioM(mesa, pecaDesempilhada.lado_esq,
                                     pecaDesempilhada.lado_dir);
          } else if (resposta == 1) {
            insere_listad_no_inicioM(mesa, pecaDesempilhada.lado_dir,
                                     pecaDesempilhada.lado_esq);
          }
        } else if (resposta == 1) {
          printf("Você deseja virar a peça? NAO(0) SIM (1) ");
          scanf("%d", &resposta);
          if (resposta == 0) {
            insere_listad_no_fimM(mesa, pecaDesempilhada.lado_esq,
                                  pecaDesempilhada.lado_dir);
          } else if (resposta == 1) {
            insere_listad_no_fimM(mesa, pecaDesempilhada.lado_dir,
                                  pecaDesempilhada.lado_esq);
          }
        }
      }
      jogadorDaVez = (jogadorDaVez + 1) % num_jogadores;
    }
    else if (resposta == 2) {
      do {
        int cavaVazio = 0;
        cavaVazio = pilha_vazia(&pilhaCava);
        if (cavaVazio == 1) {
          printf("O cava está vazio, você não pode cavar\n");
          break;
        } else if (cavaVazio == 0) {
          distribuirNaMaoCava(&pilhaCava, &pecaDesempilhada,
                              maoJogador[jogadorDaVez]);
          imprime_listad(maoJogador[jogadorDaVez], 1);
        }
        printf("\nDeseja mais uma peça? 0 - Nao 1 - Sim\n");
        scanf("\n%d", &resposta);
      } while (resposta == 1);
    }
    printf("\nMesa:");
    imprime_listadM(mesa, 1);
  }

  for (int i = 0; i < num_jogadores; i++) {
    maoJogador[i] = Destroi_listad(maoJogador[i]);
  }

  free(jogadores);

  return 0;
}