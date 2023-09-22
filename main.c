#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"

int main() {

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

    return 0;







    /*
    // Inicialize a lista de cartas
    ListaDeCartas lista;
    Inicializar(&lista);

    // Crie algumas cartas
    Carta carta1 = criarCarta(1, 0, 1); // 2 de Copas
    Carta carta2 = criarCarta(2, 0, 1); // 3 de Copas
    Carta carta3 = criarCarta(3, 0, 1); // 4 de Copas

    // Adicione as cartas à lista
    AdicionarNoTopo(&lista, carta1);
    AdicionarNoTopo(&lista, carta2);
    AdicionarNoTopo(&lista, carta3);

    // Exiba a lista de cartas
    Exibir(&lista, true);

    // Embaralhe as cartas
    Embaralhar(&lista);

    // Exiba a lista de cartas embaralhada
    Exibir(&lista, true);

    // Retire uma carta do topo
    Carta cartaRetirada;
    RetirarDoTopo(&lista, &cartaRetirada);
    printf("Carta retirada: ");
    exibir_carta(cartaRetirada);

    // Exiba a lista de cartas após a retirada
    Exibir(&lista, true);

    Mesa mesa;
    InicializarMesa(&mesa);

    // carregou o baralho de 52 cartas mas com todas virada para baixo, sendo o topo
    //CarregarBaralhoAleatorio(&mesa);



    PrepararMesa(&mesa); // ja carrega o baralho aleatorio

    ExibirMesa(&mesa);

    VerificarVitoria(&mesa);

    printf("--------------------------------:\n");

    //for (int i = 0; i < 25; i++) {
        //ComprarCarta(&mesa);
    //}

    ComprarCarta(&mesa);
    //ExibirMesa(&mesa);

    //MoverDescarteParaBases(&mesa);

    ExibirMesa(&mesa);

    int indice;
    int indice2;
    int indice3;
    printf("Digite o índice da coluna tableau 0 a 6: ");
    scanf("%d", &indice);

    //MoverDescarteParaTableau(&mesa, indice);

    MoverTableauParaBases(&mesa, indice);
    ExibirMesa(&mesa);

    printf("Digite o índice da base a ser retirada a carta 0 a 3: ");
    scanf("%d", &indice2);
    printf("Digite o índice da coluna tableau a ser colocada a carta 0 a 6: ");
    scanf("%d", &indice3);
    MoverBasesParaTableau(&mesa, indice2 , indice3);
    ExibirMesa(&mesa);
    return 0;
    */
}

