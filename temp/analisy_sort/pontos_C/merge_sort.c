#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

static int min(int x, int y) { return (x < y) ? x : y; }

static void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    // Alocação temporária
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L); free(R);
}

// 1. Recursivo
static void merge_recursive(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_recursive(arr, l, m);
        merge_recursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 2. Iterativo (Bottom-Up)
static void merge_iterative(int arr[], int n) {
    int curr_size;  
    int left_start; 
    
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            merge(arr, left_start, mid, right_end);
        }
    }
}

double run_merge_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();

    if (op == 1) merge_recursive(arr, 0, n - 1); // "recursivo"
    else merge_iterative(arr, n);                // "iterativo"

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void merge_sort_recursive(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_recursive(arr, l, m);
        merge_sort_recursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort(int arr[], int n) {
    merge_sort_recursive(arr, 0, n - 1);
}

double test_merge_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    merge_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

