# -*- coding: utf-8 -*-
from ctypes import cdll, c_int, c_char_p, string_at
import os

# 1. Carregar a Biblioteca C
try:
    LIB_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "estruturas_c", "libestruturas.so")
    lib = cdll.LoadLibrary(LIB_PATH)
except OSError as e:
    print(f"Erro ao carregar a biblioteca C: {e}")
    exit()

# 2. Configurar as Assinaturas das Funções C
lib.U_Lista_Inserir.argtypes = [c_int]
lib.U_Lista_Visualizar.restype = c_char_p
lib.U_Lista_Remover.argtypes = [c_int]

lib.U_Arvore_Inserir.argtypes = [c_int]
lib.U_Arvore_Visualizar.restype = c_char_p
lib.U_Arvore_Acessar.argtypes = [c_int]
lib.U_Arvore_Acessar.restype = c_int
lib.U_Arvore_Remover.argtypes = [c_int]

lib.liberar_tudo.argtypes = []

def visualizar_lista():
    c_string = lib.U_Lista_Visualizar()
    return string_at(c_string).decode('utf-8')

def visualizar_arvore():
    c_string = lib.U_Arvore_Visualizar()
    py_string = string_at(c_string).decode('utf-8')
    # Formatação simples para visualização
    return f"[{py_string.strip().replace(' ', ', ')}]"

# =============================================================================
# Teste de Integração
# =============================================================================
print("--- Teste de Integração Python (ctypes) e C (Estruturas de Dados) ---")

# 1. Teste da Lista (Linear)
print("\n[1. Lista (Linear)]")
lib.U_Lista_Inserir(10)
lib.U_Lista_Inserir(20)
lib.U_Lista_Inserir(30)
print(f"Lista após inserções: {visualizar_lista()}")

lib.U_Lista_Remover(20)
print(f"Lista após remover 20: {visualizar_lista()}")

lib.U_Lista_Remover(10)
print(f"Lista após remover 10: {visualizar_lista()}")

# 2. Teste da Árvore (Não Linear)
print("\n[2. Árvore Binária de Busca (Não Linear)]")
lib.U_Arvore_Inserir(50)
lib.U_Arvore_Inserir(30)
lib.U_Arvore_Inserir(70)
lib.U_Arvore_Inserir(20)
lib.U_Arvore_Inserir(40)
print(f"Árvore após inserções (In-Order): {visualizar_arvore()}")

# Acesso
print(f"Acessar 40: {'Encontrado' if lib.U_Arvore_Acessar(40) else 'Não Encontrado'}")
print(f"Acessar 99: {'Encontrado' if lib.U_Arvore_Acessar(99) else 'Não Encontrado'}")

# Remoção
lib.U_Arvore_Remover(30) # Nó com dois filhos
print(f"Árvore após remover 30: {visualizar_arvore()}")

# 3. Limpeza de Memória C
lib.liberar_tudo()
print("\nMemória C liberada com sucesso.")
