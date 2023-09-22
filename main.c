#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"

int main() {
    // Inicialize a lista de cartas
    ListaDeCartas lista;
    Inicializar(&lista);

    // Crie algumas cartas
    Carta carta1 = criarCarta(1, 0, 1); // 2 de Copas
    Carta carta2 = criarCarta(2, 0, 1); // 3 de Copas
    Carta carta3 = criarCarta(3, 0, 1); // 4 de Copas

    // Adicione as cartas à lista
    AdicionarNoTopo(&lista, carta1);
    AdicionarNoTopo(&lista, carta2);
    AdicionarNoTopo(&lista, carta3);

    // Exiba a lista de cartas
    Exibir(&lista, true);

    // Embaralhe as cartas
    Embaralhar(&lista);

    // Exiba a lista de cartas embaralhada
    Exibir(&lista, true);

    // Retire uma carta do topo
    Carta cartaRetirada;
    RetirarDoTopo(&lista, &cartaRetirada);
    printf("Carta retirada: ");
    exibir_carta(cartaRetirada);

    // Exiba a lista de cartas após a retirada
    Exibir(&lista, true);

    Mesa mesa;
    InicializarMesa(&mesa);

    // carregou o baralho de 52 cartas mas com todas virada para baixo, sendo o topo
    //CarregarBaralhoAleatorio(&mesa);



    PrepararMesa(&mesa); // ja carrega o baralho aleatorio

    ExibirMesa(&mesa);

    VerificarVitoria(&mesa);

    printf("--------------------------------:\n");
    /*
    for (int i = 0; i < 25; i++) {
        ComprarCarta(&mesa);
    }
    */
    ComprarCarta(&mesa);
    //ExibirMesa(&mesa);

    //MoverDescarteParaBases(&mesa);

    ExibirMesa(&mesa);

    int indice;
    int indice2;
    int indice3;
    printf("Digite o índice da coluna tableau 0 a 6: ");
    scanf("%d", &indice);

    //MoverDescarteParaTableau(&mesa, indice);

    MoverTableauParaBases(&mesa, indice);
    ExibirMesa(&mesa);

    printf("Digite o índice da base a ser retirada a carta 0 a 3: ");
    scanf("%d", &indice2);
    printf("Digite o índice da coluna tableau a ser colocada a carta 0 a 6: ");
    scanf("%d", &indice3);
    MoverBasesParaTableau(&mesa, indice2 , indice3);
    ExibirMesa(&mesa);
    return 0;
}

