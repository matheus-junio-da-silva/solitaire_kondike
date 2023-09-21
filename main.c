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


    return 0;
}

