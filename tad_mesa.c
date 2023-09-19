#include "tad_mesa.h"


void inicializar(Mesa *mesa) {
    // Inicializa o baralho
    mesa->baralho.topo = 0;
    // Inicializa o descarte
    mesa->descarte.topo = 0;
    // Inicializa as bases
    for (int i = 0; i < 4; i++) {
        mesa->bases[i].topo = 0;
    }
    // Inicializa o tableau
    for (int i = 0; i < 7; i++) {
        mesa->tableau[i].topo = 0;
    }
    // Zera a pontuação
    mesa->pontuacao = 0;
}

void carregarBaralho(Mesa *mesa, Carta cartas[], int numCartas) {
    // Verifica se o número de cartas é válido
    if (numCartas != 52) {
        printf("Erro: o número de cartas deve ser 52.\n");
        return;
    }
    // Insere as cartas no baralho
    for (int i = 0; i < numCartas; i++) {
        mesa->baralho.cartas[i] = cartas[i];
    }
    mesa->baralho.topo = numCartas;
    // Embaralha o baralho
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios
    for (int i = 0; i < numCartas; i++) {
        int j = rand() % numCartas;  // Gera um índice aleatório
        Carta temp = mesa->baralho.cartas[i];  // Troca as cartas nos índices i e j
        mesa->baralho.cartas[i] = mesa->baralho.cartas[j];
        mesa->baralho.cartas[j] = temp;
    }
     // Insere as cartas passadas como parâmetro no baralho, preservando a ordem passada
    for (int i = 0; i < numCartas; i++) {
        mesa->baralho.cartas[i] = cartas[i];
    }
}


/*
int main() {
    // Testando o TAD Mesa
    Mesa mesa;
    inicializar(&mesa);
    // ...
    return 0;
}
*/
