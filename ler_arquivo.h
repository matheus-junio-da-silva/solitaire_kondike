#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"

void ExibirMenu();
void ModoInterativo();
int LerJogoDeArquivo(Mesa* mesa);
void AdicionarCartaAoBaralho(Mesa* mesa, int valor, char naipe);
void PrepMesa(Mesa* mesa);
int VerificarVitoriaArquivo(Mesa* mesa);
