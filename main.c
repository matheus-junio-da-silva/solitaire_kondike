#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"

int main() {
    Carta minhaCarta = criarCarta(2, 2, 0); // verso = 1 é virado para cima
    Carta minhaCarta2 = criarCarta(2, 1, 1); // verso = 1 é virado para cima

    printf("Naipe: %d\n", retornarNaipe(minhaCarta));
    printf("Valor: %d\n", retornarValor(minhaCarta));
    printf("Posicao: %d\n", retornarPosicao(minhaCarta));

    alterarPosicao(&minhaCarta, 0);
    printf("Nova Posicao: %d\n", retornarPosicao(minhaCarta)); // Deve imprimir 0 (virada para baixo)

    printf("se retorno = 1, entao sequencia de naipe é igual. -> %d\n", verificarSequenciaMesmoNaipe(minhaCarta, minhaCarta2));

    printf("se retorno = 1, entao sequencia é alternada. -> %d\n", verificarSequenciaAlternada(minhaCarta, minhaCarta2));

    alterarPosicao(&minhaCarta, 1);

    exibir_carta(minhaCarta);
    return 0;
}

