#ifndef TAD_LISTA_DE_CARTAS_H_INCLUDED
#define TAD_LISTA_DE_CARTAS_H_INCLUDED

#include "tad_cartas.h"
#include <stdbool.h>

typedef struct No {
    Carta carta;
    struct No* proximo;
} No;

typedef struct {
    No* topo;
    int tamanho;
} ListaDeCartas;

void Inicializar(ListaDeCartas* lista);
int Tamanho(ListaDeCartas* lista);
bool EstaVazia(ListaDeCartas* lista);
void CartaNoTopo(ListaDeCartas* lista, Carta* carta);
int CartaNoTopoExtra(ListaDeCartas* lista, Carta* carta);
void CartaNaPosicao(ListaDeCartas* lista, int posicao, Carta* carta);
void AdicionarNoTopo(ListaDeCartas* lista, Carta carta);
void RetirarDoTopo(ListaDeCartas* lista, Carta* carta);
void TransferirCartas(ListaDeCartas* listaOrigem, ListaDeCartas* listaDestino, int quantidade);
void Embaralhar(ListaDeCartas* lista);
void Exibir(ListaDeCartas* lista, bool todasAsCartas);

#endif // TAD_LISTA_DE_CARTAS_H_INCLUDED
