#include <stdio.h>
#include <stdlib.h>
#include "validacao.h"


// Função responsável por ler um número inteiro.
//
// Ela continua pedindo a entrada enquanto o usuário
// não informar um valor que possa ser interpretado como inteiro.
//
// Exemplo de valores válidos:
// 10
// 25
// -5
int lerInteiro()
{
    int valor;

    // scanf retorna 1 quando consegue ler corretamente
    // um número inteiro.
    while (scanf("%d", &valor) != 1)
    {
        printf("Entrada invalida! Digite um numero: ");

        // Limpa o que ficou no teclado depois de uma entrada inválida.
        // Isso evita que o mesmo caractere seja lido novamente
        // pelo próximo scanf.
        while (getchar() != '\n');
    }

    // Remove o restante da linha digitada pelo usuário.
    while (getchar() != '\n');

    // Retorna o número inteiro que foi digitado.
    return valor;
}


// Função responsável por ler números decimais.
//
// Diferente do lerInteiro(), aqui usamos fgets para primeiro
// capturar toda a linha digitada pelo usuário.
// Depois usamos sscanf para verificar se aquela linha
// realmente contém apenas um número.
float lerFloat()
{
    float valor;

    // Guarda temporariamente o que o usuário digitou.
    char entrada[100];

    // É usado para verificar se existe algum caractere
    // depois do número informado.
    char extra;

    // Continua tentando até conseguir uma entrada válida.
    while (1)
    {
        // Lê uma linha inteira do teclado.
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        {
            printf("Erro ao ler entrada.\n");
            continue;
        }

        // Tenta transformar o conteúdo da linha em um float.
        //
        // O "%c" em extra serve para verificar se existe
        // algum outro caractere depois do número.
        //
        // Se sscanf retornar 1, significa que conseguiu ler
        // somente o número esperado.
        if (sscanf(entrada, "%f %c", &valor, &extra) == 1)
        {
            return valor;
        }

        // Caso a entrada não seja válida, pede novamente.
        printf("Entrada invalida! Digite apenas um numero: ");
    }
}


// Função responsável por limpar o que ficou no buffer do teclado.
//
// Ela é útil principalmente depois de usar scanf,
// quando ainda pode existir um '\n' esperando para ser lido.
void limparBuffer()
{
    // Continua lendo os caracteres até encontrar
    // o final da linha.
    while (getchar() != '\n');
}


// Função responsável por ler textos que não podem conter números.
//
// Ela recebe:
// - uma mensagem para mostrar ao usuário;
// - o vetor onde o texto será armazenado;
// - o tamanho máximo desse vetor.
//
// A função também verifica se:
// - o usuário digitou números;
// - o texto ficou grande demais;
// - o campo ficou vazio.
void lerTextoSemNumeros(
    const char *mensagem,
    char *texto,
    int tamanho)
{
    int possuiNumero;
    int caractere;
    int i;

    // O do-while garante que o usuário tenha pelo menos
    // uma tentativa de preenchimento antes das validações.
    do
    {
        // Começamos considerando que o texto é válido.
        // Se encontrarmos algum problema, essa variável
        // será alterada para 1.
        possuiNumero = 0;

        // Mostra a mensagem recebida pela função.
        printf("%s", mensagem);

        // Lê o texto digitado pelo usuário.
        if (fgets(texto, tamanho, stdin) == NULL)
        {
            printf("\nErro ao ler o texto.\n");

            // Encerra o programa caso aconteça um erro
            // durante a leitura.
            exit(1);
        }

        // Percorre cada caractere digitado.
        //
        // O loop para quando encontra:
        // - o final da string '\0';
        // - ou o ENTER '\n'.
        for (i = 0;
             texto[i] != '\0' && texto[i] != '\n';
             i++)
        {
            // Verifica se o caractere atual é um número.
            //
            // Os caracteres '0' até '9' representam os
            // números de 0 a 9 na tabela ASCII.
            if (texto[i] >= '0' && texto[i] <= '9')
            {
                // Encontrou um número, então o texto é inválido.
                possuiNumero = 1;
            }
        }

        // Verifica se o texto ultrapassou o tamanho máximo permitido.
        //
        // Quando o usuário digita mais caracteres do que cabem
        // no vetor, o fgets não consegue colocar tudo de uma vez.
        if (i == tamanho - 1 &&
            texto[i] != '\n' &&
            !feof(stdin))
        {
            // Limpa o restante da mensagem que ficou no teclado.
            while ((caractere = getchar()) != '\n' &&
                   caractere != EOF)
            {
            }

            // Marca a entrada como inválida.
            possuiNumero = 1;

            printf(" [!] Texto muito longo. Digite novamente.\n");

            // Volta para o início do do-while.
            continue;
        }

        // Se o usuário pressionou ENTER, substituímos o '\n'
        // pelo '\0', que representa o final da string.
        if (texto[i] == '\n')
        {
            texto[i] = '\0';
        }

        // Se foi encontrado algum número no texto,
        // mostra uma mensagem de erro.
        if (possuiNumero)
        {
            printf(" [!] Não digite números neste campo!\n");
        }

        // Se o primeiro caractere já for '\0',
        // significa que o usuário simplesmente pressionou ENTER
        // sem digitar nada.
        else if (texto[0] == '\0')
        {
            printf(" [!] O campo não pode ficar vazio!\n");

            // Marca como inválido para que o loop peça
            // o texto novamente.
            possuiNumero = 1;
        }

    // Enquanto possuiNumero for 1, a função continua pedindo
    // uma nova entrada.
    } while (possuiNumero);
}