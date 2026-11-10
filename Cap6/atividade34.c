#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Estrutura do jogador
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

// --- FUNÇÕES DE CÓPIA ---
void copiarArray(int original[], int copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        copia[i] = original[i];
    }
}

void copiarJogadores(Jogador original[], Jogador copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        copia[i] = original[i]; // Copia a estrutura inteira automaticamente
    }
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

bool validarOrdenacaoJogadoresPorNome(Jogador arr[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int cmp = strcmp(arr[i].nome, arr[i + 1].nome);
        if (cmp > 0) return false;
        if (cmp == 0 && arr[i].id > arr[i + 1].id) return false;
    }
    return true;
}

// --- SELECTION SORT (Vetor Numérico) ---
int encontrarIndiceMenor(int arr[], int inicio, int tamanho, int *comparacoes) {
    int menor = inicio;
    for (int i = inicio + 1; i < tamanho; i++) {
        (*comparacoes)++;
        if (arr[i] < arr[menor]) {
            menor = i;
        }
    }
    return menor;
}

void selectionSortNumerico(int arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int menor = encontrarIndiceMenor(arr, i, tamanho, comparacoes);
        if (menor != i) {
            int temp = arr[i];
            arr[i] = arr[menor];
            arr[menor] = temp;
            (*trocas)++;
        }
    }
}

// --- SELECTION SORT (Jogadores por Pontuação) ---
int encontrarIndiceMenorJogador(Jogador arr[], int inicio, int tamanho, int *comparacoes) {
    int menor = inicio;
    for (int i = inicio + 1; i < tamanho; i++) {
        (*comparacoes)++;
        if (arr[i].pontuacao < arr[menor].pontuacao) {
            menor = i;
        } else {
            (*comparacoes)++; // Contabiliza a verificação do desempate
            if (arr[i].pontuacao == arr[menor].pontuacao && arr[i].id < arr[menor].id) {
                menor = i;
            }
        }
    }
    return menor;
}

void selectionSortJogadores(Jogador arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int menor = encontrarIndiceMenorJogador(arr, i, tamanho, comparacoes);
        if (menor != i) {
            Jogador temp = arr[i];
            arr[i] = arr[menor];
            arr[menor] = temp;
            (*trocas)++;
        }
    }
}

// --- INSERTION SORT (Jogadores por Nome) ---
void insertionSortJogadoresPorNome(Jogador arr[], int tamanho, int *comparacoes, int *deslocamentos) {
    *comparacoes = 0;
    *deslocamentos = 0;

    for (int i = 1; i < tamanho; i++) {
        Jogador chave = arr[i]; 
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            int cmp = strcmp(arr[j].nome, chave.nome);
            bool deveDeslocar = false;

            if (cmp > 0) {
                deveDeslocar = true;
            } else if (cmp == 0) {
                (*comparacoes)++; // Contabiliza a verificação do desempate
                if (arr[j].id > chave.id) {
                    deveDeslocar = true;
                }
            }

            if (deveDeslocar) {
                arr[j + 1] = arr[j]; // Desloca a estrutura completa
                (*deslocamentos)++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}

// --- FUNÇÕES DE IMPRESSÃO ---
void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void imprimirJogadores(Jogador arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("[ID: %d | Nome: %-8s | Pontos: %d]\n", arr[i].id, arr[i].nome, arr[i].pontuacao);
    }
}

// --- CENTRAL (main) ---
int main() {
    int tamanhoNum = 10;
    int originalNum[] = {45, 12, 78, 3, 99, 21, 5, 67, 34, 8};
    int copiaNum[10];

    int tamanhoJog = 6;
    // Registros com nomes e pontuações iguais para forçar o teste do critério secundário (ID)
    Jogador originalJog[] = {
        {3, "Carlos", 150},
        {1, "Ana", 200},
        {4, "Beatriz", 150},
        {2, "Ana", 100},      
        {6, "Daniel", 100},
        {5, "Carlos", 200}    
    };
    
    // Matrizes de trabalho independentes
    Jogador copiaJogScore[6];
    Jogador copiaJogNome[6];

    // Preservar a entrada original
    copiarArray(originalNum, copiaNum, tamanhoNum);
    copiarJogadores(originalJog, copiaJogScore, tamanhoJog);
    copiarJogadores(originalJog, copiaJogNome, tamanhoJog);

    int compNum = 0, trocasNum = 0;
    int compJogScore = 0, trocasJogScore = 0;
    int compJogNome = 0, desloJogNome = 0;

    printf("--- PARTE 1: VETOR NUMERICO (SELECTION SORT) ---\n");
    selectionSortNumerico(copiaNum, tamanhoNum, &compNum, &trocasNum);
    imprimirArray(copiaNum, tamanhoNum);
    printf("Comparacoes: %d | Trocas: %d\n", compNum, trocasNum);
    printf("Validacao: %s\n\n", validarOrdenacao(copiaNum, tamanhoNum) ? "SUCESSO" : "FALHA");

    printf("--- PARTE 2: JOGADORES POR PONTUACAO (SELECTION SORT) ---\n");
    selectionSortJogadores(copiaJogScore, tamanhoJog, &compJogScore, &trocasJogScore);
    imprimirJogadores(copiaJogScore, tamanhoJog);
    printf("Comparacoes: %d | Trocas: %d\n", compJogScore, trocasJogScore);
    printf("Validacao: %s\n\n", validarOrdenacaoJogadoresPorPontuacao(copiaJogScore, tamanhoJog) ? "SUCESSO" : "FALHA");

    printf("--- PARTE 3: JOGADORES POR NOME (INSERTION SORT) ---\n");
    printf("Original:\n");
    imprimirJogadores(copiaJogNome, tamanhoJog);
    
    insertionSortJogadoresPorNome(copiaJogNome, tamanhoJog, &compJogNome, &desloJogNome);
    
    printf("\nOrdenado:\n");
    imprimirJogadores(copiaJogNome, tamanhoJog);
    printf("Comparacoes: %d | Deslocamentos: %d\n", compJogNome, desloJogNome);
    printf("Validacao: %s\n", validarOrdenacaoJogadoresPorNome(copiaJogNome, tamanhoJog) ? "SUCESSO" : "FALHA");

    return 0;
}