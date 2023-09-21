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

    /*
    for (int i = 0; i < 7; i++) {
        Exibir(&mesa->tableau[i], true);
    }
    */

    Embaralhar(&(mesa->baralho));
    Exibir(&mesa->baralho, true);
}
/*
Carregar baralho: insere cartas no baralho de acordo com as cartas passadas num
parâmetro de entrada, preservando a ordem passada.

void CarregarBaralho(Mesa* mesa, Carta* cartas, int numCartas) {
    // Certifique-se de que o número de cartas a serem carregadas seja válido
    if (numCartas < 0 || numCartas > MAX_CARTAS_MESA) {
        printf("Número de cartas inválido.\n");
        exit(1);
    }

    // Limpa o baralho existente antes de carregar as novas cartas
    LimparBaralho(mesa);

    // Adiciona as cartas ao baralho da mesa
    for (int i = 0; i < numCartas; i++) {
        if (mesa->baralho.tamanho < MAX_CARTAS_MESA) {
            AdicionarNoTopo(&(mesa->baralho), cartas[i]);
        } else {
            printf("Baralho da mesa está cheio. Não é possível adicionar mais cartas.\n");
            break;
        }
    }
}
*/

void PrepararMesa(Mesa* mesa) {
    // Carrega o baralho aleatório
    CarregarBaralhoAleatorio(mesa);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            Carta carta; // inicializa uma carta para rebeber uma carta que estava no topo
            RetirarDoTopo(&(mesa->baralho), &carta);
            if (j == i) {
                // A última carta em cada coluna fica virada para cima, obs: ultimo de cada loop do j
                alterarPosicao(&carta, 1);
            }
            AdicionarNoTopo(&(mesa->tableau[i]), carta);
        }
    }

    for (int i = 0; i < 7; i++) {
        Exibir(&mesa->tableau[i], true);
    }

}


int VerificarVitoria(Mesa* mesa) {
    // Verificar se todas as bases têm 13 cartas (uma de cada naipe)
    for (int naipe = 0; naipe < 4; naipe++) {
        if (mesa->bases[naipe].tamanho != 13) {
            printf("Ainda não venceu.\n");
            return 0; // Ainda não venceu
        }
    }

    // Verificar se todas as colunas do tableau estão vazias
    for (int coluna = 0; coluna < 7; coluna++) {
        if (!EstaVazia(&(mesa->tableau[coluna]))) {
            printf("Ainda não venceu.\n");
            return 0; // Ainda não venceu
        }
    }

    // Se todas as bases têm 13 cartas e todas as colunas do tableau estão vazias, então venceu
    printf("venceu.\n");
    return 1;
}


void ExibirMesa(Mesa* mesa) {
    // exibe a base
    printf("base:\n");
    for (int i = 0; i < 4; i++) {
        Exibir(&mesa->bases[i], true);
    }
    // exibe o tableau
    printf("Tableau:\n");
    for (int i = 0; i < 7; i++) {
        Exibir(&mesa->tableau[i], true);
    }
    // exibe o descarte
    printf("descarte:\n");
    Exibir(&mesa->descarte, true);

    // Exibir a pontuação
    printf("Pontuacao: %d\n", mesa->pontuacao);

}


void ComprarCarta(Mesa* mesa) {
    // Verificar se ainda há cartas no baralho
    if (EstaVazia(&(mesa->baralho))) {
        printf("Não há mais cartas no baralho para comprar.\n");
        // fazer um while para todas as cartas do descarte
        while (mesa->descarte.tamanho > 0){
            // fazer uma funcao que pega do descarte para o baralho e embaralha
            // inicializa uma carta para receber do descarte
            Carta cartaTopoDescarte;
            //retira do topo descarte e coloca em cartaTopoDescarte
            RetirarDoTopo(&(mesa->descarte), &cartaTopoDescarte);
            // vira a carta para baixo
            alterarPosicao(&cartaTopoDescarte, 0);
            // Adicionar a carta ao baralho
            AdicionarNoTopo(&(mesa->baralho), cartaTopoDescarte);
        }
        Embaralhar(&(mesa->baralho));
    }

    // inicializa uma carta
    Carta cartaComprada;
    //retira do topo e coloca em cartaComprada
    // a funcao AdicionarNoTopo ja decrementa 1 no tamanho
    RetirarDoTopo(&(mesa->baralho), &cartaComprada);
    // vira a carta para cima
    alterarPosicao(&cartaComprada, 1);
    // Adicionar a carta ao descarte
    // a funcao AdicionarNoTopo ja incrementa 1 no tamanho
    AdicionarNoTopo(&(mesa->descarte), cartaComprada);
    // Exibir a carta comprada
    printf("O tamanho do descarte é: %d\n", mesa->descarte.tamanho);
    printf("Você comprou a seguinte carta:\n");

    exibir_carta(cartaComprada);
}

int DeterminarBaseCorreta(Mesa* mesa, Carta carta) {
    // Percorra todas as bases
    for (int i = 0; i < 4; i++) {
        // Se a base estiver vazia e a carta for um Ás, esta é a base correta
        if (EstaVazia(&mesa->bases[i]) && carta.valor == 0) {
            return i;
        }

        // Se a base não estiver vazia, verifique se o naipe é o mesmo e o valor é um maior
        if (!EstaVazia(&mesa->bases[i]) && mesa->bases[i].topo->carta.naipe == carta.naipe && mesa->bases[i].topo->carta.valor == carta.valor - 1) {
            return i;
        }
    }

    // Se nenhuma base for adequada, retorne -1
    return -1;
}

void MoverDescarteParaBases(Mesa* mesa) {
    // Verifique se o descarte não está vazio
    if (!EstaVazia(&mesa->descarte)) {
        // Declare uma variável do tipo Carta para armazenar a carta retirada
        Carta carta;

        // Retire a carta do topo do descarte
        RetirarDoTopo(&mesa->descarte, &carta);

        // Determine a base correta para a carta
        //Carta deve ser &(mesa->descarte)
        int baseCorreta = DeterminarBaseCorreta(mesa, carta);

        // Adicione a carta à base correta
        if (baseCorreta>=0) {
            AdicionarNoTopo(&mesa->bases[baseCorreta], carta);
        }

    } else {
        // Trate o caso em que o descarte está vazio
        printf("O descarte está vazio. Nao e possivel mover cartas para as bases.\n");
    }
}

void MoverDescarteParaTableau(Mesa* mesa, int indiceTableau) {
    // Verificar se o descarte est  vazio
    if (EstaVazia(&(mesa->descarte))) {
        printf("O descarte est  vazio. N o h  cartas para mover para o tableau.\n");
        return;
    }

    // Verificar se o  ndice do tableau   valido
    if (indiceTableau < 0 || indiceTableau >= 7) {
        printf("O  ndice do tableau   inv lido.\n");
        return;
    }

    // Obter a carta do topo do descarte
    Carta cartaDescarte;
    RetirarDoTopo(&(mesa->descarte), &cartaDescarte);
    // Verificar se a carta pode ser movida para o tableau
    if (mesa->tableau[indiceTableau].tamanho == 0) {
        if (cartaDescarte.valor == 12) {
            AdicionarNoTopo(&(mesa->tableau[indiceTableau]), cartaDescarte);
            printf("A carta foi movida para o tableau %d.\n", indiceTableau + 1);
        }
        else {
            printf("A carta nao foi movida para o tableau porque nao é um rei %d.\n", indiceTableau + 1);
        }

    }
    // mesa->tableau[indiceTableau] é uma lista de carta
    // Verificar se a carta pode ser movida para o tableau
    No* noAtual = mesa->tableau[indiceTableau].topo;
    if (verificarSequenciaAlternada(cartaDescarte, noAtual->carta)) {
        // A carta pode ser movida para o tableau
        AdicionarNoTopo(&(mesa->tableau[indiceTableau]), cartaDescarte);
        printf("A carta foi movida para o tableau %d.\n", indiceTableau + 1);
    } else {
        // Se a carta n o puder ser movida para o tableau, retorna ao descarte
        AdicionarNoTopo(&(mesa->descarte), cartaDescarte);
        printf("A carta n o pode ser movida para o tableau %d.\n", indiceTableau + 1);
    }
}

void MoverTableauParaBases(Mesa* mesa, int indiceTableau) {
    // Verificar se o índice do tableau é válido
    if (indiceTableau < 0 || indiceTableau >= 7) {
        printf("O índice do tableau é inválido.\n");
        return;
    }

    // Verificar se o tableau está vazio
    if (Tamanho(&(mesa->tableau[indiceTableau])) == 0) {
        printf("O tableau %d está vazio. Não há cartas para mover para as bases.\n", indiceTableau + 1);
        return;
    }

    // Obter a carta do topo do tableau
    Carta cartaTableau;
    RetirarDoTopo(&(mesa->tableau[indiceTableau]), &cartaTableau);

    // Verificar se a carta pode ser movida para as bases do mesmo naipe
    int naipeCarta = retornarNaipe(cartaTableau);

    if (naipeCarta >= 0 && naipeCarta <= 3) {
        if (Tamanho(&(mesa->tableau[indiceTableau])) == 0) {
            if (retornarValor(cartaTableau) == 0) {
                // A carta AS do naipe pode ser movida para a base
                AdicionarNoTopo(&(mesa->bases[naipeCarta]), cartaTableau);
                printf("A carta foi movida para a base %c.\n", naipeCarta == 0 ? 'C' : (naipeCarta == 1 ? 'E' : (naipeCarta == 2 ? 'O' : 'P')));
                return;
            }
        } else {
            Carta cartaBase;
            if (CartaNoTopoExtra(&(mesa->bases[naipeCarta]), &cartaBase)) {
                // Verificar se a carta do tableau pode ser adicionada ao topo das bases
                if (retornarNaipe(cartaBase) == naipeCarta && retornarValor(cartaBase) == retornarValor(cartaTableau) - 1) {
                    AdicionarNoTopo(&(mesa->bases[naipeCarta]), cartaTableau);
                    printf("A carta foi movida para a base %c.\n", naipeCarta == 0 ? 'C' : (naipeCarta == 1 ? 'E' : (naipeCarta == 2 ? 'O' : 'P')));
                    return;
                } else {
                    // A carta não pode ser adicionada às bases
                    printf("A carta não pode ser movida para as bases.\n");
                    // Devolver a carta para o tableau
                    AdicionarNoTopo(&(mesa->tableau[indiceTableau]), cartaTableau);
                }
            }
        }
    }
}

/*
void MoverTableauParaBases(Mesa* mesa, int indiceTableau) {
    // Verificar se o índice do tableau é válido
    if (indiceTableau < 0 || indiceTableau >= 7) {
        printf("O índice do tableau é inválido.\n");
        return;
    }

    // Verificar se o tableau está vazio
    if (Tamanho(&(mesa->tableau[indiceTableau].cartas)) == 0) {
        printf("O tableau %d está vazio. Não há cartas para mover para as bases.\n", indiceTableau + 1);
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
                    // A carta não pode ser adicionada às bases
                    printf("A carta não pode ser movida para as bases.\n");
                    // Devolver a carta para o tableau
                    AdicionarNoTopo(&(mesa->tableau[indiceTableau].cartas), cartaTableau);
                }
            }
        }
    }

    // Se a carta não puder ser movida para as bases, devolvê-la ao tableau
    AdicionarNoTopo(&(mesa->tableau[indiceTableau].cartas), cartaTableau);
}



void MoverBasesParaTableau(Mesa* mesa, int indiceBase, int indiceTableau) {
    // Verificar se os índices da base e do tableau são válidos
    if (indiceBase < 0 || indiceBase >= 4 || indiceTableau < 0 || indiceTableau >= 7) {
        printf("Os índices da base e do tableau são inválidos.\n");
        return;
    }

    // Verificar se a base selecionada não está vazia
    if (Tamanho(&(mesa->bases.cartas)) == 0) {
        printf("A base %c está vazia. Não há cartas para mover para o tableau.\n", indiceBase == 0 ? 'C' : (indiceBase == 1 ? 'E' : (indiceBase == 2 ? 'O' : 'P')));
        return;
    }

    // Obter a carta do topo da base
    Carta cartaBase;
    RetirarDoTopo(&(mesa->bases.cartas), &cartaBase);

    // Verificar se o tableau está vazio ou se a carta pode ser movida para o tableau
 if (Tamanho(&(mesa->tableau[indiceTableau].cartas)) == 0 || verificarSequenciaAlternada(cartaBase, &(mesa->tableau[indiceTableau].cartas.topo->carta))) {
        printf("A carta foi movida para o tableau %d.\n", indiceTableau + 1);
    } else {
        // Se a carta não puder ser movida para o tableau, retorna à base
        AdicionarNoTopo(&(mesa->bases.cartas), cartaBase);
        printf("A carta não pode ser movida para o tableau.\n");
    }
}


void MoverEntreColunasTableau(Mesa* mesa, int qtdCartas, int indiceOrigem, int indiceDestino) {
    // Verificar se os índices de origem e destino são válidos
    if (indiceOrigem < 0 || indiceOrigem >= 7 || indiceDestino < 0 || indiceDestino >= 7) {
        printf("Índice de origem ou destino inválido.\n");
        return;
    }

    // Verificar se a coluna de origem possui pelo menos 'qtdCartas' cartas
    if (Tamanho(&(mesa->tableau[indiceOrigem].cartas)) < qtdCartas) {
        printf("A coluna de origem não possui cartas suficientes para mover.\n");
        return;
    }

    // Obter a lista de cartas da coluna de origem
    ListaDeCartas* origem = &(mesa->tableau[indiceOrigem].cartas);

    // Verificar se a coluna de destino está vazia
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
            printf("Movimento inválido. Verifique as regras do jogo.\n");
        }
    }
}
*/
