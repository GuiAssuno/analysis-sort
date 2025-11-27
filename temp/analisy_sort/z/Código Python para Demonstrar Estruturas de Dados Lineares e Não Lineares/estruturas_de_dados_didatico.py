# -*- coding: utf-8 -*-
"""
Demonstração Didática de Estruturas de Dados em Python

Objetivo:
1. Apresentar e comparar Estruturas de Dados Lineares (Lista, Fila) e Não Lineares (Árvore Binária).
2. Utilizar um conceito unificado de operações, o "U" (Unificar), para facilitar a compreensão.

Conceito "U" (Unificar) para Operações:
Para simplificar o aprendizado, as operações essenciais em qualquer estrutura de dados serão
agrupadas e apresentadas de forma unificada:

- U_Inserir (Unificar Inserção): Adicionar um novo elemento à estrutura.
- U_Remover (Unificar Remoção): Retirar um elemento da estrutura.
- U_Acessar (Unificar Acesso): Obter um elemento ou percorrer a estrutura.
- U_Visualizar (Unificar Visualização): Mostrar o estado atual da estrutura.

--------------------------------------------------------------------------------
Parte 1: Estruturas de Dados Lineares (Sequência)
--------------------------------------------------------------------------------
"""

# 1.1 Lista (List) - Acesso por Índice
class ListaLinear:
    def __init__(self):
        self.dados = []

    def U_Inserir(self, elemento, indice=None):
        """Insere um elemento. Se índice for None, insere no final (append)."""
        if indice is None:
            self.dados.append(elemento)
            print(f"-> Lista: Inserido '{elemento}' no final.")
        else:
            self.dados.insert(indice, elemento)
            print(f"-> Lista: Inserido '{elemento}' no índice {indice}.")

    def U_Remover(self, elemento=None, indice=None):
        """Remove um elemento. Prioriza remoção por elemento, depois por índice."""
        try:
            if elemento is not None:
                self.dados.remove(elemento)
                print(f"-> Lista: Removido o elemento '{elemento}'.")
            elif indice is not None:
                removido = self.dados.pop(indice)
                print(f"-> Lista: Removido o elemento '{removido}' do índice {indice}.")
            else:
                print("-> Lista: Erro! Especifique elemento ou índice para remover.")
        except ValueError:
            print(f"-> Lista: Erro! Elemento '{elemento}' não encontrado.")
        except IndexError:
            print(f"-> Lista: Erro! Índice {indice} fora do limite.")

    def U_Acessar(self, indice):
        """Acessa um elemento pelo índice."""
        try:
            return self.dados[indice]
        except IndexError:
            return f"-> Lista: Erro! Índice {indice} fora do limite."

    def U_Visualizar(self):
        """Mostra o estado atual da lista."""
        print(f"-> Lista Atual: {self.dados}")
        print(f"   (Linear: Elementos dispostos em sequência, um após o outro.)")

# 1.2 Fila (Queue) - FIFO (First-In, First-Out)
from collections import deque

class FilaLinear:
    def __init__(self):
        # Usamos deque para operações eficientes de inserção/remoção em ambas as extremidades
        self.dados = deque()

    def U_Inserir(self, elemento):
        """Insere no final da fila (enqueue)."""
        self.dados.append(elemento)
        print(f"-> Fila: Inserido '{elemento}' no final (Entrada).")

    def U_Remover(self):
        """Remove do início da fila (dequeue)."""
        if self.dados:
            removido = self.dados.popleft()
            print(f"-> Fila: Removido '{removido}' do início (Saída).")
            return removido
        else:
            print("-> Fila: Erro! Fila vazia.")
            return None

    def U_Acessar(self):
        """Acessa o primeiro elemento (peek)."""
        if self.dados:
            return self.dados[0]
        else:
            return "-> Fila: Fila vazia."

    def U_Visualizar(self):
        """Mostra o estado atual da fila."""
        print(f"-> Fila Atual (Início -> Fim): {list(self.dados)}")
        print(f"   (Linear: Ordem estrita de chegada e saída.)")

"""
--------------------------------------------------------------------------------
Parte 2: Estruturas de Dados Não Lineares (Hierarquia)
--------------------------------------------------------------------------------
"""

# 2.1 Nó da Árvore
class NoArvore:
    def __init__(self, valor):
        self.valor = valor
        self.esquerda = None
        self.direita = None

# 2.2 Árvore Binária de Busca (Binary Search Tree - BST)
class ArvoreNaoLinear:
    def __init__(self):
        self.raiz = None

    def U_Inserir(self, valor):
        """Insere um valor na árvore, mantendo a ordem BST."""
        if self.raiz is None:
            self.raiz = NoArvore(valor)
            print(f"-> Árvore: Inserido '{valor}' como raiz.")
        else:
            self._inserir_recursivo(self.raiz, valor)

    def _inserir_recursivo(self, no_atual, valor):
        if valor < no_atual.valor:
            if no_atual.esquerda is None:
                no_atual.esquerda = NoArvore(valor)
                print(f"-> Árvore: Inserido '{valor}' à esquerda de '{no_atual.valor}'.")
            else:
                self._inserir_recursivo(no_atual.esquerda, valor)
        elif valor > no_atual.valor:
            if no_atual.direita is None:
                no_atual.direita = NoArvore(valor)
                print(f"-> Árvore: Inserido '{valor}' à direita de '{no_atual.valor}'.")
            else:
                self._inserir_recursivo(no_atual.direita, valor)
        else:
            print(f"-> Árvore: Valor '{valor}' já existe. Não inserido.")

    def U_Remover(self, valor):
        """Remove um valor da árvore."""
        self.raiz = self._remover_recursivo(self.raiz, valor)
        if self.raiz is not None or valor is not None:
            print(f"-> Árvore: Tentativa de remover '{valor}'.")

    def _remover_recursivo(self, no_atual, valor):
        if no_atual is None:
            return no_atual

        if valor < no_atual.valor:
            no_atual.esquerda = self._remover_recursivo(no_atual.esquerda, valor)
        elif valor > no_atual.valor:
            no_atual.direita = self._remover_recursivo(no_atual.direita, valor)
        else:
            # Caso 1: Nó com no máximo um filho
            if no_atual.esquerda is None:
                return no_atual.direita
            elif no_atual.direita is None:
                return no_atual.esquerda

            # Caso 2: Nó com dois filhos (encontra o sucessor in-order)
            temp = self._min_valor_no(no_atual.direita)
            no_atual.valor = temp.valor
            no_atual.direita = self._remover_recursivo(no_atual.direita, temp.valor)

        return no_atual

    def _min_valor_no(self, no):
        atual = no
        while atual.esquerda is not None:
            atual = atual.esquerda
        return atual

    def U_Acessar(self, valor):
        """Busca um valor na árvore."""
        resultado = self._buscar_recursivo(self.raiz, valor)
        if resultado:
            print(f"-> Árvore: Valor '{valor}' encontrado.")
        else:
            print(f"-> Árvore: Valor '{valor}' NÃO encontrado.")
        return resultado

    def _buscar_recursivo(self, no_atual, valor):
        if no_atual is None or no_atual.valor == valor:
            return no_atual
        if valor < no_atual.valor:
            return self._buscar_recursivo(no_atual.esquerda, valor)
        return self._buscar_recursivo(no_atual.direita, valor)

    def U_Visualizar(self):
        """Mostra o estado atual da árvore (percurso In-Order)."""
        print("-> Árvore Atual (Percurso In-Order - Ordenado):")
        elementos = self._inorder_recursivo(self.raiz)
        print(f"   {elementos}")
        print(f"   (Não Linear: Elementos conectados em uma hierarquia (pai/filho), não em sequência.)")

    def _inorder_recursivo(self, no_atual, elementos=None):
        if elementos is None:
            elementos = []
        if no_atual:
            self._inorder_recursivo(no_atual.esquerda, elementos)
            elementos.append(no_atual.valor)
            self._inorder_recursivo(no_atual.direita, elementos)
        return elementos

"""
--------------------------------------------------------------------------------
Parte 3: Demonstração e Comparação
--------------------------------------------------------------------------------
"""

def demonstracao_linear():
    print("\n" + "="*50)
    print("DEMONSTRAÇÃO DE ESTRUTURAS LINEARES (Lista e Fila)")
    print("="*50)

    # Demonstração da Lista
    print("\n--- 1. Lista (Acesso por Índice) ---")
    lista = ListaLinear()
    lista.U_Visualizar()

    lista.U_Inserir("A")
    lista.U_Inserir("C")
    lista.U_Inserir("B", indice=1) # Inserção no meio (característica linear flexível)
    lista.U_Visualizar()

    print(f"U_Acessar (índice 0): {lista.U_Acessar(0)}")
    print(f"U_Acessar (índice 1): {lista.U_Acessar(1)}")

    lista.U_Remover(elemento="A")
    lista.U_Visualizar()

    lista.U_Remover(indice=0)
    lista.U_Visualizar()

    # Demonstração da Fila
    print("\n--- 2. Fila (FIFO - First-In, First-Out) ---")
    fila = FilaLinear()
    fila.U_Visualizar()

    fila.U_Inserir("Pessoa 1")
    fila.U_Inserir("Pessoa 2")
    fila.U_Inserir("Pessoa 3")
    fila.U_Visualizar()

    print(f"U_Acessar (Próximo a ser atendido): {fila.U_Acessar()}")

    fila.U_Remover() # Sai Pessoa 1
    fila.U_Visualizar()

    fila.U_Remover() # Sai Pessoa 2
    fila.U_Visualizar()

def demonstracao_nao_linear():
    print("\n" + "="*50)
    print("DEMONSTRAÇÃO DE ESTRUTURA NÃO LINEAR (Árvore Binária)")
    print("="*50)

    # Demonstração da Árvore
    arvore = ArvoreNaoLinear()
    arvore.U_Visualizar()

    # Inserção de valores (a ordem afeta a estrutura da árvore)
    print("\n--- Inserindo valores (Ordem: 50, 30, 70, 20, 40, 60, 80) ---")
    arvore.U_Inserir(50)
    arvore.U_Inserir(30)
    arvore.U_Inserir(70)
    arvore.U_Inserir(20)
    arvore.U_Inserir(40)
    arvore.U_Inserir(60)
    arvore.U_Inserir(80)
    arvore.U_Visualizar()

    # Acesso (Busca)
    print("\n--- Acesso (Busca) ---")
    arvore.U_Acessar(40)
    arvore.U_Acessar(99)

    # Remoção
    print("\n--- Remoção ---")
    arvore.U_Remover(20) # Remoção de nó folha
    arvore.U_Visualizar()

    arvore.U_Remover(70) # Remoção de nó com um filho (60 ou 80)
    arvore.U_Visualizar()

    arvore.U_Remover(50) # Remoção da raiz (nó com dois filhos)
    arvore.U_Visualizar()

def comparacao_final():
    print("\n" + "="*50)
    print("COMPARAÇÃO FINAL: LINEAR vs NÃO LINEAR")
    print("="*50)

    print("""
    A principal diferença reside na **organização** e no **acesso** aos dados:

    1. ESTRUTURAS LINEARES (Lista, Fila):
       - Organização: Sequencial. Cada elemento tem um antecessor e um sucessor (exceto o primeiro e o último).
       - Acesso: Baseado na posição (índice) ou na ordem de chegada/saída (FIFO/LIFO).
       - Exemplo: Uma fila de pessoas no banco, uma lista de compras.

    2. ESTRUTURAS NÃO LINEARES (Árvore, Grafo):
       - Organização: Hierárquica ou em rede. Um elemento pode ter múltiplos "filhos" ou conexões.
       - Acesso: Baseado na relação entre os elementos (navegação de pai para filho, ou entre nós conectados).
       - Exemplo: A estrutura de pastas em um computador, uma rede social.

    O conceito "U" (Unificar) mostra que, independentemente da complexidade,
    as operações fundamentais (Inserir, Remover, Acessar, Visualizar) são as mesmas,
    mas a **forma como são implementadas** e o **tempo que levam** mudam drasticamente
    entre estruturas lineares e não lineares.
    """)

if __name__ == "__main__":
    demonstracao_linear()
    demonstracao_nao_linear()
    comparacao_final()
