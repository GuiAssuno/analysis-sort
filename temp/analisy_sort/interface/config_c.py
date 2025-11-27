import ctypes
import pathlib
import os

# --- 1. Carregar a biblioteca C ---
try:
    #LIB_PATH = os.path.join(os.path.dirname(__file__), "libquicksort.so")
    caminho_abs_arquivo = pathlib.Path(__file__).resolve()
    pasta = caminho_abs_arquivo.parent.parent
    pasta = pasta / 'library' / 'libc.so'
    lib = ctypes.CDLL(pasta)
except OSError as e:
    print(f"Erro ao carregar a biblioteca C: {e}")
    exit()

#================================================ Definir as funções =============================================
lib.inicia_quick_sort.restype = ctypes.c_double  
lib.inicia_quick_sort.argtypes = [
    ctypes.POINTER(ctypes.c_int), 
    ctypes.c_int,                 
    ctypes.c_int                 
]



import ctypes
import pathlib
import os

# --- 1. Carregar a biblioteca ---
try:
    caminho_abs = pathlib.Path(__file__).resolve()
    # Ajuste o caminho conforme onde sua pasta 'library' e o .so estão
    # Supondo que library esteja no mesmo nível destes arquivos py:
    caminho_lib = caminho_abs.parent / 'libsorting.so' 
    
    lib = ctypes.CDLL(str(caminho_lib))
except OSError as e:
    print(f"Erro crítico ao carregar a lib C: {e}")
    exit()

# --- 2. Configuração Automática das Funções de Teste ---
# Lista de funções que retornam double e aceitam (int*, int)
funcoes_padrao = [
    "test_bubble_sort", "test_selection_sort", "test_insertion_sort",
    "test_merge_sort", "test_heap_sort", "test_shell_sort",
    "test_counting_sort", "test_radix_sort", "test_intro_sort"
]

for nome in funcoes_padrao:
    try:
        func = getattr(lib, nome)
        func.restype = ctypes.c_double
        func.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
    except AttributeError:
        pass # Ignora se a função não existir na lib ainda

# --- 3. Configuração Específica do Quick Sort ---
try:
    lib.inicia_quick_sort.restype = ctypes.c_double
    lib.inicia_quick_sort.argtypes = [
        ctypes.POINTER(ctypes.c_int), 
        ctypes.c_int,                 
        ctypes.c_int                 
    ]
except AttributeError:
    pass

# Exportamos a variável 'lib' para ser usada pelos outros arquivos

















































# Agora a maioria das funções aceita: (Vetor, Tamanho, Opcao)
funcoes_com_opcao = [
    "run_bubble_sort", "run_insertion_sort", "run_selection_sort",
    "run_merge_sort", "run_heap_sort", "run_shell_sort", "run_radix_sort"
]

for nome in funcoes_com_opcao:
    try:
        func = getattr(lib, nome)
        func.restype = ctypes.c_double
        func.argtypes = [
            ctypes.POINTER(ctypes.c_int), 
            ctypes.c_int, 
            ctypes.c_int # Argumento extra OP
        ]
    except AttributeError:
        pass

# Quick Sort continua igual (3 argumentos)
lib.inicia_quick_sort.restype = ctypes.c_double
lib.inicia_quick_sort.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int]