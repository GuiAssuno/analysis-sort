#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sorting.h"

// --- Funções Auxiliares ---

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// --- 1. Insertion Sort (Para pequenos sub-arrays) ---

void insertion_sort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// --- 2. Heap Sort (Para fallback) ---

void heapify(int arr[], int n, int i, int low) {
    int largest = i;
    int left = 2 * (i - low) + 1 + low;
    int right = 2 * (i - low) + 2 + low;
    
    if (left <= n && arr[left] > arr[largest])
        largest = left;
    
    if (right <= n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest, low);
    }
}

void heap_sort(int arr[], int low, int high) {
    int n = high;
    
    for (int i = (n - low) / 2 + low; i >= low; i--)
        heapify(arr, n, i, low);
    
    for (int i = n; i > low; i--) {
        swap(&arr[low], &arr[i]);
        heapify(arr, i - 1, low, low);
    }
}

// --- 3. Quick Sort (Função principal) ---

int median_of_three(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);
        
    return mid; // Retorna o índice do pivô (que agora está em mid)
}

int partition(int arr[], int low, int high) {
    // Usa mediana de três para escolher um pivô melhor
    int pivot_index = median_of_three(arr, low, high);
    swap(&arr[pivot_index], &arr[high]); // Move o pivô para o final
    
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void introspective_sort_recursive(int arr[], int low, int high, int depth_limit) {
    while (high - low + 1 > INSERTION_SORT_THRESHOLD) {
        if (depth_limit == 0) {
            // Fallback para Heap Sort
            heap_sort(arr, low, high);
            return;
        }
        
        int pi = partition(arr, low, high);
        
        // Reduz o limite de profundidade
        depth_limit--;
        
        // Chamada recursiva para a partição menor
        if (pi - low < high - pi) {
            introspective_sort_recursive(arr, low, pi - 1, depth_limit);
            low = pi + 1; // Loop para a partição maior (otimização de cauda)
        } else {
            introspective_sort_recursive(arr, pi + 1, high, depth_limit);
            high = pi - 1; // Loop para a partição maior (otimização de cauda)
        }
    }
}

// --- Função Principal Introspective Sort ---

void intro_sort(int arr[], int n) {
    if (n <= 1) return;
    
    // Limite de profundidade: 2 * log2(n)
    int depth_limit = 2 * (int)log2(n);
    
    introspective_sort_recursive(arr, 0, n - 1, depth_limit);
    
    // Finaliza com Insertion Sort para os pequenos sub-arrays restantes
    insertion_sort(arr, 0, n - 1);
}
