#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// função para gerar números aleatórios no vetor
void gerador_num(int vetor[], int n){

    // inicia o gerador de números de acordo com o horário atual, para garantir a aleatoriedade dos valores
    srand(time(NULL));

    // laço que percorre todo o vetor
    for(int i = 0; i < n; i++){
        // vetor recebe valores aleatórios de 0 a 1000
        vetor[i] = rand() % (1000);
    }

}

// função para inverter a ordem dos números dentro do vetor
void inversao(int vetor[], int id_num1, int id_num2){

    // declara a variável auxiliar, da qual recebe o valor do primeiro índice
    int aux = vetor[id_num1];
    // primeiro índice recebe o valor do segundo índice
    vetor[id_num1] = vetor[id_num2];
    // segundo índice recebe o valor da variável auxiliar
    vetor[id_num2] = aux;
}

// PIVÔS

// função que realiza o particionamento hoare usando o pivô do primeiro índice
int primeiro(int vetor[], int ptr_left, int ptr_right){

    // declara a variável pivô, da qual recebe o pivô do vetor
    int pivo = vetor[ptr_left];
    // declara a variável ponteiro i, da qual recebe o índice do pivô - 1
    int i = ptr_left-1;
    // declara a variável ponteiro j, da qual recebe o último índice do vetor atual + 1
    int j = ptr_right+1;

    // abre um laço while "infinito"
    while(1){

        // laços que andam com os ponteiros até identificar uma troca
        while(vetor[++i] < pivo);
        while(vetor[--j] > pivo);

        // caso os ponteiros cruzem, retorna j e sai do laço
        if(i >= j){
            return j;
            break;
        }

        // chama a função de troca
        inversao(vetor, i, j);
    }
}

int ultimo(int vetor[], int ptr_left, int ptr_right) {
    //cria partições maior que o pivot e menor que o pivot
    int pivo = vetor[ptr_right];
    int i = (ptr_left - 1);

    for (int j = ptr_left; j <= ptr_right - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            inversao(vetor, i, j); // executa troca quando acha um elemento menor igual o pivot
        }
    }
    inversao(vetor, i+1, ptr_right);// coloca o pivo no lugar exato dele ao final da operação
    return (i + 1);
}

int mediana(int vetor[], int left, int right) {
    int meio= (left + right) / 2;
    int a = vetor[right];
    int b = vetor[meio];
    int c = vetor[right];
    
    int mediana;

    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        mediana = meio;
    } else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        mediana = left;
    } else {
        mediana = left;
    }

    inversao(vetor, mediana, right);

    return vetor[right];
}

int ultimo_mediana(int vetor[], int ptr_left, int ptr_right) {
    int pivo = 0;
    //cria partições maior que o pivot e menor que o pivot
    pivo = mediana(vetor, ptr_left, ptr_right);
    int i = (ptr_left - 1);

    for (int j = ptr_left; j <= ptr_right - 1; j++) {
        if (vetor[j] < pivo) {
            i++;
            inversao(vetor, i, j); // executa troca quando acha um elemento menor igual o pivot
        }
    }
    inversao(vetor, i+1, ptr_right);// coloca o pivo no lugar exato dele ao final da operação
    return (i + 1);
}

// Função principal do Quick Sort 3-Way
void quickSort3Way(int vetor[], int low, int high) {
    if (high <= low) return;

    int lt = low;        // Ponteiro para elementos MENORES que o pivô
    int gt = high;       // Ponteiro para elementos MAIORES que o pivô
    int i = low + 1;     // Ponteiro de varredura
    int pivo = vetor[low]; // Escolhendo o primeiro elemento como pivô

    // Particionamento
    while (i <= gt) {
        if (vetor[i] < pivo) {
            inversao(vetor,lt,i);
            lt++;
            i++;
        } else if (vetor[i] > pivo) {
            inversao(vetor,i, gt);
            gt--;
        } else {
            // Se for igual ao pivô
            i++;
        }
    }

    // Chamadas recursivas
    quickSort3Way(vetor, low, lt - 1);
    quickSort3Way(vetor, gt + 1, high);
}

// PARTICIONAMENTOS

// função que inicia o particionamento hoare usando o pivô do primeiro índice
void inicia_primeiro(int vetor[], int left, int right) {

    // confere se a ordenação já terminou, verificando se ainda existem 2 ou mais valores no vetor
    if (left < right) {

        // recebe o índice do pivô
        int index_pivo = primeiro(vetor, left, right);
        // divide o vetor em dois para ordenar
        inicia_primeiro(vetor, left, index_pivo);
        inicia_primeiro(vetor, index_pivo+1, right);
    }
}

void inicia_ultimo(int vetor[], int left, int right) {
    if (left < right) {
        int index_pivo = ultimo(vetor, left, right);
        inicia_ultimo(vetor, left, index_pivo - 1);
        inicia_ultimo(vetor, index_pivo + 1, right);
    }
}

void inicia_ultimo_mediana(int vetor[], int left, int right) {
    if (left < right) {
        int index_pivo = ultimo_mediana(vetor, left, right);
        inicia_ultimo_mediana(vetor, left, index_pivo - 1);
        inicia_ultimo_mediana(vetor, index_pivo + 1, right);
    }
}

// INICIALIZADORES

// função que ordena o vetor com o método lomuto
double lomuto(int vetor [], int n){
    //função que inicia a contagem de tempo e inicia o quick sort
    clock_t start, end;
    double time_seg;

    start = clock();
    inicia_ultimo(vetor, 0, n-1);
    end = clock();

    time_seg = ((double) (end -start)) / CLOCKS_PER_SEC;

    return time_seg; // retorna o tempo em segundo da operação

}

double lomuto_mediana_3(int vetor [], int n){
    //função que inicia a contagem de tempo e inicia o quick sort
    clock_t start, end;
    double time_seg;

    start = clock();
    inicia_ultimo_mediana(vetor, 0, n-1);
    end = clock();

    time_seg = ((double) (end -start)) / CLOCKS_PER_SEC;

    return time_seg; // retorna o tempo em segundo da operação

}

// função que ordena o vetor com o método hoare
double hoare(int vetor [], int n){
    //função que inicia a contagem de tempo e inicia o quick sort
    clock_t start, end;
    double time_seg;

    start = clock();
    inicia_primeiro(vetor, 0, n-1);
    end = clock();

    time_seg = ((double) (end -start)) / CLOCKS_PER_SEC;

    return time_seg; // retorna o tempo em segundo da operação
    // chama a função para iniciar o particionamento hoare
    
}

// função que ordena o vetor com o método 3 vias
double via_3(int vetor [], int n){
    
    clock_t start, end;
    double time_seg;
    
    // inicia a contagem de tempo e inicia o quick sort
    start = clock();
    quickSort3Way(vetor, 0, n-1);
    end = clock();

    time_seg = ((double) (end -start)) / CLOCKS_PER_SEC;
    return time_seg; // retorna o tempo em segundo da operação
}
