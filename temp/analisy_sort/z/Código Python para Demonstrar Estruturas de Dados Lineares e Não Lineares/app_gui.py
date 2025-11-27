# -*- coding: utf-8 -*-
import tkinter as tk
from tkinter import ttk, messagebox
from ctypes import cdll, c_int, c_char_p, c_void_p, string_at
import os

# 1. Carregar a Biblioteca C
try:
    # O caminho deve ser ajustado se o script for movido
    LIB_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "libestruturas.so")
    lib = cdll.LoadLibrary(LIB_PATH)
except OSError as e:
    print(f"Erro ao carregar a biblioteca C: {e}")
    print("Certifique-se de que 'libestruturas.so' foi compilada corretamente e está no diretório 'estruturas_c'.")
    exit()

# 2. Configurar as Assinaturas das Funções C
# Funções de Lista (Linear)
lib.U_Lista_Inserir.argtypes = [c_int]
lib.U_Lista_Inserir.restype = c_void_p

lib.U_Lista_Remover.argtypes = [c_int]
lib.U_Lista_Remover.restype = c_void_p

lib.U_Lista_Visualizar.argtypes = []
lib.U_Lista_Visualizar.restype = c_char_p # Retorna um ponteiro para char*

# Funções de Árvore (Não Linear)
lib.U_Arvore_Inserir.argtypes = [c_int]
lib.U_Arvore_Inserir.restype = c_void_p

lib.U_Arvore_Remover.argtypes = [c_int]
lib.U_Arvore_Remover.restype = c_void_p

lib.U_Arvore_Acessar.argtypes = [c_int]
lib.U_Arvore_Acessar.restype = c_int # Retorna 1 (True) ou 0 (False)

lib.U_Arvore_Visualizar.argtypes = []
lib.U_Arvore_Visualizar.restype = c_char_p # Retorna um ponteiro para char*

# Função de limpeza de memória
lib.liberar_tudo.argtypes = []
lib.liberar_tudo.restype = c_void_p


class EstruturaDadosApp:
    def __init__(self, master):
        self.master = master
        master.title("Estruturas de Dados: Python (GUI) + C (Operações)")
        master.protocol("WM_DELETE_WINDOW", self.on_closing) # Chama a função de limpeza ao fechar

        self.valor_entrada = tk.StringVar()
        self.estrutura_selecionada = tk.StringVar(value="Lista")

        # Configuração da Interface
        self.setup_gui()
        self.atualizar_visualizacao()

    def setup_gui(self):
        # Frame Principal
        main_frame = ttk.Frame(self.master, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

        # Título
        ttk.Label(main_frame, text="Demonstração de Estruturas de Dados (C)", font=("Arial", 14, "bold")).grid(row=0, column=0, columnspan=3, pady=10)

        # Seleção de Estrutura
        ttk.Label(main_frame, text="Estrutura:").grid(row=1, column=0, sticky=tk.W, padx=5, pady=5)
        self.radio_lista = ttk.Radiobutton(main_frame, text="Lista (Linear)", variable=self.estrutura_selecionada, value="Lista", command=self.atualizar_visualizacao)
        self.radio_lista.grid(row=1, column=1, sticky=tk.W, padx=5, pady=5)
        self.radio_arvore = ttk.Radiobutton(main_frame, text="Árvore (Não Linear)", variable=self.estrutura_selecionada, value="Arvore", command=self.atualizar_visualizacao)
        self.radio_arvore.grid(row=1, column=2, sticky=tk.W, padx=5, pady=5)

        # Entrada de Valor
        ttk.Label(main_frame, text="Valor (Inteiro):").grid(row=2, column=0, sticky=tk.W, padx=5, pady=5)
        self.entrada = ttk.Entry(main_frame, textvariable=self.valor_entrada, width=10)
        self.entrada.grid(row=2, column=1, sticky=(tk.W, tk.E), padx=5, pady=5)

        # Botões de Operação (Conceito "U")
        operacoes_frame = ttk.Frame(main_frame)
        operacoes_frame.grid(row=3, column=0, columnspan=3, pady=10)

        ttk.Button(operacoes_frame, text="U_Inserir", command=self.u_inserir).grid(row=0, column=0, padx=5)
        ttk.Button(operacoes_frame, text="U_Remover", command=self.u_remover).grid(row=0, column=1, padx=5)
        ttk.Button(operacoes_frame, text="U_Acessar", command=self.u_acessar).grid(row=0, column=2, padx=5)

        # Visualização
        ttk.Label(main_frame, text="Visualização (U_Visualizar):", font=("Arial", 10, "bold")).grid(row=4, column=0, columnspan=3, sticky=tk.W, padx=5, pady=(10, 0))
        self.visualizacao_label = ttk.Label(main_frame, text="", wraplength=400, justify=tk.LEFT)
        self.visualizacao_label.grid(row=5, column=0, columnspan=3, sticky=(tk.W, tk.E), padx=5, pady=(0, 10))

        # Status/Mensagens
        ttk.Label(main_frame, text="Status:", font=("Arial", 10, "bold")).grid(row=6, column=0, sticky=tk.W, padx=5, pady=(10, 0))
        self.status_label = ttk.Label(main_frame, text="Pronto.", wraplength=400, justify=tk.LEFT)
        self.status_label.grid(row=7, column=0, columnspan=3, sticky=(tk.W, tk.E), padx=5, pady=(0, 10))

    def get_valor(self):
        try:
            valor = int(self.valor_entrada.get())
            return valor
        except ValueError:
            messagebox.showerror("Erro de Entrada", "Por favor, insira um número inteiro válido.")
            return None

    def atualizar_visualizacao(self):
        estrutura = self.estrutura_selecionada.get()
        try:
            if estrutura == "Lista":
                # Chama a função C e decodifica a string
                c_string = lib.U_Lista_Visualizar()
                py_string = string_at(c_string).decode('utf-8')
                self.visualizacao_label.config(text=f"Lista (Linear): {py_string}\n(Ordem sequencial de inserção)")
            elif estrutura == "Arvore":
                # Chama a função C e decodifica a string
                c_string = lib.U_Arvore_Visualizar()
                py_string = string_at(c_string).decode('utf-8')
                self.visualizacao_label.config(text=f"Árvore (Não Linear - In-Order): [{py_string.strip().replace(' ', ', ')}]\n(Ordem hierárquica, visualizada em ordem crescente)")
        except Exception as e:
            self.status_label.config(text=f"Erro de visualização: {e}")

    def u_inserir(self):
        valor = self.get_valor()
        if valor is None: return

        estrutura = self.estrutura_selecionada.get()
        if estrutura == "Lista":
            lib.U_Lista_Inserir(valor)
            self.status_label.config(text=f"U_Inserir: Valor {valor} adicionado à Lista (Linear).")
        elif estrutura == "Arvore":
            lib.U_Arvore_Inserir(valor)
            self.status_label.config(text=f"U_Inserir: Valor {valor} adicionado à Árvore (Não Linear).")

        self.atualizar_visualizacao()

    def u_remover(self):
        valor = self.get_valor()
        if valor is None: return

        estrutura = self.estrutura_selecionada.get()
        if estrutura == "Lista":
            lib.U_Lista_Remover(valor)
            self.status_label.config(text=f"U_Remover: Valor {valor} removido da Lista (Linear).")
        elif estrutura == "Arvore":
            lib.U_Arvore_Remover(valor)
            self.status_label.config(text=f"U_Remover: Valor {valor} removido da Árvore (Não Linear).")

        self.atualizar_visualizacao()

    def u_acessar(self):
        valor = self.get_valor()
        if valor is None: return

        estrutura = self.estrutura_selecionada.get()
        if estrutura == "Lista":
            # A Lista em C não tem uma função de acesso simples, vamos simular a busca
            # Poderíamos implementar uma busca em C, mas para manter o foco na integração,
            # vamos usar a visualização para verificar a presença.
            c_string = lib.U_Lista_Visualizar()
            py_string = string_at(c_string).decode('utf-8')
            if str(valor) in py_string:
                resultado = "ENCONTRADO"
            else:
                resultado = "NÃO ENCONTRADO"
            self.status_label.config(text=f"U_Acessar (Lista): Valor {valor} {resultado}.")

        elif estrutura == "Arvore":
            encontrado = lib.U_Arvore_Acessar(valor)
            resultado = "ENCONTRADO" if encontrado else "NÃO ENCONTRADO"
            self.status_label.config(text=f"U_Acessar (Árvore): Valor {valor} {resultado}.")

        self.atualizar_visualizacao()

    def on_closing(self):
        """Chama a função C para liberar a memória antes de fechar a aplicação."""
        lib.liberar_tudo()
        print("Memória C liberada. Fechando aplicação.")
        self.master.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    app = EstruturaDadosApp(root)
    root.mainloop()
