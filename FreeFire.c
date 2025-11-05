#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

int comparacoes = 0;

void cadastrarComponente(struct Componente componentes[], int *total) {
    if (*total >= 20) {
        printf("\nLimite de componentes atingido\n");
        return;
    }
    
    printf("\nNome do componente: ");
    scanf("%s", componentes[*total].nome);
    
    printf("Tipo (estrutural/eletronico/energia): ");
    scanf("%s", componentes[*total].tipo);
    
    printf("Prioridade (1-5): ");
    scanf("%d", &componentes[*total].prioridade);
    
    (*total)++;
    printf("\nComponente cadastrado\n");
}

void mostrarComponentes(struct Componente componentes[], int total) {
    if (total == 0) {
        printf("\nNenhum componente cadastrado\n");
        return;
    }
    
    printf("\n========== LISTA DE COMPONENTES ==========\n");
    for (int i = 0; i < total; i++) {
        printf("\n[%d] Nome: %s\n", i + 1, componentes[i].nome);
        printf("    Tipo: %s\n", componentes[i].tipo);
        printf("    Prioridade: %d\n", componentes[i].prioridade);
    }
    printf("\n==========================================\n");
}

void bubbleSortNome(struct Componente componentes[], int total) {
    comparacoes = 0;
    clock_t inicio = clock();
    
    int i, j;
    struct Componente temp;
    
    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\nBubble Sort por NOME concluido\n");
    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempo);
}

void insertionSortTipo(struct Componente componentes[], int total) {
    comparacoes = 0;
    clock_t inicio = clock();
    
    int i, j;
    struct Componente chave;
    
    for (i = 1; i < total; i++) {
        chave = componentes[i];
        j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j = j - 1;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\nInsertion Sort por TIPO concluido\n");
    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempo);
}

void selectionSortPrioridade(struct Componente componentes[], int total) {
    comparacoes = 0;
    clock_t inicio = clock();
    
    int i, j, indiceMenor;
    struct Componente temp;
    
    for (i = 0; i < total - 1; i++) {
        indiceMenor = i;
        
        for (j = i + 1; j < total; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        
        if (indiceMenor != i) {
            temp = componentes[i];
            componentes[i] = componentes[indiceMenor];
            componentes[indiceMenor] = temp;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\nSelection Sort por PRIORIDADE concluido\n");
    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo: %.6f segundos\n", tempo);
}

void buscaBinariaNome(struct Componente componentes[], int total) {
    if (total == 0) {
        printf("\nNenhum componente cadastrado\n");
        return;
    }
    
    char busca[30];
    printf("\nDigite o nome do componente-chave: ");
    scanf("%s", busca);
    
    comparacoes = 0;
    int esquerda = 0;
    int direita = total - 1;
    int meio;
    
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        comparacoes++;
        
        int resultado = strcmp(componentes[meio].nome, busca);
        
        if (resultado == 0) {
            printf("\n*** COMPONENTE-CHAVE ENCONTRADO ***\n");
            printf("Nome: %s\n", componentes[meio].nome);
            printf("Tipo: %s\n", componentes[meio].tipo);
            printf("Prioridade: %d\n", componentes[meio].prioridade);
            printf("Comparacoes na busca: %d\n", comparacoes);
            printf("\nTorre de fuga pode ser montada!\n");
            return;
        }
        
        if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    printf("\nComponente nao encontrado\n");
    printf("Comparacoes na busca: %d\n", comparacoes);
}

void removerComponente(struct Componente componentes[], int *total) {
    if (*total == 0) {
        printf("\nNenhum componente para remover\n");
        return;
    }
    
    char busca[30];
    printf("\nNome do componente a remover: ");
    scanf("%s", busca);
    
    int posicao = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(componentes[i].nome, busca) == 0) {
            posicao = i;
            break;
        }
    }
    
    if (posicao == -1) {
        printf("\nComponente nao encontrado\n");
        return;
    }
    
    for (int i = posicao; i < *total - 1; i++) {
        componentes[i] = componentes[i + 1];
    }
    
    (*total)--;
    printf("\nComponente removido\n");
}

int main(void) {
    struct Componente componentes[20];
    int totalComponentes = 0;
    int opcao;
    
    printf("======================================\n");
    printf("  SISTEMA DE TORRE DE FUGA - v1.0\n");
    printf("======================================\n");
    
    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Remover componente\n");
        printf("4 - Ordenar por NOME (Bubble Sort)\n");
        printf("5 - Ordenar por TIPO (Insertion Sort)\n");
        printf("6 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("7 - Buscar componente-chave (Busca Binaria)\n");
        printf("0 - Sair\n");
        printf("====================================\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrarComponente(componentes, &totalComponentes);
                break;
                
            case 2:
                mostrarComponentes(componentes, totalComponentes);
                break;
                
            case 3:
                removerComponente(componentes, &totalComponentes);
                break;
                
            case 4:
                if (totalComponentes == 0) {
                    printf("\nNenhum componente para ordenar\n");
                } else {
                    bubbleSortNome(componentes, totalComponentes);
                    mostrarComponentes(componentes, totalComponentes);
                }
                break;
                
            case 5:
                if (totalComponentes == 0) {
                    printf("\nNenhum componente para ordenar\n");
                } else {
                    insertionSortTipo(componentes, totalComponentes);
                    mostrarComponentes(componentes, totalComponentes);
                }
                break;
                
            case 6:
                if (totalComponentes == 0) {
                    printf("\nNenhum componente para ordenar\n");
                } else {
                    selectionSortPrioridade(componentes, totalComponentes);
                    mostrarComponentes(componentes, totalComponentes);
                }
                break;
                
            case 7:
                printf("\nATENCAO: O vetor precisa estar ordenado por NOME!\n");
                printf("Use a opcao 4 antes de buscar.\n");
                buscaBinariaNome(componentes, totalComponentes);
                break;
                
            case 0:
                printf("\nEncerrando sistema...\n");
                printf("Boa sorte na fuga!\n");
                break;
                
            default:
                printf("\nOpcao invalida\n");
        }
        
    } while (opcao != 0);
    
    return 0;
}