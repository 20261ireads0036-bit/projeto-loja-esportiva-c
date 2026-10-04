#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

int adicionarAoVetor(ProdutoEsportivo **produtos, int *quantidade, ProdutoEsportivo novoProdutoEsportivo)
{
    ProdutoEsportivo *temp;

    temp = realloc(
        *produtos,
        (*quantidade + 1) * sizeof(ProdutoEsportivo));

    if (temp == NULL)
    {
        return 0;
    }

    *produtos = temp;

    (*produtos)[*quantidade] = novoProdutoEsportivo;

    (*quantidade)++;

    return 1;
}

void listarTodos(ProdutoEsportivo produtos[], int quantidade)
{

    printf("\n");
    printf("========================================\n");
    printf("       LISTA DE PRODUTOS ESPORTIVOS     \n");
    printf("========================================\n");

    for (int i = 0; i < quantidade; i++)
    {

        printf("\n");
        printf("Produto %d\n", i + 1);
        printf("----------------------------------------\n");

        printf("Codigo:      %d\n", produtos[i].codigo);
        printf("Nome:        %s\n", produtos[i].nome);
        printf("Modalidade:  %s\n", produtos[i].modalidade);
        printf("Marca:       %s\n", produtos[i].marca);
        printf("Preco:       R$ %.2f\n", produtos[i].preco);
        printf("Quantidade: %d\n", produtos[i].quantidadeEstoque);

        printf("----------------------------------------\n");
    }

    printf("\n========================================\n");
    printf("Total de produtos: %d\n", quantidade);
    printf("========================================\n");
}

ProdutoEsportivo *buscarPorCodigo(
    ProdutoEsportivo produtos[],
    int quantidade,
    int codigo_buscado)
{
    for (int i = 0; i < quantidade; i++)
    {
        if (produtos[i].codigo == codigo_buscado)
        {
            return &produtos[i];
        }
    }

    return NULL;
}

void salvarProdutos(ProdutoEsportivo produtos[], int quantidade, char *nomeArquivo)
{

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {

        fprintf(
            arquivo,
            "%d;%s;%s;%s;%.2f;%d\n",
            produtos[i].codigo,
            produtos[i].nome,
            produtos[i].modalidade,
            produtos[i].marca,
            produtos[i].preco,
            produtos[i].quantidadeEstoque);
    }

    fclose(arquivo);
}

int removerProdutoEsportivo(ProdutoEsportivo **produtos, int *quantidade, int codigo)
{
    int indice = -1;

    for (int i = 0; i < *quantidade; i++)
    {
        if ((*produtos)[i].codigo == codigo)
        {
            indice = i;
            break;
        }
    }

    if (indice == -1)
    {
        return 0;
    }

    for (int i = indice; i < *quantidade - 1; i++)
    {
        (*produtos)[i] = (*produtos)[i + 1];
    }

    (*quantidade)--;

    return 1;
}

int carregarProdutos(ProdutoEsportivo produtos[], char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    int quantidade = 0;

    while (fscanf(
               arquivo,
               "%d;%49[^;];%29[^;];%29[^;];%f;%d",
               &produtos[quantidade].codigo,
               produtos[quantidade].nome,
               produtos[quantidade].modalidade,
               produtos[quantidade].marca,
               &produtos[quantidade].preco,
               &produtos[quantidade].quantidadeEstoque) == 6)
    {
        quantidade++;
    }

    fclose(arquivo);

    return quantidade;
}

void receberNovaColecao(
    ProdutoEsportivo *produto,
    int quantidadeRecebida,
    float novoPreco)
{
    produto->quantidadeEstoque += quantidadeRecebida;
    produto->preco = novoPreco;
}

void liberarProdutos(ProdutoEsportivo **produtos, int *quantidade)
{
    free(*produtos);

    *produtos = NULL;
    *quantidade = 0;
}

void relatorioPorModalidade(
    ProdutoEsportivo produtos[],
    int quantidade,
    char *modalidade)
{
    int encontrou = 0;

    printf("\n========== Relatorio por Modalidade ==========\n");
    printf("Modalidade: %s\n\n", modalidade);

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(produtos[i].modalidade, modalidade) == 0)
        {
            printf("Codigo: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Marca: %s\n", produtos[i].marca);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
            printf("Estoque: %d\n", produtos[i].quantidadeEstoque);
            printf("---------------------------------------------\n");

            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Nenhum produto encontrado nessa modalidade.\n");
    }
}

void ordenarPorPreco(
    ProdutoEsportivo *produtos[],
    int quantidade)
{
    for (int i = 0; i < quantidade - 1; i++)
    {
        for (int j = i + 1; j < quantidade; j++)
        {
            if (produtos[i]->preco > produtos[j]->preco)
            {
                ProdutoEsportivo *temp = produtos[i];

                produtos[i] = produtos[j];

                produtos[j] = temp;
            }
        }
    }
}