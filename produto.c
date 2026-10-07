#include "produto.h"
#include "validacao.h"

// Função responsável por criar um novo produto na memória.
//
// Ela recebe os dados do produto, reserva um espaço na memória
// e preenche esse espaço com as informações recebidas.
//
// Retorna:
// - o endereço do produto criado, caso dê certo;
// - NULL, caso não seja possível reservar memória.
ProdutoEsportivo *cadastrarProdutoEsportivo(
    int *codigo,
    char *nome[50],
    char *modalidade[30],
    char *marca[30],
    float *preco,
    int *quantidadeEstoque)
{
    // Reserva memória suficiente para armazenar uma estrutura
    // completa do tipo ProdutoEsportivo.
    ProdutoEsportivo *produto = malloc(sizeof(ProdutoEsportivo));

    // Verifica se a memória foi realmente reservada.
    // Se o malloc falhar, retorna NULL para informar que
    // não foi possível criar o produto.
    if (produto == NULL)
    {
        return NULL;
    }

    // Preenche cada campo da estrutura com os dados recebidos.
    produto->codigo = *codigo;
    strcpy(produto->nome, *nome);
    strcpy(produto->modalidade, *modalidade);
    strcpy(produto->marca, *marca);
    produto->preco = *preco;
    produto->quantidadeEstoque = *quantidadeEstoque;

    // Retorna o endereço do produto criado.
    return produto;
}


// Função responsável por atualizar diretamente a quantidade
// de um determinado produto no estoque.
//
// Ela recebe o endereço do ponteiro que aponta para o produto
// e o novo valor que deverá ser colocado no estoque.
void atualizarQuantidadeEstoque(
    ProdutoEsportivo **item,
    int *novo_valor)
{
    // Acessa o produto através do ponteiro e substitui
    // a quantidade atual pelo novo valor informado.
    *item->quantidadeEstoque = *novo_valor;
}


// Função responsável por realizar uma venda.
//
// Primeiro verifica se existe quantidade suficiente no estoque.
// Se houver, diminui a quantidade vendida e retorna o valor total.
//
// Retorna:
// - valor total da venda, se houver estoque suficiente;
// - -1, caso o estoque não seja suficiente.
int venderProdutoEsportivo(
    ProdutoEsportivo **produto,
    int *quantidade)
{
    // Verifica se o estoque atual é suficiente para realizar a venda.
    if (*produto->quantidadeEstoque >= *quantidade)
    {
        // Diminui do estoque a quantidade que foi vendida.
        *produto->quantidadeEstoque -= *quantidade;

        // Calcula e retorna o valor total da venda.
        return *produto->preco * *quantidade;
    }
    else
    {
        // Retorna -1 para indicar que não existe estoque suficiente.
        return -1;
    }
}


// Função responsável por reservar produtos para uma equipe.
//
// A reserva funciona de forma parecida com uma venda:
// verifica se existe estoque suficiente e, caso exista,
// retira a quantidade reservada do estoque.
//
// Retorna:
// - 1 se a reserva foi realizada;
// - 0 se não houver estoque suficiente.
int reservarParaEquipe(
    ProdutoEsportivo **produto,
    int *quantidade)
{
    // Verifica se há produtos suficientes no estoque.
    if (*produto->quantidadeEstoque >= *quantidade)
    {
        // Retira do estoque a quantidade que foi reservada.
        *produto->quantidadeEstoque -= *quantidade;

        // Indica que a reserva foi realizada com sucesso.
        return 1;
    }

    // Indica que não foi possível realizar a reserva.
    return 0;
}


// Função responsável por calcular o preço de um produto
// depois da aplicação de um desconto para atleta federado.
//
// A função não altera o preço original do produto.
// Ela apenas calcula o novo preço e devolve esse valor.
float aplicarDescontoAtletaFederado(
    ProdutoEsportivo **produto,
    float *percentual)
{
    float precoComDesconto;

    // Calcula o valor do desconto e subtrai do preço original.
    //
    // Exemplo:
    // Produto = R$ 100,00
    // Desconto = 10%
    // Resultado = R$ 90,00
    precoComDesconto =
        *produto->preco -
        (*produto->preco * *percentual / 100);

    // Retorna o preço já com o desconto aplicado.
    return precoComDesconto;
}


// Função responsável por buscar e mostrar produtos
// que estejam dentro de uma determinada faixa de preço.
//
// O usuário informa o valor mínimo e o valor máximo.
// Depois disso, a função percorre todos os produtos
// e mostra somente aqueles que estão dentro da faixa.
void listarProdutosPorFaixaPreco(
    ProdutoEsportivo *produtos[],
    int *quantidade)
{
    // Guarda quantos produtos foram encontrados dentro da faixa.
    int contador = 0;

    float valorMinimo;
    float valorMaximo;

    // Repete a leitura dos valores até que a faixa
    // de preço seja considerada válida.
    while (1)
    {
        printf("\nDigite o valor minimo: ");
        valorMinimo = lerFloat();

        printf("Digite o valor maximo: ");
        valorMaximo = lerFloat();

        // Verifica se o valor mínimo é menor ou igual ao máximo.
        if (valorMinimo <= valorMaximo)
        {
            printf("\nErro: o valor minimo nao pode ser maior que o valor maximo.\n");
            break;
        }

        // Caso a faixa seja inválida, pede os valores novamente.
        printf("\nErro: o valor minimo nao pode ser maior que o valor maximo!\n");
        printf("Digite os valores novamente.\n");
    }

    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("  ║              LISTA DE PRODUTOS FILTRADOS           ║\n");
    printf("  ╚══════════════════════════════════════════════════════╝\n");

    // Primeiro percorre todos os produtos apenas para descobrir
    // quantos deles estão dentro da faixa de preço informada.
    for (int i = 0; i < *quantidade; i++)
    {
        // Verifica se o preço do produto está entre o mínimo
        // e o máximo informados pelo usuário.
        if (*produtos[i].preco >= valorMinimo &&
            *produtos[i].preco <= valorMaximo)
        {
            contador++;
        }
    }

    // Mostra a quantidade de produtos encontrados.
    printf("\n══════════════════════════════════════════════════════\n");
    printf(" Total de produtos: %d\n", contador);
    printf("══════════════════════════════════════════════════════\n");

    // Se nenhum produto estiver dentro da faixa,
    // informa ao usuário e encerra a função.
    if (contador == 0)
    {
        printf("\nNenhum produto encontrado nessa faixa de preco.\n");
        return;
    }

    // Percorre novamente todos os produtos.
    // Dessa vez, em vez de apenas contar, mostra os dados
    // dos produtos que estão dentro da faixa escolhida.
    for (int i = 0; i < *quantidade; i++)
    {
        // Verifica novamente se o produto está dentro da faixa.
        if (*produtos[i].preco >= valorMinimo &&
            *produtos[i].preco <= valorMaximo)
        {
            printf("\n");
            printf(" Produto %d\n", i + 1);
            printf(" ──────────────────────────────────────────────────────\n");

            // Mostra os dados do produto encontrado.
            printf("   Codigo ........: %d\n", *produtos[i].codigo);
            printf("   Nome ..........: %s\n", *produtos[i].nome);
            printf("   Modalidade ....: %s\n", *produtos[i].modalidade);
            printf("   Marca .........: %s\n", *produtos[i].marca);
            printf("   Preco .........: R$ %.2f\n", *produtos[i].preco);

            printf(
                "   Quantidade ....: %d un.\n",
                *produtos[i].quantidadeEstoque
            );

            printf(" ──────────────────────────────────────────────────────\n");
        }
    }
}