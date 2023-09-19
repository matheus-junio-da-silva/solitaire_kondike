#ifndef TAD_CARTAS_PONTO_H
#define TAD_CARTAS_PONTO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int naipe;
    int valor;
    int virada_para_cima;
    struct Carta* proxima;
} Carta;

Carta criarCarta(int valor, int naipe , int virada_para_cima);

int retornarNaipe(Carta carta);
int retornarValor(Carta carta);
int retornarPosicao(Carta carta);

void alterarPosicao(Carta *carta, int virada_para_cima);

int verificarSequenciaMesmoNaipe(Carta carta1, Carta carta2);
int verificarSequenciaAlternada(Carta carta1, Carta carta2);

int verifica_valor(int valor);
int verifica_naipe(int naipe);
int verifica_verso(int verso);

void exibir_carta(Carta carta);
#endif // TAD_CARTAS_H
