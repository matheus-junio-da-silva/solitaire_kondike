#ifndef TAD_MESA_H
#define TAD_MESA_H

#include "tad_cartas.h"
#include "tad_lista_cartas.h"

typedef struct Mesa{
    ListaDeCartas baralho;
    ListaDeCartas descarte;
    ListaDeCartas bases[4];
    ListaDeCartas tableau[7];
    int pontuacao;
} Mesa;

void InicializarMesa(Mesa* mesa);
void CarregarBaralhoAleatorio(Mesa* mesa);
void CarregarBaralho(Mesa* mesa, Carta* cartas, int numCartas);
void PrepararMesa(Mesa* mesa);
int VerificarVitoria(Mesa* mesa);
void ExibirMesa(Mesa* mesa);
void ComprarCarta(Mesa* mesa);
int DeterminarBaseCorreta(Mesa* mesa, Carta carta);
void MoverDescarteParaBases(Mesa* mesa);
void MoverDescarteParaTableau(Mesa* mesa, int indiceTableau);
void MoverTableauParaBases(Mesa* mesa, int indiceTableau);
void MoverBasesParaTableau(Mesa* mesa, int indiceBase, int indiceTableau);
void MoverEntreColunasTableau(Mesa* mesa, int qtdCartas, int indiceOrigem, int indiceDestino);
void LimparBaralho(Mesa *mesa);
void diminuirPontuacao(Mesa *mesa, int valor);
void aumentarPontuacao(Mesa *mesa, int valor);

#endif // TAD_MESA_H_INCLUDED
