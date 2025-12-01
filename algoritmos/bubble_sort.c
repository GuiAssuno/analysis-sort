#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "sorting.h"

static void swap(int* a, int* b) 
{ 
    int t = *a; *a = *b; *b = t; 
    //g_swaps++;
}
    
// 1. Padrão
static void bubble_standard(int vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            //g_comparisons++;
            if (vetor[j] > vetor[j + 1]) swap(&vetor[j], &vetor[j + 1]);
        }
    }
}

// 2. Otimizado
static void bubble_optimized(int vetor[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                swap(&vetor[j], &vetor[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 3. Cocktail Shaker (Vai e Volta)
static void bubble_cocktail(int vetor[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;
        // Ida (Esquerda -> Direita)
        for (int i = start; i < end; ++i) {
            if (vetor[i] > vetor[i + 1]) {
                swap(&vetor[i], &vetor[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;

        // Volta (Direita -> Esquerda)
        for (int i = end - 1; i >= start; --i) {
            if (vetor[i] > vetor[i + 1]) {
                swap(&vetor[i], &vetor[i + 1]);
                swapped = true;
            }
        }
        start++;
    }
}

double inicia_bubble_sort(int vetor[], int n, int op) {
    clock_t inicio, fim;
    double tempo;
    //reset_metrics();

    void (*bubble)(int[], int) = NULL;
    
    // Mapeamento Python: standard->1, optimized->2, cocktail->3 (supondo ordem)
    // Ajuste conforme os valores que você enviará do Python ("standard", "optimized", "cocktail")
    // Sugiro usar strings ou garantir a ordem dos IDs. Aqui assumo IDs numéricos.
    
    if (op == 1)            // Padrão
    {   
        bubble = &bubble_standard;
    } 
    else 
        if (op == 2)        // Otimizado
        { 
            bubble = &bubble_optimized;
        } 
    else{                   // Cocktail
        bubble = &bubble_cocktail;               
    }
    
    inicio = clock();
    bubble(vetor, n);
    fim = clock();
    
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    return tempo;

}
