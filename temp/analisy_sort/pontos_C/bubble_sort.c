#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "sorting.h"

static void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

// 1. Padrão
static void bubble_standard(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(&arr[j], &arr[j + 1]);
        }
    }
}

// 2. Otimizado
static void bubble_optimized(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 3. Cocktail Shaker (Vai e Volta)
static void bubble_cocktail(int arr[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        // Ida (Esquerda -> Direita)
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;

        // Volta (Direita -> Esquerda)
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = true;
            }
        }
        start++;
    }
}

double run_bubble_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    // Mapeamento Python: standard->1, optimized->2, cocktail->3 (supondo ordem)
    // Ajuste conforme os valores que você enviará do Python ("standard", "optimized", "cocktail")
    // Sugiro usar strings ou garantir a ordem dos IDs. Aqui assumo IDs numéricos.
    if (op == 1) bubble_standard(arr, n);       // Padrão
    else if (op == 2) bubble_optimized(arr, n); // Otimizado
    else bubble_cocktail(arr, n);               // Cocktail (novo)
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// 1. Padrão: Sempre percorre tudo
static void bubble_standard(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 2. Otimizado: Para se não houver trocas
static void bubble_optimized(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

double run_bubble_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    // Mapeamento: "standard" -> 1, "optimized" -> 2
    // Você deve garantir que o Python envie esses números
    if (op == 1) bubble_standard(arr, n);
    else bubble_optimized(arr, n);
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void bubble_sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

double test_bubble_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    bubble_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

