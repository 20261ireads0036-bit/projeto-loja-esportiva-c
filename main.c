#include "produto.h"
#include "estoque.h"
#include "validacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define LINHA_DUPLA "══════════════════════════════════════════════════════"
#define LINHA_SIMPLES "──────────────────────────────────────────────────────"

int main(void)
{
    // Define a codificação do terminal para permitir a exibição correta
    // de caracteres como "ç", "ã", "é" e outros acentos.
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Define o padrão numérico usado pelo programa.
    // Com "C", o programa trabalha internamente com ponto decimal.
    setlocale(LC_NUMERIC, "C");

    int opcao;

    // Ponteiro que vai guardar o endereço do vetor de produtos.
    // Inicialmente não aponta para nenhum espaço de memória.
    ProdutoEsportivo *produtos = NULL;

    // Guarda quantos produtos existem atualmente no vetor.
    int quantidade = 0;

    // Reserva espaço na memória para até 100 produtos.
    produtos = malloc(100 * sizeof(ProdutoEsportivo));

    // Verifica se a memória foi realmente reservada.
    // Se o malloc falhar, o programa não pode continuar trabalhando
    // com o vetor de produtos.
    if (produtos == NULL)
    {
        printf("\n[ERRO] Não foi possível alocar memória.\n\n");
        return 1;
    }

    // Carrega os produtos que já estavam salvos no arquivo TXT.
    // A função retorna a quantidade de produtos encontrados e carregados.
    quantidade = carregarProdutos(produtos, "estoque_esportivo.txt");

    // O menu continua aparecendo enquanto o usuário não escolher 0.
    do
    {
        printf("\n");
        printf("╔" LINHA_DUPLA "╗\n");
        printf("║                  VITÓRIA ESPORTES                    ║\n");
        printf("║                 Controle de Estoque                  ║\n");
        printf("╚" LINHA_DUPLA "╝\n\n");

        printf("   [1]  Cadastrar produto\n");
        printf("   [2]  Remover produto\n");
        printf("   [3]  Listar todos\n");
        printf("   [4]  Buscar por código\n");
        printf("   [5]  Vender produto\n");
        printf("   [6]  Reservar para equipe\n");
        printf("   [7]  Receber nova coleção\n");
        printf("   [8]  Relatório por modalidade\n");
        printf("   [9]  Ordenar por preço\n");
        printf("   [10] Buscar por faixa de preço\n");
        printf("   [0]  Sair\n");

        printf("\n" LINHA_SIMPLES "\n");
        printf(" Escolha uma opção: ");

        // Lê a opção escolhida pelo usuário.
        opcao = lerInteiro();

        // Dependendo da opção escolhida, uma operação diferente
        // do sistema será executada.
        switch (opcao)
        {
            // =========================================================
            // 1 - CADASTRAR PRODUTO
            // =========================================================
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

                // Verifica se já existe um produto com esse código.
                // Enquanto existir, o usuário precisa informar outro código.
                while (buscarPorCodigo(produtos, quantidade, codigo) != NULL)
                {
                    printf("\n [!] Esse código já está cadastrado!\n");
                    printf(" Digite um novo código: ");
                    codigo = lerInteiro();
                }

                // Lê os dados de texto do produto.
                // A função também impede que sejam inseridos números
                // nesses campos.
                lerTextoSemNumeros(" Nome: ", nome, sizeof(nome));
                lerTextoSemNumeros(" Modalidade: ", modalidade, sizeof(modalidade));
                lerTextoSemNumeros(" Marca: ", marca, sizeof(marca));

                printf(" Preço (R$): ");
                preco = lerFloat();

                // Garante que o preço informado não seja negativo.
                while (preco < 0)
                {
                    printf(" [!] O preço não pode ser negativo.\n");
                    printf(" Digite novamente: ");
                    preco = lerFloat();
                }

                printf(" Quantidade em estoque: ");
                quantidadeEstoque = lerInteiro();

                // Garante que a quantidade inicial também não seja negativa.
                while (quantidadeEstoque < 0)
                {
                    printf(" [!] A quantidade não pode ser negativa.\n");
                    printf(" Digite novamente: ");
                    quantidadeEstoque = lerInteiro();
                }

                // Cria um novo produto na memória usando os dados
                // informados pelo usuário.
                ProdutoEsportivo *novoProduto =
                    cadastrarProdutoEsportivo(
                        codigo,
                        nome,
                        modalidade,
                        marca,
                        preco,
                        quantidadeEstoque
                    );

                // Verifica se foi possível criar o produto.
                if (novoProduto == NULL)
                {
                    printf("\n [ERRO] Falha ao cadastrar o produto.\n\n");
                    break;
                }

                // Adiciona o produto criado ao vetor principal.
                // Como a função recebe o produto por valor, usamos *novoProduto
                // para acessar o conteúdo apontado pelo ponteiro.
                if (adicionarAoVetor(&produtos, &quantidade, *novoProduto))
                {
                    printf("\n [OK] Produto cadastrado com sucesso!\n\n");

                    // Salva imediatamente o estoque atualizado no arquivo.
                    salvarProdutos(
                        produtos,
                        quantidade,
                        "estoque_esportivo.txt"
                    );
                }
                else
                {
                    printf("\n [ERRO] Falha ao adicionar o produto ao estoque.\n\n");
                }

                // Libera a memória usada temporariamente pelo novo produto.
                free(novoProduto);

                break;
            }

            // =========================================================
            // 2 - REMOVER PRODUTO
            // =========================================================
            case 2:
            {
                int codigo;

                printf("\n" LINHA_DUPLA "\n");
                printf("                REMOVER PRODUTO\n");
                printf(LINHA_DUPLA "\n\n");

                printf(" Código do produto a ser removido: ");
                codigo = lerInteiro();

                // Procura o produto pelo código e, se encontrar,
                // remove o produto inteiro do vetor.
                if (removerProdutoEsportivo(&produtos, &quantidade, codigo))
                {
                    // Depois da remoção, salva o novo estado do estoque.
                    salvarProdutos(produtos, quantidade, "estoque_esportivo.txt");

                    printf("\n [OK] Produto removido com sucesso!\n\n");
                }
                else
                {
                    printf("\n [!] Produto não encontrado!\n\n");
                }

                break;
            }

            // =========================================================
            // 3 - LISTAR TODOS OS PRODUTOS
            // =========================================================
            case 3:
            {
                // Mostra todos os produtos que estão atualmente
                // armazenados no vetor.
                listarTodos(produtos, quantidade);

                printf("\n");
                break;
            }

            // =========================================================
            // 4 - BUSCAR PRODUTO POR CÓDIGO
            // =========================================================
            case 4:
            {
                int codigo;

                printf("\n" LINHA_DUPLA "\n");
                printf("                BUSCAR PRODUTO\n");
                printf(LINHA_DUPLA "\n\n");

                printf(" Código do produto: ");
                codigo = lerInteiro();

                // Procura no vetor um produto que tenha o código informado.
                // A função retorna o endereço do produto encontrado.
                ProdutoEsportivo *produtoEncontrado =
                    buscarPorCodigo(produtos, quantidade, codigo);

                // Se não encontrou nenhum produto, retorna NULL.
                if (produtoEncontrado == NULL)
                {
                    printf("\n [!] Produto não encontrado!\n\n");
                    break;
                }

                // Como encontramos o produto, usamos -> para acessar
                // seus dados através do ponteiro.
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

            // =========================================================
            // 5 - VENDER PRODUTO
            // =========================================================
            case 5:
            {
                int codigo;

                printf("\n" LINHA_DUPLA "\n");
                printf("                     VENDA\n");
                printf(LINHA_DUPLA "\n\n");

                printf(" Código do produto: ");
                codigo = lerInteiro();

                // Procura o produto que será vendido.
                ProdutoEsportivo *produtoEncontrado =
                    buscarPorCodigo(produtos, quantidade, codigo);

                // Impede a venda caso o código não exista.
                if (produtoEncontrado == NULL)
                {
                    printf("\n [!] Produto não encontrado!\n\n");
                    break;
                }

                // Mostra as informações do produto antes da venda.
                printf("\n" LINHA_SIMPLES "\n");
                printf(" Produto encontrado!\n");
                printf(LINHA_SIMPLES "\n");
                printf("   Nome ..........: %s\n", produtoEncontrado->nome);
                printf("   Preço .........: R$ %.2f\n", produtoEncontrado->preco);
                printf("   Estoque .......: %d un.\n", produtoEncontrado->quantidadeEstoque);
                printf(LINHA_SIMPLES "\n\n");

                int qtd;

                printf(" Quantidade para venda: ");
                qtd = lerInteiro();

                // A quantidade vendida precisa ser maior que zero.
                while (qtd <= 0)
                {
                    printf(" [!] A quantidade deve ser maior que zero.\n");
                    printf(" Digite novamente: ");
                    qtd = lerInteiro();
                }

                // Verifica se existe estoque suficiente para realizar a venda.
                if (qtd > produtoEncontrado->quantidadeEstoque)
                {
                    printf("\n [!] Estoque insuficiente!\n\n");
                    break;
                }

                char atletaFederado;

                printf(" O cliente é atleta federado? (S/N): ");
                scanf(" %c", &atletaFederado);
                limparBuffer();

                // Continua perguntando enquanto o usuário não informar
                // uma resposta válida: S ou N.
                while (atletaFederado != 'S' &&
                       atletaFederado != 's' &&
                       atletaFederado != 'N' &&
                       atletaFederado != 'n')
                {
                    printf(" [!] Opção inválida! Digite S ou N.\n");
                    printf(" O cliente é atleta federado? (S/N): ");
                    scanf(" %c", &atletaFederado);
                    limparBuffer();
                }

                // Começa considerando o preço normal do produto.
                float precoUnitario = produtoEncontrado->preco;

                // Se o cliente for atleta federado, será aplicado
                // um desconto informado pelo usuário.
                if (atletaFederado == 'S' || atletaFederado == 's')
                {
                    float percentual;

                    printf(" Percentual de desconto (%%): ");
                    percentual = lerFloat();

                    // O desconto precisa estar entre 0% e 100%.
                    while (percentual < 0 || percentual > 100)
                    {
                        printf(" [!] O desconto deve estar entre 0%% e 100%%.\n");
                        printf(" Digite novamente: ");
                        percentual = lerFloat();
                    }

                    // Calcula o preço do produto depois do desconto.
                    precoUnitario = aplicarDescontoAtletaFederado(
                        produtoEncontrado,
                        percentual
                    );

                    printf("\n Preço com desconto: R$ %.2f\n", precoUnitario);
                }

                // Retira do estoque a quantidade que foi vendida.
                produtoEncontrado->quantidadeEstoque -= qtd;

                // Calcula quanto o cliente deverá pagar pela venda inteira.
                float valor = precoUnitario * qtd;

                printf("\n" LINHA_SIMPLES "\n");
                printf(" [OK] Venda realizada com sucesso!\n");
                printf("      Valor total: R$ %.2f\n", valor);
                printf(LINHA_SIMPLES "\n\n");

                // Salva o estoque depois da alteração.
                salvarProdutos(produtos, quantidade, "estoque_esportivo.txt");

                break;
            }

            // =========================================================
            // 6 - RESERVAR PARA EQUIPE
            // =========================================================
            case 6:
            {
                int codigo;

                printf("\n" LINHA_DUPLA "\n");
                printf("                    RESERVA\n");
                printf(LINHA_DUPLA "\n\n");

                printf(" Código do produto: ");
                codigo = lerInteiro();

                // Procura o produto que será reservado.
                ProdutoEsportivo *produtoEncontrado =
                    buscarPorCodigo(produtos, quantidade, codigo);

                if (produtoEncontrado == NULL)
                {
                    printf("\n [!] Produto não encontrado!\n\n");
                    break;
                }

                printf("\n" LINHA_SIMPLES "\n");
                printf(" Produto encontrado!\n");
                printf(LINHA_SIMPLES "\n");
                printf("   Nome ..........: %s\n", produtoEncontrado->nome);
                printf("   Estoque .......: %d un.\n", produtoEncontrado->quantidadeEstoque);
                printf(LINHA_SIMPLES "\n\n");

                int qtd;

                printf(" Quantidade para reserva: ");
                qtd = lerInteiro();

                // Não permite reservar zero ou uma quantidade negativa.
                while (qtd <= 0)
                {
                    printf(" [!] A quantidade deve ser maior que zero.\n");
                    printf(" Digite novamente: ");
                    qtd = lerInteiro();
                }

                // Tenta retirar a quantidade solicitada do estoque
                // para fazer a reserva.
                if (reservarParaEquipe(produtoEncontrado, qtd))
                {
                    printf("\n [OK] Reserva realizada com sucesso!\n\n");
                }
                else
                {
                    printf("\n [!] Estoque insuficiente!\n\n");
                }

                // Salva o estoque após a alteração.
                salvarProdutos(produtos, quantidade, "estoque_esportivo.txt");

                break;
            }

            // =========================================================
            // 7 - RECEBER NOVA COLEÇÃO
            // =========================================================
            case 7:
            {
                int codigo;

                printf("\n" LINHA_DUPLA "\n");
                printf("                 NOVA COLEÇÃO\n");
                printf(LINHA_DUPLA "\n\n");

                printf(" Código do produto: ");
                codigo = lerInteiro();

                // Procura o produto que receberá novas unidades.
                ProdutoEsportivo *produtoEncontrado =
                    buscarPorCodigo(produtos, quantidade, codigo);

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
                printf("   Estoque atual .: %d un.\n", produtoEncontrado->quantidadeEstoque);
                printf(LINHA_SIMPLES "\n\n");

                int quantidadeRecebida;
                float novoPreco;

                printf(" Quantidade recebida: ");
                quantidadeRecebida = lerInteiro();

                // A quantidade recebida precisa ser maior que zero.
                while (quantidadeRecebida <= 0)
                {
                    printf(" [!] A quantidade deve ser maior que zero.\n");
                    printf(" Digite novamente: ");
                    quantidadeRecebida = lerInteiro();
                }

                printf(" Novo preço (R$): ");
                novoPreco = lerFloat();

                // O novo preço não pode ser negativo.
                while (novoPreco < 0)
                {
                    printf(" [!] O preço não pode ser negativo.\n");
                    printf(" Digite novamente: ");
                    novoPreco = lerFloat();
                }

                // Atualiza o estoque adicionando as novas unidades
                // e também atualiza o preço do produto.
                receberNovaColecao(
                    produtoEncontrado,
                    quantidadeRecebida,
                    novoPreco
                );

                printf("\n" LINHA_SIMPLES "\n");
                printf(" [OK] Nova coleção registrada com sucesso!\n");
                printf("      Novo estoque: %d un.\n", produtoEncontrado->quantidadeEstoque);
                printf("      Novo preço..: R$ %.2f\n", produtoEncontrado->preco);
                printf(LINHA_SIMPLES "\n\n");

                // Salva as alterações no arquivo.
                salvarProdutos(produtos, quantidade, "estoque_esportivo.txt");

                break;
            }

            // =========================================================
            // 8 - RELATÓRIO POR MODALIDADE
            // =========================================================
            case 8:
            {
                char modalidade[30];

                printf("\n" LINHA_DUPLA "\n");
                printf("            RELATÓRIO POR MODALIDADE\n");
                printf(LINHA_DUPLA "\n\n");

                // Pergunta qual modalidade o usuário deseja consultar.
                lerTextoSemNumeros(
                    " Modalidade: ",
                    modalidade,
                    sizeof(modalidade)
                );

                printf("\n");

                // Mostra os produtos que pertencem à modalidade informada.
                relatorioPorModalidade(produtos, quantidade, modalidade);

                printf("\n");

                break;
            }

            // =========================================================
            // 9 - ORDENAR PRODUTOS POR PREÇO
            // =========================================================
            case 9:
            {
                // Organiza os produtos do vetor de acordo com seus preços.
                ordenarPorPreco(produtos, quantidade);

                // Salva o vetor depois de reorganizado.
                salvarProdutos(produtos, quantidade, "estoque_esportivo.txt");

                printf("\n [OK] Produtos ordenados por preço!\n\n");

                break;
            }

            // =========================================================
            // 10 - BUSCAR POR FAIXA DE PREÇO
            // =========================================================
            case 10:
            {
                // A própria função pergunta a faixa de preço
                // e mostra os produtos que estão dentro dela.
                listarProdutosPorFaixaPreco(produtos, quantidade);

                break;
            }

            // =========================================================
            // 0 - SAIR
            // =========================================================
            case 0:
            {
                printf("\n" LINHA_SIMPLES "\n");
                printf("   Saindo do sistema... Até logo!\n");
                printf(LINHA_SIMPLES "\n\n");

                break;
            }

            // Caso o usuário digite qualquer número que não exista no menu.
            default:
            {
                printf("\n [!] Opção inválida! Tente novamente.\n\n");

                break;
            }
        }

    } while (opcao != 0);

    // Antes de encerrar, salva novamente o estoque.
    // Assim, qualquer alteração feita durante a execução
    // fica registrada no arquivo TXT.
    salvarProdutos(produtos, quantidade, "estoque_esportivo.txt");

    // Libera a memória usada pelo vetor de produtos.
    // Também atualiza a quantidade para indicar que não há mais produtos
    // sendo mantidos na memória.
    liberarProdutos(&produtos, &quantidade);

    // Indica ao sistema operacional que o programa terminou normalmente.
    return 0;
}