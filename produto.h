#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//================STRUCT PRINCIPAL!================\\.
typedef struct {
  int codigo;
  char nome[50];
  char modalidade[30];
  char marca[30];
  float preco;
  int quantidadeEstoque;

} ProdutoEsportivo;

ProdutoEsportivo *cadastrarProdutoEsportivo(int codigo, char nome[50], char modalidade[30], char marca[30], float preco);

int adicionarAoVetor(ProdutoEsportivo **produtos, int *quantidade, ProdutoEsportivo *novoProduto);

void listarTodos(ProdutoEsportivo *produtos[], int *quantidade);

ProdutoEsportivo *buscarPorCodigo(ProdutoEsportivo *produtos[], int *quantidade, int *codigoBuscado);

void atualizarQuantidadeEstoque(ProdutoEsportivo *item, int novo_valor);

#endif