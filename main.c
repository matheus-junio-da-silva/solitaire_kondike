#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"
#include "ler_arquivo.h"

int main() {

    printf("Bem-vindo ao jogo de Paciencia!\n");

    int modo;
    printf("Escolha o modo de utilizacao (1 - Interativo, 2 - Arquivo): ");
    scanf("%d", &modo);

    if (modo == 1) {
        ModoInterativo();
    } else if (modo == 2) {
        char arquivo[100];
        printf("Informe o caminho do arquivo: ");
        scanf("%s", arquivo);
        Mesa mesa;
        InicializarMesa(&mesa);
        CarregarBaralho(&mesa);
        LerJogoDeArquivo(&mesa, arquivo);
    } else {
        printf("Modo invalido. Encerrando o jogo.\n");
    }

    return 0;
}

