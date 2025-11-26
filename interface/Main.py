import ctypes
import random
import streamlit as slit
import pandas as pd
import pathlib
import time

list_f = list()
flag_lista_gerada = False

# --- 1. Carregar a biblioteca C ---
try:
    caminho_abs_arquivo = pathlib.Path(__file__).resolve()
    pasta = caminho_abs_arquivo.parent.parent
    pasta / 'library' / 'libc.so'
    lib = ctypes.CDLL(pasta)
except OSError as e:
    print(f"Erro ao carregar a biblioteca C: {e}")
    print("Você compilou o quick_sort.c para libc.so?")
    exit()

# --- 2. Definir a função ---
lib.lomuto.restype = ctypes.c_double  
lib.lomuto.argtypes = [
    ctypes.POINTER(ctypes.c_int), # ponteiro para o vetor de int
    ctypes.c_int,                 # int 
]

lib.hoare.restype = ctypes.c_double  
lib.hoare.argtypes = [
    ctypes.POINTER(ctypes.c_int), # ponteiro para o vetor de int
    ctypes.c_int,                 # int n
]

lib.via_3.restype = ctypes.c_double  
lib.via_3.argtypes = [
    ctypes.POINTER(ctypes.c_int), # ponteiro para o vetor de int
    ctypes.c_int,                 # int n
]


# --- 3. Função Python ---
def executar_c(tamanho, op_metodo, caso, lista_fixa, flag):
    
    if not flag_lista_gerada:
        if caso:
            dados = [random.randint(0, 1000) for _ in range(tamanho)]
            lista_fixa = list(dados)
        else:
            # Gerar elementos aleatórios (Python é mais rápido nisso)
            dados = [random.randint(0, 10000) for _ in range(tamanho)]
            dados.sort()
            lista_fixa = list(dados)
    elif flag_lista_gerada:
            dados = list(lista_fixa)
    else:
        return 0
    
    # Converte a lista Python em um array C
    ArrayC = ctypes.c_int * tamanho
    vetor_c = ArrayC(*dados) # O '*' "desempacota" a lista
    
    # Python chama C aqui. O C executa na velocidade máxima.
    if op_metodo == 'lomuto':
        tempo_segundos = lib.lomuto(vetor_c, tamanho -1)
    elif op_metodo == 'hoare':
        tempo_segundos = lib.hoare(vetor_c, tamanho -1)
    elif op_metodo == 'via_3':
        tempo_segundos = lib.via_3(vetor_c, tamanho -1)    
    else:
        return 0
        
    tempo_ms = tempo_segundos * 1000.0
    print(f"C retornou: {tempo_ms:.4f} ms")
    
    return tempo_ms, lista_fixa



# --- Gerenciamento de Estado (para guardar os dados do gráfico) ---
if 'resultados' not in slit.session_state:
    slit.session_state.resultados = pd.DataFrame(columns=['Tamanho', 'Tempo', 'Metodo'])

# --- Interface Gráfica (Side Bar) ---
slit.sidebar.title("Configurações")


mapa_algoritmo = {
    "Lomuto": "lomuto",
    "Hoare": "hoare",
    "3-Vias": "via_3"
}

mapa_metodos = {
    "Melhor/Medio":True,
    "Pior":False,
}

algoritmo = slit.sidebar.selectbox("Algoritmo de Partição",  ("Lomuto","Hoare","3-Vias"), index=0)
op_algoritimo = mapa_algoritmo[algoritmo]


# Slider para o tamanho
tam = slit.sidebar.slider("Tamanho do Vetor", 
                        min_value=1000, 
                        max_value=10000, 
                        value=1000, 
                        step=100)

# Escolha de dados
tipo_dados = slit.sidebar.radio("Caso", ("Melhor/Medio", "Pior"))
op_vetor = mapa_metodos[tipo_dados]

# Botão de Executar
if slit.sidebar.button("Executar Teste"):
    # Chamar nossa função "wrapper" que chama o C
    

    with slit.spinner(f"Executando {algoritmo} de {tam} elementos..."):
        tempo_ms, list_f = executar_c(tamanho=tam, op_metodo=op_algoritimo, caso=op_vetor,lista_fixa= list_f, flag= flag_lista_gerada)
    
    flag_lista_gerada = True
    # Adicionar dados ao nosso DataFrame
    nova_linha = pd.DataFrame({
        'Tamanho': [tam],
        'Tempo': [tempo_ms],
        'Metodo': [algoritmo]
    })
    slit.session_state.resultados = pd.concat([slit.session_state.resultados, nova_linha], ignore_index=True)

# Botão de Limpar
if slit.sidebar.button("Limpar Dados do Gráfico"):
    slit.session_state.resultados = pd.DataFrame(columns=['Tamanho', 'Tempo', 'Metodo'])
    flag_lista_gerada = False
    

# ------------------------------------------ Área Principal (Gráfico e Dados) ---------------------------------------
slit.title("Analise de Algoritmos e de Pivot" \
" QuickSort")

slit.header("Gráfico de Desempenho")

if not slit.session_state.resultados.empty:
    # O Streamlit cria um gráfico de linhas automaticamente!
    slit.line_chart(
        slit.session_state.resultados,
        x='Tamanho',
        y='Tempo',
        x_label= 'Tamanho',
        y_label='Tempo(ms)',
        color='Metodo' # Uma linha para cada método!
    )
    
    slit.header("Dados Coletados")
    slit.dataframe(slit.session_state.resultados)
else:
    pass