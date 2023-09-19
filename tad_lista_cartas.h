#ifndef TAD_LISTA_DE_CARTAS_H
#define TAD_LISTA_DE_CARTAS_H

#include "tad_cartas.h"


typedef struct{
    Carta carta;
    struct NoCarta *prox;
}NoCarta;

typedef struct{
    NoCarta *topo;
}ListaDeCartas;

ListaDeCartas criarListaDeCartas();
int vazia(ListaDeCartas lista);
int tamanho(ListaDeCartas lista);
void adicionarCartaAoTopo(ListaDeCartas *lista, Carta carta);
void retirarCartaDoTopo(ListaDeCartas *lista);
void embaralhar(ListaDeCartas *lista);
void exibir(ListaDeCartas lista);


#endif // TAD_LISTA_DE_CARTAS_H
