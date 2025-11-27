#include <stdio.h>
#include <stdlib.h> // min
#include <time.h>
#include "sorting.h"

static const int RUN = 32;

static int min_val(int a, int b) { return (a < b) ? a : b; }

// Insertion Sort específico para faixas (usado pelo TimSort)
static void insertion_sort_tim(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Merge específico (similar ao Merge Sort)
static void merge_tim(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int *left = (int*)malloc(len1 * sizeof(int));
    int *right = (int*)malloc(len2 * sizeof(int));

    for (int x = 0; x < len1; x++) left[x] = arr[l + x];
    for (int x = 0; x < len2; x++) right[x] = arr[m + 1 + x];

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < len1) arr[k++] = left[i++];
    while (j < len2) arr[k++] = right[j++];

    free(left);
    free(right);
}

static void tim_sort_standard(int arr[], int n) {
    // 1. Ordena sub-arrays de tamanho RUN
    for (int i = 0; i < n; i += RUN)
        insertion_sort_tim(arr, i, min_val((i + RUN - 1), (n - 1)));

    // 2. Merge dos sub-arrays
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min_val((left + 2 * size - 1), (n - 1));

            if (mid < right)
                merge_tim(arr, left, mid, right);
        }
    }
}

double run_tim_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    tim_sort_standard(arr, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}