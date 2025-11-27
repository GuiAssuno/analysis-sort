#include <stdio.h>
#include <time.h>
#include <string.h> // Para memmove
#include "sorting.h"

// 1. Linear (Padrão)
static void insertion_linear(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 2. Binária (Usa busca binária para achar local)
static int binary_search(int a[], int item, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (item == a[mid]) return mid + 1;
        else if (item > a[mid]) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}

static void insertion_binary(int arr[], int n) {
    int i, loc, j, selected;
    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = arr[i];
        
        // Acha onde inserir usando busca binária
        loc = binary_search(arr, selected, 0, j);
        
        // Move elementos para frente para abrir espaço
        // memmove é mais eficiente que loop manual para blocos de memória
        while (j >= loc) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[loc] = selected;
    }
}

double run_insertion_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();

    if (op == 1) insertion_linear(arr, n); // "linear"
    else insertion_binary(arr, n);         // "binary"

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void insertion_sort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

double test_insertion_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    insertion_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

