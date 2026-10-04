#include "produto.h"

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
    float percentual
)
{
    produto->preco =
        produto->preco -
        (produto->preco * percentual / 100);

    return produto->preco;
}
