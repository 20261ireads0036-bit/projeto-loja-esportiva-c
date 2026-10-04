#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "produto.h"

int adicionarAoVetor(ProdutoEsportivo **produtos, int *quantidade, ProdutoEsportivo novoProdutoEsportivo);

void listarTodos(ProdutoEsportivo produtos[], int quantidade);

ProdutoEsportivo *buscarPorCodigo(ProdutoEsportivo produtos[], int quantidade, int codigo_buscado);

int removerProdutoEsportivo(ProdutoEsportivo **produtos, int *quantidade, int codigo);

void salvarProdutos(ProdutoEsportivo produtos[], int quantidade, char *nomeArquivo);

int carregarProdutos(ProdutoEsportivo produtos[], char *nomeArquivo);

void liberarProdutos(ProdutoEsportivo **produtos, int *quantidade);

void relatorioPorModalidade(ProdutoEsportivo produtos[], int quantidade, char *modalidade);

void ordenarPorPreco(ProdutoEsportivo *produtos[], int quantidade);

void receberNovaColecao(ProdutoEsportivo *produto, int quantidadeRecebida, float novoPreco);

#endif