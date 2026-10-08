#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Aumenta o vetor em uma posição com realloc e coloca o produto novo no final.
// Se faltar memória retorna 0, se deu certo retorna 1.
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

// Mostra na tela todos os produtos cadastrados, um por um, com todos os dados,
// e no final imprime quantos produtos existem no total.
void listarTodos(ProdutoEsportivo produtos[], int quantidade)
{
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║              LISTA DE PRODUTOS ESPORTIVOS            ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf("\n");
        printf(" Produto %d\n", i + 1);
        printf(" ──────────────────────────────────────────────────────\n");

        printf("   Código ........: %d\n", produtos[i].codigo);
        printf("   Nome ..........: %s\n", produtos[i].nome);
        printf("   Modalidade ....: %s\n", produtos[i].modalidade);
        printf("   Marca .........: %s\n", produtos[i].marca);
        printf("   Preço .........: R$ %.2f\n", produtos[i].preco);
        printf("   Quantidade ....: %d un.\n", produtos[i].quantidadeEstoque);

        printf(" ──────────────────────────────────────────────────────\n");
    }

    printf("\n══════════════════════════════════════════════════════\n");
    printf(" Total de produtos: %d\n", quantidade);
    printf("══════════════════════════════════════════════════════\n");
}

// Procura um produto pelo código percorrendo o vetor.
// Devolve o endereço do produto se achar, ou NULL se não existir nenhum com esse código.
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

// Grava todos os produtos num arquivo de texto, uma linha por produto,
// com os campos separados por ponto e vírgula. Se não conseguir abrir o arquivo, só avisa e sai.
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

// Tira um produto do vetor pelo código. Primeiro acha a posição dele, depois puxa
// todo mundo que vem depois uma casa pra trás pra tapar o buraco e diminui a quantidade.
// Retorna 1 se removeu e 0 se o código não foi encontrado.
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

// Lê o arquivo salvo antes e vai preenchendo o vetor, linha por linha, até acabar.
// Devolve quantos produtos conseguiu ler (0 se o arquivo não existir).
// Obs: o vetor já precisa ter espaço suficiente pra tudo que vier do arquivo.
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

// Registra a chegada de uma nova coleção de um produto: soma as unidades que
// chegaram ao estoque e já atualiza o preço pro valor novo.
void receberNovaColecao(
    ProdutoEsportivo *produto,
    int quantidadeRecebida,
    float novoPreco)
{
    produto->quantidadeEstoque += quantidadeRecebida;
    produto->preco = novoPreco;
}

// Libera a memória do vetor e zera tudo, deixando o ponteiro em NULL
// pra não ficar apontando pra lixo. Chamar isso antes de encerrar o programa.
void liberarProdutos(ProdutoEsportivo **produtos, int *quantidade)
{
    free(*produtos);

    *produtos = NULL;
    *quantidade = 0;
}

// Mostra só os produtos de uma modalidade específica (ex: futebol, vôlei).
// Se não tiver nenhum, avisa que não encontrou nada.
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
        // Compara ignorando letras maiúsculas e minúsculas.
        if (_stricmp(produtos[i].modalidade, modalidade) == 0)
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
// Ordena o vetor do mais barato pro mais caro (trocando os produtos de lugar
// quando estão fora de ordem) e depois imprime a lista já ordenada.
// Cuidado: isso muda a ordem do vetor original, não é só pra exibição.
void ordenarPorPreco(ProdutoEsportivo *produtos, int quantidade)
{
    for (int i = 0; i < quantidade - 1; i++)
    {
        for (int j = i + 1; j < quantidade; j++)
        {
            if (produtos[i].preco > produtos[j].preco)
            {
                ProdutoEsportivo temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
            }
        }
    }

    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║              PRODUTOS ORDENADOS POR PREÇO            ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf("   %2d. %-25s R$ %9.2f\n",
               i + 1,
               produtos[i].nome,
               produtos[i].preco);
    }

    printf("\n──────────────────────────────────────────────────────\n");
}