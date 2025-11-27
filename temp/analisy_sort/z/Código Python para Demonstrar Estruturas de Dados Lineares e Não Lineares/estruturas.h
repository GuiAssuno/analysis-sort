#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Definição da Estrutura de Lista (Linear)
typedef struct NoLista {
    int dado;
    struct NoLista *proximo;
} NoLista;

// Definição da Estrutura de Árvore (Não Linear)
typedef struct NoArvore {
    int dado;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

// Variáveis globais para as raízes das estruturas
extern NoLista *raiz_lista;
extern NoArvore *raiz_arvore;

// Funções para Lista (Linear)
void U_Lista_Inserir(int dado);
void U_Lista_Remover(int dado);
char* U_Lista_Visualizar(); // Retorna string formatada

// Funções para Árvore (Não Linear)
void U_Arvore_Inserir(int dado);
void U_Arvore_Remover(int dado);
int U_Arvore_Acessar(int dado); // Retorna 1 se encontrado, 0 caso contrário
char* U_Arvore_Visualizar(); // Retorna string formatada

// Funções de utilidade
void liberar_memoria_lista(NoLista *no);
void liberar_memoria_arvore(NoArvore *no);

#endif // ESTRUTURAS_H
