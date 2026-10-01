#include "produto.h"

ProdutoEsportivo *cadastrarProdutoEsportivo(int codigo, char nome[50],
                                            char modalidade[30], char marca[30],
                                            float preco) {
  ProdutoEsportivo *produto = malloc(sizeof(ProdutoEsportivo));

  produto->codigo = codigo;
  strcpy(produto->nome, nome);
  strcpy(produto->modalidade, modalidade);
  strcpy(produto->marca, marca);
  produto->preco = preco;

  return produto;
}

int adicionarAoVetor(ProdutoEsportivo **produtos, int *quantidade,
                     ProdutoEsportivo *novoProduto) {
  ProdutoEsportivo *temp;

  temp = realloc(*produtos, (*quantidade + 1) * sizeof(ProdutoEsportivo));

  if (temp == NULL) {
    return 0;
  }

  *produtos = temp;

  (*produtos)[*quantidade] = *novoProduto;

  (*quantidade)++;

  return 1;
}

void listarTodos(ProdutoEsportivo *produtos[], int *quantidade) {

  printf("\n");
  printf("========================================\n");
  printf("       LISTA DE PRODUTOS ESPORTIVOS     \n");
  printf("========================================\n");

  for (int i = 0; i < *quantidade; i++) {

    printf("\n");
    printf("Produto %d\n", i + 1);
    printf("----------------------------------------\n");

    printf("Codigo:      %d\n", produtos[i]->codigo);
    printf("Nome:        %s\n", produtos[i]->nome);
    printf("Modalidade:  %s\n", produtos[i]->modalidade);
    printf("Marca:       %s\n", produtos[i]->marca);
    printf("Preco:       R$ %.2f\n", produtos[i]->preco);

    printf("----------------------------------------\n");
  }

  printf("\n========================================\n");
  printf("Total de produtos: %d\n", *quantidade);
  printf("========================================\n");
}

ProdutoEsportivo *buscarPorCodigo(ProdutoEsportivo *produtos[], int *quantidade,
                                  int *codigoBuscado) {

  for (int i = 0; i < *quantidade; i++) {

    if (produtos[i]->codigo == *codigoBuscado) {

      printf("\n");
      printf("========================================\n");
      printf("          PRODUTO ENCONTRADO            \n");
      printf("========================================\n");

      printf("Codigo:      %d\n", produtos[i]->codigo);
      printf("Nome:        %s\n", produtos[i]->nome);
      printf("Modalidade:  %s\n", produtos[i]->modalidade);
      printf("Marca:       %s\n", produtos[i]->marca);
      printf("Preco:       R$ %.2f\n", produtos[i]->preco);

      printf("========================================\n");

      return produtos[i];
    }
  }

  printf("\n");
  printf("========================================\n");
  printf("          PRODUTO NAO ENCONTRADO        \n");
  printf("========================================\n");
  printf("Nenhum produto possui o codigo %d.\n", *codigoBuscado);
  printf("========================================\n");

  return NULL;
}

void atualizarQuantidadeEstoque(ProdutoEsportivo *item, int novo_valor) {
  item->quantidadeEstoque = novo_valor;
}
