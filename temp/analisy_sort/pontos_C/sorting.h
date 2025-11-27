#ifndef SORTING_H
#define SORTING_H

#define INSERTION_SORT_THRESHOLD 16

double inicia_quick_sort(int vetor[], int n, int op);
double run_bubble_sort(int vetor[], int n, int op);
double run_selection_sort(int vetor[], int n, int op); // Selection geralmente só tem 1 jeito, mas mantemos o padrão
double run_insertion_sort(int vetor[], int n, int op);
double run_merge_sort(int vetor[], int n, int op);
double run_heap_sort(int vetor[], int n, int op);
double run_shell_sort(int vetor[], int n, int op);
double run_radix_sort(int vetor[], int n, int op);

double test_intro_sort(int vetor[], int n);

double run_counting_sort(int vetor[], int n, int op);
double run_comb_sort(int vetor[], int n, int op);
double run_gnome_sort(int vetor[], int n, int op);
double run_intro_sort(int vetor[], int n, int op);

#endif

