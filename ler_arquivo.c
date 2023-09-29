#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"

void ExibirMenu() {
    printf("Escolha uma acao:\n");
    printf("1. Mover carta do tableau para foundation.\n");
    printf("2. Mover carta do tableau para tableau.\n");
    printf("3. Mover carta da foundation para tableau.\n");
    printf("4. Mover carta da foundation para foundation.\n");
    printf("5. Virar carta do estoque.\n");
    printf("6. Sair do jogo.\n");
}

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

int LerJogoDeArquivo(Mesa* mesa, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;  // Retornar 0 para indicar erro
    }

    // Variáveis temporárias para armazenar informações do arquivo
    int numCartas;
    char naipe;
    int valor;

    // Ler o número de cartas no baralho
    fscanf(arquivo, "%d", &numCartas);

    // Ler e adicionar as cartas ao baralho da mesa
    for (int i = 0; i < numCartas; i++) {
        fscanf(arquivo, "(%d %c)", &valor, &naipe);
        // Exemplo: AdicionarCartaAoBaralho(mesa, valor, naipe);
    }

    char operacao[3];  // Para armazenar as operações (CC, DB, DT, TB, BT, ou TT)
    int parametros[3];  // Para armazenar os parâmetros das operações

    // Ler e processar as operações
    while (fscanf(arquivo, "%s", operacao) != EOF) {
        if (strcmp(operacao, "CC") == 0) {

        } else if (strcmp(operacao, "DB") == 0) {
            // Processar operação DB (Exemplo: DescartarDoBaralho(mesa);)
        } else if (strcmp(operacao, "DT") == 0) {
            // Ler o índice do tableau
            fscanf(arquivo, "%d", &parametros[0]);
            // Processar operação DT (Exemplo: DescartarDoTableau(mesa, parametros[0]);)
        } else if (strcmp(operacao, "TB") == 0) {
            // Ler o índice do tableau
            fscanf(arquivo, "%d", &parametros[0]);
            // Processar operação TB (Exemplo: MoverParaBaralhoDoTableau(mesa, parametros[0]);)
        } else if (strcmp(operacao, "BT") == 0) {
            // Ler o naipe e o índice do tableau
            fscanf(arquivo, " %c %d", &naipe, &parametros[0]);
            // Processar operação BT (Exemplo: MoverCartaParaTableau(mesa, naipe, parametros[0]);)
        } else if (strcmp(operacao, "TT") == 0) {
            // Ler os três parâmetros: quantidade, índice de origem e índice de destino
            fscanf(arquivo, "%d %d %d", &parametros[0], &parametros[1], &parametros[2]);
            // Processar operação TT (Exemplo: MoverCartasEntreColunasTableau(mesa, parametros[0], parametros[1], parametros[2]);)
        } else {
            printf("Operacao desconhecida: %s\n", operacao);
        }
    }

    fclose(arquivo);
    return 1;  // Retornar 1 para indicar sucesso
}
