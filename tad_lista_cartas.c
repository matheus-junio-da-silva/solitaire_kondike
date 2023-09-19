#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"


// Inicializar a lista
void Inicializar(ListaDeCartas* lista) {
    lista->topo = NULL;
    lista->tamanho = 0;
}

// Retornar tamanho
int Tamanho(ListaDeCartas* lista) {
    return lista->tamanho;
}

// Verificar se está vazia
bool EstaVazia(ListaDeCartas* lista) {
    return lista->tamanho == 0;
}


// Retornar a carta que está no topo
void CartaNoTopo(ListaDeCartas* lista, Carta* carta) {
    if (!EstaVazia(lista)) {
        *carta = lista->topo->carta;
    } else {
       printf("Lista vazia");
    }
}


// Retornar a carta que está numa dada posição
void CartaNaPosicao(ListaDeCartas* lista, int posicao, Carta* carta) {
    if (posicao >= 0 && posicao < lista->tamanho) {
        No* atual = lista->topo;
        for (int i = 0; i < posicao; i++) {
            atual = atual->proximo;
        }
        *carta = atual->carta;
    } else {
        printf("Posicao Invalida");
    }
}


// Adicionar carta ao topo
void AdicionarNoTopo(ListaDeCartas* lista, Carta carta) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro na alocação de memoria");
        exit(1);
    }
    novoNo->carta = carta;
    novoNo->proximo = lista->topo;
    lista->topo = novoNo;
    lista->tamanho++;
}

// Retirar carta do topo
void RetirarDoTopo(ListaDeCartas* lista, Carta* carta) {
    if (!EstaVazia(lista)) {
        No* noRemovido = lista->topo;
        *carta = noRemovido->carta;
        lista->topo = lista->topo->proximo;
        free(noRemovido);
        lista->tamanho--;
    } else {
        printf("Lista Vazia\n");
        // Aqui você pode tratar o caso em que a lista está vazia
    }
}



// Transferir cartas
void TransferirCartas(ListaDeCartas* listaOrigem, ListaDeCartas* listaDestino, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        if (!EstaVazia(listaOrigem)) {
            Carta cartaTransferida;
            RetirarDoTopo(listaOrigem, &cartaTransferida);
            AdicionarNoTopo(listaDestino, cartaTransferida);
        } else {
            printf("A lista de origem está vazia.\n");
            // Aqui você pode tratar o caso em que a lista de origem está vazia
            // Por exemplo, encerrando o loop ou exibindo uma mensagem de erro
            break;
        }
    }
}

// Embaralha a lista de cartas usando o algoritmo de Fisher-Yates
void Embaralhar(ListaDeCartas* lista) {
    // Obtém o tempo atual para inicializar a semente do gerador de números aleatórios
    srand(time(NULL));

    int tamanho = lista->tamanho;
    if (tamanho <= 1) {
        // Não é necessário embaralhar listas com 0 ou 1 carta
        return;
    }

    No* atual = lista->topo;

    // Percorre a lista e troca cada carta com uma carta aleatória subsequente
    for (int i = 0; i < tamanho - 1; i++) {
        int j = i + rand() % (tamanho - i); // Gera um índice aleatório a partir de i até o fim
        Carta temp = atual->carta;

        // Move o ponteiro 'atual' para a carta no índice j
        No* n = lista->topo;
        for (int k = 0; k < j; k++) {
            n = n->proximo;
        }

        atual->carta = n->carta;
        n->carta = temp;

        atual = atual->proximo;
    }
}
// Exibir
void Exibir(ListaDeCartas* lista, bool todasAsCartas) {
    if (EstaVazia(lista)) {
        printf("A lista de cartas está vazia.\n");
    } else {
        No* atual = lista->topo;
        printf("Lista de Cartas:\n");
        int i = 0;
        while (atual != NULL) {
            if (todasAsCartas || i == 0) {
                printf("%d%c ", atual->carta.valor, atual->carta.naipe);
            } else {
                printf("?? "); // Para cartas não visíveis
            }
            atual = atual->proximo;
            i++;
        }
        printf("\n");
    }
}
