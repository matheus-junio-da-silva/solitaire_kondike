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
    No* novoTopo = (No*)malloc(sizeof(No));
    if (novoTopo == NULL) {
        printf("Erro na alocação de memoria");
        exit(1);
    }

    // o seguinte codigo é como se fosse uma escada
    // assim que se cria um novo topo a carta que estava no ultimo degrau
    // cai para o penultimo e o novo topo entra no lugar dela
    // e esse novo topo mantem o endereço de memoria do penultimo topo no "proximo"
    novoTopo->carta = carta;
    // no caso proximo é o topo que esta abaixo do topo de cima
    novoTopo->proximo = lista->topo;
    // topo é um No, e No é uma lista encadeada que contem carta e proximo
    lista->topo = novoTopo;
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
        // vai ser null assim que chegar na ultima carta (a mais distante do topo)
        while (atual != NULL) {
            if (todasAsCartas || i == 0) {
                // deve utilizar a funcao que printa a carta do tad_cartas
                exibir_carta(atual->carta);
            } else {
                printf("?? "); // Para cartas não visíveis
            }
            //topo 2
            //  topo proximo(1)
            //      topo proximo(0)
            // no caso proximo é o topo que esta abaixo do topo de cima
            atual = atual->proximo;
            i++;
        }
        printf("\n");
    }
}
