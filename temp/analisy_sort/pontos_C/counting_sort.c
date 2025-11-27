#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

// 1. Padrão (Assume min = 0, falha com negativos se não ajustado)
static void counting_standard(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    
    // Aloca vetor de contagem (0 até max)
    int *count = (int*)calloc(max + 1, sizeof(int));
    int *output = (int*)malloc(n * sizeof(int));

    if (!count || !output) return; // Erro de memória

    for (int i = 0; i < n; i++) count[arr[i]]++;
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    
    free(count);
    free(output);
}

// 2. Com Shift (Detecta negativos e ajusta o range)
static void counting_shift(int arr[], int n) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    
    int range = max - min + 1;
    int *count = (int*)calloc(range, sizeof(int));
    int *output = (int*)malloc(n * sizeof(int));
    
    if (!count || !output) return;

    for (int i = 0; i < n; i++) count[arr[i] - min]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    
    free(count);
    free(output);
}

double run_counting_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    if (op == 1) counting_standard(arr, n); // Assume apenas positivos
    else counting_shift(arr, n);            // Seguro (calcula min)
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}













void counting_sort(int arr[], int n) {
    int max = arr[0];
    int min = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    
    int range = max - min + 1;
    int *count = (int*)calloc(range, sizeof(int));
    int *output = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++)
        count[arr[i] - min]++;
    
    for (int i = 1; i < range; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    free(count);
    free(output);
}

double test_counting_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    counting_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

