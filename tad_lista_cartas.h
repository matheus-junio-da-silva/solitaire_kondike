#ifndef TAD_LISTA_DE_CARTAS_H
#define TAD_LISTA_DE_CARTAS_H

#include "tad_cartas.h"


typedef struct NoCarta NoCarta;
typedef struct ListaDeCartas ListaDeCartas;

ListaDeCartas criarListaDeCartas();
int vazia(ListaDeCartas lista);
int tamanho(ListaDeCartas lista);
void adicionarCartaAoTopo(ListaDeCartas *lista, Carta carta);
Carta retirarCartaDoTopo(ListaDeCartas *lista);
void embaralhar(ListaDeCartas *lista);
void exibir(ListaDeCartas lista);


#endif // TAD_LISTA_DE_CARTAS_H

