#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void copiarArray(int original[], int copia[], int tamanho) {
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

void insertionSort(int arr[], int tamanho, int *comparacoes, int *deslocamentos) {
    *comparacoes = 0;
    *deslocamentos = 0;

    for (int i = 1; i < tamanho; i++) {
        int chave = arr[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;

            if (arr[j] > chave) {
                arr[j + 1] = arr[j];
                (*deslocamentos)++;
                j = j - 1;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}

void imprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int tamanho = 10;
    int original[] = {45, 12, 78, 3, 99, 21, 5, 67, 34, 8};
    int copia[10];

    printf("Array original:\n");
    imprimirArray(original, tamanho);

    copiarArray(original, copia, tamanho);

    int comparacoes = 0;
    int deslocamentos = 0;

    insertionSort(copia, tamanho, &comparacoes, &deslocamentos);

    printf("\nArray ordenado pelo Insertion Sort:\n");
    imprimirArray(copia, tamanho);

    printf("\n--- Metricas do Laboratorio ---\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Deslocamentos realizados: %d\n", deslocamentos);

    if (validarOrdenacao(copia, tamanho)) {
        printf("\nStatus da Validacao: SUCESSO! O array esta corretamente ordenado.\n");
    } else {
        printf("\nStatus da Validacao: FALHA! O array nao esta ordenado.\n");
    }

    return 0;
}