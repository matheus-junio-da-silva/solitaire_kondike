#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"
#include "ler_arquivo.h"
#include "interativo.h"
int main() {

    printf("Bem-vindo ao jogo de Paciencia!\n");

    int modo;
    printf("Escolha o modo de utilizacao (1 - Interativo, 2 - Arquivo): ");
    scanf("%d", &modo);

    if (modo == 1) {
        ModoInterativo();
    } else if (modo == 2) {
        //FILE *arquivo;
        //char nome_do_arquivo[100] = "teste.txt";
        //arquivo = fopen(nome_do_arquivo, "r");
        /*
        if (arquivo == NULL) {
            printf("Não foi possível abrir o arquivo %s\n", nome_do_arquivo);
            return 1;
        }
        */
        Mesa mesa;
        InicializarMesa(&mesa);
        LerJogoDeArquivo(&mesa);

    } else {
        printf("Modo invalido. Encerrando o jogo.\n");
    }

    return 0;
}

