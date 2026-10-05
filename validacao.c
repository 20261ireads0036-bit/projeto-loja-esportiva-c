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

    while (scanf("%f", &valor) != 1)
    {
        printf("Entrada invalida! Digite um numero: ");

        while (getchar() != '\n');
    }

    while (getchar() != '\n');

    return valor;
}