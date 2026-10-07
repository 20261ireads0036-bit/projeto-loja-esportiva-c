#include "produto.h"
#include "validacao.h"

// Cria um produto novo na memória (malloc) já com todos os dados preenchidos
// e devolve o endereço dele. Se não der pra alocar, retorna NULL.
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

// Troca a quantidade em estoque do produto pelo valor novo que for passado.
void atualizarQuantidadeEstoque(ProdutoEsportivo *item, int novo_valor)
{
    item->quantidadeEstoque = novo_valor;
}

// Faz a venda: se tiver estoque suficiente, desconta a quantidade vendida
// e devolve o valor total da compra. Se não tiver, devolve -1 e não mexe no estoque.
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

// Separa uma quantidade do estoque pra uma equipe. Se tiver o suficiente,
// tira do estoque e retorna 1; se não tiver, retorna 0 e deixa tudo como estava.
int reservarParaEquipe(ProdutoEsportivo *produto, int quantidade)
{
    if (produto->quantidadeEstoque >= quantidade)
    {
        produto->quantidadeEstoque -= quantidade;

        return 1;
    }

    return 0;
}

// Calcula o preço com desconto de atleta federado a partir de uma porcentagem
// (ex: 10 pra 10%). Só devolve o valor calculado, não altera o preço do produto.
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

// Pede um valor mínimo e um máximo pro usuário e lista só os produtos cujo
// preço está dentro dessa faixa. Mostra o total encontrado antes da lista e,
// se não tiver nenhum, avisa que não achou nada.
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