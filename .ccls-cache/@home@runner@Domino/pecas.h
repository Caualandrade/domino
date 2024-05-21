#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int lado_esq;
  int lado_dir;
} PecaDomino;

void inicializa_pecas(PecaDomino pecas[]) {
  int num_pecas = 0;
  for (int i = 0; i <= 6; i++) {
    for (int j = i; j <= 6; j++) {
      pecas[num_pecas].lado_esq = i;
      pecas[num_pecas].lado_dir = j;
      num_pecas++;
    }
  }
}

void embaralha_pecas(PecaDomino pecas[]) {
  srand(time(NULL));

  for (int i = 27; i > 0; i--) {
    int j = rand() % (i + 1);

    PecaDomino temp = pecas[i];
    pecas[i] = pecas[j];
    pecas[j] = temp;
  }
}

void listar_pecas(PecaDomino *pecas) {
  printf("Pecas embaralhadas:\n");
  for (int i = 0; i < 28; i++) {
    printf("\n[%d|%d]", pecas[i].lado_esq, pecas[i].lado_dir);
  }
  printf("\n");
}