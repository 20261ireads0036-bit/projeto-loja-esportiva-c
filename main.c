#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


//================STRUCT PRINCIPAL!================\\.
typedef struct{
    int codigo;
    char nome[50];
    char modalidade[30];
    char marca[30];
    float preco;
    int quantidadeEstoque;

} ProdutoEsportivo;


//=============FUNÇÕES OBRIGATÓRIAS===============\\:
//=================================================
//=================================================

ProdutoEsportivo *cadastrarProdutoEsportivo(/* parâmetros com os dados de um novo produtoesportivo */){
    //Aloca dinamicamente (malloc) um novo ProdutoEsportivo, preenche todos os seus campos — incluindo a(s) struct(s) aninhada(s) — e devolve o ponteiro para essa struct.
}

int adicionarAoVetor(ProdutoEsportivo **produtos, int *quantidade, ProdutoEsportivo novoProdutoEsportivo){
    //Aumenta o vetor produtos com realloc (quantidade+1 posições), copia o novo registro para a última posição e incrementa o contador. Retorna 1 em caso de sucesso e 0 se a alocação falhar.
}

void listarTodos(ProdutoEsportivo produtos[], int quantidade){
    //Percorre o vetor produtos e exibe, de forma organizada, todos os campos de cada registro (inclusive os campos das structs aninhadas).
}

ProdutoEsportivo *buscarPorCodigo(ProdutoEsportivo produtos[], int quantidade, /* tipo */ codigoBuscado){
    //Percorre o vetor comparando o campo codigo de cada registro com o valor buscado e devolve o ponteiro para o registro encontrado, ou NULL caso não exista.
}

void atualizarQuantidadeEstoque(ProdutoEsportivo *item, /* novo valor */){
    //Recebe o registro por ponteiro e atualiza diretamente o campo quantidadeEstoque, usando o operador -> (passagem por referência).
}

int removerProdutoEsportivo(ProdutoEsportivo **produtos, int *quantidade, /* tipo */ codigo){
    //Localiza o registro pelo codigo, desloca os elementos seguintes uma posição para trás e reduz o vetor com realloc. Retorna 1 se removeu, 0 se não encontrou.
}

void salvarProdutos(ProdutoEsportivo produtos[], int quantidade, char *nomeArquivo){
    //Abre o arquivo "estoque_esportivo.txt" em modo escrita e grava, uma linha por registro, todos os campos necessários para reconstruir os dados depois.
}

int carregarProdutos(ProdutoEsportivo produtos[], char *nomeArquivo){
    //Abre o arquivo "estoque_esportivo.txt" em modo leitura (se existir) e preenche o vetor produtos com os registros salvos, devolvendo quantos foram carregados.
}

void liberarProdutos(ProdutoEsportivo **produtos, int *quantidade){
    //Libera (free) toda a memória alocada dinamicamente para o vetor produtos e zera o contador de quantidade.
}

//========================================}}
//========================================}}





//============FUNÇÕES ESPECÍFICAS DO SISTEMA:============\\:
//==========================================
//==========================================


int venderProdutoEsportivo(ProdutoEsportivo *produto, int quantidade){
    //Verifica se quantidadeEstoque é suficiente e, em caso positivo, decrementa o estoque e devolve o valor total da venda (preco * quantidade); caso contrário devolve -1.
}

int reservarParaEquipe(ProdutoEsportivo *produto, int quantidade){
    //Separa uma quantidade de itens do estoque para entrega futura a uma equipe ou escola parceira, decrementando quantidadeEstoque e devolvendo 1 se havia saldo suficiente.
}

float aplicarDescontoAtletaFederado(ProdutoEsportivo *produto, float percentual){
    //Reduz o campo preco do produto pelo percentual informado (benefício para atletas federados cadastrados) e devolve o novo preço.
}

void receberNovaColecao(ProdutoEsportivo *produto, int quantidadeRecebida, float novoPreco){
    //Registra a chegada de uma nova coleção/temporada: soma quantidadeRecebida a quantidadeEstoque e atualiza o campo preco para o valor da nova coleção.
}

//===================================================}}
//===================================================}}




//==========RELATÓRIOS E ANÁLISES DO CONTEXTO:==========\.
//=====================================================
//=====================================================


void relatorioPorModalidade(ProdutoEsportivo produtos[], int quantidade, char *modalidade){
    //Lista todos os produtos de uma modalidade específica, com marca, preço e quantidade em estoque.
}

void ordenarPorPreco(ProdutoEsportivo produtos[], int quantidade){
    //Ordena o vetor de produtos em ordem crescente de preço, trocando as structs inteiras de posição quando necessário.
}


int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);



    return 0;
}