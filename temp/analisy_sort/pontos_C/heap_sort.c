#include <stdio.h>
#include <time.h>
#include "sorting.h"

static void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

// --- Método 1: Heapify Padrão (Floyd) ---
static void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

static void heap_sort_standard(int arr[], int n) {
    // Constrói heap (rearranjar array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrai um por um
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// --- Método 2: Sift-Up (Construção por inserção) ---
static void sift_up(int arr[], int i) {
    int parent = (i - 1) / 2;
    if (i > 0 && arr[i] > arr[parent]) {
        swap(&arr[i], &arr[parent]);
        sift_up(arr, parent);
    }
}

static void heap_sort_siftup(int arr[], int n) {
    // Constrói heap inserindo um a um
    for (int i = 1; i < n; i++)
        sift_up(arr, i);

    // Extrai (mesma lógica de extração, mas o build foi diferente)
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0); // Usa heapify para descer o elemento trocado
    }
}

double run_heap_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    if (op == 1) heap_sort_standard(arr, n); // "heapify"
    else heap_sort_siftup(arr, n);           // "siftup"
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        heapify(arr, i, 0);
    }
}

double test_heap_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    heap_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

