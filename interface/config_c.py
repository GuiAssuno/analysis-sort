import ctypes
import pathlib
import platform
import random

system = platform.system()

if system == "Windows":
    lib_name = "libsort.dll"
elif system == "Linux":
    lib_name = "libsort.so"


try:
    caminho_abs_arquivo = pathlib.Path(__file__).resolve()
    pasta = caminho_abs_arquivo.parent.parent
    pasta = pasta / 'library' / lib_name
    print(f"Carregando biblioteca C em: {pasta}")
    lib = ctypes.CDLL(pasta)
except OSError as e:
    print(f"Erro ao carregar a biblioteca C: {e}")
    exit()


funcoes = [
    "inicia_bubble_sort", "inicia_quick_sort"      
]

for nome in funcoes:
    fun = getattr(lib, nome)
    try:
        fun.restype = ctypes.c_double
        fun.argtypes = [
            ctypes.POINTER(ctypes.c_int), 
            ctypes.c_int, 
            ctypes.c_int 
        ]
    except AttributeError:
        pass

