#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

// Estrutura de Nó para os baldes
struct Node {
    int data;
    struct Node *next;
};

// Inserção ordenada na lista encadeada (balde)
static void sorted_insert(struct Node **head_ref, int val) {
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = val;
    new_node->next = NULL;

    if (*head_ref == NULL || (*head_ref)->data >= val) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        struct Node *current = *head_ref;
        while (current->next != NULL && current->next->data < val) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

static void bucket_sort_standard(int arr[], int n) {
    if (n <= 0) return;

    // 1. Acha max para normalizar
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    max++; // Evita divisão por zero ou indice fora

    // 2. Cria baldes
    int num_buckets = n; // Regra de ouro: n baldes para n elementos
    struct Node **buckets = (struct Node**)calloc(num_buckets, sizeof(struct Node*));

    // 3. Espalha nos baldes
    for (int i = 0; i < n; i++) {
        int bi = (long long)num_buckets * arr[i] / max; // Índice proporcional
        sorted_insert(&buckets[bi], arr[i]);
    }

    // 4. Concatena de volta
    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        struct Node *node = buckets[i];
        while (node != NULL) {
            arr[index++] = node->data;
            struct Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(buckets);
}

double run_bucket_sort(int arr[], int n, int op) {
    clock_t start, end;
    start = clock();
    bucket_sort_standard(arr, n);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}