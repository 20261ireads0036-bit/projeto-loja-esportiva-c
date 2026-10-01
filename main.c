#include "produto.h"


int removerProdutoEsportivo(ProdutoEsportivo **produtos, int *quantidade,
                            int codigo) {
  // Localiza o registro pelo codigo, desloca os elementos seguintes uma posição
  // para trás e reduz o vetor com realloc. Retorna 1 se removeu, 0 se não
  // encontrou.
}

void salvarProdutos(ProdutoEsportivo produtos[], int quantidade,
                    char *nomeArquivo) {
  // Abre o arquivo "estoque_esportivo.txt" em modo escrita e grava, uma linha
  // por registro, todos os campos necessários para reconstruir os dados depois.
}

int carregarProdutos(ProdutoEsportivo produtos[], char *nomeArquivo) {
  // Abre o arquivo "estoque_esportivo.txt" em modo leitura (se existir) e
  // preenche o vetor produtos com os registros salvos, devolvendo quantos foram
  // carregados.
}

void liberarProdutos(ProdutoEsportivo **produtos, int *quantidade) {
  // Libera (free) toda a memória alocada dinamicamente para o vetor produtos e
  // zera o contador de quantidade.
}

//========================================}}
//========================================}}

//============FUNÇÕES ESPECÍFICAS DO SISTEMA:============\\:
//==========================================
//==========================================

int venderProdutoEsportivo(ProdutoEsportivo *produto, int quantidade) {
  // Verifica se quantidadeEstoque é suficiente e, em caso positivo, decrementa
  // o estoque e devolve o valor total da venda (preco * quantidade); caso
  // contrário devolve -1.
}

int reservarParaEquipe(ProdutoEsportivo *produto, int quantidade) {
  // Separa uma quantidade de itens do estoque para entrega futura a uma equipe
  // ou escola parceira, decrementando quantidadeEstoque e devolvendo 1 se havia
  // saldo suficiente.
}

float aplicarDescontoAtletaFederado(ProdutoEsportivo *produto,
                                    float percentual) {
  // Reduz o campo preco do produto pelo percentual informado (benefício para
  // atletas federados cadastrados) e devolve o novo preço.
}

void receberNovaColecao(ProdutoEsportivo *produto, int quantidadeRecebida,
                        float novoPreco) {
  // Registra a chegada de uma nova coleção/temporada: soma quantidadeRecebida a
  // quantidadeEstoque e atualiza o campo preco para o valor da nova coleção.
}

//===================================================}}
//===================================================}}

//==========RELATÓRIOS E ANÁLISES DO CONTEXTO:==========\.
//=====================================================
//=====================================================

void relatorioPorModalidade(ProdutoEsportivo produtos[], int quantidade,
                            char *modalidade) {
  // Lista todos os produtos de uma modalidade específica, com marca, preço e
  // quantidade em estoque.
}

void ordenarPorPreco(ProdutoEsportivo produtos[], int quantidade) {
  // Ordena o vetor de produtos em ordem crescente de preço, trocando as structs
  // inteiras de posição quando necessário.
}

int main() {

    ProdutoEsportivo *produtos = NULL;
    int quantidade = 0;

    ProdutoEsportivo *produto = cadastrarProdutoEsportivo(
        1,
        "Bola",
        "Futebol",
        "Marca_boa",
        299
    );

    ProdutoEsportivo *produto2 = cadastrarProdutoEsportivo(
        2,
        "Bola2",
        "Futebol2",
        "Marca_boa2",
        2992
    );

    if (produto == NULL) {
        printf("Erro ao cadastrar produto.\n");
        return 1;
    }

  
    if (!adicionarAoVetor(&produtos, &quantidade, produto)) {
        printf("Erro ao adicionar produto ao vetor.\n");

        free(produto);
        return 1;
    }

    if (!adicionarAoVetor(&produtos, &quantidade, produto2)) {
        printf("Erro ao adicionar produto ao vetor.\n");

        free(produto2);
        return 1;
    }

    listarTodos(&produtos, &quantidade);


    free(produto);
    free(produtos);

    return 0;
}