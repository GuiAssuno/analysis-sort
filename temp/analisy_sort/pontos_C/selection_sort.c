#include <stdio.h>
#include <time.h>
#include "sorting.h"

static void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

// 1. Padrão (Min)
static void selection_standard(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

// 2. Bidirecional (Min e Max simultâneos)
static void selection_double(int arr[], int n) {
    int i = 0, j = n - 1;
    while (i < j) {
        int min_idx = i, max_idx = i;
        for (int k = i; k <= j; k++) {
            if (arr[k] < arr[min_idx]) min_idx = k;
            if (arr[k] > arr[max_idx]) max_idx = k;
        }
        
        swap(&arr[i], &arr[min_idx]);
        
        // Correção crítica: se o max estava na posição i, ele foi movido para min_idx
        if (max_idx == i) max_idx = min_idx;
        
        swap(&arr[j], &arr[max_idx]);
        i++; j--;
    }
}

double run_selection_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    if (op == 1) selection_standard(arr, n);
    else selection_double(arr, n);
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}













void selection_sort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

double test_selection_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    selection_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

