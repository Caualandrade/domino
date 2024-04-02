#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 28

#include "pilha.h"
#include "pecas.h"

typedef struct
{
    char nome[50];
} Jogador;

typedef struct
{
    int lado_esq;
    int lado_dir;
} PecaDomino;

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

void interface()
{
    printf("##########################\n");
    printf("######### DOMINO #########\n");
    printf("######### REGRAS #########\n 1- Permitido 2 ou 4 jogadores\n 2- \n 3- \n 4- \n");
    printf("##########################\n");
}

typedef struct
{
    int topo;
    PecaDomino item[MAX];
} tp_pilha;

void inicializa_pilha(tp_pilha *p)
{
    p->topo = -1;
}

int pilha_cheia(tp_pilha *p)
{
    if (p->topo == MAX - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int push(tp_pilha *p, PecaDomino e)
{
    if (pilha_cheia(p) == 1)
        return 0;
    p->topo++;
    p->item[p->topo] = e;
    return 1;
}

int pilha_vazia(tp_pilha *p)
{
    if (p->topo == -1)
        return 1;
    return 0;
}

int pop(tp_pilha *p, PecaDomino *e)
{
    if (pilha_vazia(p))
        return 0;
    *e = p->item[p->topo];
    p->topo--;
    return 1;
}

void imprime_pilha(tp_pilha p)
{
    PecaDomino e;
    printf("\n");
    while (!pilha_vazia(&p))
    {
        pop(&p, &e);
        printf("\n[%d][%d]", e.lado_esq, e.lado_dir);
    }
}

void maracao_criacao_da_pilha()
{
    printf("----- Pilha criada -----");
}

void empilhar_pecas(tp_pilha *p,PecaDomino pecas[]){
    for (int i = 0; i < MAX; i++)
    {
        push(p,pecas[i]);
    }
}

int main()
{

    PecaDomino pecas[28];
    PecaDomino pecaDesempilhada;
    tp_pilha pilha;
    int num_jogadores;
    int permitido = 0;

    interface();

    inicializa_pecas(pecas);
    embaralha_pecas(pecas);

    do
    {
        printf("Quantos jogadores deseja criar?");
        scanf("%d", &num_jogadores);
        permitido = verificar_qntd_jogadores(num_jogadores);
    } while (permitido == 0);

    Jogador *jogadores = criar_jogadores(num_jogadores);
    listar_jogadores(num_jogadores, jogadores);

    printf("\n");
    maracao_criacao_da_pilha();
    inicializa_pilha(&pilha);
    empilhar_pecas(&pilha,pecas);
    imprime_pilha(pilha);
    printf("\n----------------");
    int retirado = pop(&pilha, &pecaDesempilhada);
    if(retirado){
        printf("\nPeca retirada [%d][%d]", pecaDesempilhada.lado_esq,pecaDesempilhada.lado_dir);   
    }
    
    printf("\n----------------");
    imprime_pilha(pilha);
    free(jogadores);

    return 0;
}
