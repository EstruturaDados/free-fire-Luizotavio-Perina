#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Item {
    char nome[30];
    int quantidade;
};

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
    
    printf("\nITENS NA MOCHILA\n");
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
    
    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", inventario[i].nome);            
            printf("Quantidade: %d\n", inventario[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nItem nao encontrado\n");
    }
}

int main(void) {
    struct Item inventario[10];
    int totalItens = 0;
    int opcao;
    
    printf("SISTEMA DE INVENTARIO\n");
    
    do {
        printf("\n1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
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
            case 0:
                printf("\nEncerrando sistema\n");
                break;
            default:
                printf("\nOpcao invalida\n");
        }
    } while (opcao != 0);
    
    return 0;
}