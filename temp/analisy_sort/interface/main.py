import ctypes
import random
import streamlit as slit
import pandas as pd
import pathlib
import time

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

#=================================================== Função Python ============================================
def executar(tamanho, op_metodo, forma_vetor=False):
    
    dados = criar_vetor(tamanho= tamanho, formato= forma_vetor)

    # Converte a lista Python em um array C
    ArrayC = ctypes.c_int * tamanho
    vetor_c = ArrayC(*dados) # O '*' "desempacota" a lista

    # --- 4. Chamar a função C! ---
    print(f"Executando C: tam={tamanho}, op={op_metodo}")
    
    # Python chama C aqui. O C executa na velocidade máxima.
    tempo_segundos = lib.inicia_quick_sort(vetor_c, tamanho, op_metodo)
    
    tempo_ms = tempo_segundos * 1000.0
    print(f"C retornou: {tempo_ms:.4f} ms")
    
    return tempo_ms


def criar_vetor(tamanho, formato):
    dados = []
    
    match(formato):
        case "aleatorio":
            dados = [random.randint(0, int(tamanho)) for _ in range(tamanho)]

        case "fixo":
            lista_base = [3, 7, 9, 2, 9, 6, 4, 1, 0, 8, 5]
            if tamanho > len(lista_base):
                dados = (lista_base * (tamanho // len(lista_base) + 1))[:tamanho]
            else:
                dados = lista_base[:tamanho]

        case "repetido":
            dados = [random.randint(0, int(tamanho * 0.2)) for n in range(tamanho)]

        case "ordenado":
            dados = [random.randint(0, tamanho) for _ in range(tamanho)]
            dados.sort()

        case "ordenado_inverso":
            dados = [random.randint(0, tamanho) for _ in range(tamanho)]
            dados.sort(reverse=True)

        case "quase_ordenado":
            dados = list(range(tamanho))
            qtd_trocas = int(tamanho * 0.05) 
            if qtd_trocas < 1: qtd_trocas = 1
            
            for _ in range(qtd_trocas):
                i1 = random.randint(0, tamanho-1)
                i2 = random.randint(0, tamanho-1)
                dados[i1], dados[i2] = dados[i2], dados[i1]

        case "semi_ordenado_começo":
            meio = tamanho // 2 
            dados = []
            for n in range(tamanho):
                if n >= meio:
                    dados.append(random.randint(0, tamanho * 2))  
                else:
                    dados.append(n)  

        case "semi_ordenado_alternado":
            dados = []
            for n in range(tamanho):
                if n % 2 == 0:
                    dados.append(random.randint(0, tamanho))  
                else:
                    dados.append(n) 

        case "semi_ordenado_começo_depois_alterna":
            meio = tamanho // 2
            dados = []
            for n in range(tamanho):
                if n > meio:
                    if n % 2 == 0:
                        dados.append(random.randint(0, tamanho * 2))
                    else:
                        dados.append(n)  
                else:
                    dados.append(n)
        
       
    return dados

# --- para guardar os dados do gráfico ---
if 'resultados' not in slit.session_state:
    slit.session_state.resultados = pd.DataFrame(columns=['Algotirmo','Metodo','Array','Tamanho', 'Tempo (ms)'])


#=================================================== dic-opções =====================================================

# bubble sort
bubble_sort = {
    "Padrão": "standard",
    "Otimizado (Stop early)": "optimized"
}

# heap sort
heap_sort = {
    "Heapify (Floyd)": "heapify",
    "Sift-Up (Simples)": "siftup"
}

# insertion sort
insert_sort = {
    "Linear (Padrão)": "linear",
    "Binária": "binary"
}

# merge sort
merge_sort = {
    "Recursivo (Top-Down)": "recursivo",
    "Iterativo (Bottom-Up)": "iterativo"
}

# quick sort
algoritmo = {
    "Lomuto": "1",
    "Hoare": "2",
    "3-Vias": "3"
}

metodos = {
    "Último":"1",
    "Primeiro":"2",
    "Mediana de 3":"3",
    "Meio":"4",
    "Aleatório":"5"
}

# radix sort
radix_sort = {
    "LSD (Menos Signif.)": "LSD",
    "MSD (Mais Signif.)": "MSD"
}

# shell sort
shell_sort = {"Shell (N/2)":"1",
        "Knuth (3k-1)/2":"2",
        "Ciura (Exp. Melhor)":"3",
        "Hibbard":"4"
}

#===================================================== OPÇÕES ======================================================

chaves = {
    "Bubble Sort": [bubble_sort],
    "Counting Sort": [],
    "Heap Sort": [heap_sort],
    "Insertion Sort": [insert_sort],
    "Intro Sort": [], 
    "Merge Sort": [merge_sort],
    "Quick Sort": [algoritmo, metodos], 
    "Radix Sort": [radix_sort],
    "Selection Sort": [], 
    "Shell Sort": [shell_sort]
}

tipo_ordenar = {
    "Completo": "ordenado",
    "Quase": "quase_ordenado", 
    "Inverso": "ordenado_inverso", 
    "Alternando": "semi_ordenado_alternado", 
    "1° Metade Ord. / Alterna": "semi_ordenado_começo_depois_alterna", 
    "1° Metade Ord. / Aleatorio": "semi_ordenado_começo"
}

tipo_vetor ={
    "Aleatórios": "aleatorio",
    "Fixo": "fixo", 
    "Duplicados": "repetido", 
    "Ordenado": "ordenado" 
}

#=================================================== front-end =====================================================
#================================================= coluna-lateral ==================================================


slit.sidebar.title("Configurações")

op_sort = slit.sidebar.selectbox("Escolha o Sort", list(chaves.keys()), index=None)


match (op_sort):
    case "Bubble Sort":
        op = slit.sidebar.selectbox("Tipo de Variavel", list(chaves[op_sort][0].keys()))
        op_algoritmo = chaves[op_sort][0][op]
    #case "Counting Sort":
        
    
    case "Heap Sort": 
        op = slit.sidebar.selectbox("Tipo de Construção", list(chaves[op_sort][0].keys()))
        op_algoritmo = chaves[op_sort][0][op]
                                          
    case "Insertion Sort": 
        op = slit.sidebar.selectbox("Tipo de Busca", list(chaves[op_sort][0].keys()))
        op_algoritmo = chaves[op_sort][0][op]
    #case "Intro Sort": 

    
    case "Merge Sort": 
        op = slit.sidebar.selectbox("Qual tipo", list(chaves[op_sort][0].keys()))
        op_algoritmo = chaves[op_sort][0][op]

    case "Quick Sort": 
        part = slit.sidebar.selectbox("Algoritmo de Partição",  list(chaves[op_sort][0].keys()))
        op_algoritmo = chaves[op_sort][0][part]

        pivot = slit.sidebar.selectbox("Método de Escolha do Pivô", list(chaves[op_sort][1].keys()))
        op_pivot = chaves[op_sort][1][pivot]

    case "Radix Sort": 
        op = slit.sidebar.selectbox("Tipo de Ordem", list(chaves[op_sort][0].keys()))
        op_algoritmo = chaves[op_sort][0][op]

    #case "Selection Sort":

    case "Shell Sort":
        op_algoritmo = slit.sidebar.selectbox("Tipo de Gaps", list(chaves[op_sort][0].keys()))
        op_algoritmo = chaves[op_sort][0][op_algoritmo]

# Slider para o tamanho
tam = slit.sidebar.slider("Tamanho do Vetor", 
                        min_value=1000, 
                        max_value=100000, 
                        value=1000, 
                        step=1000)

# ==================================================== Escolha de dados =======================================================
tipo_dados = slit.sidebar.radio("Tipo de Dados", list(tipo_vetor.keys()))
tipo_dados = tipo_vetor[tipo_dados]

if tipo_dados == "ordenado":
    tipo_dados = slit.sidebar.radio("Forma de Ordenação", list(tipo_ordenar.keys()))
    tipo_dados = tipo_ordenar[tipo_dados]

# ==================================================== botão de Executar ==================================================
if slit.sidebar.button("Executar"): 
    try:
        if pivot in chaves[op_sort][1]: # if exclusivo para quick sort pois tem dois parametros
            op_code = int(op_algoritmo + op_pivot) # 
    except: 
        op_code = op_algoritmo

    with slit.spinner(f"executando {op_code} de {tam} elementos"):
        # tam => Tamanho do vetor | op_code => o algoritmo ultilizado | tipo_dados => forma que os dados do vetor estaram
        tempo_ms = executar(tamanho= tam, op_metodo= op_code, forma_vetor= tipo_dados)
    
    # Adicionar dados ao nosso DataFrame
    nova_linha = pd.DataFrame({
        'Algoritmo': [op_sort],
        'Metodo': [op_algoritmo],
        'Array' : [tipo_dados],
        'Tamanho': [tam],
        'Tempo (ms)': [tempo_ms]
    })
    slit.session_state.resultados = pd.concat([slit.session_state.resultados, nova_linha], ignore_index=True)

# ====================================================== botão de Limpar =====================================================
if slit.sidebar.button("Limpar Dados", type="secondary"):
    slit.session_state.resultados = pd.DataFrame(columns=['Algotirmo','Metodo','Array','Tamanho', 'Tempo (ms)'])


# ====================================================== COLUNA-PRINCIPAL ============================================

slit.title("Analise de Algoritmos de Ordenação")

slit.header("Gráfico de Desempenho")

if not slit.session_state.resultados.empty:
    # O Streamlit cria um gráfico de linhas automaticamente!
    slit.line_chart(
        slit.session_state.resultados,
        x='Tamanho',
        y='Tempo (ms)',
        x_label= 'Tamanho',
        y_label='Tempo (ms)',
        color='Metodo' # Uma linha para cada método!
    )
    
    slit.header("Dados Coletados")
    slit.dataframe(slit.session_state.resultados)
else:
    slit.info("Clique em 'Executar' na barra lateral para começar.")









































































































import streamlit as slit
import pandas as pd
import func as bk # Importa suas funções e dicionários

# --- Configuração da Sessão ---
if 'resultados' not in slit.session_state:
    slit.session_state.resultados = pd.DataFrame(columns=['Algoritmo','Metodo','Array','Tamanho', 'Tempo (ms)'])

# --- Sidebar ---
slit.sidebar.title("Configurações")

# Usa os dicionários que estão no backend (bk.chaves)
op_sort = slit.sidebar.selectbox("Escolha o Sort", list(bk.chaves.keys()), index=None)

op_algoritmo = None
op_pivot = None

# ... (Sua lógica de menus, usando bk.chaves no lugar de chaves) ...
# Exemplo:
if op_sort == "Quick Sort":
    part = slit.sidebar.selectbox("Partição", list(bk.chaves[op_sort][0].keys()))
    op_algoritmo = bk.chaves[op_sort][0][part]
    # ... etc

# Slider e Dados
tam = slit.sidebar.slider("Tamanho", 1000, 100000, 1000, 1000)
tipo_dados = slit.sidebar.radio("Tipo de Dados", list(bk.tipo_vetor.keys()))
cod_tipo_dados = bk.tipo_vetor[tipo_dados] # Pega o código (ex: "aleatorio")

# --- Botão Executar ---
if slit.sidebar.button("Executar"):
    # Monta o código
    op_code = op_algoritmo
    if op_pivot:
        op_code = int(str(op_algoritmo) + str(op_pivot))

    with slit.spinner("Processando..."):
        # CHAMA A FUNÇÃO QUE ESTÁ NO OUTRO ARQUIVO
        tempo = bk.executar(tamanho=tam, op_metodo=op_code, forma_vetor=cod_tipo_dados)
    
    # Atualiza gráfico
    nova_linha = pd.DataFrame({
        'Algoritmo': [op_sort],
        'Tempo (ms)': [tempo],
        'Tamanho': [tam]
    })
    slit.session_state.resultados = pd.concat([slit.session_state.resultados, nova_linha], ignore_index=True)

# --- Gráficos ---
slit.title("Análise de Algoritmos")
if not slit.session_state.resultados.empty:
    slit.line_chart(slit.session_state.resultados, x='Tamanho', y='Tempo (ms)', color='Algoritmo')