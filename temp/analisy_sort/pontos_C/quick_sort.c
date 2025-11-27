#include <stdio.h>
#include <time.h>
#include <stdlib.h>  
#include "sorting.h"

void quick_sort_3way(int vetor[], int esquerda, int direita, void(*metodo)(int[], int, int,int(*),int(*)));
void quick_sort_hoare(int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int));
void quick_sort_lomuto (int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int));

//        ############        LOMUTO        ############
int lomuto_ultimo_elemento(int vetor[], int esquerda, int direita);
int lomuto_primeiro_elemento(int vetor[], int esquerda, int direita);
int lomuto_mediana_treis(int vetor[], int esquerda, int direita);
int lomuto_aleatorio(int vetor[], int esquerda, int direita);
int lomuto_mediana(int vetor[], int esquerda, int direita);

//        ############        HOARE        ############           
int hoare_ultimo_elemento(int vetor[], int esquerda, int direita);
int hoare_primeiro_elemento(int vetor[], int esquerda, int direita);
int hoare_mediana_treis(int vetor[], int esquerda, int direita);
int hoare_aleatorio(int vetor[], int esquerda, int direita);
int hoare_mediana(int vetor[], int esquerda, int direita);

//        ############        3 VIAS       ############3-Way
void via_ultimo_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
void via_primeiro_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
void via_mediana_treis(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
void via_aleatorio(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
void via_mediana(int vetor[], int esquerda, int direita, int *i_out, int *j_out);

double inicia_quick_sort(int vetor[], int n, int op) 
{
    clock_t start, fim;
    double tempo;
    void (*algoritmo_escolhido)(int[], int, int, int(*)(int[], int, int)) = NULL;
    int (*metodo_escolhido)(int[], int, int) = NULL;
    void (*metodo_3way)(int[],int,int,int(*),int(*)) = NULL;

//configurando os algoritimos com seus metodos de escolha de pivo
    if ((op > 10)&&(op < 20))
    {// --- --- --- --- --- --- --- --- --- --- --- lomuto  --- --- --- --- --- --- --- --- --- --- ---
        algoritmo_escolhido = &quick_sort_lomuto;

        switch (op)
        {// opções de pivôs
        case 11: metodo_escolhido = &lomuto_ultimo_elemento; break;
        case 12: metodo_escolhido = &lomuto_primeiro_elemento; break;
        case 13: metodo_escolhido = &lomuto_mediana_treis; break;
        case 14: metodo_escolhido = &lomuto_aleatorio; break;
        case 15: metodo_escolhido = &lomuto_mediana; break;
        default: break;
        }
    }
    else
        if(op > 20 && (op < 30))
        {// --- --- --- --- --- --- --- --- --- --- --- hoare --- --- --- --- --- --- --- --- --- --- ---
            algoritmo_escolhido = &quick_sort_hoare;
        switch (op)
        {// opções de pivôs
        case 21: metodo_escolhido = &hoare_ultimo_elemento; break;
        case 22: metodo_escolhido = &hoare_primeiro_elemento; break;
        case 23: metodo_escolhido = &hoare_mediana_treis; break;
        case 24: metodo_escolhido = &hoare_aleatorio; break;
        case 25: metodo_escolhido = &hoare_mediana; break;
        
        default: break;
        }        
    }
    else 
        if(op > 30 && (op < 40))
        {// --- --- --- --- --- --- --- --- --- --- --- 3way --- --- --- --- --- --- --- --- --- --- ---
        switch (op)
        {// opções de pivôs
        case 31: metodo_3way = &via_ultimo_elemento; break;
        case 32: metodo_3way = &via_primeiro_elemento; break;
        case 33: metodo_3way = &via_mediana_treis; break;
        case 34: metodo_3way = &via_aleatorio; break;
        case 35: metodo_3way = &via_mediana; break;
        
        default: break;
        }        
    }


    if (metodo_3way)
    {
        start = clock();// inicia a contagem de clock de execução
        
        //executa o algoritmo escolhido junto com seu metodo de escolha de pivo selecionado
        quick_sort_3way(vetor, 0, n - 1, metodo_3way);  
        
        fim = clock();//termina a contagem de clock de orginização

        //converte contage de clocks para clocks por segundo
        tempo = ((double)(fim - start)) / CLOCKS_PER_SEC;
        
        return tempo; //retorna o tempo de execução
    }
    else
        if (metodo_escolhido)
        {
            start = clock();// inicia a contagem de clock de execução
        
            //executa o algoritmo escolhido junto com seu metodo de escolha de pivo selecionado
            algoritmo_escolhido(vetor, 0, n - 1, metodo_escolhido);  
            
            fim = clock();//termina a contagem de clock de orginização

            //converte contage de clocks para clocks por segundo
            tempo = ((double)(fim - start)) / CLOCKS_PER_SEC;
            
            return tempo; //retorna o tempo de execução
        }
    else return 0;  
}

void inverte(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

//=============================================== Pivôs ================================================

int* pivot_mediana_3(int vetor[], int esquerda, int direita)
{
    int meio= (esquerda + direita) / 2;
    int a = vetor[esquerda];
    int b = vetor[meio];
    int c = vetor[direita];
    
    int mediana;

    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        mediana = meio;
    } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        mediana = esquerda;
    } else {
        mediana = direita;
    }

    return &vetor[mediana];

}

//=============================================== Lomuto ===============================================
int lomuto_ultimo_elemento(int vetor[], int esquerda, int direita) 
{
    int pivo = vetor[ direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

int lomuto_primeiro_elemento(int vetor[], int esquerda, int direita) 
{
    inverte(&vetor[esquerda], &vetor[direita]);
    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

int lomuto_mediana_treis(int vetor[], int esquerda, int direita) 
{
    inverte (&vetor[direita], pivot_mediana_3(vetor, esquerda, direita));
    
    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

int lomuto_aleatorio(int vetor[], int esquerda, int direita) 
{
    inverte (&vetor[direita], &vetor[esquerda + (rand() % (direita - esquerda + 1))]);
    
    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

int lomuto_mediana(int vetor[], int esquerda, int direita) 
{
    inverte (&vetor[direita], &vetor[((esquerda + direita) / 2)]);

    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

//=============================================== Hoare ================================================
int hoare_ultimo_elemento(int vetor[], int esquerda, int direita) 
{
    inverte(&vetor[esquerda], &vetor[direita]);
    int pivo = vetor[esquerda];
    int i = (esquerda - 1);
    int j = direita + 1;

    while (1) {

        do {
            i++;
        } while (vetor[i] < pivo);

        do {
            j--;
        } while (vetor[j] > pivo);

        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

int hoare_primeiro_elemento(int vetor[], int esquerda, int direita) 
{
    int pivo = vetor[esquerda];
    int i = (esquerda - 1);
    int j = direita + 1;

    while (1) {

        do {
            i++;
        } while (vetor[i] < pivo);


        do {
            j--;
        } while (vetor[j] > pivo);

        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

int hoare_mediana_treis(int vetor[], int esquerda, int direita) 
{    
    inverte (&vetor[esquerda], pivot_mediana_3(vetor, esquerda, direita));

    int pivo = vetor[esquerda];
    int i = (esquerda - 1);
    int j = direita + 1;

    while (1) {

        do {
            i++;
        } while (vetor[i] < pivo);


        do {
            j--;
        } while (vetor[j] > pivo);

        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

int hoare_aleatorio(int vetor[], int esquerda, int direita) 
{    
    inverte (&vetor[esquerda], &vetor[esquerda + (rand() % (direita - esquerda + 1))]);

    int pivo = vetor[esquerda];
    int i = (esquerda - 1);
    int j = direita + 1;

    while (1) {
        do {
            i++;
        } while (vetor[i] < pivo);


        do {
            j--;
        } while (vetor[j] > pivo);

        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

int hoare_mediana(int vetor[], int esquerda, int direita) 
{
    inverte (&vetor[esquerda], &vetor[((esquerda + direita) / 2)]);

    int pivo = vetor[esquerda];
    int i = esquerda - 1;
    int j = direita + 1;

    while (1) {
        
        do {
            i++;
        } while (vetor[i] < pivo);

        do {
            j--;
        } while (vetor[j] > pivo);

        if (i >= j) {
            break;
        }

        inverte(&vetor[i], &vetor[j]);
    }
    return (j);
}

//================================================= 3way ===============================================
void via_ultimo_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out){

    inverte(&vetor[esquerda], &vetor[direita]);
    int pivo = vetor[direita]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {
        if (vetor[i] < pivo) {
            inverte(&vetor[lt], &vetor[i]);
            lt++;
            i++;
        } else if (vetor[i] > pivo) {
            inverte(&vetor[i], &vetor[gt]);
            gt--;
            // Não incrementa i, pois o que veio de gt é desconhecido
        } else {
            // Se for igual
            i++;
        }
    }
    
    // Atualiza os ponteiros para a função chamadora saber onde cortar
    *i_out = lt; 
    *j_out = gt;
}

void via_primeiro_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out) {

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {
        if (vetor[i] < pivo) {
            inverte(&vetor[lt], &vetor[i]);
            lt++;
            i++;
        } else if (vetor[i] > pivo) {
            inverte(&vetor[i], &vetor[gt]);
            gt--;
            // Não incrementa i, pois o que veio de gt é desconhecido
        } else {
            // Se for igual
            i++;
        }
    }
    
    // Atualiza os ponteiros para a função chamadora saber onde cortar
    *i_out = lt; 
    *j_out = gt;
}

void via_mediana_treis(int vetor[], int esquerda, int direita, int *i_out, int *j_out) 
{
    inverte (&vetor[esquerda], pivot_mediana_3(vetor, esquerda, direita));

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {
        if (vetor[i] < pivo) {
            inverte(&vetor[lt], &vetor[i]);
            lt++;
            i++;
        } else if (vetor[i] > pivo) {
            inverte(&vetor[i], &vetor[gt]);
            gt--;
            // Não incrementa i, pois o que veio de gt é desconhecido
        } else {
            // Se for igual
            i++;
        }
    }
    
    // Atualiza os ponteiros para a função chamadora saber onde cortar
    *i_out = lt; 
    *j_out = gt;
}

void via_aleatorio(int vetor[], int esquerda, int direita, int *i_out, int *j_out) 
{    
    inverte (&vetor[esquerda], &vetor[esquerda + (rand() % (direita - esquerda + 1))]);

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {
        if (vetor[i] < pivo) {
            inverte(&vetor[lt], &vetor[i]);
            lt++;
            i++;
        } else if (vetor[i] > pivo) {
            inverte(&vetor[i], &vetor[gt]);
            gt--;
            // Não incrementa i, pois o que veio de gt é desconhecido
        } else {
            // Se for igual
            i++;
        }
    }
    
    // Atualiza os ponteiros para a função chamadora saber onde cortar
    *i_out = lt; 
    *j_out = gt;
}

void via_mediana(int vetor[], int esquerda, int direita, int *i_out, int *j_out) 
{
    inverte (&vetor[esquerda], &vetor[((esquerda + direita) / 2)]);

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {
        if (vetor[i] < pivo) {
            inverte(&vetor[lt], &vetor[i]);
            lt++;
            i++;
        } else if (vetor[i] > pivo) {
            inverte(&vetor[i], &vetor[gt]);
            gt--;
            // Não incrementa i, pois o que veio de gt é desconhecido
        } else {
            // Se for igual
            i++;
        }
    }
    
    // Atualiza os ponteiros para a função chamadora saber onde cortar
    *i_out = lt; 
    *j_out = gt;
}

//============================================= Algoritmos =============================================
void quick_sort_lomuto (int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int)) 
{
    int parte;

    if (esquerda < direita) 
    {
        parte = metodo(vetor, esquerda, direita);
        quick_sort_lomuto(vetor, esquerda, parte - 1, metodo);
        quick_sort_lomuto(vetor, parte + 1, direita, metodo);
        
    }
}

void quick_sort_hoare(int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int)) 
{
    int parte;

    if (esquerda >= direita) {
        return;
    }
    parte = metodo(vetor, esquerda, direita);
    quick_sort_hoare(vetor, esquerda, parte, metodo);
    quick_sort_hoare(vetor, parte + 1, direita, metodo);
}

void quick_sort_3way(int vetor[], int esquerda, int direita, void(*metodo)(int[], int, int, int(*), int(*))) 
{
    int parlt = 0, pargt =0 ;

    if (esquerda >= direita) {
        return;
    }
    metodo(vetor, esquerda, direita, &parlt, &pargt);
    quick_sort_3way(vetor, esquerda, parlt - 1, metodo);
    quick_sort_3way(vetor, pargt + 1, direita, metodo);
}














// Protótipo
static void quick_sort_dual_pivot(int vetor[], int low, int high);

// Implementação
static void quick_sort_dual_pivot(int arr[], int low, int high) {
    if (low < high) {
        // pivô 1 (lp) e pivô 2 (rp)
        if (arr[low] > arr[high]) {
            inverte(&arr[low], &arr[high]);
        }
        int lp = arr[low];
        int rp = arr[high];
        
        int i = low + 1;
        int k = low + 1;
        int g = high - 1;

        while (k <= g) {
            if (arr[k] < lp) {
                inverte(&arr[k], &arr[i]);
                i++;
            } else if (arr[k] >= rp) {
                while (arr[g] > rp && k < g) {
                    g--;
                }
                inverte(&arr[k], &arr[g]);
                g--;
                if (arr[k] < lp) {
                    inverte(&arr[k], &arr[i]);
                    i++;
                }
            }
            k++;
        }
        i--;
        g++;
        
        inverte(&arr[low], &arr[i]);
        inverte(&arr[high], &arr[g]);

        quick_sort_dual_pivot(arr, low, i - 1);
        quick_sort_dual_pivot(arr, i + 1, g - 1);
        quick_sort_dual_pivot(arr, g + 1, high);
    }
}

// ATUALIZAÇÃO NA inicia_quick_sort (Dentro do quick_sort.c)
// Adicione este bloco else if:

// ... (bloco do 3-Way termina no op < 40) ...
else if (op > 40 && op < 50) { // Dual Pivot (Ex: op 41, 42...)
    // Como Dual Pivot é robusto, geralmente não variamos o método de pivô 
    // da mesma forma, mas usamos a função base.
    quick_sort_dual_pivot(vetor, 0, n - 1);
}