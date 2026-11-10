#include <stdio.h>
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

bool validarOrdenacaoJogadoresPorVida(Jogador arr[], int tamanho, bool crescente) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (crescente) {
            if (arr[i].vida > arr[i + 1].vida) return false;
        } else {
            if (arr[i].vida < arr[i + 1].vida) return false;
        }
    }
    return true;
}

// --- ALGORITMOS ANTERIORES (SELECTION, INSERTION, BUBBLE) ---
int encontrarIndiceMenor(int arr[], int inicio, int tamanho, int *comparacoes) {
    int menor = inicio;
    for (int i = inicio + 1; i < tamanho; i++) {
        (*comparacoes)++;
        if (arr[i] < arr[menor]) menor = i;
    }
    return menor;
}

void selectionSortNumerico(int arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0; *trocas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int menor = encontrarIndiceMenor(arr, i, tamanho, comparacoes);
        if (menor != i) {
            int temp = arr[i]; arr[i] = arr[menor]; arr[menor] = temp;
            (*trocas)++;
        }
    }
}

int encontrarIndiceMenorJogador(Jogador arr[], int inicio, int tamanho, int *comparacoes) {
    int menor = inicio;
    for (int i = inicio + 1; i < tamanho; i++) {
        (*comparacoes)++;
        if (arr[i].pontuacao < arr[menor].pontuacao) menor = i;
        else {
            (*comparacoes)++;
            if (arr[i].pontuacao == arr[menor].pontuacao && arr[i].id < arr[menor].id) menor = i;
        }
    }
    return menor;
}

void selectionSortJogadores(Jogador arr[], int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0; *trocas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        int menor = encontrarIndiceMenorJogador(arr, i, tamanho, comparacoes);
        if (menor != i) {
            Jogador temp = arr[i]; arr[i] = arr[menor]; arr[menor] = temp;
            (*trocas)++;
        }
    }
}

void insertionSortJogadoresPorNome(Jogador arr[], int tamanho, int *comparacoes, int *deslocamentos) {
    *comparacoes = 0; *deslocamentos = 0;
    for (int i = 1; i < tamanho; i++) {
        Jogador chave = arr[i]; 
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            int cmp = strcmp(arr[j].nome, chave.nome);
            bool deveDeslocar = false;
            if (cmp > 0) deveDeslocar = true;
            else if (cmp == 0) {
                (*comparacoes)++;
                if (arr[j].id > chave.id) deveDeslocar = true;
            }
            if (deveDeslocar) {
                arr[j + 1] = arr[j]; 
                (*deslocamentos)++; j--;
            } else break;
        }
        arr[j + 1] = chave;
    }
}

bool precisaTrocarVida(Jogador a, Jogador b, bool crescente) {
    if (crescente) return a.vida > b.vida;
    else return a.vida < b.vida; 
}

void bubbleSortJogadoresPorVida(Jogador arr[], int tamanho, bool crescente, int *comparacoes, int *trocas, int *passagens) {
    *comparacoes = 0; *trocas = 0; *passagens = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        (*passagens)++;
        bool trocou = false;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            (*comparacoes)++;
            if (precisaTrocarVida(arr[j], arr[j + 1], crescente)) {
                Jogador temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
                (*trocas)++; trocou = true;
            }
        }
        if (!trocou) break;
    }
}

// --- PARTE 6: MERGE SORT (ESTRUTURA RECURSIVA E INTERCALAÇÃO) ---

// Função que recebe duas metades ordenadas (como se fossem 2 vetores) e produz um terceiro (temp)
void mesclar(int arr[], int inicio, int meio, int fim, int temp[], int *comparacoes) {
    // Índices independentes para as duas entradas e para o vetor de saída
    int i = inicio;      // Índice do "primeiro vetor" (metade esquerda)
    int j = meio + 1;    // Índice do "segundo vetor" (metade direita)
    int k = inicio;      // Índice do "terceiro vetor" (vetor temporário)

    // Intercala os elementos até que uma das metades termine
    while (i <= meio && j <= fim) {
        (*comparacoes)++;
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes quando a segunda entrada terminar
    while (i <= meio) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // Copia os elementos restantes quando a primeira entrada terminar
    while (j <= fim) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // Produz a saída com todos os valores, copiando de volta para o array original
    for (int idx = inicio; idx <= fim; idx++) {
        arr[idx] = temp[idx];
    }
}

// Estrutura recursiva principal do Merge Sort
void mergeSortRecursivo(int arr[], int inicio, int fim, int temp[], int *comparacoes) {
    if (inicio < fim) {
        // [ETAPA 1: DIVIDIR] - Calcula corretamente o ponto médio
        int meio = inicio + (fim - inicio) / 2; // Evita overflow em vetores muito grandes

        // [ETAPA 2: RESOLVER] - Chama a recursão para as duas metades
        mergeSortRecursivo(arr, inicio, meio, temp, comparacoes);
        mergeSortRecursivo(arr, meio + 1, fim, temp, comparacoes);

        // [ETAPA 3: COMBINAR] - Intercala as duas metades ordenadas
        mesclar(arr, inicio, meio, fim, temp, comparacoes);
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
        printf("[ID: %d | Nome: %-8s | Pontos: %3d | Vida: %3d]\n", arr[i].id, arr[i].nome, arr[i].pontuacao, arr[i].vida);
    }
}

// --- CENTRAL (main) ---
int main() {
    int tamanhoNum = 10;
    int originalNum[] = {45, 12, 78, 3, 99, 21, 5, 67, 34, 8};
    int copiaNum[10];

    int tamanhoJog = 6;
    Jogador originalJog[] = {
        {3, "Carlos", 150, 80},
        {1, "Ana", 200, 100},
        {4, "Beatriz", 150, 45},
        {2, "Ana", 100, 60},      
        {6, "Daniel", 100, 25},
        {5, "Carlos", 200, 95}    
    };
    
    Jogador copiaJogScore[6], copiaJogNome[6], copiaJogVida[6];

    copiarArray(originalNum, copiaNum, tamanhoNum);
    copiarJogadores(originalJog, copiaJogScore, tamanhoJog);
    copiarJogadores(originalJog, copiaJogNome, tamanhoJog);
    copiarJogadores(originalJog, copiaJogVida, tamanhoJog); 

    int compNum = 0, trocasNum = 0;
    int compJogScore = 0, trocasJogScore = 0;
    int compJogNome = 0, desloJogNome = 0;
    int compJogVida = 0, trocasJogVida = 0, passagensJogVida = 0;

    printf("=================================================\n");
    printf("        CENTRAL DE ORDENACAO DO LABORATORIO      \n");
    printf("=================================================\n\n");

    printf("--- PARTE 1: VETOR NUMERICO (SELECTION SORT) ---\n");
    selectionSortNumerico(copiaNum, tamanhoNum, &compNum, &trocasNum);
    printf("Comparacoes: %d | Trocas: %d\n\n", compNum, trocasNum);

    printf("--- PARTE 2: JOGADORES POR PONTUACAO (SELECTION SORT) ---\n");
    selectionSortJogadores(copiaJogScore, tamanhoJog, &compJogScore, &trocasJogScore);
    printf("Comparacoes: %d | Trocas: %d\n\n", compJogScore, trocasJogScore);

    printf("--- PARTE 3: JOGADORES POR NOME (INSERTION SORT) ---\n");
    insertionSortJogadoresPorNome(copiaJogNome, tamanhoJog, &compJogNome, &desloJogNome);
    printf("Comparacoes: %d | Deslocamentos: %d\n\n", compJogNome, desloJogNome);

    printf("--- PARTE 5: JOGADORES POR VIDA (BUBBLE SORT) ---\n");
    bool ordemCrescente = false; 
    bubbleSortJogadoresPorVida(copiaJogVida, tamanhoJog, ordemCrescente, &compJogVida, &trocasJogVida, &passagensJogVida);
    printf("Comparacoes: %d | Trocas: %d\n\n", compJogVida, trocasJogVida);

    // --- EXECUÇÃO DA PARTE 6 (MERGE SORT BASE) ---
    printf("--- PARTE 6: VETOR NUMERICO (ESTRUTURA RECURSIVA DO MERGE SORT) ---\n");
    
    int copiaMerge[10];
    int tempMerge[10]; // O "terceiro vetor" usado para a intercalação
    copiarArray(originalNum, copiaMerge, tamanhoNum);
    int compMerge = 0;

    printf("Original:\n");
    imprimirArray(copiaMerge, tamanhoNum);

    // Chamada inicial para resolver todo o vetor (de 0 a tamanho-1)
    mergeSortRecursivo(copiaMerge, 0, tamanhoNum - 1, tempMerge, &compMerge);

    printf("\nOrdenado por Divisao, Resolucao e Combinacao:\n");
    imprimirArray(copiaMerge, tamanhoNum);

    printf("\nMetricas da Intercalacao (Parte 6):\n");
    printf("Comparacoes realizadas durante as fusoes: %d\n", compMerge);
    printf("Validacao: %s\n", validarOrdenacao(copiaMerge, tamanhoNum) ? "SUCESSO" : "FALHA");

    return 0;
}