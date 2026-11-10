#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// --- ESTRUTURAS ---
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
        copia[i] = original[i];
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
            (*comparacoes)++;
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
                (*comparacoes)++;
                if (arr[j].id > chave.id) {
                    deveDeslocar = true;
                }
            }

            if (deveDeslocar) {
                arr[j + 1] = arr[j]; 
                (*deslocamentos)++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}

// --- BUBBLE SORT (Otimizado) ---
void bubbleSortOtimizado(int arr[], int tamanho, int *comparacoes, int *trocas, int *passagens) {
    *comparacoes = 0;
    *trocas = 0;
    *passagens = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        (*passagens)++;
        bool trocou = false;
        
        // Reduz a faixa útil usando "tamanho - 1 - i", pois os "i" maiores já estão no final
        for (int j = 0; j < tamanho - 1 - i; j++) {
            (*comparacoes)++;
            // Compara elementos vizinhos
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*trocas)++;
                trocou = true; // Indica que ocorreu pelo menos uma troca
            }
        }
        
        // Interrompe quando nenhuma troca ocorrer (vetor já está ordenado)
        if (!trocou) {
            break;
        }
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
    Jogador originalJog[] = {
        {3, "Carlos", 150},
        {1, "Ana", 200},
        {4, "Beatriz", 150},
        {2, "Ana", 100},      
        {6, "Daniel", 100},
        {5, "Carlos", 200}    
    };
    
    Jogador copiaJogScore[6];
    Jogador copiaJogNome[6];

    copiarArray(originalNum, copiaNum, tamanhoNum);
    copiarJogadores(originalJog, copiaJogScore, tamanhoJog);
    copiarJogadores(originalJog, copiaJogNome, tamanhoJog);

    int compNum = 0, trocasNum = 0;
    int compJogScore = 0, trocasJogScore = 0;
    int compJogNome = 0, desloJogNome = 0;

    printf("--- PARTE 1: VETOR NUMERICO (SELECTION SORT) ---\n");
    selectionSortNumerico(copiaNum, tamanhoNum, &compNum, &trocasNum);
    printf("Comparacoes: %d | Trocas: %d\n\n", compNum, trocasNum);

    printf("--- PARTE 2: JOGADORES POR PONTUACAO (SELECTION SORT) ---\n");
    selectionSortJogadores(copiaJogScore, tamanhoJog, &compJogScore, &trocasJogScore);
    printf("Comparacoes: %d | Trocas: %d\n\n", compJogScore, trocasJogScore);

    printf("--- PARTE 3: JOGADORES POR NOME (INSERTION SORT) ---\n");
    insertionSortJogadoresPorNome(copiaJogNome, tamanhoJog, &compJogNome, &desloJogNome);
    printf("Comparacoes: %d | Deslocamentos: %d\n\n", compJogNome, desloJogNome);

    // --- PARTE 4: BUBBLE SORT OTIMIZADO (Teste de Cenários) ---
    printf("--- PARTE 4: TESTES BUBBLE SORT OTIMIZADO ---\n");
    
    int arrAleatorio[] = {45, 12, 78, 3, 99, 21, 5, 67, 34, 8};
    int arrOrdenado[] = {3, 5, 8, 12, 21, 34, 45, 67, 78, 99};
    int arrInverso[] = {99, 78, 67, 45, 34, 21, 12, 8, 5, 3};
    
    int copiaAleatorio[10], copiaOrdenado[10], copiaInverso[10];
    copiarArray(arrAleatorio, copiaAleatorio, tamanhoNum);
    copiarArray(arrOrdenado, copiaOrdenado, tamanhoNum);
    copiarArray(arrInverso, copiaInverso, tamanhoNum);

    int compBubble, trocasBubble, passagensBubble;

    // Cenário 1: Ordenado
    bubbleSortOtimizado(copiaOrdenado, tamanhoNum, &compBubble, &trocasBubble, &passagensBubble);
    printf("[Vetor Ordenado]\nPassagens: %d | Comparacoes: %d | Trocas: %d\n", passagensBubble, compBubble, trocasBubble);

    // Cenário 2: Inverso
    bubbleSortOtimizado(copiaInverso, tamanhoNum, &compBubble, &trocasBubble, &passagensBubble);
    printf("[Vetor Inverso]\nPassagens: %d | Comparacoes: %d | Trocas: %d\n", passagensBubble, compBubble, trocasBubble);

    // Cenário 3: Aleatório
    bubbleSortOtimizado(copiaAleatorio, tamanhoNum, &compBubble, &trocasBubble, &passagensBubble);
    printf("[Vetor Aleatorio]\nPassagens: %d | Comparacoes: %d | Trocas: %d\n", passagensBubble, compBubble, trocasBubble);

    return 0;
}