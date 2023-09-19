
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef TAD_MESA_DE_CARTAS_H
#define TAD_MESA_DE_CARTAS_H

// Definindo a estrutura da carta
typedef struct {
    int valor;
    char naipe;
} Carta;

// Definindo a estrutura da lista de cartas
typedef struct {
    Carta cartas[52];
    int topo;
} ListaCartas;

// Definindo a estrutura da mesa
typedef struct {
    ListaCartas baralho;
    ListaCartas descarte;
    ListaCartas bases[4];
    ListaCartas tableau[7];
    int pontuacao;
} Mesa;

// Funções do TAD Mesa
void inicializar(Mesa *mesa);
void carregarBaralhoAleatorio(Mesa *mesa);
void carregarBaralho(Mesa *mesa, Carta cartas[], int numCartas);
void preparar(Mesa *mesa);
int verificarVitoria(Mesa *mesa);
void exibir(Mesa *mesa);
void comprarCarta(Mesa *mesa);
void moverDescarteParaBases(Mesa *mesa, int indiceBase);
void moverDescarteParaTableau(Mesa *mesa, int indiceTableau);
void moverTableauParaBases(Mesa *mesa, int indiceTableau, int indiceBase);
void moverBasesParaTableau(Mesa *mesa, int indiceBase, int indiceTableau);
void moverEntreColunasDoTableau(Mesa *mesa, int numCartas, int indiceOrigem, int indiceDestino);

#endif
