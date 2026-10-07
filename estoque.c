#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"


// Adiciona um novo produto ao vetor de produtos.
//
// Como o vetor pode precisar de mais espaço conforme novos produtos
// são cadastrados, usamos realloc para aumentar o tamanho da memória.
//
// Retorna:
// 1 -> se o produto foi adicionado com sucesso
// 0 -> se não foi possível aumentar a memória
int adicionarAoVetor(
    ProdutoEsportivo **produtos,
    int *quantidade,
    ProdutoEsportivo novoProdutoEsportivo)
{
    ProdutoEsportivo *temp;

    // Tenta aumentar o espaço reservado para o vetor,
    // adicionando espaço para mais um ProdutoEsportivo.
    temp = realloc(
        *produtos,
        (*quantidade + 1) * sizeof(ProdutoEsportivo));

    // Se o realloc falhar, o vetor original continua intacto
    // e a função informa que não foi possível adicionar o produto.
    if (temp == NULL)
    {
        return 0;
    }

    // Atualiza o ponteiro principal para apontar para o novo espaço
    // de memória criado pelo realloc.
    *produtos = temp;

    // Coloca o novo produto na primeira posição livre do vetor.
    *produtos[*quantidade] = novoProdutoEsportivo;

    // Aumenta a quantidade de produtos armazenados.
    (*quantidade)++;

    return 1;
}


// Mostra todos os produtos que estão atualmente cadastrados.
//
// A função percorre o vetor do primeiro até o último produto
// e exibe todas as informações de cada um.
void listarTodos(
    ProdutoEsportivo *produtos[],
    int *quantidade)
{
    printf("\n");

    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║              LISTA DE PRODUTOS ESPORTIVOS            ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");

    // Percorre todos os produtos existentes no vetor.
    for (int i = 0; i < *quantidade; i++)
    {
        printf("\n");

        // Mostra a posição do produto dentro da lista.
        printf(" Produto %d\n", i + 1);
        printf(" ──────────────────────────────────────────────────────\n");

        // Exibe os dados do produto atual.
        printf("   Código ........: %d\n", *produtos[i].codigo);
        printf("   Nome ..........: %s\n", *produtos[i].nome);
        printf("   Modalidade ....: %s\n", *produtos[i].modalidade);
        printf("   Marca .........: %s\n", *produtos[i].marca);
        printf("   Preço .........: R$ %.2f\n", *produtos[i].preco);
        printf("   Quantidade ....: %d un.\n", *produtos[i].quantidadeEstoque);

        printf(" ──────────────────────────────────────────────────────\n");
    }

    // Depois de listar todos os produtos, mostra a quantidade total.
    printf("\n══════════════════════════════════════════════════════\n");
    printf(" Total de produtos: %d\n", *quantidade);
    printf("══════════════════════════════════════════════════════\n");
}


// Procura um produto usando o código informado.
//
// A função percorre o vetor procurando um produto cujo código
// seja igual ao código recebido.
//
// Retorna:
// - o endereço do produto encontrado;
// - NULL caso nenhum produto tenha aquele código.
ProdutoEsportivo *buscarPorCodigo(
    ProdutoEsportivo *produtos[],
    int *quantidade,
    int *codigo_buscado)
{
    // Percorre todos os produtos existentes.
    for (int i = 0; i < *quantidade; i++)
    {
        // Compara o código do produto atual com o código procurado.
        if (*produtos[i].codigo == *codigo_buscado)
        {
            // Retorna o endereço do produto encontrado.
            return &*produtos[i];
        }
    }

    // Se chegar até aqui, significa que nenhum produto foi encontrado.
    return NULL;
}


// Salva todos os produtos em um arquivo de texto.
//
// O arquivo é usado para manter os produtos armazenados mesmo
// depois que o programa for fechado.
//
// Cada produto é salvo em uma linha, usando ';' para separar
// os diferentes campos.
void salvarProdutos(
    ProdutoEsportivo *produtos[],
    int *quantidade,
    char *nomeArquivo)
{
    // Abre o arquivo no modo "w".
    // Se o arquivo já existir, seu conteúdo será sobrescrito.
    FILE *arquivo = fopen(nomeArquivo, "w");

    // Verifica se o arquivo conseguiu ser aberto.
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Percorre todos os produtos cadastrados.
    for (int i = 0; i < *quantidade; i++)
    {
        // Grava os dados do produto no arquivo.
        // O ';' separa cada informação.
        fprintf(
            arquivo,
            "%d;%s;%s;%s;%.2f;%d\n",
            *produtos[i].codigo,
            *produtos[i].nome,
            *produtos[i].modalidade,
            *produtos[i].marca,
            *produtos[i].preco,
            *produtos[i].quantidadeEstoque);
    }

    // Fecha o arquivo depois de terminar a gravação.
    fclose(arquivo);
}


// Remove um produto inteiro do vetor usando seu código.
//
// Primeiro procura a posição do produto.
// Depois desloca os produtos seguintes uma posição para trás,
// ocupando o espaço que ficou vazio.
//
// Retorna:
// 1 -> produto removido
// 0 -> produto não encontrado
int removerProdutoEsportivo(
    ProdutoEsportivo **produtos,
    int *quantidade,
    int *codigo)
{
    // Começamos considerando que o produto não foi encontrado.
    int indice = -1;

    // Procura o produto pelo código.
    for (int i = 0; i < *quantidade; i++)
    {
        if ((*produtos)[i].codigo == *codigo)
        {
            // Guarda a posição onde o produto foi encontrado.
            indice = i;
            break;
        }
    }

    // Se o índice continua -1, nenhum produto foi encontrado.
    if (indice == -1)
    {
        return 0;
    }

    // A partir do produto removido, desloca todos os produtos
    // seguintes uma posição para trás.
    //
    // Exemplo:
    // [A][B][C][D]
    // Se B for removido:
    // [A][C][D][D]
    //
    // Depois a quantidade é diminuída e o último espaço deixa
    // de fazer parte do vetor.
    for (int i = indice; i < *quantidade - 1; i++)
    {
        (*produtos)[i] = (*produtos)[i + 1];
    }

    // Diminui a quantidade total de produtos.
    (*quantidade)--;

    // Informa que a remoção aconteceu.
    return 1;
}


// Carrega os produtos que estavam salvos no arquivo TXT.
//
// Essa função é chamada quando o programa inicia.
// Ela lê cada linha do arquivo e coloca os dados dentro do vetor.
//
// Retorna a quantidade de produtos carregados.
int carregarProdutos(
    ProdutoEsportivo *produtos[],
    char *nomeArquivo)
{
    // Abre o arquivo no modo "r", ou seja, somente para leitura.
    FILE *arquivo = fopen(nomeArquivo, "r");

    // Se o arquivo não existir ou não puder ser aberto,
    // simplesmente começa com nenhum produto carregado.
    if (arquivo == NULL)
    {
        return 0;
    }

    // Começamos na primeira posição do vetor.
    int quantidade = 0;

    // Continua lendo enquanto conseguir encontrar os 6 campos
    // esperados em cada produto.
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
        // Depois de carregar um produto corretamente,
        // passa para a próxima posição do vetor.
        quantidade++;
    }

    // Fecha o arquivo depois de terminar a leitura.
    fclose(arquivo);

    // Retorna quantos produtos foram carregados.
    return quantidade;
}


// Registra a chegada de uma nova coleção.
//
// A função adiciona a quantidade recebida ao estoque atual
// e substitui o preço antigo pelo novo preço informado.
void receberNovaColecao(
    ProdutoEsportivo **produto,
    int *quantidadeRecebida,
    float *novoPreco)
{
    // Soma as novas unidades ao estoque existente.
    *produto->quantidadeEstoque += *quantidadeRecebida;

    // Atualiza o preço do produto.
    *produto->preco = *novoPreco;
}


// Libera a memória usada pelo vetor de produtos.
//
// Essa função deve ser chamada quando o programa terminar,
// evitando deixar memória ocupada sem necessidade.
void liberarProdutos(
    ProdutoEsportivo **produtos,
    int *quantidade)
{
    // Libera a memória que foi reservada para o vetor.
    free(*produtos);

    // Depois de liberar a memória, colocamos o ponteiro como NULL.
    // Isso evita que ele continue apontando para uma área que já foi liberada.
    *produtos = NULL;

    // Como não existem mais produtos carregados na memória,
    // zeramos também a quantidade.
    *quantidade = 0;
}


// Mostra um relatório contendo somente os produtos
// pertencentes à modalidade informada.
//
// A comparação é feita usando strcmp.
void relatorioPorModalidade(
    ProdutoEsportivo *produtos[],
    int *quantidade,
    char *modalidade)
{
    // Essa variável serve para saber se encontramos pelo menos
    // um produto da modalidade pesquisada.
    int encontrou = 0;

    printf("\n========== Relatorio por Modalidade ==========\n");
    printf("Modalidade: %s\n\n", modalidade);

    // Percorre todos os produtos do vetor.
    for (int i = 0; i < *quantidade; i++)
    {
        // strcmp retorna 0 quando as duas strings são iguais.
        if (strcmp(*produtos[i].modalidade, *modalidade) == 0)
        {
            // Mostra os dados do produto encontrado.
            printf("Codigo: %d\n", *produtos[i].codigo);
            printf("Nome: %s\n", *produtos[i].nome);
            printf("Marca: %s\n", *produtos[i].marca);
            printf("Preco: R$ %.2f\n", *produtos[i].preco);
            printf("Estoque: %d\n", *produtos[i].quantidadeEstoque);

            printf("---------------------------------------------\n");

            // Marca que pelo menos um produto foi encontrado.
            encontrou = 1;
        }
    }

    // Se nenhum produto foi encontrado durante o percurso,
    // mostra uma mensagem informando isso.
    if (!encontrou)
    {
        printf("Nenhum produto encontrado nessa modalidade.\n");
    }
}


// Ordena os produtos do menor para o maior preço.
//
// A função compara os preços dos produtos e troca suas posições
// quando encontra um produto mais barato depois de um mais caro.
void ordenarPorPreco(
    ProdutoEsportivo **produtos,
    int *quantidade)
{
    // Primeiro laço responsável por escolher o produto
    // que será comparado com os próximos.
    for (int i = 0; i < *quantidade - 1; i++)
    {
        // Segundo laço percorre os produtos que vêm depois
        // da posição atual.
        for (int j = i + 1; j < *quantidade; j++)
        {
            // Se o produto atual tiver preço maior que o próximo,
            // precisamos trocar os dois de posição.
            if (*produtos[i].preco > *produtos[j].preco)
            {
                // Guarda temporariamente o produto da posição i.
                ProdutoEsportivo temp = *produtos[i];

                // Coloca o produto mais barato na posição i.
                *produtos[i] = *produtos[j];

                // Coloca o produto que estava em i na posição j.
                *produtos[j] = temp;
            }
        }
    }

    // Depois da ordenação, mostra os produtos já organizados.
    printf("\n");

    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║              PRODUTOS ORDENADOS POR PREÇO            ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n\n");

    // Mostra a lista ordenada do menor para o maior preço.
    for (int i = 0; i < *quantidade; i++)
    {
        printf(
            "   %2d. %-25s R$ %9.2f\n",
            i + 1,
            *produtos[i].nome,
            *produtos[i].preco);
    }

    printf("\n──────────────────────────────────────────────────────\n");
}