#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

void copiarArray(int original[], int copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        copia[i] = original[i];
    }
}

void copiarJogadores(Jogador original[], Jogador copia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        copia[i] = original[i];
    }
}

bool validarOrdenacao(int arr[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

bool validarOrdenacaoJogadores(Jogador arr[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (arr[i].pontuacao > arr[i + 1].pontuacao) {
            return false;
        } else if (arr[i].pontuacao == arr[i + 1].pontuacao) {
            if (arr[i].id > arr[i + 1].id) {
                return false;
            }
        }
    }
    return true;
}

int encontrarIndiceMenor(int arr[], int inicio, int tamanho, int *comparacoes) {
    int indiceMenor = inicio;
    for (int i = inicio + 1; i < tamanho; i++) {
        (*comparacoes)++;
        if (arr[i] < arr[indiceMenor]) {
            indiceMenor = i;
        }
    }
    return indiceMenor;
}

void selectionSortNumerico(int arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMenor = encontrarIndiceMenor(arr, i, tamanho, comparacoes);
        
        if (indiceMenor != i) {
            int temp = arr[i];
            arr[i] = arr[indiceMenor];
            arr[indiceMenor] = temp;
            (*trocas)++;
        }
    }
}

int encontrarIndiceMenorJogador(Jogador arr[], int inicio, int tamanho, int *comparacoes) {
    int indiceMenor = inicio;
    for (int i = inicio + 1; i < tamanho; i++) {
        (*comparacoes)++;
        if (arr[i].pontuacao < arr[indiceMenor].pontuacao) {
            indiceMenor = i;
        } else {
            (*comparacoes)++;
            if (arr[i].pontuacao == arr[indiceMenor].pontuacao && arr[i].id < arr[indiceMenor].id) {
                indiceMenor = i;
            }
        }
    }
    return indiceMenor;
}

void selectionSortJogadores(Jogador arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMenor = encontrarIndiceMenorJogador(arr, i, tamanho, comparacoes);
        
        if (indiceMenor != i) {
            Jogador temp = arr[i];
            arr[i] = arr[indiceMenor];
            arr[indiceMenor] = temp;
            (*trocas)++;
        }
    }
}

void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void imprimirJogadores(Jogador arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("[ID: %d | Nome: %s | Pontos: %d]\n", arr[i].id, arr[i].nome, arr[i].pontuacao);
    }
}

int main() {
    int tamanhoNum = 10;
    int originalNum[] = {45, 12, 78, 3, 99, 21, 5, 67, 34, 8};
    int copiaNum[10];

    int tamanhoJog = 5;
    Jogador originalJog[] = {
        {3, "Carlos", 150},
        {1, "Ana", 200},
        {4, "Beatriz", 150},
        {2, "Daniel", 100},
        {5, "Eduardo", 200}
    };
    Jogador copiaJog[5];

    copiarArray(originalNum, copiaNum, tamanhoNum);
    copiarJogadores(originalJog, copiaJog, tamanhoJog);

    int compNum = 0, trocasNum = 0;
    int compJog = 0, trocasJog = 0;

    printf("--- PARTE 1: VETOR NUMERICO ---\n");
    printf("Original:\n");
    imprimirArray(copiaNum, tamanhoNum);
    
    selectionSortNumerico(copiaNum, tamanhoNum, &compNum, &trocasNum);
    
    printf("Ordenado:\n");
    imprimirArray(copiaNum, tamanhoNum);
    printf("Comparacoes: %d | Trocas: %d\n", compNum, trocasNum);
    printf("Validacao: %s\n\n", validarOrdenacao(copiaNum, tamanhoNum) ? "SUCESSO" : "FALHA");

    printf("--- PARTE 2: REGISTROS DE JOGADORES ---\n");
    printf("Original:\n");
    imprimirJogadores(copiaJog, tamanhoJog);
    
    selectionSortJogadores(copiaJog, tamanhoJog, &compJog, &trocasJog);
    
    printf("\nOrdenado (Por Pontuacao e ID):\n");
    imprimirJogadores(copiaJog, tamanhoJog);
    printf("Comparacoes: %d | Trocas: %d\n", compJog, trocasJog);
    printf("Validacao: %s\n", validarOrdenacaoJogadores(copiaJog, tamanhoJog) ? "SUCESSO" : "FALHA");

    return 0;
}