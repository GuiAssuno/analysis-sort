#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

static int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    return max;
}

// --- LSD (Least Significant Digit) ---
static void count_sort_lsd(int arr[], int n, int exp) {
    int *output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

static void radix_lsd(int arr[], int n) {
    int max = get_max(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        count_sort_lsd(arr, n, exp);
}

// --- MSD (Most Significant Digit) ---
static void radix_msd_recursive(int arr[], int n, int exp) {
    if (n <= 1 || exp == 0) return;

    // Buckets (baldes) para contar e organizar
    int count[10] = {0};
    int *aux = (int*)malloc(n * sizeof(int));

    // Contagem
    for (int i = 0; i < n; i++) 
        count[(arr[i] / exp) % 10]++;

    // Posições (índices iniciais de cada balde)
    int start[10];
    start[0] = 0;
    for (int i = 1; i < 10; i++) 
        start[i] = start[i - 1] + count[i - 1];
    
    // Cópia para o array auxiliar (precisa de cópia do start para não perder referência)
    int current_pos[10];
    for(int i=0; i<10; i++) current_pos[i] = start[i];

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        aux[current_pos[digit]++] = arr[i];
    }

    // Copia de volta
    for (int i = 0; i < n; i++) arr[i] = aux[i];
    free(aux);

    // Recursão para cada balde
    for (int i = 0; i < 10; i++) {
        if (count[i] > 1) {
            radix_msd_recursive(arr + start[i], count[i], exp / 10);
        }
    }
}

static void radix_msd(int arr[], int n) {
    int max = get_max(arr, n);
    // Acha a maior potência de 10
    int exp = 1;
    while (max / (exp * 10) > 0) exp *= 10;
    
    radix_msd_recursive(arr, n, exp);
}

double run_radix_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();

    if (op == 1) radix_lsd(arr, n); // "LSD"
    else radix_msd(arr, n);         // "MSD"

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void counting_sort_radix(int arr[], int n, int exp) {
    int *output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    free(output);
}

void radix_sort(int arr[], int n) {
    int max = get_max(arr, n);
    
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting_sort_radix(arr, n, exp);
}

double test_radix_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    radix_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

