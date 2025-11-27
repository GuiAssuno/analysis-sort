import ctypes
import random
import time
import pandas as pd
import matplotlib.pyplot as plt
import os
import sys

# --- 1. Configuração da Biblioteca C ---
# O nome do arquivo da biblioteca é libquicksort.so
LIB_PATH = os.path.join(os.path.dirname(__file__), "libquicksort.so")

try:
    lib = ctypes.CDLL(LIB_PATH)
except OSError as e:
    print(f"Erro ao carregar a biblioteca C em {LIB_PATH}: {e}")
    print("Certifique-se de que o arquivo 'libquicksort.so' foi compilado corretamente.")
    sys.exit(1)

# --- 2. Definir a Estrutura de Retorno C (AnalysisResult) ---
class AnalysisResult(ctypes.Structure):
    _fields_ = [
        ("time_ms", ctypes.c_double),
        ("comparisons", ctypes.c_longlong),
        ("swaps", ctypes.c_longlong),
    ]

# --- 3. Definir a Função C (analyze_quicksort) ---
lib.analyze_quicksort.restype = AnalysisResult
lib.analyze_quicksort.argtypes = [
    ctypes.POINTER(ctypes.c_int), # vetor de int
    ctypes.c_int,                 # n (tamanho)
    ctypes.c_int,                 # algorithm_code
    ctypes.c_int,                 # pivot_code
    ctypes.c_int                  # data_code (não usado, mas mantido para compatibilidade)
]

# --- 4. Mapeamento de Configurações ---
ALGORITHMS = {
    0: "Lomuto",
    1: "Hoare",
    2: "3-Way (Dijkstra)"
}

PIVOTS = {
    0: "Último Elemento",
    1: "Primeiro Elemento",
    2: "Mediana de Três",
    3: "Aleatório"
}

# Cenários de Teste: (algorithm_code, pivot_code, data_case_name, data_generator_func)
# O gerador de dados é implementado no Python para maior controle sobre os casos.

def generate_random(n): # Caso Médio
    return [random.randint(0, 1000000) for _ in range(n)]

def generate_sorted(n): # Pior Caso para Lomuto/Hoare (pivô simples), Melhor Caso para 3-Way
    return list(range(n))

def generate_reverse_sorted(n): # Pior Caso para Lomuto/Hoare (pivô simples)
    return list(range(n, 0, -1))

def generate_repeated(n): # Melhor Caso para 3-Way
    return [random.randint(0, 9) for _ in range(n)] # Apenas 10 valores únicos

TEST_CASES = [
    # Exemplo de Análise: Lomuto com Mediana de Três (Melhor/Médio)
    (0, 2, "Lomuto (Mediana de 3) - Médio", generate_random),
    # Exemplo de Análise: Lomuto com Último (Pior Caso)
    (0, 0, "Lomuto (Último) - Pior (Ordenado)", generate_sorted),
    # Exemplo de Análise: Hoare com Aleatório (Médio)
    (1, 3, "Hoare (Aleatório) - Médio", generate_random),
    # Exemplo de Análise: 3-Way com Último (Melhor Caso)
    (2, 0, "3-Way (Último) - Melhor (Repetido)", generate_repeated),
    # Exemplo de Análise: 3-Way com Mediana de Três (Médio)
    (2, 2, "3-Way (Mediana de 3) - Médio", generate_random),
]

# Tamanhos de entrada para teste (em milhares)
INPUT_SIZES_K = [1, 5, 10, 20, 50, 100, 200, 500]
INPUT_SIZES = [k * 1000 for k in INPUT_SIZES_K if k <= 50]

# --- 5. Função de Execução e Coleta de Dados ---
def run_analysis():
    all_results = []
    
    total_tests = len(TEST_CASES) * len(INPUT_SIZES)
    current_test = 0

    print("Iniciando a análise de desempenho do Quick Sort...")
    
    for algorithm_code, pivot_code, case_name, data_generator in TEST_CASES:
        print(f"\n--- Testando: {case_name} ---")
        
        for n in INPUT_SIZES:
            current_test += 1
            print(f"  [{current_test}/{total_tests}] Tamanho N={n}...", end=" ", flush=True)
            
            # 1. Gerar os dados no Python
            data = data_generator(n)
            
            # 2. Converter a lista Python em um array C
            ArrayC = ctypes.c_int * n
            vetor_c = ArrayC(*data)
            
            # 3. Chamar a função C para análise
            result = lib.analyze_quicksort(vetor_c, n, algorithm_code, pivot_code, 0)
            
            # 4. Armazenar os resultados
            all_results.append({
                'Tamanho (N)': n,
                'Tamanho (K)': n / 1000,
                'Tempo (ms)': result.time_ms,
                'Comparações': result.comparisons,
                'Trocas': result.swaps,
                'Cenário': case_name,
                'Algoritmo': ALGORITHMS[algorithm_code],
                'Pivô': PIVOTS[pivot_code]
            })
            print(f"Tempo: {result.time_ms:.2f} ms")

    print("\nAnálise concluída. Gerando DataFrame...")
    return pd.DataFrame(all_results)

# --- 6. Função de Geração de Gráfico ---
def generate_plot(df):
    plt.style.use('seaborn-v0_8-whitegrid')
    
    # Cria a figura e os eixos
    fig, ax = plt.subplots(figsize=(14, 8))
    
    # Plota os dados
    for case in df['Cenário'].unique():
        subset = df[df['Cenário'] == case]
        ax.plot(subset['Tamanho (K)'], subset['Tempo (ms)'], marker='o', linestyle='-', label=case)

    # Configurações do Gráfico
    ax.set_title('Desempenho do Quick Sort: Comparação de Algoritmos e Pivôs', fontsize=16, fontweight='bold')
    ax.set_xlabel('Tamanho do Vetor (N em milhares)', fontsize=12)
    ax.set_ylabel('Tempo de Execução (ms)', fontsize=12)
    
    # Adiciona a legenda fora do gráfico para melhor visibilidade
    ax.legend(title='Cenário de Teste', bbox_to_anchor=(1.05, 1), loc='upper left')
    
    # Adiciona uma grade mais fina
    ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    
    # Salva o gráfico
    plot_filename = "quick_sort_performance_analysis.png"
    plt.savefig(plot_filename, bbox_inches='tight')
    print(f"\nGráfico de desempenho salvo como: {plot_filename}")
    
    # Salva os dados brutos em CSV
    csv_filename = "quick_sort_performance_data.csv"
    df.to_csv(csv_filename, index=False)
    print(f"Dados brutos salvos como: {csv_filename}")
    
    return plot_filename, csv_filename

# --- 7. Execução Principal ---
if __name__ == "__main__":
    df_results = run_analysis()
    plot_file, data_file = generate_plot(df_results)
    
    # Para fins de entrega, precisamos dos caminhos absolutos
    print(f"RESULTADO_PLOT:{os.path.abspath(plot_file)}")
    print(f"RESULTADO_DATA:{os.path.abspath(data_file)}")
