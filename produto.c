#include "produto.h"
#include "validacao.h"

ProdutoEsportivo *cadastrarProdutoEsportivo(int codigo, char nome[50], char modalidade[30], char marca[30], float preco, int quantidadeEstoque)
{
    ProdutoEsportivo *produto = malloc(sizeof(ProdutoEsportivo));

    if (produto == NULL)
    {
        return NULL;
    }

    produto->codigo = codigo;

    strcpy(produto->nome, nome);

    strcpy(produto->modalidade, modalidade);

    strcpy(produto->marca, marca);

    produto->preco = preco;

    produto->quantidadeEstoque = quantidadeEstoque;

    return produto;
}

void atualizarQuantidadeEstoque(ProdutoEsportivo *item, int novo_valor)
{
    item->quantidadeEstoque = novo_valor;
}

int venderProdutoEsportivo(ProdutoEsportivo *produto, int quantidade)
{
    if (produto->quantidadeEstoque >= quantidade)
    {
        produto->quantidadeEstoque -= quantidade;

        return produto->preco * quantidade;
    }
    else
    {
        return -1;
    }
}

int reservarParaEquipe(ProdutoEsportivo *produto, int quantidade)
{
    if (produto->quantidadeEstoque >= quantidade)
    {
        produto->quantidadeEstoque -= quantidade;

        return 1;
    }

    return 0;
}

float aplicarDescontoAtletaFederado(
    ProdutoEsportivo *produto,
    float percentual)
{
    float precoComDesconto;

      precoComDesconto =
        produto->preco -
        (produto->preco * percentual / 100);

    return precoComDesconto;
}

void listarProdutosPorFaixaPreco(ProdutoEsportivo produtos[], int quantidade)
{
    int contador = 0;
    float valorMinimo;
    float valorMaximo;

    while (1)
    {
        printf("\nDigite o valor minimo: ");
        valorMinimo = lerFloat();

        printf("Digite o valor maximo: ");
        valorMaximo = lerFloat();

        if (valorMinimo <= valorMaximo)
        {
            printf("\nErro: o valor minimo nao pode ser maior que o valor maximo.\n");
            break;
        }
        printf("\nErro: o valor minimo nao pode ser maior que o valor maximo!\n");
        printf("Digite os valores novamente.\n");
    }
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("  ║             LISTA DE PRODUTOS FILTRADOS              ║\n");
    printf("  ╚══════════════════════════════════════════════════════╝\n");

    for (int i = 0; i < quantidade; i++)
    {
        if (produtos[i].preco >= valorMinimo &&
            produtos[i].preco <= valorMaximo)
        {
            contador++;
        }
    }

    printf("\n══════════════════════════════════════════════════════\n");
    printf(" Total de produtos: %d\n", contador);
    printf("══════════════════════════════════════════════════════\n");

    if (contador == 0)
    {
        printf("\nNenhum produto encontrado nessa faixa de preco.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (produtos[i].preco >= valorMinimo &&
            produtos[i].preco <= valorMaximo)
        {
            printf("\n");
            printf(" Produto %d\n", i + 1);
            printf(" ──────────────────────────────────────────────────────\n");

            printf("   Codigo ........: %d\n", produtos[i].codigo);
            printf("   Nome ..........: %s\n", produtos[i].nome);
            printf("   Modalidade ....: %s\n", produtos[i].modalidade);
            printf("   Marca .........: %s\n", produtos[i].marca);
            printf("   Preco .........: R$ %.2f\n", produtos[i].preco);
            printf("   Quantidade ....: %d un.\n",
                   produtos[i].quantidadeEstoque);

            printf(" ──────────────────────────────────────────────────────\n");
        }
    }
}
