#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "sorting.h"

static bool is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1]) return false;
    return true;
}

static void shuffle(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int r = rand() % n;
        int temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
}

double run_bogo_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    // Trava de segurança: Bogo Sort é perigoso para CPU
    if (n > 12) { 
        // Retorna -1 para indicar erro/aborto se quiser tratar no python
        return -1.0; 
    }

    while (!is_sorted(arr, n)) {
        shuffle(arr, n);
    }
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}