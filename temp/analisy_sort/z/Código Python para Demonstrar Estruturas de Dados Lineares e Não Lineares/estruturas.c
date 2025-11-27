#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

// Variáveis globais (raízes)
NoLista *raiz_lista = NULL;
NoArvore *raiz_arvore = NULL;

// Tamanho máximo da string de visualização
#define MAX_VISUALIZACAO 1024

// =============================================================================
// Funções de Utilidade
// =============================================================================

void liberar_memoria_lista(NoLista *no) {
    NoLista *atual = no;
    NoLista *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

void liberar_memoria_arvore(NoArvore *no) {
    if (no != NULL) {
        liberar_memoria_arvore(no->esquerda);
        liberar_memoria_arvore(no->direita);
        free(no);
    }
}

// =============================================================================
// Parte 1: Lista (Linear)
// =============================================================================

void U_Lista_Inserir(int dado) {
    NoLista *novo_no = (NoLista*)malloc(sizeof(NoLista));
    if (novo_no == NULL) {
        fprintf(stderr, "Erro de alocação de memória para Lista.\n");
        return;
    }
    novo_no->dado = dado;
    novo_no->proximo = NULL;

    if (raiz_lista == NULL) {
        raiz_lista = novo_no;
    } else {
        NoLista *atual = raiz_lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }
}

void U_Lista_Remover(int dado) {
    NoLista *atual = raiz_lista;
    NoLista *anterior = NULL;

    while (atual != NULL && atual->dado != dado) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        // Elemento não encontrado
        return;
    }

    if (anterior == NULL) {
        // Removendo a raiz
        raiz_lista = atual->proximo;
    } else {
        // Removendo um nó no meio ou no fim
        anterior->proximo = atual->proximo;
    }

    free(atual);
}

char* U_Lista_Visualizar() {
    static char buffer[MAX_VISUALIZACAO];
    NoLista *atual = raiz_lista;
    int offset = 0;

    offset += snprintf(buffer + offset, MAX_VISUALIZACAO - offset, "[");

    while (atual != NULL) {
        offset += snprintf(buffer + offset, MAX_VISUALIZACAO - offset, "%d", atual->dado);
        if (atual->proximo != NULL) {
            offset += snprintf(buffer + offset, MAX_VISUALIZACAO - offset, ", ");
        }
        atual = atual->proximo;
    }

    offset += snprintf(buffer + offset, MAX_VISUALIZACAO - offset, "]");
    return buffer;
}

// =============================================================================
// Parte 2: Árvore Binária de Busca (Não Linear)
// =============================================================================

NoArvore* _U_Arvore_Inserir_Recursivo(NoArvore *no, int dado) {
    if (no == NULL) {
        NoArvore *novo_no = (NoArvore*)malloc(sizeof(NoArvore));
        if (novo_no == NULL) {
            fprintf(stderr, "Erro de alocação de memória para Árvore.\n");
            return NULL;
        }
        novo_no->dado = dado;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
        return novo_no;
    }

    if (dado < no->dado) {
        no->esquerda = _U_Arvore_Inserir_Recursivo(no->esquerda, dado);
    } else if (dado > no->dado) {
        no->direita = _U_Arvore_Inserir_Recursivo(no->direita, dado);
    }
    // Ignora se o dado for igual (não permite duplicatas)

    return no;
}

void U_Arvore_Inserir(int dado) {
    raiz_arvore = _U_Arvore_Inserir_Recursivo(raiz_arvore, dado);
}

NoArvore* _min_valor_no(NoArvore* no) {
    NoArvore* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

NoArvore* _U_Arvore_Remover_Recursivo(NoArvore* raiz, int dado) {
    if (raiz == NULL) return raiz;

    if (dado < raiz->dado) {
        raiz->esquerda = _U_Arvore_Remover_Recursivo(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = _U_Arvore_Remover_Recursivo(raiz->direita, dado);
    } else {
        // Nó com no máximo um filho
        if (raiz->esquerda == NULL) {
            NoArvore *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoArvore *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos: pega o sucessor in-order (menor na subárvore direita)
        NoArvore* temp = _min_valor_no(raiz->direita);

        // Copia o conteúdo do sucessor in-order para este nó
        raiz->dado = temp->dado;

        // Remove o sucessor in-order
        raiz->direita = _U_Arvore_Remover_Recursivo(raiz->direita, temp->dado);
    }
    return raiz;
}

void U_Arvore_Remover(int dado) {
    raiz_arvore = _U_Arvore_Remover_Recursivo(raiz_arvore, dado);
}

int U_Arvore_Acessar(int dado) {
    NoArvore *atual = raiz_arvore;
    while (atual != NULL) {
        if (dado == atual->dado) {
            return 1; // Encontrado
        } else if (dado < atual->dado) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }
    return 0; // Não encontrado
}

void _U_Arvore_Visualizar_InOrder(NoArvore *no, char *buffer, int *offset) {
    if (no != NULL) {
        _U_Arvore_Visualizar_InOrder(no->esquerda, buffer, offset);

        *offset += snprintf(buffer + *offset, MAX_VISUALIZACAO - *offset, "%d", no->dado);
        // Adiciona vírgula e espaço se não for o último (difícil de saber sem percorrer tudo)
        // Vamos simplificar e deixar a formatação para o Python, ou usar um delimitador.
        // Usaremos um espaço como delimitador simples.
        *offset += snprintf(buffer + *offset, MAX_VISUALIZACAO - *offset, " ");

        _U_Arvore_Visualizar_InOrder(no->direita, buffer, offset);
    }
}

char* U_Arvore_Visualizar() {
    static char buffer[MAX_VISUALIZACAO];
    int offset = 0;

    _U_Arvore_Visualizar_InOrder(raiz_arvore, buffer, &offset);

    // Remove o espaço extra no final, se houver
    if (offset > 0 && buffer[offset - 1] == ' ') {
        buffer[offset - 1] = '\0';
    } else {
        buffer[offset] = '\0';
    }

    return buffer;
}

// Função de inicialização para liberar memória (chamada no final da aplicação Python)
void liberar_tudo() {
    liberar_memoria_lista(raiz_lista);
    liberar_memoria_arvore(raiz_arvore);
    raiz_lista = NULL;
    raiz_arvore = NULL;
}
