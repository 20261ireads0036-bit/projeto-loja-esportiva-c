#include "produto.h"
#include "estoque.h"
#include "validacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_NUMERIC, "C");

    int opcao;

    ProdutoEsportivo *produtos = NULL;
    int quantidade = 0;

    produtos = malloc(100 * sizeof(ProdutoEsportivo *));

    if (produtos == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    quantidade = carregarProdutos(produtos, "estoque.txt");

    do
    {
        system("cls");

        printf("\n");
        printf("============================================================\n");
        printf("                    VITORIA ESPORTES                        \n");
        printf("                 Sistema de Estoque                         \n");
        printf("============================================================\n");
        printf("\n");

        printf("  [1]  Cadastrar Produto\n");
        printf("  [2]  Salvar Produtos no Estoque\n");
        printf("  [3]  Remover Produto\n");
        printf("  [4]  Listar Todos\n");
        printf("  [5]  Buscar por Codigo\n");
        printf("  [6]  Vender Produto\n");
        printf("  [7]  Reservar para Equipe\n");
        printf("  [8]  Receber Nova Colecao\n");
        printf("  [9]  Relatorio por Modalidade\n");
        printf("  [10] Ordenar por Preco\n");
        printf("  [0]  Sair\n");

        printf("\n------------------------------------------------------------\n");
        printf("Quantidade de produtos cadastrados: %d\n", quantidade);
        printf("------------------------------------------------------------\n");

        printf("\nEscolha uma opcao: ");
        opcao = lerInteiro();

        switch (opcao)
        {
        case 1:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                    CADASTRAR PRODUTO                       \n");
            printf("============================================================\n\n");

            int codigo;
            char nome[50];
            char modalidade[30];
            char marca[30];
            float preco;
            int quantidadeEstoque;

            printf("Codigo: ");
            codigo = lerInteiro();

            while (buscarPorCodigo(produtos, quantidade, codigo) != NULL)
            {
                printf("\nEsse codigo ja esta cadastrado!\n");
                printf("Digite um novo codigo: ");

                codigo = lerInteiro();
            }

            printf("Nome: ");
            scanf(" %49[^\n]", nome);

            printf("Modalidade: ");
            scanf(" %29[^\n]", modalidade);

            printf("Marca: ");
            scanf(" %29[^\n]", marca);

            printf("Preco: R$ ");
            preco = lerFloat();

            printf("Quantidade em estoque: ");
            quantidadeEstoque = lerInteiro();

            ProdutoEsportivo *novoProduto =
                cadastrarProdutoEsportivo(
                    codigo,
                    nome,
                    modalidade,
                    marca,
                    preco,
                    quantidadeEstoque);

            if (novoProduto == NULL)
            {
                printf("\nErro ao cadastrar produto.\n");
                break;
            }

            if (adicionarAoVetor(
                    &produtos,
                    &quantidade,
                    *novoProduto))
            {
                printf("\n------------------------------------------------------------\n");
                printf("Produto cadastrado com sucesso!\n");
                printf("------------------------------------------------------------\n");
            }
            else
            {
                printf("\nErro ao adicionar produto ao estoque.\n");
            }

            free(novoProduto);

            break;
        }

        case 2:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                 SALVAR PRODUTOS                            \n");
            printf("============================================================\n\n");

            salvarProdutos(
                produtos,
                quantidade,
                "estoque.txt");

            printf("Produtos salvos com sucesso!\n");

            break;
        }

        case 3:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                  REMOVER PRODUTO                           \n");
            printf("============================================================\n\n");

            int codigo;

            printf("Digite o codigo do produto: ");

            codigo = lerInteiro();

            if (removerProdutoEsportivo(
                    &produtos,
                    &quantidade,
                    codigo))
            {
                salvarProdutos(
                    produtos,
                    quantidade,
                    "estoque.txt");

                printf("\n------------------------------------------------------------\n");
                printf("Produto removido com sucesso!\n");
                printf("------------------------------------------------------------\n");
            }
            else
            {
                printf("\nProduto nao encontrado!\n");
            }

            break;
        }

        case 4:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                    LISTA DE PRODUTOS                       \n");
            printf("============================================================\n\n");

            listarTodos(
                produtos,
                quantidade);

            break;
        }

        case 5:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                    BUSCAR PRODUTO                          \n");
            printf("============================================================\n\n");

            int codigo;

            printf("Digite o codigo do produto: ");

            codigo = lerInteiro();

            ProdutoEsportivo *produtoEncontrado =
                buscarPorCodigo(
                    produtos,
                    quantidade,
                    codigo);

            if (produtoEncontrado == NULL)
            {
                printf("\nProduto nao encontrado!\n");
                break;
            }

            printf("\n");
            printf("---------------- PRODUTO ENCONTRADO -----------------------\n");
            printf("Codigo:      %d\n", produtoEncontrado->codigo);
            printf("Nome:        %s\n", produtoEncontrado->nome);
            printf("Modalidade:  %s\n", produtoEncontrado->modalidade);
            printf("Marca:       %s\n", produtoEncontrado->marca);
            printf("Preco:       R$ %.2f\n", produtoEncontrado->preco);
            printf("Estoque:     %d unidade(s)\n",
                   produtoEncontrado->quantidadeEstoque);
            printf("------------------------------------------------------------\n");

            break;
        }

        case 6:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                     VENDA DE PRODUTO                      \n");
            printf("============================================================\n\n");

            int codigo;

            printf("Digite o codigo do produto: ");
            codigo = lerInteiro();

            /*
             * Procura o produto pelo codigo.
             */
            ProdutoEsportivo *produtoEncontrado =
                buscarPorCodigo(
                    produtos,
                    quantidade,
                    codigo);

            if (produtoEncontrado == NULL)
            {
                printf("\nProduto nao encontrado!\n");
                break;
            }

            printf("\n---------------- PRODUTO ENCONTRADO -----------------------\n");
            printf("Nome:    %s\n", produtoEncontrado->nome);
            printf("Preco:   R$ %.2f\n", produtoEncontrado->preco);
            printf("Estoque: %d unidade(s)\n",
                   produtoEncontrado->quantidadeEstoque);
            printf("------------------------------------------------------------\n");

            int qtd;

            printf("\nQuantidade para venda: ");
            qtd = lerInteiro();

            char atletaFederado;

            printf("Cliente e atleta federado? (S/N): ");
            scanf(" %c", &atletaFederado);

            if (atletaFederado == 'S' ||
                atletaFederado == 's')
            {
                float percentual;

                printf("Percentual de desconto: ");
                percentual = lerFloat();

                float novoPreco =
                    aplicarDescontoAtletaFederado(
                        produtoEncontrado,
                        percentual);

                printf("\nPreco com desconto: R$ %.2f\n",
                       novoPreco);
            }

            float valor =
                venderProdutoEsportivo(
                    produtoEncontrado,
                    qtd);

            if (valor == -1)
            {
                printf("\nEstoque insuficiente!\n");
            }
            else
            {
                printf("\n");
                printf("------------------------------------------------------------\n");
                printf("Venda realizada com sucesso!\n");
                printf("Valor total: R$ %.2f\n", valor);
                printf("Estoque restante: %d unidade(s)\n",
                       produtoEncontrado->quantidadeEstoque);
                printf("------------------------------------------------------------\n");
            }

            salvarProdutos(
                produtos,
                quantidade,
                "estoque.txt");

            break;
        }

        case 7:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                   RESERVA PARA EQUIPE                      \n");
            printf("============================================================\n\n");

            int codigo;

            printf("Digite o codigo do produto: ");
            codigo = lerInteiro();

            /*
             * Procura o produto pelo codigo.
             */
            ProdutoEsportivo *produtoEncontrado =
                buscarPorCodigo(
                    produtos,
                    quantidade,
                    codigo);

            if (produtoEncontrado == NULL)
            {
                printf("\nProduto nao encontrado!\n");
                break;
            }

            printf("\n---------------- PRODUTO ENCONTRADO -----------------------\n");
            printf("Nome:    %s\n", produtoEncontrado->nome);
            printf("Estoque: %d unidade(s)\n",
                   produtoEncontrado->quantidadeEstoque);
            printf("------------------------------------------------------------\n");

            int qtd;

            printf("\nQuantidade para reserva: ");
            qtd = lerInteiro();

            if (reservarParaEquipe(
                    produtoEncontrado,
                    qtd))
            {
                printf("\n");
                printf("------------------------------------------------------------\n");
                printf("Reserva realizada com sucesso!\n");
                printf("Estoque restante: %d unidade(s)\n",
                       produtoEncontrado->quantidadeEstoque);
                printf("------------------------------------------------------------\n");
            }
            else
            {
                printf("\nEstoque insuficiente!\n");
            }

            salvarProdutos(
                produtos,
                quantidade,
                "estoque.txt");

            break;
        }

        case 8:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                   NOVA COLECAO                             \n");
            printf("============================================================\n\n");

            int codigo;

            printf("Digite o codigo do produto: ");
            codigo = lerInteiro();

            ProdutoEsportivo *produtoEncontrado =
                buscarPorCodigo(
                    produtos,
                    quantidade,
                    codigo);

            if (produtoEncontrado == NULL)
            {
                printf("\nProduto nao encontrado!\n");
                break;
            }

            printf("\n---------------- PRODUTO ENCONTRADO -----------------------\n");
            printf("Nome:         %s\n", produtoEncontrado->nome);
            printf("Preco atual:  R$ %.2f\n", produtoEncontrado->preco);
            printf("Estoque atual: %d unidade(s)\n",
                   produtoEncontrado->quantidadeEstoque);
            printf("------------------------------------------------------------\n");

            int quantidadeRecebida;
            float novoPreco;

            printf("\nQuantidade recebida: ");
            quantidadeRecebida = lerInteiro();

            printf("Novo preco: R$ ");
            novoPreco = lerFloat();

            receberNovaColecao(
                produtoEncontrado,
                quantidadeRecebida,
                novoPreco);

            printf("\n");
            printf("------------------------------------------------------------\n");
            printf("Nova colecao registrada com sucesso!\n");
            printf("Novo estoque: %d unidade(s)\n",
                   produtoEncontrado->quantidadeEstoque);
            printf("Novo preco:   R$ %.2f\n",
                   produtoEncontrado->preco);
            printf("------------------------------------------------------------\n");

            salvarProdutos(
                produtos,
                quantidade,
                "estoque.txt");

            break;
        }

        case 9:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                RELATORIO POR MODALIDADE                    \n");
            printf("============================================================\n\n");

            char modalidade[30];

            printf("Digite a modalidade: ");
            scanf(" %29[^\n]", modalidade);

            relatorioPorModalidade(
                produtos,
                quantidade,
                modalidade);

            break;
        }

        case 10:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                 ORDENAR POR PRECO                          \n");
            printf("============================================================\n\n");

            ordenarPorPreco(
                produtos,
                quantidade);

            printf("Produtos ordenados do menor para o maior preco!\n\n");

            listarTodos(
                produtos,
                quantidade);

            break;
        }

        case 0:
        {
            printf("\n");
            printf("============================================================\n");
            printf("                 ENCERRANDO SISTEMA                         \n");
            printf("============================================================\n");
            printf("\nSaindo do sistema...\n");

            break;
        }

        default:
        {
            printf("\n");
            printf("------------------------------------------------------------\n");
            printf("Opcao invalida! Escolha uma opcao do menu.\n");
            printf("------------------------------------------------------------\n");

            break;
        }
        }

    } while (opcao != 0);

    salvarProdutos(
        produtos,
        quantidade,
        "estoque.txt");

    liberarProdutos(
        &produtos,
        &quantidade);

    return 0;
}