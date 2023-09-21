#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"

#define NUM_BASES 4
#define NUM_TABLEAU 7
#define MAX_CARTAS_MESA 52
#define NUM_COLUNAS_TABLEAU 7
#define NUM_NAIPE 4
#define NUM_CARTAS_POR_NAIPE 13

void InicializarMesa(Mesa* mesa) {
    // topo null
    Inicializar(&mesa->baralho);
    Inicializar(&mesa->descarte);
    for (int i = 0; i < 4; i++) {
        // null nos 4 indices do vetor
        Inicializar(&mesa->bases[i]);
    }
    for (int i = 0; i < 7; i++) {
        Inicializar(&mesa->tableau[i]);
    }
    mesa->pontuacao = 0;
}

void CarregarBaralhoAleatorio(Mesa* mesa) {
    for (int naipe = 0; naipe < 4; naipe++) {
        for (int valor = 0; valor < 13; valor++) {
            Carta novaCarta = criarCarta(valor, naipe, 0);
            AdicionarNoTopo(&(mesa->baralho), novaCarta);
        }
    }
    for (int i = 0; i < 7; i++) {
        Exibir(&mesa->tableau[i], true);
    }

    Embaralhar(&(mesa->baralho));
}
/*
Carregar baralho: insere cartas no baralho de acordo com as cartas passadas num
par�metro de entrada, preservando a ordem passada.

void CarregarBaralho(Mesa* mesa, Carta* cartas, int numCartas) {
    // Certifique-se de que o n�mero de cartas a serem carregadas seja v�lido
    if (numCartas < 0 || numCartas > MAX_CARTAS_MESA) {
        printf("N�mero de cartas inv�lido.\n");
        exit(1);
    }

    // Limpa o baralho existente antes de carregar as novas cartas
    LimparBaralho(mesa);

    // Adiciona as cartas ao baralho da mesa
    for (int i = 0; i < numCartas; i++) {
        if (mesa->baralho.tamanho < MAX_CARTAS_MESA) {
            AdicionarNoTopo(&(mesa->baralho), cartas[i]);
        } else {
            printf("Baralho da mesa est� cheio. N�o � poss�vel adicionar mais cartas.\n");
            break;
        }
    }
}
*/

void PrepararMesa(Mesa* mesa) {
    // Carrega o baralho aleat�rio
    CarregarBaralhoAleatorio(mesa);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            Carta carta; // inicializa uma carta para rebeber uma carta que estava no topo
            RetirarDoTopo(&(mesa->baralho), &carta);
            if (j == i) {
                // A �ltima carta em cada coluna fica virada para cima, obs: ultimo de cada loop do j
                alterarPosicao(&carta, 1);
            }
            AdicionarNoTopo(&(mesa->tableau[i]), carta);
        }
    }

    Exibir(&mesa->baralho, true);

    /*
    // Distribui as cartas do baralho para o tableau, como descrito na introdu��o
    for (int coluna = 0; coluna < 7; coluna++) {
        for (int carta = 0; carta <= coluna; carta++) {
            Carta cartaDistribuida;
            RetirarDoTopo(&(mesa->baralho), &cartaDistribuida);
            AdicionarNoTopo(&(mesa->tableau[coluna]), cartaDistribuida);
        }
        // Vira a �ltima carta de cada coluna para cima
        if (mesa->tableau[coluna].tamanho > 0) {
            No* ultimaCarta = mesa->tableau[coluna].topo;
            for (int i = 0; i < mesa->tableau[coluna].tamanho - 1; i++) {
                ultimaCarta = ultimaCarta->proximo;
            }
            alterarPosicao(&(ultimaCarta->carta), 1); // Virar para cima
        }
    }
    */
}

/*
int VerificarVitoria(Mesa* mesa) {
    // Verificar se todas as bases t�m 13 cartas (uma de cada naipe)
    for (int naipe = 0; naipe < NUM_NAIPE; naipe++) {
        if (mesa->bases.tamanho != NUM_CARTAS_POR_NAIPE) {
            return 0; // Ainda n�o venceu
        }
    }

    // Verificar se todas as colunas do tableau est�o vazias
    for (int coluna = 0; coluna < NUM_COLUNAS_TABLEAU; coluna++) {
        if (!EstaVazia(&(mesa->tableau[coluna]))) {
            return 0; // Ainda n�o venceu
        }
    }

    // Se todas as bases t�m 13 cartas e todas as colunas do tableau est�o vazias, ent�o venceu
    return 1;
}


void ExibirMesa(Mesa* mesa) {
    // Exibir as bases
    printf("Bases:\n");
    for (int naipe = 0; naipe < NUM_NAIPE; naipe++) {
        printf("[%c] ", NomeNaipe(naipe));
        ExibirListaDeCartas(&(mesa->bases), 1); // Exibir todas as cartas
        printf("\n");
    }

    // Exibir o tableau
    printf("Tableau:\n");
    for (int coluna = 0; coluna < NUM_COLUNAS_TABLEAU; coluna++) {
        printf("Coluna %d: ", coluna + 1);
        ExibirListaDeCartas(&(mesa->tableau[coluna]), 1); // Exibir todas as cartas
        printf("\n");
    }

    // Exibir o descarte
    printf("Descarte: ");
    ExibirListaDeCartas(&(mesa->descarte), 1); // Exibir todas as cartas
    printf("\n");

    // Exibir a pontua��o
    printf("Pontua��o: %d\n", mesa->pontuacao);
}


void ComprarCarta(Mesa* mesa) {
    // Verificar se ainda h� cartas no baralho
    if (EstaVazia(&(mesa->baralho))) {
        printf("N�o h� mais cartas no baralho para comprar.\n");
        return;
    }

    // Retirar a carta do topo do baralho
    Carta cartaComprada;
    RetirarDoTopo(&(mesa->baralho), &cartaComprada);

    // Adicionar a carta ao descarte
    AdicionarNoTopo(&(mesa->descarte), cartaComprada);

    // Exibir a carta comprada
    printf("Voc� comprou a seguinte carta:\n");
    ExibirCarta(cartaComprada);
}


void MoverDescarteParaBases(Mesa* mesa) {
    // Verifique se o descarte n�o est� vazio
    if (!EstaVazia(&mesa->descarte)) {
        // Declare uma vari�vel do tipo Carta para armazenar a carta retirada
        Carta carta;

        // Retire a carta do topo do descarte
        RetirarDoTopo(&mesa->descarte, &carta);

        // Adicione a carta �s bases
        AdicionarNoTopo(&mesa->bases, carta);
    } else {
        // Trate o caso em que o descarte est� vazio
        printf("O descarte est� vazio. N�o � poss�vel mover cartas para as bases.\n");
        // Voc� pode adicionar um tratamento personalizado aqui, se necess�rio.
    }
}


void MoverDescarteParaTableau(Mesa* mesa, int indiceTableau) {
    // Verificar se o descarte est� vazio
    if (EstaVazia(&(mesa->descarte))) {
        printf("O descarte est� vazio. N�o h� cartas para mover para o tableau.\n");
        return;
    }

    // Verificar se o �ndice do tableau � v�lido
    if (indiceTableau < 0 || indiceTableau >= 7) {
        printf("O �ndice do tableau � inv�lido.\n");
        return;
    }

    // Obter a carta do topo do descarte
    Carta cartaDescarte;
    RetirarDoTopo(&(mesa->descarte), &cartaDescarte);

    // Verificar se a carta pode ser movida para o tableau
    if (mesa->tableau[indiceTableau].tamanho == 0 ||
        verificarSequenciaAlternada(cartaDescarte, mesa->tableau[indiceTableau].cartas[mesa->tableau[indiceTableau].tamanho - 1])) {
        // A carta pode ser movida para o tableau
        AdicionarNoTopo(&(mesa->tableau[indiceTableau].cartas), cartaDescarte);
        printf("A carta foi movida para o tableau %d.\n", indiceTableau + 1);
    } else {
        // Se a carta n�o puder ser movida para o tableau, retorna ao descarte
        AdicionarNoTopo(&(mesa->descarte), cartaDescarte);
        printf("A carta n�o pode ser movida para o tableau %d.\n", indiceTableau + 1);
    }
}


void MoverTableauParaBases(Mesa* mesa, int indiceTableau) {
    // Verificar se o �ndice do tableau � v�lido
    if (indiceTableau < 0 || indiceTableau >= 7) {
        printf("O �ndice do tableau � inv�lido.\n");
        return;
    }

    // Verificar se o tableau est� vazio
    if (Tamanho(&(mesa->tableau[indiceTableau].cartas)) == 0) {
        printf("O tableau %d est� vazio. N�o h� cartas para mover para as bases.\n", indiceTableau + 1);
        return;
    }

    // Obter a carta do topo do tableau
    Carta cartaTableau;
    RetirarDoTopo(&(mesa->tableau[indiceTableau].cartas), &cartaTableau);

    // Verificar se a carta pode ser movida para as bases do mesmo naipe
    int naipeCarta = retornarNaipe(cartaTableau);

    if (naipeCarta >= 0 && naipeCarta <= 3) {
        if (Tamanho(&(mesa->bases.cartas)) == 0) {
            if (retornarValor(cartaTableau) == 0) {
                // A carta AS do naipe pode ser movida para a base
                AdicionarNoTopo(&(mesa->bases.cartas), cartaTableau);
                printf("A carta foi movida para a base %c.\n", naipeCarta == 0 ? 'C' : (naipeCarta == 1 ? 'E' : (naipeCarta == 2 ? 'O' : 'P')));
                return;
            }
        } else {
            Carta cartaBase;
            if (CartaNoTopo(&(mesa->bases.cartas), &cartaBase)) {
                // Verificar se a carta do tableau pode ser adicionada ao topo das bases
                if (retornarNaipe(cartaBase) == naipeCarta && retornarValor(cartaBase) == retornarValor(cartaTableau) - 1) {
                    AdicionarNoTopo(&(mesa->bases.cartas), cartaTableau);
                    printf("A carta foi movida para a base %c.\n", naipeCarta == 0 ? 'C' : (naipeCarta == 1 ? 'E' : (naipeCarta == 2 ? 'O' : 'P')));
                    return;
                } else {
                    // A carta n�o pode ser adicionada �s bases
                    printf("A carta n�o pode ser movida para as bases.\n");
                    // Devolver a carta para o tableau
                    AdicionarNoTopo(&(mesa->tableau[indiceTableau].cartas), cartaTableau);
                }
            }
        }
    }

    // Se a carta n�o puder ser movida para as bases, devolv�-la ao tableau
    AdicionarNoTopo(&(mesa->tableau[indiceTableau].cartas), cartaTableau);
}



void MoverBasesParaTableau(Mesa* mesa, int indiceBase, int indiceTableau) {
    // Verificar se os �ndices da base e do tableau s�o v�lidos
    if (indiceBase < 0 || indiceBase >= 4 || indiceTableau < 0 || indiceTableau >= 7) {
        printf("Os �ndices da base e do tableau s�o inv�lidos.\n");
        return;
    }

    // Verificar se a base selecionada n�o est� vazia
    if (Tamanho(&(mesa->bases.cartas)) == 0) {
        printf("A base %c est� vazia. N�o h� cartas para mover para o tableau.\n", indiceBase == 0 ? 'C' : (indiceBase == 1 ? 'E' : (indiceBase == 2 ? 'O' : 'P')));
        return;
    }

    // Obter a carta do topo da base
    Carta cartaBase;
    RetirarDoTopo(&(mesa->bases.cartas), &cartaBase);

    // Verificar se o tableau est� vazio ou se a carta pode ser movida para o tableau
 if (Tamanho(&(mesa->tableau[indiceTableau].cartas)) == 0 || verificarSequenciaAlternada(cartaBase, &(mesa->tableau[indiceTableau].cartas.topo->carta))) {
        printf("A carta foi movida para o tableau %d.\n", indiceTableau + 1);
    } else {
        // Se a carta n�o puder ser movida para o tableau, retorna � base
        AdicionarNoTopo(&(mesa->bases.cartas), cartaBase);
        printf("A carta n�o pode ser movida para o tableau.\n");
    }
}


void MoverEntreColunasTableau(Mesa* mesa, int qtdCartas, int indiceOrigem, int indiceDestino) {
    // Verificar se os �ndices de origem e destino s�o v�lidos
    if (indiceOrigem < 0 || indiceOrigem >= 7 || indiceDestino < 0 || indiceDestino >= 7) {
        printf("�ndice de origem ou destino inv�lido.\n");
        return;
    }

    // Verificar se a coluna de origem possui pelo menos 'qtdCartas' cartas
    if (Tamanho(&(mesa->tableau[indiceOrigem].cartas)) < qtdCartas) {
        printf("A coluna de origem n�o possui cartas suficientes para mover.\n");
        return;
    }

    // Obter a lista de cartas da coluna de origem
    ListaDeCartas* origem = &(mesa->tableau[indiceOrigem].cartas);

    // Verificar se a coluna de destino est� vazia
    if (Tamanho(&(mesa->tableau[indiceDestino].cartas)) == 0) {
        // Movimentar as 'qtdCartas' cartas da coluna de origem para a coluna de destino
        for (int i = 0; i < qtdCartas; i++) {
            Carta cartaMovida;
            RetirarDoTopo(origem, &cartaMovida);
            AdicionarNoTopo(&(mesa->tableau[indiceDestino].cartas), cartaMovida);
        }
        printf("%d carta(s) movida(s) da coluna %d para a coluna %d.\n", qtdCartas, indiceOrigem + 1, indiceDestino + 1);
    } else {
        // Verificar se a carta do topo da coluna de origem pode ser movida para a coluna de destino
        Carta cartaOrigemTopo;
        Carta cartaDestinoTopo;
        CartaNoTopo(origem, &cartaOrigemTopo);
        CartaNoTopo(&(mesa->tableau[indiceDestino].cartas), &cartaDestinoTopo);

        if (verificarSequenciaAlternada(cartaOrigemTopo, cartaDestinoTopo) && qtdCartas == 1) {
            // Movimentar a carta da coluna de origem para a coluna de destino
            RetirarDoTopo(origem, &cartaOrigemTopo);
            AdicionarNoTopo(&(mesa->tableau[indiceDestino].cartas), cartaOrigemTopo);
            printf("Uma carta movida da coluna %d para a coluna %d.\n", indiceOrigem + 1, indiceDestino + 1);
        } else {
            printf("Movimento inv�lido. Verifique as regras do jogo.\n");
        }
    }
}
*/
