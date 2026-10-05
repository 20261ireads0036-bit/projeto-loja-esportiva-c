#include "produto.h"
#include "estoque.h"
#include "validacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define LINHA_DUPLA "══════════════════════════════════════════════════════"
#define LINHA_SIMPLES "──────────────────────────────────────────────────────"

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
        printf("\n[ERRO] Não foi possível alocar memória.\n\n");
        return 1;
    }

    quantidade = carregarProdutos(produtos, "estoque.txt");

    do
    {
        printf("\n");
        printf("╔" LINHA_DUPLA "╗\n");
        printf("║                  VITÓRIA ESPORTES                    ║\n");
        printf("║                 Controle de Estoque                  ║\n");
        printf("╚" LINHA_DUPLA "╝\n");
        printf("\n");

        printf("   [1]  Cadastrar produto\n");
        printf("   [2]  Remover produto\n");
        printf("   [3]  Listar todos\n");
        printf("   [4]  Buscar por código\n");
        printf("   [5]  Vender produto\n");
        printf("   [6]  Reservar para equipe\n");
        printf("   [7]  Receber nova coleção\n");
        printf("   [8]  Relatório por modalidade\n");
        printf("   [9] Ordenar por preço\n");
        printf("   [10] Buscar por faixa de preço\n");
        printf("   [0]  Sair\n");

        printf("\n" LINHA_SIMPLES "\n");
        printf(" Escolha uma opção: ");
        opcao = lerInteiro();

        switch (opcao)
        {
        case 1:
        {
            int codigo;
            char nome[50];
            char modalidade[30];
            char marca[30];
            float preco;
            int quantidadeEstoque;

            printf("\n" LINHA_DUPLA "\n");
            printf("               CADASTRAR PRODUTO\n");
            printf(LINHA_DUPLA "\n\n");

            printf(" Código: ");
            codigo = lerInteiro();

            while (buscarPorCodigo(produtos, quantidade, codigo) != NULL)
            {
                printf("\n [!] Esse código já está cadastrado!\n\n");
                printf(" Digite um novo código: ");

                codigo = lerInteiro();
            }

            printf(" Nome: ");
            scanf(" %49[^\n]", nome);

            printf(" Modalidade: ");
            scanf(" %29[^\n]", modalidade);

            printf(" Marca: ");
            scanf(" %29[^\n]", marca);

            printf(" Preço (R$): ");
            preco = lerFloat();

            printf(" Quantidade em estoque: ");
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
                printf("\n [ERRO] Falha ao cadastrar o produto.\n\n");
                break;
            }

            if (adicionarAoVetor(
                    &produtos,
                    &quantidade,
                    *novoProduto))
            {
                printf("\n [OK] Produto cadastrado com sucesso!\n\n");

                salvarProdutos(
                    produtos,
                    quantidade,
                    "estoque.txt");

                break;
            }
            else
            {
                printf("\n [ERRO] Falha ao adicionar o produto ao estoque.\n\n");
            }

            free(novoProduto);

            break;
        }

        case 2:
        {
            int codigo;

            printf("\n" LINHA_DUPLA "\n");
            printf("                REMOVER PRODUTO\n");
            printf(LINHA_DUPLA "\n\n");

            printf(" Código do produto a ser removido: ");

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

                printf("\n [OK] Produto removido com sucesso!\n\n");
            }
            else
            {
                printf("\n [!] Produto não encontrado!\n\n");
            }

            break;
        }

        case 3:
        {

            listarTodos(
                produtos,
                quantidade);

            printf("\n");

            break;
        }

        case 4:
        {
            int codigo;

            printf("\n" LINHA_DUPLA "\n");
            printf("                BUSCAR PRODUTO\n");
            printf(LINHA_DUPLA "\n\n");

            printf(" Código do produto: ");

            codigo = lerInteiro();

            ProdutoEsportivo *produtoEncontrado =
                buscarPorCodigo(
                    produtos,
                    quantidade,
                    codigo);

            if (produtoEncontrado == NULL)
            {
                printf("\n [!] Produto não encontrado!\n\n");
                break;
            }

            printf("\n" LINHA_SIMPLES "\n");
            printf("              PRODUTO ENCONTRADO\n");
            printf(LINHA_SIMPLES "\n\n");
            printf("   Código ........: %d\n", produtoEncontrado->codigo);
            printf("   Nome ..........: %s\n", produtoEncontrado->nome);
            printf("   Modalidade ....: %s\n", produtoEncontrado->modalidade);
            printf("   Marca .........: %s\n", produtoEncontrado->marca);
            printf("   Preço .........: R$ %.2f\n", produtoEncontrado->preco);
            printf("   Estoque .......: %d un.\n", produtoEncontrado->quantidadeEstoque);
            printf("\n" LINHA_SIMPLES "\n\n");

            break;
        }

        case 5:
        {
            int codigo;

            printf("\n" LINHA_DUPLA "\n");
            printf("                     VENDA\n");
            printf(LINHA_DUPLA "\n\n");

            printf(" Código do produto: ");
            codigo = lerInteiro();

            ProdutoEsportivo *produtoEncontrado =
                buscarPorCodigo(
                    produtos,
                    quantidade,
                    codigo);

            if (produtoEncontrado == NULL)
            {
                printf("\n [!] Produto não encontrado!\n\n");
                break;
            }

            printf("\n" LINHA_SIMPLES "\n");
            printf(" Produto encontrado!\n");
            printf(LINHA_SIMPLES "\n");
            printf("   Nome ..........: %s\n", produtoEncontrado->nome);
            printf("   Preço .........: R$ %.2f\n", produtoEncontrado->preco);
            printf("   Estoque .......: %d un.\n",
                   produtoEncontrado->quantidadeEstoque);
            printf(LINHA_SIMPLES "\n\n");

            int qtd;

            printf(" Quantidade para venda: ");
            qtd = lerInteiro();

            char atletaFederado;

            printf(" O cliente é atleta federado? (S/N): ");
            scanf(" %c", &atletaFederado);

            if (atletaFederado == 'S' ||
                atletaFederado == 's')
            {
                float percentual;

                printf(" Percentual de desconto (%%): ");
                percentual = lerFloat();

                float novoPreco =
                    aplicarDescontoAtletaFederado(
                        produtoEncontrado,
                        percentual);

                printf(
                    "\n Preço com desconto: R$ %.2f\n",
                    novoPreco);
            }

            float valor =
                venderProdutoEsportivo(
                    produtoEncontrado,
                    qtd);

            if (valor == -1)
            {
                printf("\n [!] Estoque insuficiente!\n\n");
            }
            else
            {
                printf("\n" LINHA_SIMPLES "\n");
                printf(" [OK] Venda realizada com sucesso!\n");
                printf("      Valor total: R$ %.2f\n",
                       valor);
                printf(LINHA_SIMPLES "\n\n");
            }

            salvarProdutos(
                produtos,
                quantidade,
                "estoque.txt");

            break;
        }

        case 6:
        {
            int codigo;

            printf("\n" LINHA_DUPLA "\n");
            printf("                    RESERVA\n");
            printf(LINHA_DUPLA "\n\n");

            printf(" Código do produto: ");
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
                printf("\n [!] Produto não encontrado!\n\n");
                break;
            }

            printf("\n" LINHA_SIMPLES "\n");
            printf(" Produto encontrado!\n");
            printf(LINHA_SIMPLES "\n");
            printf("   Nome ..........: %s\n", produtoEncontrado->nome);
            printf("   Estoque .......: %d un.\n",
                   produtoEncontrado->quantidadeEstoque);
            printf(LINHA_SIMPLES "\n\n");

            int qtd;

            printf(" Quantidade para reserva: ");
            qtd = lerInteiro();

            if (reservarParaEquipe(
                    produtoEncontrado,
                    qtd))
            {
                printf("\n [OK] Reserva realizada com sucesso!\n\n");
            }
            else
            {
                printf("\n [!] Estoque insuficiente!\n\n");
            }

            salvarProdutos(
                produtos,
                quantidade,
                "estoque.txt");

            break;
        }

        case 7:
        {
            int codigo;

            printf("\n" LINHA_DUPLA "\n");
            printf("                 NOVA COLEÇÃO\n");
            printf(LINHA_DUPLA "\n\n");

            printf(" Código do produto: ");
            codigo = lerInteiro();

            ProdutoEsportivo *produtoEncontrado =
                buscarPorCodigo(
                    produtos,
                    quantidade,
                    codigo);

            if (produtoEncontrado == NULL)
            {
                printf("\n [!] Produto não encontrado!\n\n");
                break;
            }

            printf("\n" LINHA_SIMPLES "\n");
            printf(" Produto encontrado!\n");
            printf(LINHA_SIMPLES "\n");
            printf("   Nome ..........: %s\n", produtoEncontrado->nome);
            printf("   Preço atual ...: R$ %.2f\n", produtoEncontrado->preco);
            printf("   Estoque atual .: %d un.\n",
                   produtoEncontrado->quantidadeEstoque);
            printf(LINHA_SIMPLES "\n\n");

            int quantidadeRecebida;
            float novoPreco;

            printf(" Quantidade recebida: ");
            quantidadeRecebida = lerInteiro();

            printf(" Novo preço (R$): ");
            novoPreco = lerFloat();

            receberNovaColecao(
                produtoEncontrado,
                quantidadeRecebida,
                novoPreco);

            printf("\n" LINHA_SIMPLES "\n");
            printf(" [OK] Nova coleção registrada com sucesso!\n");
            printf("      Novo estoque: %d un.\n",
                   produtoEncontrado->quantidadeEstoque);
            printf("      Novo preço..: R$ %.2f\n",
                   produtoEncontrado->preco);
            printf(LINHA_SIMPLES "\n\n");

            salvarProdutos(
                produtos,
                quantidade,
                "estoque.txt");

            break;
        }
        case 8:
        {
            char modalidade[30];

            printf("\n" LINHA_DUPLA "\n");
            printf("            RELATÓRIO POR MODALIDADE\n");
            printf(LINHA_DUPLA "\n\n");

            printf(" Modalidade: ");
            scanf(" %29[^\n]", modalidade);

            printf("\n");

            relatorioPorModalidade(
                produtos,
                quantidade,
                modalidade);

            printf("\n");

            break;
        }
        case 9:
        {

            printf("\n [OK] Produtos ordenados por preço!\n");

            ordenarPorPreco(
                produtos,
                quantidade);

            printf("\n");

            break;
        }
        case 10:
        {
            listarProdutosPorFaixaPreco(produtos, quantidade);
            break;
        }

        case 0:
        {
            printf("\n" LINHA_SIMPLES "\n");
            printf("   Saindo do sistema... Até logo!\n");
            printf(LINHA_SIMPLES "\n\n");

            break;
        }

        default:
        {
            printf("\n [!] Opção inválida! Tente novamente.\n\n");

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
