#include <stdio.h>
#include <stdlib.h> // Necessário para malloc e free
#include <stdbool.h>
#include <string.h>

// --- ESTRUTURAS ---
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
    int vida; 
} Jogador;

// --- FUNÇÕES DE CÓPIA ---
void copiarArray(int original[], int copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) copia[i] = original[i];
}
void copiarJogadores(Jogador original[], Jogador copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) copia[i] = original[i];
}

// --- FUNÇÕES DE VALIDAÇÃO ---
bool validarOrdenacao(int arr[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

bool validarOrdenacaoJogadoresPorPontuacao(Jogador arr[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (arr[i].pontuacao > arr[i + 1].pontuacao) return false;
        if (arr[i].pontuacao == arr[i + 1].pontuacao && arr[i].id > arr[i + 1].id) return false;
    }
    return true;
}

// (Omiti as outras validações no topo por brevidade, mas elas seguem a mesma lógica)

// --- ALGORITMOS ANTERIORES (Resumidos para manter a central limpa) ---
// SELECTION, INSERTION e BUBBLE SORT continuam disponíveis se chamados.

// --- PARTE 7: MERGE SORT COMPLETO (NUMÉRICO E ESTRUTURAS) ---

// 1. MERGE SORT PARA NÚMEROS
void mesclarNumerico(int arr[], int inicio, int meio, int fim, int temp[], int *comparacoes) {
    int i = inicio, j = meio + 1, k = inicio;

    while (i <= meio && j <= fim) {
        (*comparacoes)++;
        // O uso de <= garante a estabilidade e a preservação de elementos repetidos
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= meio) temp[k++] = arr[i++];
    while (j <= fim) temp[k++] = arr[j++];
    for (int idx = inicio; idx <= fim; idx++) arr[idx] = temp[idx];
}

void mergeSortRecursivoNumerico(int arr[], int inicio, int fim, int temp[], int *comparacoes) {
    // Caso-base: intervalos com zero ou um elemento já estão ordenados
    if (inicio >= fim) return; 

    int meio = inicio + (fim - inicio) / 2;
    mergeSortRecursivoNumerico(arr, inicio, meio, temp, comparacoes); // Ordena metade esquerda
    mergeSortRecursivoNumerico(arr, meio + 1, fim, temp, comparacoes); // Ordena metade direita
    mesclarNumerico(arr, inicio, meio, fim, temp, comparacoes); // Combina as metades
}

// Wrapper (Encapsulador) para gerenciar a memória auxiliar
void mergeSortNumerico(int arr[], int tamanho, int *comparacoes) {
    *comparacoes = 0;
    // Alocação dinâmica de memória auxiliar
    int *temp = (int *)malloc(tamanho * sizeof(int));
    if (temp != NULL) {
        mergeSortRecursivoNumerico(arr, 0, tamanho - 1, temp, comparacoes);
        free(temp); // Liberação de memória auxiliar após o uso
    } else {
        printf("Erro de alocacao de memoria!\n");
    }
}

// 2. MERGE SORT PARA ESTRUTURAS (JOGADORES)

// Critério explícito para ordenação de estruturas (Pontuação Crescente -> ID Crescente)
bool deveVirAntesOuIgual(Jogador a, Jogador b) {
    if (a.pontuacao < b.pontuacao) return true;
    if (a.pontuacao == b.pontuacao && a.id <= b.id) return true;
    return false;
}

void mesclarJogadores(Jogador arr[], int inicio, int meio, int fim, Jogador temp[], int *comparacoes) {
    int i = inicio, j = meio + 1, k = inicio;

    while (i <= meio && j <= fim) {
        (*comparacoes)++;
        // Aplicação do critério explícito
        if (deveVirAntesOuIgual(arr[i], arr[j])) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= meio) temp[k++] = arr[i++];
    while (j <= fim) temp[k++] = arr[j++];
    for (int idx = inicio; idx <= fim; idx++) arr[idx] = temp[idx];
}

void mergeSortRecursivoJogadores(Jogador arr[], int inicio, int fim, Jogador temp[], int *comparacoes) {
    if (inicio >= fim) return; // Caso-base

    int meio = inicio + (fim - inicio) / 2;
    mergeSortRecursivoJogadores(arr, inicio, meio, temp, comparacoes);
    mergeSortRecursivoJogadores(arr, meio + 1, fim, temp, comparacoes);
    mesclarJogadores(arr, inicio, meio, fim, temp, comparacoes);
}

void mergeSortJogadores(Jogador arr[], int tamanho, int *comparacoes) {
    *comparacoes = 0;
    Jogador *temp = (Jogador *)malloc(tamanho * sizeof(Jogador));
    if (temp != NULL) {
        mergeSortRecursivoJogadores(arr, 0, tamanho - 1, temp, comparacoes);
        free(temp); // Liberação da memória
    } else {
        printf("Erro de alocacao de memoria para Jogadores!\n");
    }
}

// --- FUNÇÕES DE IMPRESSÃO ---
void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) printf("%d ", arr[i]);
    printf("\n");
}

void imprimirJogadores(Jogador arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("[ID: %d | Nome: %-8s | Pontos: %3d | Vida: %3d]\n", arr[i].id, arr[i].nome, arr[i].pontuacao, arr[i].vida);
    }
}

// --- CENTRAL (main) ---
int main() {
    int tamanhoNum = 10;
    // O array possui repetições propositais de número (ex: o '34' inserido) para provar que nada se perde
    int originalNum[] = {45, 12, 78, 3, 99, 21, 5, 34, 34, 8};
    int copiaMergeNum[10];

    int tamanhoJog = 6;
    // Jogadores com pontuações repetidas
    Jogador originalJog[] = {
        {3, "Carlos", 150, 80},
        {1, "Ana", 200, 100},
        {4, "Beatriz", 150, 45},
        {2, "Ana", 100, 60},      
        {6, "Daniel", 100, 25},
        {5, "Carlos", 200, 95}    
    };
    Jogador copiaMergeJog[6];

    copiarArray(originalNum, copiaMergeNum, tamanhoNum);
    copiarJogadores(originalJog, copiaMergeJog, tamanhoJog);

    int compMergeNum = 0;
    int compMergeJog = 0;

    printf("=================================================\n");
    printf("        CENTRAL DE ORDENACAO DO LABORATORIO      \n");
    printf("=================================================\n\n");

    // TESTE 1: MERGE SORT NUMÉRICO
    printf("--- PARTE 7A: MERGE SORT COMPLETO (NUMERICO) ---\n");
    printf("Entrada (com repeticao): ");
    imprimirArray(copiaMergeNum, tamanhoNum);

    mergeSortNumerico(copiaMergeNum, tamanhoNum, &compMergeNum);

    printf("Ordenado               : ");
    imprimirArray(copiaMergeNum, tamanhoNum);
    printf("Comparacoes: %d\n", compMergeNum);
    printf("Validacao da saida contra a central: %s\n\n", validarOrdenacao(copiaMergeNum, tamanhoNum) ? "SUCESSO" : "FALHA");

    // TESTE 2: MERGE SORT ESTRUTURAS
    printf("--- PARTE 7B: MERGE SORT COMPLETO (ESTRUTURAS) ---\n");
    printf("Entrada (Jogadores originais):\n");
    imprimirJogadores(copiaMergeJog, tamanhoJog);

    mergeSortJogadores(copiaMergeJog, tamanhoJog, &compMergeJog);

    printf("\nOrdenado por Pontuacao (Desempate por ID):\n");
    imprimirJogadores(copiaMergeJog, tamanhoJog);
    printf("Comparacoes: %d\n", compMergeJog);
    printf("Validacao da saida contra a central: %s\n", validarOrdenacaoJogadoresPorPontuacao(copiaMergeJog, tamanhoJog) ? "SUCESSO" : "FALHA");

    return 0;
}