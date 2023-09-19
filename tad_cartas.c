#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"

int verifica_valor(int valor){
    if(valor<0 || valor>12)
    {
        printf("o valor da carta deve ser um inteiro de 0 a 12");
        exit(1);
    };
    return valor;
}

int verifica_naipe(int naipe) {
    if(naipe< 0 || naipe>3)
    {
        printf("o naipe da carta deve ser um inteiro de 0 a 3");
        exit(1);
    };
    return naipe;
}

int verifica_verso(int verso){
    if(verso< 0 || verso>1)
    {
        printf("o verso da carta deve ser um inteiro 0 ou 1");
        exit(1);
    };
    return verso;
}


Carta criarCarta(int valor, int naipe ,int virada_para_cima) {
    verifica_valor(valor);
    verifica_naipe(naipe);
    verifica_verso(virada_para_cima);
    Carta carta;
    carta.naipe = naipe;
    carta.valor = valor;
    carta.virada_para_cima = virada_para_cima;
    return carta;
}

// Funcao para retornar o naipe de uma carta, retorna em inteiro o naipe, de 0 a 3, sendo o 0 o AS...
int retornarNaipe(Carta carta) {
    return carta.naipe;
}

int retornarValor(Carta carta) {
    return carta.valor;
}

// (0 para baixo, 1 para cima)
int retornarPosicao(Carta carta) {
    return carta.virada_para_cima;
}

void alterarPosicao(Carta *carta, int virada_para_cima) {
    carta->virada_para_cima = virada_para_cima;
}

// para base, pois as sequencias da base devem ter o mesmo naipe
int verificarSequenciaMesmoNaipe(Carta carta1, Carta carta2) {
    if (carta1.naipe == carta2.naipe) return 1;
    return 0;
}

// atencao!!!! copas = 0, espadas = 1, ouros = 2, paus = 3
// ex: ao verificar copas e ouros vai ser falso
// ex: ao verificar espadas e copas vai ser verdadeiro
// para o tableau!!
// ex: se o valor da primeira carta for 4 e a segunda for 5 vai ser verdadeiro
int verificarSequenciaAlternada(Carta carta1, Carta carta2) {
    if(((carta1.naipe % 2) != (carta2.naipe % 2)) && ((carta1.valor + 1) == carta2.valor)) return 1;
    return 0;
}

void exibir_carta(Carta carta) {
    char naipes[] = {'C', 'E', 'O', 'P'};
    int valor_carta = carta.valor;
    if (carta.virada_para_cima) {
        printf("[%d,%c]\n", ++valor_carta, naipes[carta.naipe]);
    } else {
        printf("[]");
    }
}
