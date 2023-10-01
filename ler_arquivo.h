#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifndef LER_ARQUIVO_H
#define LER_ARQUIVO_H

#include "tad_cartas.h"
#include "tad_lista_cartas.h"
#include "tad_mesa.h"



void ExibirMenu();
void ModoInterativo();
int LerJogoDeArquivo(Mesa* mesa, int* verifica);
void AdicionarCartaAoBaralho(Mesa* mesa, int valor, char naipe);
void PrepMesa(Mesa* mesa);
int VerificarVitoriaArquivo(Mesa* mesa,int numCartas);
int VerificarDerrota(Mesa* mesa,int numCartas);
#endif
