#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// Estrutura para representar uma carta
typedef struct {
    int valor;
    char naipe;
} Carta;

// Função para processar uma linha de carta
Carta processarCarta(char *linha) {
    Carta carta;
    sscanf(linha, "(%d %c)", &carta.valor, &carta.naipe);
    return carta;
}

int main() {
    FILE *arquivo;
    char linha[MAX_LINE_LENGTH];
    int linhaNumero = 0;

    arquivo = fopen("test.txt", "r"); // Substitua "teste_paciencia.txt" pelo nome do seu arquivo de teste

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linhaNumero++;

        // Ignorar linhas em branco ou comentários (iniciadas com '#')
        if (linha[0] == '\n' || linha[0] == '#') {
            continue;
        }

        // Processar a linha como uma carta
        Carta carta = processarCarta(linha);
        printf("Linha %d: Valor: %d, Naipe: %c\n", linhaNumero, carta.valor, carta.naipe);
    }

    fclose(arquivo);
    return 0;
}

