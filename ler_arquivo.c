#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"

int VerificarVitoriaArquivo(Mesa* mesa,int numCartas) {
    // Verificar se todas as bases têm 13 cartas (uma de cada naipe)

    int base[3];

    for (int naipe = 0; naipe < 4; naipe++) {
        base[naipe] = mesa->bases[naipe].tamanho;
    }
    int count = 0;
    for (int naipe = 0; naipe < 4; naipe++) {
        count += base[naipe];
    }
    // Se todas as bases têm 13 cartas e todas as colunas do tableau estão vazias, então venceu
    if(count != numCartas) {
        printf("ainda nao venceu.\n");
        return 0;
    }
    printf("venceu.\n");
    printf("Pontuacao: %d\n", mesa->pontuacao);
    return 1;
}

void PrepMesa(Mesa* mesa) {
    // Carrega o baralho aleatório
    //CarregarBaralhoAleatorio(mesa);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            Carta carta; // inicializa uma carta para rebeber uma carta que estava no topo
            RetirarDoTopo(&(mesa->baralho), &carta);

            if (j == i) {
                // A última carta em cada coluna fica virada para cima, obs: ultimo de cada loop do j
                alterarPosicao(&carta, 1);
            }
            //alterarPosicao(&carta, 1);
            AdicionarNoTopo(&(mesa->tableau[i]), carta);
        }
    }

    for (int i = 0; i < 7; i++) {
        Exibir(&mesa->tableau[i], true);
    }

}

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
    char nomeArquivo[100] = "teste2.txt";
    /*
    char nomeArquivo[100];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);
    printf("O nome do arquivo digitado foi: %s\n", nomeArquivo);
    */
    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;  // Retornar 0 para indicar erro
    }

    //mesa->descarte.tamanho = 0;


    // Variáveis temporárias para armazenar informações do arquivo
    int numCartas;
    char naipe;
    int valor;
    char base[3];
    // Ler o número de cartas no baralho
    fscanf(arquivo, "%d", &numCartas);

    // Ler e adicionar as cartas ao baralho da mesa
    for (int i = 0; i < numCartas; i++) {
        fscanf(arquivo, "\n(%d %c)", &valor, &naipe);
        AdicionarCartaAoBaralho(mesa, valor-1, naipe);
        Carta carta;
        CartaNoTopo(&(mesa->baralho), &carta);
        printf("Naipe da carta: %d\n", carta.naipe);
        printf("valor da carta: %d\n", carta.valor);

    }

    PrepMesa(mesa);

    ExibirMesa(mesa);

    char operacao[3];  // Para armazenar as operações (CC, DB, DT, TB, BT, ou TT)
    int parametros[3];  // Para armazenar os parâmetros das operações
    char linha[10];
    // Ler e processar as operações
    while (fscanf(arquivo, "%s", operacao) != EOF) {
        if (VerificarVitoriaArquivo(mesa, numCartas)) {
            printf("Parabens! Voce venceu o jogo!\n");
            return 1;
        }
        if (strcmp(operacao, "CC") == 0) {
            ComprarCarta(mesa);
            ExibirMesa(mesa);
        } else if (strcmp(operacao, "DB") == 0) {
            // Processar operação DB (Exemplo: DescartarDoBaralho(mesa);)

            MoverDescarteParaBases(mesa);
            ExibirMesa(mesa);

        } else if (strcmp(operacao, "DT") == 0) {
            // Ler o índice do tableau
            fscanf(arquivo, "%d", &parametros[0]);
            // Processar operação DT (Exemplo: DescartarDoTableau(mesa, parametros[0]);)

            MoverDescarteParaTableau(mesa, (parametros[0])-1);
            ExibirMesa(mesa);

        } else if (strcmp(operacao, "TB") == 0) {
            // Ler o índice do tableau
            fscanf(arquivo, "%d", &parametros[0]);
            printf("oiiiiii");
            // Processar operação TB (Exemplo: MoverParaBaralhoDoTableau(mesa, parametros[0]);)
            MoverTableauParaBases(mesa, (parametros[0])-1);
            ExibirMesa(mesa);
        } else if (strcmp(operacao, "BT") == 0) {
            // Ler o naipe e o índice do tableau
            fscanf(arquivo, "%s", linha);
            sscanf(linha, "%c %d", &base[0], &parametros[0]);
            // Processar operação BT (Exemplo: MoverCartaParaTableau(mesa, naipe, parametros[0]);)
            printf("olaaaaaaaaaaaa%c", base[0]);
            switch(base[0]) {
            case 'C':  // Copas
                MoverBasesParaTableau(mesa, 0, parametros[0]);
                break;
            case 'E':  // Espadas
                MoverBasesParaTableau(mesa, 1, parametros[0]);
                break;
            case 'O':  // Ouros
                MoverBasesParaTableau(mesa, 2, parametros[0]);
                break;
            case 'P':  // Paus
                MoverBasesParaTableau(mesa, 3, parametros[0]);
                break;
            default:
            printf("base desconhecida: %c\n", base[0]);
            return 0;  // Retorne se o naipe for desconhecido
            }
            ExibirMesa(mesa);


        } else if (strcmp(operacao, "TT") == 0) {
            // Ler os três parâmetros: quantidade, índice de origem e índice de destino
            fscanf(arquivo, "%d %d %d", &parametros[0], &parametros[1], &parametros[2]);
            // Processar operação TT (Exemplo: MoverCartasEntreColunasTableau(mesa, parametros[0], parametros[1], parametros[2]);)
            printf("zzzzzzzzzz");
            MoverEntreColunasTableau(mesa, (parametros[0]), (parametros[1])-1, (parametros[2])-1);
            printf("aaaaaaaaaaaa");
            ExibirMesa(mesa);
        }else if (strcmp(operacao, "X") == 0) {
            ExibirMesa(mesa);
            printf("Pontuacao: %d\n", mesa->pontuacao);
        }else {
            printf("Operacao desconhecida: %s\n", operacao);
        }

    }
    if (feof(arquivo)) {
        printf("Fim do arquivo alcançado.\n");
    } else if (ferror(arquivo)) {
        printf("Erro durante a leitura do arquivo.\n");
    } else {
        printf("aaaaaaaaaaaa");
    }


    ExibirMesa(mesa);
    printf("Pontuacao: %d\n", mesa->pontuacao);
    fclose(arquivo);
    return 1;  // Retornar 1 para indicar sucesso
}
