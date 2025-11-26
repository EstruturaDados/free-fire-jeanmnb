#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
#define MAX_ITENS 10     // Capacidade máxima da mochila (Requisito: até 10 itens)
Item inventario[MAX_ITENS]; // O vetor (lista sequencial) que simula a mochila
int numItens = 0;           // Contador de itens atualmente na mochila

// --- Protótipos das Funções ---
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void exibirMenu();
int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
int opcao;

    // Loop principal do programa que exibe o menu e processa a escolha do jogador.
    // Garante a Usabilidade e clareza da interface.
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        // Leitura segura da opção
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de falha na leitura (caractere não numérico)
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1; // Define uma opção inválida para repetir o loop
        }

        printf("\n"); // Espaçamento para melhor usabilidade

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("👋 Jogo Encerrado. Inventario salvo com sucesso!\n");
                break;
            default:
                printf("⚠️ Opcao invalida. Tente novamente.\n");
        }
        
        // Separação visual após cada operação para manter a clareza
        if (opcao != 0) {
            printf("\n--- Inventario Atualizado ---\n");
            listarItens();
            printf("-----------------------------\n");
        }

    } while (opcao != 0);

    return 0;
}
// ---------------------------------

// --- Funções Obrigatórias ---

/**
 * @brief Exibe o menu de opções para o jogador.
 */
void exibirMenu() {
    printf("\n==== 🎒 Inventario (Mochila de Loot Inicial) ====\n");
    printf("1. ➕ Cadastrar Novo Item\n");
    printf("2. ➖ Remover Item (pelo nome)\n");
    printf("3. 📋 Listar Todos os Itens\n");
    printf("4. 🔎 Buscar Item (pelo nome)\n");
    printf("0. 🚪 Sair do Jogo\n");
    printf("================================================\n");
}

/**
 * @brief Cadastra um novo item no inventário (mochila).
 * Requisito: Cadastro de itens.
 */
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("❌ Mochila cheia! Capacidade maxima de %d itens atingida.\n", MAX_ITENS);
        return;
    }

    Item novoItem;

    printf("--- Cadastro de Novo Item ---\n");
    
    // Leitura do Nome (string)
    printf("Digite o nome do item (max 29 caracteres): ");
    // Uso de scanf("%29s") para ler strings sem espaços e evitar buffer overflow
    // Nota: fgets() seria mais robusto para strings com espaço, mas requer limpeza de buffer.
    if (scanf("%29s", novoItem.nome) != 1) {
         printf("⚠️ Erro ao ler o nome.\n");
         return;
    }
    
    // Leitura do Tipo (string)
    printf("Digite o tipo do item (ex: arma, municao, cura, ferramenta - max 19 caracteres): ");
    if (scanf("%19s", novoItem.tipo) != 1) {
         printf("⚠️ Erro ao ler o tipo.\n");
         return;
    }

    // Leitura da Quantidade (inteiro)
    printf("Digite a quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade <= 0) {
        printf("⚠️ Quantidade invalida. O item nao sera adicionado.\n");
        // Limpa o buffer de entrada em caso de erro de leitura (caractere não numérico)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    // Copia o novo item para a próxima posição livre no vetor
    inventario[numItens] = novoItem;
    numItens++; // Incrementa o contador de itens
    
    printf("✅ Item '%s' cadastrado com sucesso na mochila!\n", novoItem.nome);
}

/**
 * @brief Remove um item do inventário pelo nome.
 * Requisito: Remoção de itens.
 */
void removerItem() {
    if (numItens == 0) {
        printf("❌ A mochila esta vazia. Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("--- Remocao de Item ---\n");
    printf("Digite o nome do item a ser removido (max 29 caracteres): ");
    if (scanf("%29s", nomeBusca) != 1) {
         printf("⚠️ Erro ao ler o nome.\n");
         return;
    }

    int i, encontrado = 0;
    
    // Percorre o vetor para encontrar o item (busca sequencial implícita)
    for (i = 0; i < numItens; i++) {
        // strcmp retorna 0 se as strings forem iguais (caso-sensível)
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            // Item encontrado
            encontrado = 1;
            
            // Reorganiza o vetor (Remoção):
            // Desloca todos os itens subsequentes uma posição para a esquerda,
            // sobrescrevendo o item a ser removido.
            for (int j = i; j < numItens - 1; j++) {
                inventario[j] = inventario[j+1];
            }
            
            numItens--; // Decrementa o contador de itens
            printf("✅ Item '%s' removido com sucesso da mochila.\n", nomeBusca);
            return; // Sai da função após a remoção
        }
    }

    if (!encontrado) {
        printf("⚠️ Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

/**
 * @brief Lista todos os itens atualmente registrados no inventário.
 * Requisito: Listagem dos itens registrados.
 */
void listarItens() {
    if (numItens == 0) {
        printf("📦 A mochila esta vazia.\n");
        return;
    }

    printf("==== Itens na Mochila (%d/%d) ====\n", numItens, MAX_ITENS);
    
    // Laço 'for' para percorrer o vetor e exibir os dados de cada struct Item.
    for (int i = 0; i < numItens; i++) {
        printf("Posicao %02d | Nome: %-15s | Tipo: %-10s | Quantidade: %d\n", 
               i, 
               inventario[i].nome, 
               inventario[i].tipo, 
               inventario[i].quantidade);
    }
    printf("======================================\n");
}

/**
 * @brief Busca um item no inventário pelo nome (Busca Sequencial).
 * Requisito: Busca sequencial.
 */
void buscarItem() {
    if (numItens == 0) {
        printf("❌ A mochila esta vazia. Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("--- Busca de Item ---\n");
    printf("Digite o nome do item a ser buscado (max 29 caracteres): ");
    if (scanf("%29s", nomeBusca) != 1) {
         printf("⚠️ Erro ao ler o nome.\n");
         return;
    }

    int encontrado = 0;

    // Implementação da BUSCA SEQUENCIAL:
    // Percorre o vetor Item por Item, comparando o nome de cada elemento.
    for (int i = 0; i < numItens; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            // Item encontrado
            encontrado = 1;
            printf("\n✅ Item ENCONTRADO (Posicao %d):\n", i);
            printf("  - Nome: %s\n", inventario[i].nome);
            printf("  - Tipo: %s\n", inventario[i].tipo);
            printf("  - Quantidade: %d\n", inventario[i].quantidade);
            // Poderia continuar o loop para encontrar duplicatas, mas paramos no primeiro.
            break; 
        }
    }

    if (!encontrado) {
        printf("⚠️ Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}
    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[30];      // Nome do item (ex: Pistola, Kit Médico)
    char tipo[20];      // Tipo do item (ex: arma, munição, cura, ferramenta)
    int quantidade;     // Quantidade do item
} Item;
// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
