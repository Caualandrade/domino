#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int lado_esq;
    int lado_dir;
} PecaDomino;

typedef struct
{
    char nome[50];
} Jogador;

Jogador *criar_jogadores(int num_jog)
{
    Jogador *jogadores = (Jogador *)malloc(num_jog * sizeof(Jogador));
    for (int i = 0; i < num_jog; i++)
    {
        printf("Qual eh o nome do jogador %d? ", i + 1);
        scanf("%s", jogadores[i].nome);
    }
    return jogadores;
}

void listar_jogadores(int num_jogadores, Jogador *lista_jogadores)
{
    printf("Lista de jogadores:\n");
    for (int i = 0; i < num_jogadores; i++)
    {
        printf("Jogador %d: %s\n", i + 1, lista_jogadores[i].nome);
    }
}

int verificar_qntd_jogadores(int qntd)
{
    if (qntd == 2 || qntd == 4)
    {
        return 1;
    }
    else
    {
        printf("Numero de jogadores invalidos. Apenas 2 ou 4 jogadores\n");
        return 0;
    }
}

void inicializa_pecas(PecaDomino pecas[])
{
    int num_pecas = 0;
    for (int i = 0; i <= 6; i++)
    {
        for (int j = i; j <= 6; j++)
        {
            pecas[num_pecas].lado_esq = i;
            pecas[num_pecas].lado_dir = j;
            num_pecas++;
        }
    }
}

void embaralha_pecas(PecaDomino pecas[])
{
    srand(time(NULL));

    for (int i = 27; i > 0; i--)
    {
        int j = rand() % (i + 1);

        PecaDomino temp = pecas[i];
        pecas[i] = pecas[j];
        pecas[j] = temp;
    }
}

void listar_pecas(PecaDomino *pecas)
{
    printf("Pecas embaralhadas:\n");
    for (int i = 0; i < 28; i++)
    {
        printf("\n[%d|%d]", pecas[i].lado_esq, pecas[i].lado_dir);
    }
    printf("\n");
}

void interface()
{
    printf("##########################\n");
    printf("######### DOMINO #########\n");
    printf("######### REGRAS #########\n 1- Permitido 2 ou 4 jogadores\n 2- \n 3- \n 4- \n");
    printf("##########################\n");
}

int main()
{

    interface();

    PecaDomino pecas[28];

    inicializa_pecas(pecas);
    embaralha_pecas(pecas);
    listar_pecas(pecas);

    int num_jogadores;
    int permitido = 0;

    do
    {
        printf("Quantos jogadores deseja criar?");
        scanf("%d", &num_jogadores);
        permitido = verificar_qntd_jogadores(num_jogadores);
    } while (permitido == 0);

    Jogador *jogadores = criar_jogadores(num_jogadores);
    listar_jogadores(num_jogadores, jogadores);

    free(jogadores);

    return 0;
}
