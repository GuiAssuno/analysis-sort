#include <stdio.h>
#include <time.h>
#include <stdlib.h>  
#include "sorting.h"

static void inverte(int* a, int* b);
static void quick_sort_3way(int vetor[], int esquerda, int direita, void(*metodo)(int[], int, int,int(*),int(*)));
static void quick_sort_hoare(int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int));
static void quick_sort_lomuto (int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int));

//        ############        LOMUTO        ############
static int lomuto_ultimo_elemento(int vetor[], int esquerda, int direita);
static int lomuto_primeiro_elemento(int vetor[], int esquerda, int direita);
static int lomuto_mediana_treis(int vetor[], int esquerda, int direita);
static int lomuto_aleatorio(int vetor[], int esquerda, int direita);
static int lomuto_mediana(int vetor[], int esquerda, int direita);

//        ############        HOARE        ############           
static int hoare_ultimo_elemento(int vetor[], int esquerda, int direita);
static int hoare_primeiro_elemento(int vetor[], int esquerda, int direita);
static int hoare_mediana_treis(int vetor[], int esquerda, int direita);
static int hoare_aleatorio(int vetor[], int esquerda, int direita);
static int hoare_mediana(int vetor[], int esquerda, int direita);

//        ############        3 VIAS       ############3-Way
static void via_ultimo_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
static void via_primeiro_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
static void via_mediana_treis(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
static void via_aleatorio(int vetor[], int esquerda, int direita, int *i_out, int *j_out);
static void via_mediana(int vetor[], int esquerda, int direita, int *i_out, int *j_out);

// Protótipo
static void quick_sort_dual_pivot(int vetor[], int low, int high);

double inicia_quick_sort(int vetor[], int n, int op) 
{
    clock_t inicio, fim;
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
    else 
        if (op > 40 && op < 50) 
        {
        // Como Dual Pivot é robusto, geralmente não varia o método de pivô 
    
        inicio = clock();// inicia a contagem de clock de execução
        
        //executa o algoritmo escolhido 
        quick_sort_dual_pivot(vetor, 0, n - 1);
        fim = clock();//termina a contagem de clock de orginização

        //converte contage de clocks para clocks por segundo
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        
        return tempo; //retorna o tempo de execução
    }

    if (metodo_3way)
    {
        inicio = clock();// inicia a contagem de clock de execução
        
        //executa o algoritmo escolhido junto com seu metodo de escolha de pivo selecionado
        quick_sort_3way(vetor, 0, n - 1, metodo_3way);  
        
        fim = clock();//termina a contagem de clock de orginização

        //converte contage de clocks para clocks por segundo
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        
        return tempo; //retorna o tempo de execução
    }
    else
        if (metodo_escolhido)
        {
            inicio = clock();// inicia a contagem de clock de execução
        
            //executa o algoritmo escolhido junto com seu metodo de escolha de pivo selecionado
            algoritmo_escolhido(vetor, 0, n - 1, metodo_escolhido);  
            
            fim = clock();//termina a contagem de clock de orginização

            //converte contage de clocks para clocks por segundo
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            
            return tempo; //retorna o tempo de execução
        }
    else return 0;  
}

static void inverte(int* a, int* b) {
    int t = *a;*a = *b;*b = t;
    //g_swaps++;
}

//=============================================== Pivôs ================================================

static int* pivot_mediana_3(int vetor[], int esquerda, int direita)
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
static int lomuto_ultimo_elemento(int vetor[], int esquerda, int direita) 
{
    int pivo = vetor[ direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {//g_comparisons++;
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

static int lomuto_primeiro_elemento(int vetor[], int esquerda, int direita) 
{
    inverte(&vetor[esquerda], &vetor[direita]);
    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) { //g_comparisons++;
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

static int lomuto_mediana_treis(int vetor[], int esquerda, int direita) 
{
    inverte (&vetor[direita], pivot_mediana_3(vetor, esquerda, direita));
    
    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {//g_comparisons++;
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

static int lomuto_aleatorio(int vetor[], int esquerda, int direita) 
{
    inverte (&vetor[direita], &vetor[esquerda + (rand() % (direita - esquerda + 1))]);
    
    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {//g_comparisons++;
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

static int lomuto_mediana(int vetor[], int esquerda, int direita) 
{
    inverte (&vetor[direita], &vetor[((esquerda + direita) / 2)]);

    int pivo = vetor[direita];
    int i = (esquerda - 1);
    
    for (int j = esquerda; j <= direita - 1; j++) {//g_comparisons++;
        if (vetor[j] < pivo) {
            i++;
            inverte(&vetor[i], &vetor[j]);
        }
    }
    inverte(&vetor[i + 1], &vetor[direita]);
    return (i + 1);
}

//=============================================== Hoare ================================================
static int hoare_ultimo_elemento(int vetor[], int esquerda, int direita) 
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

        //g_comparisons++;
        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

static int hoare_primeiro_elemento(int vetor[], int esquerda, int direita) 
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
        //g_comparisons++;
        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

static int hoare_mediana_treis(int vetor[], int esquerda, int direita) 
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
        //g_comparisons++;
        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

static int hoare_aleatorio(int vetor[], int esquerda, int direita) 
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
        
        //g_comparisons++;
        if (i >= j)
            return j;

        inverte(&vetor[i], &vetor[j]);
    }
}

static int hoare_mediana(int vetor[], int esquerda, int direita) 
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

        //g_comparisons++;
        if (i >= j) {
            break;
        }

        inverte(&vetor[i], &vetor[j]);
    }
    return (j);
}

//================================================= 3way ===============================================
static void via_ultimo_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out){

    inverte(&vetor[esquerda], &vetor[direita]);
    int pivo = vetor[direita]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {
        //g_comparisons++;
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

static void via_primeiro_elemento(int vetor[], int esquerda, int direita, int *i_out, int *j_out) {

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {
        //g_comparisons++;
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

static void via_mediana_treis(int vetor[], int esquerda, int direita, int *i_out, int *j_out) 
{
    inverte (&vetor[esquerda], pivot_mediana_3(vetor, esquerda, direita));

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {//g_comparisons++;
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

static void via_aleatorio(int vetor[], int esquerda, int direita, int *i_out, int *j_out) 
{    
    inverte (&vetor[esquerda], &vetor[esquerda + (rand() % (direita - esquerda + 1))]);

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {//g_comparisons++;
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

static void via_mediana(int vetor[], int esquerda, int direita, int *i_out, int *j_out) 
{
    inverte (&vetor[esquerda], &vetor[((esquerda + direita) / 2)]);

    int pivo = vetor[esquerda]; // Pivô na esquerda
    int lt = esquerda;          // Less Than (menores)
    int gt = direita;           // Greater Than (maiores)
    int i = esquerda + 1;       // Scan

    while (i <= gt) {//g_comparisons++;
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
static void quick_sort_lomuto (int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int)) 
{
    int parte;

    if (esquerda < direita) 
    {
        parte = metodo(vetor, esquerda, direita);
        quick_sort_lomuto(vetor, esquerda, parte - 1, metodo);
        quick_sort_lomuto(vetor, parte + 1, direita, metodo);
        
    }
}

static void quick_sort_hoare(int vetor[], int esquerda, int direita, int(*metodo)(int[], int, int)) 
{
    int parte;

    if (esquerda >= direita) {
        return;
    }
    parte = metodo(vetor, esquerda, direita);
    quick_sort_hoare(vetor, esquerda, parte, metodo);
    quick_sort_hoare(vetor, parte + 1, direita, metodo);
}

static void quick_sort_3way(int vetor[], int esquerda, int direita, void(*metodo)(int[], int, int, int(*), int(*))) 
{
    int parlt = 0, pargt =0 ;

    if (esquerda >= direita) {
        return;
    }
    metodo(vetor, esquerda, direita, &parlt, &pargt);
    quick_sort_3way(vetor, esquerda, parlt - 1, metodo);
    quick_sort_3way(vetor, pargt + 1, direita, metodo);
}


static void quick_sort_dual_pivot(int vetor[], int low, int high) {
    if (low < high) {
        // pivô 1 (lp) e pivô 2 (rp)
        if (vetor[low] > vetor[high]) {
            inverte(&vetor[low], &vetor[high]);
        }
        int lp = vetor[low];
        int rp = vetor[high];
        
        int i = low + 1;
        int k = low + 1;
        int g = high - 1;

        while (k <= g) {
            if (vetor[k] < lp) {
                inverte(&vetor[k], &vetor[i]);
                i++;
            } else if (vetor[k] >= rp) {
                while (vetor[g] > rp && k < g) {
                    g--;
                }
                inverte(&vetor[k], &vetor[g]);
                g--;
                if (vetor[k] < lp) {
                    inverte(&vetor[k], &vetor[i]);
                    i++;
                }
            }
            k++;
        }
        i--;
        g++;
        
        inverte(&vetor[low], &vetor[i]);
        inverte(&vetor[high], &vetor[g]);

        quick_sort_dual_pivot(vetor, low, i - 1);
        quick_sort_dual_pivot(vetor, i + 1, g - 1);
        quick_sort_dual_pivot(vetor, g + 1, high);
    }
}