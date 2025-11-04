#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Item {
    char nome[30];
    int quantidade;
};

struct No {
    struct Item dados;
    struct No* proximo;
};

int contadorComparacoes = 0;

void inserirItem(struct Item inventario[], int *total) {
    if (*total >= 10) {
        printf("\nMochila cheia\n");
        return;
    }
    
    printf("\nDigite o nome do item: ");
    scanf("%s", inventario[*total].nome);
    
    printf("Digite a quantidade: ");
    scanf("%d", &inventario[*total].quantidade);
    
    (*total)++;
    printf("\nItem adicionado com sucesso\n");
}

void removerItem(struct Item inventario[], int *total) {
    if (*total == 0) {
        printf("\nMochila vazia\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\nDigite o nome do item a remover: ");
    scanf("%s", nomeBusca);
    
    int encontrado = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }
    
    if (encontrado == -1) {
        printf("\nItem nao encontrado\n");
        return;
    }
    
    for (int i = encontrado; i < *total - 1; i++) {
        inventario[i] = inventario[i + 1];
    }
    
    (*total)--;
    printf("\nItem removido com sucesso\n");
}

void listarItens(struct Item inventario[], int total) {
    if (total == 0) {
        printf("\nMochila vazia\n");
        return;
    }
    
    printf("\nITENS NA MOCHILA (VETOR)\n");
    for (int i = 0; i < total; i++) {
        printf("\n[%d] Nome: %s\n", i + 1, inventario[i].nome);
        printf("Quantidade: %d\n", inventario[i].quantidade);
    }
}

void buscarItem(struct Item inventario[], int total) {
    if (total == 0) {
        printf("\nMochila vazia\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    scanf("%s", nomeBusca);
    
    contadorComparacoes = 0;
    int encontrado = 0;
    
    for (int i = 0; i < total; i++) {
        contadorComparacoes++;
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", inventario[i].nome);
            printf("Quantidade: %d\n", inventario[i].quantidade);
            printf("Numero de comparacoes: %d\n", contadorComparacoes);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nItem nao encontrado\n");
        printf("Numero de comparacoes: %d\n", contadorComparacoes);
    }
}

void ordenarVetor(struct Item inventario[], int total) {
    int i, j;
    struct Item temp;
    
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (strcmp(inventario[j].nome, inventario[j + 1].nome) > 0) {
                temp = inventario[j];
                inventario[j] = inventario[j + 1];
                inventario[j + 1] = temp;
            }
        }
    }
    
    printf("\nVetor ordenado por nome\n");
}

void buscaBinaria(struct Item inventario[], int total) {
    if (total == 0) {
        printf("\nMochila vazia\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar (busca binaria): ");
    scanf("%s", nomeBusca);
    
    contadorComparacoes = 0;
    int inicio = 0;
    int fim = total - 1;
    int meio;
    
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        contadorComparacoes++;
        
        int comparacao = strcmp(inventario[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", inventario[meio].nome);
            printf("Quantidade: %d\n", inventario[meio].quantidade);
            printf("Numero de comparacoes: %d\n", contadorComparacoes);
            return;
        }
        
        if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    printf("\nItem nao encontrado\n");
    printf("Numero de comparacoes: %d\n", contadorComparacoes);
}

void inserirLista(struct No** inicio) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    
    if (novoNo == NULL) {
        printf("\nErro ao alocar memoria\n");
        return;
    }
    
    printf("\nDigite o nome do item: ");
    scanf("%s", novoNo->dados.nome);
    
    printf("Digite a quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    
    novoNo->proximo = NULL;
    
    if (*inicio == NULL) {
        *inicio = novoNo;
    } else {
        struct No* atual = *inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    
    printf("\nItem adicionado na lista\n");
}

void removerLista(struct No** inicio) {
    if (*inicio == NULL) {
        printf("\nLista vazia\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\nDigite o nome do item a remover: ");
    scanf("%s", nomeBusca);
    
    struct No* atual = *inicio;
    struct No* anterior = NULL;
    
    while (atual != NULL && strcmp(atual->dados.nome, nomeBusca) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("\nItem nao encontrado\n");
        return;
    }
    
    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    free(atual);
    printf("\nItem removido da lista\n");
}

void listarLista(struct No* inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia\n");
        return;
    }
    
    printf("\nITENS NA MOCHILA (LISTA ENCADEADA)\n");
    struct No* atual = inicio;
    int contador = 1;
    
    while (atual != NULL) {
        printf("\n[%d] Nome: %s\n", contador, atual->dados.nome);
        printf("Quantidade: %d\n", atual->dados.quantidade);
        atual = atual->proximo;
        contador++;
    }
}

void buscarLista(struct No* inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia\n");
        return;
    }
    
    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    scanf("%s", nomeBusca);
    
    contadorComparacoes = 0;
    struct No* atual = inicio;
    
    while (atual != NULL) {
        contadorComparacoes++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Numero de comparacoes: %d\n", contadorComparacoes);
            return;
        }
        atual = atual->proximo;
    }
    
    printf("\nItem nao encontrado\n");
    printf("Numero de comparacoes: %d\n", contadorComparacoes);
}

void liberarLista(struct No* inicio) {
    struct No* atual = inicio;
    struct No* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

int main(void) {
    struct Item inventario[10];
    int totalItens = 0;
    struct No* lista = NULL;
    int opcao, tipoEstrutura;
    
    printf("SISTEMA DE INVENTARIO - COMPARACAO DE ESTRUTURAS\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Trabalhar com VETOR\n");
        printf("2 - Trabalhar com LISTA ENCADEADA\n");
        printf("0 - Sair\n");
        printf("\nEscolha a estrutura: ");
        scanf("%d", &tipoEstrutura);
        
        if (tipoEstrutura == 1) {
            do {
                printf("\n--- MENU VETOR ---\n");
                printf("1 - Adicionar item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar item (sequencial)\n");
                printf("5 - Ordenar vetor\n");
                printf("6 - Buscar item (binaria)\n");
                printf("0 - Voltar\n");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao);
                
                switch (opcao) {
                    case 1:
                        inserirItem(inventario, &totalItens);
                        break;
                    case 2:
                        removerItem(inventario, &totalItens);
                        break;
                    case 3:
                        listarItens(inventario, totalItens);
                        break;
                    case 4:
                        buscarItem(inventario, totalItens);
                        break;
                    case 5:
                        ordenarVetor(inventario, totalItens);
                        break;
                    case 6:
                        buscaBinaria(inventario, totalItens);
                        break;
                    case 0:
                        printf("\nVoltando ao menu principal\n");
                        break;
                    default:
                        printf("\nOpcao invalida\n");
                }
            } while (opcao != 0);
            
        } else if (tipoEstrutura == 2) {
            do {
                printf("\n--- MENU LISTA ENCADEADA ---\n");
                printf("1 - Adicionar item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar item\n");
                printf("0 - Voltar\n");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao);
                
                switch (opcao) {
                    case 1:
                        inserirLista(&lista);
                        break;
                    case 2:
                        removerLista(&lista);
                        break;
                    case 3:
                        listarLista(lista);
                        break;
                    case 4:
                        buscarLista(lista);
                        break;
                    case 0:
                        printf("\nVoltando ao menu principal\n");
                        break;
                    default:
                        printf("\nOpcao invalida\n");
                }
            } while (opcao != 0);
            
        } else if (tipoEstrutura == 0) {
            printf("\nEncerrando sistema\n");
        } else {
            printf("\nOpcao invalida\n");
        }
        
    } while (tipoEstrutura != 0);
    
    liberarLista(lista);
    
    return 0;
}