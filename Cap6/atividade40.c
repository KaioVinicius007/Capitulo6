#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> // Necessário para inicializar o gerador aleatório

// --- ESTRUTURAS ---
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
    int vida; 
} Jogador;

// --- UTILITÁRIOS ---
void copiarArray(int original[], int copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) copia[i] = original[i];
}

void copiarJogadores(Jogador original[], Jogador copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) copia[i] = original[i];
}

bool deveVirAntesOuIgual(Jogador a, Jogador b) {
    if (a.pontuacao < b.pontuacao) return true;
    if (a.pontuacao == b.pontuacao && a.id <= b.id) return true;
    return false;
}

// --- ALGORITMOS DE ORDENAÇÃO (COM MÉTRICAS) ---

// 1. SELECTION SORT (JOGADORES)
void selectionSortJogadores(Jogador arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0; *trocas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;
            if (deveVirAntesOuIgual(arr[j], arr[menor])) menor = j;
        }
        if (menor != i) {
            Jogador temp = arr[i]; arr[i] = arr[menor]; arr[menor] = temp;
            (*trocas)++;
        }
    }
}

// 2. INSERTION SORT (JOGADORES)
void insertionSortJogadores(Jogador arr[], int tamanho, int *comparacoes, int *deslocamentos) {
    *comparacoes = 0; *deslocamentos = 0;
    for (int i = 1; i < tamanho; i++) {
        Jogador chave = arr[i]; 
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (!deveVirAntesOuIgual(arr[j], chave)) {
                arr[j + 1] = arr[j]; 
                (*deslocamentos)++;
                j--;
            } else break;
        }
        arr[j + 1] = chave;
    }
}

// 3. BUBBLE SORT (JOGADORES)
void bubbleSortJogadores(Jogador arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0; *trocas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            (*comparacoes)++;
            if (!deveVirAntesOuIgual(arr[j], arr[j + 1])) {
                Jogador temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
                (*trocas)++; trocou = true;
            }
        }
        if (!trocou) break;
    }
}

// 4. MERGE SORT (JOGADORES)
void mesclarJogadores(Jogador arr[], int inicio, int meio, int fim, Jogador temp[], int *comparacoes) {
    int i = inicio, j = meio + 1, k = inicio;
    while (i <= meio && j <= fim) {
        (*comparacoes)++;
        if (deveVirAntesOuIgual(arr[i], arr[j])) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= meio) temp[k++] = arr[i++];
    while (j <= fim) temp[k++] = arr[j++];
    for (int idx = inicio; idx <= fim; idx++) arr[idx] = temp[idx];
}

void mergeSortRecursivoJogadores(Jogador arr[], int inicio, int fim, Jogador temp[], int *comparacoes) {
    if (inicio >= fim) return;
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
        free(temp);
    }
}

// 5. QUICK SORT (JOGADORES) COM PIVÔ ALEATÓRIO
int particionarJogadores(Jogador arr[], int inicio, int fim, int *comparacoes, int *trocas) {
    // Escolhe um pivô pseudoaleatório restrito ao subintervalo atual
    int pivo_idx = inicio + rand() % (fim - inicio + 1);
    
    // Coloca o pivô aleatório na posição final para usar a lógica padrão de partição (Lomuto)
    Jogador tempPivo = arr[pivo_idx];
    arr[pivo_idx] = arr[fim];
    arr[fim] = tempPivo;
    (*trocas)++;

    Jogador pivo = arr[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        (*comparacoes)++;
        if (deveVirAntesOuIgual(arr[j], pivo)) {
            i++;
            Jogador temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            (*trocas)++;
        }
    }
    Jogador tempFinal = arr[i + 1]; arr[i + 1] = arr[fim]; arr[fim] = tempFinal;
    (*trocas)++;
    
    return i + 1;
}

void quickSortRecursivoJogadores(Jogador arr[], int inicio, int fim, int *comparacoes, int *trocas) {
    if (inicio < fim) {
        int pivo_idx = particionarJogadores(arr, inicio, fim, comparacoes, trocas);
        quickSortRecursivoJogadores(arr, inicio, pivo_idx - 1, comparacoes, trocas);
        quickSortRecursivoJogadores(arr, pivo_idx + 1, fim, comparacoes, trocas);
    }
}

void quickSortJogadores(Jogador arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0; *trocas = 0;
    quickSortRecursivoJogadores(arr, 0, tamanho - 1, comparacoes, trocas);
}

// --- CENTRAL DE RELATÓRIOS (main) ---
int main() {
    // Inicializa o gerador pseudoaleatório uma única vez na central
    srand((unsigned int)time(NULL));

    int tamanhoJog = 8;
    Jogador baseJogadores[] = {
        {3, "Carlos", 150, 80},
        {1, "Ana",    200, 100},
        {4, "Bia",    150, 45},
        {2, "Ana",    100, 60},      
        {6, "Daniel", 100, 25},
        {5, "Carlos", 200, 95},
        {8, "Zeca",   300, 10},
        {7, "Bia",     50, 100}
    };
    
    Jogador copia[8];

    // Variáveis de métricas
    int compSel = 0, trocasSel = 0;
    int compIns = 0, desloIns = 0;
    int compBub = 0, trocasBub = 0;
    int compMer = 0; // Merge não usa trocas, usa cópias diretas no temp
    int compQui = 0, trocasQui = 0;

    printf("=================================================\n");
    printf("     CENTRAL DE ORDENACAO - RELATORIO FINAL      \n");
    printf("=================================================\n\n");

    // 1. Selection
    copiarJogadores(baseJogadores, copia, tamanhoJog);
    selectionSortJogadores(copia, tamanhoJog, &compSel, &trocasSel);

    // 2. Insertion
    copiarJogadores(baseJogadores, copia, tamanhoJog);
    insertionSortJogadores(copia, tamanhoJog, &compIns, &desloIns);

    // 3. Bubble
    copiarJogadores(baseJogadores, copia, tamanhoJog);
    bubbleSortJogadores(copia, tamanhoJog, &compBub, &trocasBub);

    // 4. Merge
    copiarJogadores(baseJogadores, copia, tamanhoJog);
    mergeSortJogadores(copia, tamanhoJog, &compMer);

    // 5. Quick
    copiarJogadores(baseJogadores, copia, tamanhoJog);
    quickSortJogadores(copia, tamanhoJog, &compQui, &trocasQui);

    // --- RELATÓRIO ---
    printf("%-15s | %-12s | %-12s\n", "ALGORITMO", "COMPARACOES", "MOVIMENTOS");
    printf("-------------------------------------------------\n");
    printf("%-15s | %-12d | %d (trocas)\n", "Selection Sort", compSel, trocasSel);
    printf("%-15s | %-12d | %d (desloc.)\n", "Insertion Sort", compIns, desloIns);
    printf("%-15s | %-12d | %d (trocas)\n", "Bubble Sort", compBub, trocasBub);
    printf("%-15s | %-12d | %s\n", "Merge Sort", compMer, "N/A (copias)");
    printf("%-15s | %-12d | %d (trocas)\n", "Quick Sort", compQui, trocasQui);
    printf("-------------------------------------------------\n");
    printf("\n* Movimentos do Merge Sort referem-se a copias no vetor temp.\n");
    printf("* Quick Sort utilizou particionamento com pivo pseudoaleatorio.\n");

    return 0;
}