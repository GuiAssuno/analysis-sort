#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "sorting.h"

static void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

static void comb_sort_standard(int arr[], int n) {
    int gap = n;
    float shrink = 1.3;
    bool sorted = false;

    while (!sorted) {
        gap = (int)(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = true; // Assume ordenado, se não houver trocas no gap=1, termina
        }

        for (int i = 0; i + gap < n; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                sorted = false; // Se houve troca, não está ordenado
            }
        }
    }
}

double run_comb_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    comb_sort_standard(arr, n);
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}