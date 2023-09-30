#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"

void AdicionarCartaAoBaralho(Mesa* mesa, int valor, char naipe) {
    Carta carta;
    carta.valor = valor;

    switch(naipe) {
        case 'C':  // Copas
            carta.naipe = 0;
            break;
        case 'E':  // Espadas
            carta.naipe = 1;
            break;
        case 'O':  // Ouros
            carta.naipe = 2;
            break;
        case 'P':  // Paus
            carta.naipe = 3;
            break;
        default:
            printf("Naipe desconhecido: %c\n", naipe);
            return;  // Retorne se o naipe for desconhecido
    }

    carta.virada_para_cima = 0;
    AdicionarNoTopo(&(mesa->baralho), carta);
}


void ExibirMenu() {
    printf("Escolha uma acao:\n");
    printf("1. Mover carta do tableau para foundation.\n");
    printf("2. Mover carta do tableau para tableau.\n");
    printf("3. Mover carta da foundation para tableau.\n");
    printf("4. Mover carta da foundation para foundation.\n");
    printf("5. Virar carta do estoque.\n");
    printf("6. Sair do jogo.\n");
}

int LerJogoDeArquivo(Mesa* mesa) {
    char nomeArquivo[100] = "teste.txt";
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;  // Retornar 0 para indicar erro
    }

    // Vari�veis tempor�rias para armazenar informa��es do arquivo
    int numCartas;
    char naipe;
    int valor;
    // Ler o n�mero de cartas no baralho
    fscanf(arquivo, "%d", &numCartas);

    // Ler e adicionar as cartas ao baralho da mesa
    for (int i = 0; i < numCartas; i++) {
        fscanf(arquivo, "\n(%d %c)", &valor, &naipe);
        AdicionarCartaAoBaralho(mesa, valor, naipe);
        Carta carta;
        CartaNoTopo(&(mesa->baralho), &carta);
        printf("Naipe da carta: %d\n", carta.naipe);
        printf("valor da carta: %d\n", carta.valor);

    }

    char operacao[3];  // Para armazenar as opera��es (CC, DB, DT, TB, BT, ou TT)
    int parametros[3];  // Para armazenar os par�metros das opera��es

    // Ler e processar as opera��es
    while (fscanf(arquivo, "%s", operacao) != EOF) {
        if (strcmp(operacao, "CC") == 0) {
            ComprarCarta(mesa);
        } else if (strcmp(operacao, "DB") == 0) {
            // Processar opera��o DB (Exemplo: DescartarDoBaralho(mesa);)
            MoverDescarteParaBases(mesa);
        } else if (strcmp(operacao, "DT") == 0) {
            // Ler o �ndice do tableau
            fscanf(arquivo, "%d", &parametros[0]);
            // Processar opera��o DT (Exemplo: DescartarDoTableau(mesa, parametros[0]);)
            MoverDescarteParaTableau(mesa, parametros[0]);
        } else if (strcmp(operacao, "TB") == 0) {
            // Ler o �ndice do tableau
            fscanf(arquivo, "%d", &parametros[0]);
            printf("oiiiiii");
            // Processar opera��o TB (Exemplo: MoverParaBaralhoDoTableau(mesa, parametros[0]);)
        } else if (strcmp(operacao, "BT") == 0) {
            // Ler o naipe e o �ndice do tableau
            fscanf(arquivo, " %c %d", &naipe, &parametros[0]);
            // Processar opera��o BT (Exemplo: MoverCartaParaTableau(mesa, naipe, parametros[0]);)
        } else if (strcmp(operacao, "TT") == 0) {
            // Ler os tr�s par�metros: quantidade, �ndice de origem e �ndice de destino
            fscanf(arquivo, "%d %d %d", &parametros[0], &parametros[1], &parametros[2]);
            // Processar opera��o TT (Exemplo: MoverCartasEntreColunasTableau(mesa, parametros[0], parametros[1], parametros[2]);)
        } else {
            printf("Operacao desconhecida: %s\n", operacao);
        }
    }

    fclose(arquivo);
    return 1;  // Retornar 1 para indicar sucesso
}
