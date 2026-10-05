#include <stdio.h>
#include "validacao.h"

int lerInteiro()
{
    int valor;

    while (scanf("%d", &valor) != 1)
    {
        printf("Entrada invalida! Digite um numero: ");

        while (getchar() != '\n');
    }

    while (getchar() != '\n');

    return valor;
}

float lerFloat()
{
    float valor;
    char entrada[100];
    char extra;

    while (1)
    {
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        {
            printf("Erro ao ler entrada.\n");
            continue;
        }

        if (sscanf(entrada, "%f %c", &valor, &extra) == 1)
        {
            return valor;
        }

        printf("Entrada invalida! Digite apenas um numero: ");
    }
}

void limparBuffer(){
    while (getchar() != '\n');
}