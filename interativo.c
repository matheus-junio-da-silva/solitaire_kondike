#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"
#include "ler_arquivo.h"

void ModoInterativo() {

    srand(time(NULL));  // Seed para a função de embaralhar

    Mesa mesa;
    InicializarMesa(&mesa);

    // Carrega um baralho aleatório
    //CarregarBaralhoAleatorio(&mesa);

    // Prepara a mesa distribuindo cartas para o tableau
    PrepararMesa(&mesa);

    // Exibe o estado inicial da mesa
    printf("Estado inicial da mesa:\n");
    ExibirMesa(&mesa);

    // Jogo principal
    int opcao;
    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Comprar uma carta\n");
        printf("2. Mover carta do descarte para bases\n");
        printf("3. Mover carta do descarte para tableau\n");
        printf("4. Mover carta do bases para tableau\n");
        printf("5. Mover carta entre colunas do tableau\n");
        printf("6. Exibir a mesa\n");
        printf("7. Mover carta do tableau para bases\n");
        printf("0. Sair\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                ComprarCarta(&mesa);
                ExibirMesa(&mesa);
                break;
            case 2:
                MoverDescarteParaBases(&mesa);
                ExibirMesa(&mesa);
                break;
            case 3:
                printf("Informe o indice do tableau (0 a 6): ");
                int indiceTableau;
                scanf("%d", &indiceTableau);
                MoverDescarteParaTableau(&mesa, indiceTableau);
                ExibirMesa(&mesa);
                break;
            case 4:
                printf("Informe o indice da base (0 a 3): ");
                int indiceBase;
                scanf("%d", &indiceBase);
                printf("Informe o indice do tableau (0 a 6): ");
                scanf("%d", &indiceTableau);
                MoverBasesParaTableau(&mesa, indiceBase, indiceTableau);
                ExibirMesa(&mesa);
                break;
            case 5:
                printf("Informe o numero de cartas a serem movidas: ");
                int qtdCartas;
                scanf("%d", &qtdCartas);
                printf("Informe o indice da coluna de origem (0 a 6): ");
                int indiceOrigem;
                scanf("%d", &indiceOrigem);
                printf("Informe o indice da coluna de destino (0 a 6): ");
                int indiceDestino;
                scanf("%d", &indiceDestino);
                MoverEntreColunasTableau(&mesa, qtdCartas, indiceOrigem, indiceDestino);
                ExibirMesa(&mesa);
                break;
            case 6:
                ExibirMesa(&mesa);
                break;
            case 7:
                printf("Informe o indice do tableau (0 a 6): ");
                scanf("%d", &indiceTableau);
                MoverTableauParaBases(&mesa, indiceTableau);
                ExibirMesa(&mesa);
                break;
            case 0:
                printf("Saindo do jogo. Obrigado por jogar!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        // Verifica se o jogador venceu
        if (VerificarVitoria(&mesa)) {
            printf("Parabens! Voce venceu o jogo!\n");
            break;
        }

    } while (opcao != 0 && !VerificarVitoria(&mesa));

}

