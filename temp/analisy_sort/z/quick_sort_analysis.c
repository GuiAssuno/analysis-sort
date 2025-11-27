#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Variáveis globais para contagem de operações
long long comparisons = 0;
long long swaps = 0;

// Estrutura para retornar múltiplos valores (tempo e contagens)
typedef struct {
    double time_ms;
    long long comparisons;
    long long swaps;
} AnalysisResult;

// Função auxiliar para troca de elementos e contagem
void swap(int* a, int* b) {
    swaps++;
    int t = *a;
    *a = *b;
    *b = t;
}

// ========================================= Geradores de Vetores ===========================================

// 0: Aleatório (Caso Médio)
void generate_random(int vetor[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % 1000000;
    }
}

// 1: Ordenado (Pior Caso para Pivô Simples, Melhor Caso para 3-Way)
void generate_sorted(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = i;
    }
}

// 2: Inversamente Ordenado (Pior Caso para Pivô Simples)
void generate_reverse_sorted(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = n - i;
    }
}

// 3: Quase Ordenado (Melhor Caso para Pivô Simples)
void generate_nearly_sorted(int vetor[], int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = i;
    }
    // Troca 1% dos elementos
    srand(time(NULL));
    int num_swaps = n / 100;
    for (int i = 0; i < num_swaps; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        swap(&vetor[idx1], &vetor[idx2]);
    }
    swaps = 0; // Não conta as trocas da geração
}

// 4: Elementos Repetidos (Melhor Caso para 3-Way)
void generate_repeated(int vetor[], int n) {
    srand(time(NULL));
    int num_unique = 10; // Apenas 10 valores únicos
    for (int i = 0; i < n; i++) {
        vetor[i] = rand() % num_unique;
    }
}

// ========================================= Funções de Pivô ===========================================

// 0: Último Elemento
int pivot_last(int vetor[], int esquerda, int direita) {
    // O pivô já está na posição direita, não precisa de troca
    return vetor[direita];
}

// 1: Primeiro Elemento
int pivot_first(int vetor[], int esquerda, int direita) {
    swap(&vetor[esquerda], &vetor[direita]);
    return vetor[direita];
}

// 2: Mediana de Três
int pivot_median_of_three(int vetor[], int esquerda, int direita) {
    int meio = esquerda + (direita - esquerda) / 2;
    
    // Ordena esquerda, meio e direita
    comparisons += 3; // 3 comparações para ordenar 3 elementos
    if (vetor[esquerda] > vetor[meio]) swap(&vetor[esquerda], &vetor[meio]);
    if (vetor[esquerda] > vetor[direita]) swap(&vetor[esquerda], &vetor[direita]);
    if (vetor[meio] > vetor[direita]) swap(&vetor[meio], &vetor[direita]);
    
    // Coloca a mediana (vetor[meio]) na posição direita
    swap(&vetor[meio], &vetor[direita]);
    return vetor[direita];
}

// 3: Aleatório
int pivot_random(int vetor[], int esquerda, int direita) {
    int r = esquerda + (rand() % (direita - esquerda + 1));
    swap(&vetor[r], &vetor[direita]);
    return vetor[direita];
}

// ========================================= Esquemas de Partição ===========================================

// Lomuto Partition Scheme
int partition_lomuto(int vetor[], int esquerda, int direita, int (*pivot_selector)(int[], int, int)) {
    int pivot_value = pivot_selector(vetor, esquerda, direita);
    int i = esquerda - 1;
    
    for (int j = esquerda; j <= direita - 1; j++) {
        comparisons++;
        if (vetor[j] < pivot_value) {
            i++;
            swap(&vetor[i], &vetor[j]);
        }
    }
    swap(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

// Hoare Partition Scheme
int partition_hoare(int vetor[], int esquerda, int direita, int (*pivot_selector)(int[], int, int)) {
    // Hoare usa o pivô no meio, mas para unificar, vamos usar o pivot_selector
    // e garantir que o pivô esteja em vetor[direita] antes de começar a partição.
    int pivot_value = pivot_selector(vetor, esquerda, direita);
    
    int i = esquerda - 1;
    int j = direita;
    
    while (1) {
        // Encontra elemento à esquerda (i) que é >= pivô
        do {
            i++;
            comparisons++;
        } while (vetor[i] < pivot_value);
        
        // Encontra elemento à direita (j) que é <= pivô
        do {
            j--;
            comparisons++;
        } while (vetor[j] > pivot_value);
        
        // Se os ponteiros se cruzarem, a partição está completa
        if (i >= j) {
            // O Hoare retorna o índice 'j' que é o limite da partição
            return j;
        }
        
        // Troca os elementos encontrados
        swap(&vetor[i], &vetor[j]);
    }
}

// 3-Way Partition Scheme (Dijkstra)
void partition_3way(int vetor[], int esquerda, int direita, int *lt, int *gt, int (*pivot_selector)(int[], int, int)) {
    int pivot_value = pivot_selector(vetor, esquerda, direita);
    
    *lt = esquerda; // lt (less than) -> limite da seção < pivô
    *gt = direita;  // gt (greater than) -> limite da seção > pivô
    int i = esquerda;  // ponteiro de varredura
    
    // O loop para quando 'i' cruza 'gt'
    while (i <= *gt) {
        comparisons++;
        if (vetor[i] < pivot_value) {
            // Elemento é MENOR que o pivô
            swap(&vetor[*lt], &vetor[i]);
            (*lt)++;
            i++;
        } else if (vetor[i] > pivot_value) {
            // Elemento é MAIOR que o pivô
            swap(&vetor[i], &vetor[*gt]);
            (*gt)--;
            // 'i' não é incrementado, pois o elemento que veio de 'gt'
            // ainda não foi verificado
        } else {
            // Elemento é IGUAL ao pivô
            i++;
        }
    }
}

// ========================================= Quick Sort Recursivo ===========================================

// Quick Sort Lomuto
void quick_sort_lomuto_recursive(int vetor[], int esquerda, int direita, int (*pivot_selector)(int[], int, int)) {
    if (esquerda < direita) {
        int parte = partition_lomuto(vetor, esquerda, direita, pivot_selector);
        quick_sort_lomuto_recursive(vetor, esquerda, parte - 1, pivot_selector);
        quick_sort_lomuto_recursive(vetor, parte + 1, direita, pivot_selector);
    }
}

// Quick Sort Hoare
void quick_sort_hoare_recursive(int vetor[], int esquerda, int direita, int (*pivot_selector)(int[], int, int)) {
    if (esquerda < direita) {
        int parte = partition_hoare(vetor, esquerda, direita, pivot_selector);
        quick_sort_hoare_recursive(vetor, esquerda, parte, pivot_selector);
        quick_sort_hoare_recursive(vetor, parte + 1, direita, pivot_selector);
    }
}

// Quick Sort 3-Way
void quick_sort_3way_recursive(int vetor[], int esquerda, int direita, int (*pivot_selector)(int[], int, int)) {
    if (esquerda < direita) {
        int lt, gt;
        partition_3way(vetor, esquerda, direita, &lt, &gt, pivot_selector);
        quick_sort_3way_recursive(vetor, esquerda, lt - 1, pivot_selector);
        quick_sort_3way_recursive(vetor, gt + 1, direita, pivot_selector);
    }
}

// ========================================= Função Principal de Análise (Exportada) ===========================================

// Função principal que será chamada pelo Python
AnalysisResult analyze_quicksort(int vetor[], int n, int algorithm_code, int pivot_code, int data_code) {
    // 1. Resetar contadores
    comparisons = 0;
    swaps = 0;

    // 2. Gerar o vetor de dados
    int *temp_vetor = (int *)malloc(n * sizeof(int));
    if (temp_vetor == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        AnalysisResult error_result = {0.0, -1, -1};
        return error_result;
    }

    // Copia o vetor de entrada para o vetor temporário
    memcpy(temp_vetor, vetor, n * sizeof(int));

    // O código original tinha geradores de números, mas para garantir que o Python
    // possa controlar o vetor (para casos melhor/pior/médio), o Python deve
    // gerar o vetor e passá-lo.
    // Se o Python passar um vetor aleatório, ele será o caso médio.
    // Se o Python passar um vetor ordenado, ele será o pior caso (Lomuto/Hoare) ou melhor caso (3-Way).
    // Para simplificar a interface, vamos manter a geração de dados no Python.
    // Apenas para fins de demonstração, se o Python passar um vetor vazio, geramos um aleatório.
    if (n == 0) {
        generate_random(temp_vetor, n);
    }

    // 3. Selecionar o algoritmo e o pivô
    void (*quick_sort_func)(int[], int, int, int (*)(int[], int, int));
    int (*pivot_selector)(int[], int, int);

    // Seleção do Algoritmo de Partição
    if (algorithm_code == 0) { // Lomuto
        quick_sort_func = quick_sort_lomuto_recursive;
    } else if (algorithm_code == 1) { // Hoare
        quick_sort_func = quick_sort_hoare_recursive;
    } else if (algorithm_code == 2) { // 3-Way
        quick_sort_func = quick_sort_3way_recursive;
    } else {
        fprintf(stderr, "Código de algoritmo inválido: %d\n", algorithm_code);
        free(temp_vetor);
        AnalysisResult error_result = {0.0, -1, -1};
        return error_result;
    }

    // Seleção do Método de Pivô
    if (pivot_code == 0) { // Último
        pivot_selector = pivot_last;
    } else if (pivot_code == 1) { // Primeiro
        pivot_selector = pivot_first;
    } else if (pivot_code == 2) { // Mediana de Três
        pivot_selector = pivot_median_of_three;
    } else if (pivot_code == 3) { // Aleatório
        pivot_selector = pivot_random;
    } else {
        fprintf(stderr, "Código de pivô inválido: %d\n", pivot_code);
        free(temp_vetor);
        AnalysisResult error_result = {0.0, -1, -1};
        return error_result;
    }

    // 4. Executar e medir o tempo
    clock_t start, end;
    start = clock();

    quick_sort_func(temp_vetor, 0, n - 1, pivot_selector);

    end = clock();

    // 5. Calcular o tempo e preparar o resultado
    double time_taken = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC; // Tempo em milissegundos

    free(temp_vetor);

    AnalysisResult result = {time_taken, comparisons, swaps};
    return result;
}
