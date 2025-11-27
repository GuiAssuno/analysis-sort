#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void counting_sort_radix(int arr[], int n, int exp) {
    int *output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};
    
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    
    free(output);
}

void radix_sort(int arr[], int n) {
    int max = get_max(arr, n);
    
    for (int exp = 1; max / exp > 0; exp *= 10)
        counting_sort_radix(arr, n, exp);
}

double test_radix_sort(int arr[], int n) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    radix_sort(arr, n);
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

