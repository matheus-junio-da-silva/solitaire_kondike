#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"
#include "Tad_Lista_de_Cartas.h"

// Fun��o para criar uma lista de cartas vazia
ListaDeCartas criarListaDeCartas() {
    ListaDeCartas lista;
    lista.topo = NULL;
    return lista;
}

// Fun��o para verificar se a lista de cartas est� vazia
int vazia(ListaDeCartas lista) {
    return lista.topo == NULL;
}

// Fun��o para retornar o tamanho da lista de cartas
int tamanho(ListaDeCartas lista) {
    int count = 0;
    NoCarta *atual = lista.topo;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

// Fun��o para adicionar uma carta ao topo da lista de cartas
void adicionarCartaAoTopo(ListaDeCartas *lista, Carta carta) {
    NoCarta *novoNo = (NoCarta *)malloc(sizeof(NoCarta));
    if (novoNo == NULL) {
        printf("Erro: Falha na aloca��o de mem�ria.\n");
        exit(1);
    }
    novoNo->carta = carta;
    novoNo->prox = lista->topo;
    lista->topo = novoNo;
}

// Fun��o para retirar a carta do topo da lista de cartas
Carta retirarCartaDoTopo(ListaDeCartas *lista) {
    if (vazia(*lista)) {
        printf("Erro: A lista de cartas est� vazia.\n");
        exit(1);
    }
    NoCarta *temp = lista->topo;
    Carta carta = temp->carta;
    lista->topo = temp->prox;
    free(temp);
    return carta;
}

// Fun��o para embaralhar a lista de cartas (implementa��o simples)
void embaralhar(ListaDeCartas *lista) {
    int tam = tamanho(*lista);
    if (tam <= 1) {
        return;
    }

    NoCarta *head = lista->topo;
    for (int i = tam - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Troca os elementos nas posições i e j
        Carta temp = head->carta;
        NoCarta *current_i = head;
        NoCarta *current_j = head;

        for (int k = 0; k < i; k++) {
            current_i = current_i->prox;
        }
        for (int k = 0; k < j; k++) {
            current_j = current_j->prox;
        }

        current_i->carta = current_j->carta;
        current_j->carta = temp;

        head = lista->topo;
    }
}

// ...


// Fun��o para exibir todas as cartas da lista
void exibir(ListaDeCartas lista) {
    NoCarta *atual = lista.topo;
    while (atual != NULL) {
        printf("%c%c%s\n", atual->carta.valor, atual->carta.naipe,
               atual->carta.virada_para_cima ? " (Virada para cima)" : " (Virada para baixo)");
        atual = atual->prox;
    }
}
