#include <stdio.h>
#include <time.h>
#include <math.h>
#include "sorting.h"

// Função genérica que recebe um gap
static void shell_sort_generic(int arr[], int n, int gap) {
    for (int i = gap; i < n; i++) {
        int temp = arr[i];
        int j;
        for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            arr[j] = arr[j - gap];
        arr[j] = temp;
    }
}

// 1. Shell (N/2)
static void shell_original(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        shell_sort_generic(arr, n, gap);
}

// 2. Knuth ((3^k - 1) / 2) -> 1, 4, 13, 40...
static void shell_knuth(int arr[], int n) {
    int h = 1;
    while (h < n / 3) h = 3 * h + 1;
    while (h >= 1) {
        shell_sort_generic(arr, n, h);
        h /= 3;
    }
}

// 3. Hibbard (2^k - 1) -> 1, 3, 7, 15...
static void shell_hibbard(int arr[], int n) {
    int k = 1;
    while ((pow(2, k) - 1) < n) k++;
    k--; // Volta para o maior gap menor que n
    
    while (k > 0) {
        int gap = (int)pow(2, k) - 1;
        shell_sort_generic(arr, n, gap);
        k--;
    }
}

// 4. Ciura (Sequência empírica ótima para arrays médios)
static void shell_ciura(int arr[], int n) {
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    int n_gaps = 8;
    
    for (int i = 0; i < n_gaps; i++) {
        if (gaps[i] < n)
            shell_sort_generic(arr, n, gaps[i]);
    }
}

double run_shell_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();

    switch(op) {
        case 1: shell_original(arr, n); break; // Shell
        case 2: shell_knuth(arr, n); break;    // Knuth
        case 3: shell_ciura(arr, n); break;    // Ciura
        case 4: shell_hibbard(arr, n); break;  // Hibbard
        default: shell_original(arr, n); break;
    }

    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

double test_shell_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    shell_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

