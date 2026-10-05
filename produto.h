#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

//================STRUCT PRINCIPAL!================\\.
typedef struct {
  int codigo;
  char nome[50];
  char modalidade[30];
  char marca[30];
  float preco;
  int quantidadeEstoque;

} ProdutoEsportivo;

ProdutoEsportivo *cadastrarProdutoEsportivo(int codigo, char nome[50], char modalidade[30], char marca[30], float preco, int quantidadeEstoque);

void atualizarQuantidadeEstoque(ProdutoEsportivo *item, int novo_valor);

int reservarParaEquipe(ProdutoEsportivo *produto, int quantidade);

int venderProdutoEsportivo(ProdutoEsportivo *produto, int quantidade);

float aplicarDescontoAtletaFederado(ProdutoEsportivo *produto, float percentual);

void listarProdutosPorFaixaPreco (ProdutoEsportivo produtos[], int quantidade);

#endif