#include <stdio.h>
#include <time.h>
#include "sorting.h"

static void swap(int* a, int* b) { int t = *a; *a = *b; *b = t; }

static void gnome_sort_standard(int arr[], int n) {
    int index = 0;
    while (index < n) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            swap(&arr[index], &arr[index - 1]);
            index--;
        }
    }
}

double run_gnome_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    
    gnome_sort_standard(arr, n);
    
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}