#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "intro_sort.h"

#define ARRAY_SIZE 1000000 // 1 milhão de elementos para um teste mais robusto

void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        // Gera números aleatórios entre 0 e 999999
        arr[i] = rand() % 1000000;
    }
}

void copy_array(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void print_array(int arr[], int n, int max_print) {
    int limit = (n < max_print) ? n : max_print;
    printf("[");
    for (int i = 0; i < limit; i++) {
        printf("%d", arr[i]);
        if (i < limit - 1) printf(", ");
    }
    if (n > max_print) printf(", ...");
    printf("]\n");
}

double test_intro_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    intro_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int main() {
    int *original_array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    int *test_array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    double time_taken;
    
    if (original_array == NULL || test_array == NULL) {
        perror("Falha ao alocar memória");
        return 1;
    }
    
    srand(time(NULL));
    generate_random_array(original_array, ARRAY_SIZE);
    
    printf("=======================================================\n");
    printf("  TESTE DO ALGORITMO INTROSPECTIVE SORT EM C\n");
    printf("=======================================================\n");
    printf("Tamanho do array: %d elementos\n", ARRAY_SIZE);
    printf("Primeiros 10 elementos do array original:\n");
    print_array(original_array, ARRAY_SIZE, 10);
    printf("=======================================================\n\n");
    
    // Teste do Introspective Sort
    printf("1. INTROSPECTIVE SORT\n");
    copy_array(original_array, test_array, ARRAY_SIZE);
    time_taken = test_intro_sort(test_array, ARRAY_SIZE);
    printf("   Tempo de execucao: %.6f segundos\n", time_taken);
    printf("   Primeiros 10 elementos ordenados: ");
    print_array(test_array, ARRAY_SIZE, 10);
    printf("\n");
    
    printf("=======================================================\n");
    printf("  TESTE CONCLUIDO\n");
    printf("=======================================================\n");
    
    free(original_array);
    free(test_array);
    
    return 0;
}
