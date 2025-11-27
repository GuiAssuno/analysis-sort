import random
import ctypes
from config_c import lib # Importa a biblioteca configurada

# --- Dicionários de Opções (Movi para cá para o app.py poder ler e montar o menu) ---
bubble_sort = {"Padrão": "standard", "Otimizado": "optimized"}
# ... (coloque todos os seus outros dicionários aqui: heap_sort, insert_sort, etc) ...

# Exemplo do dicionário principal (simplificado)
chaves = {
    "Bubble Sort": [bubble_sort],
    # ... adicione os outros ...
    "Quick Sort": [{"Lomuto": "1", "Hoare": "2", "3-Vias": "3"}, 
                   {"Último":"1", "Primeiro":"2", "Mediana de 3":"3", "Aleatório":"5"}]
}

tipo_vetor ={
    "Aleatórios": "aleatorio", "Fixo": "fixo", 
    "Duplicados": "repetido", "Ordenado": "ordenado" 
}
# (Adicione o dicionário tipo_ordenar aqui também)

# --- Funções Lógicas ---

def criar_vetor(tamanho, formato):
    dados = []
    match(formato):
        case "aleatorio":
            dados = [random.randint(0, int(tamanho)) for _ in range(tamanho)]
        # ... (copie o resto da sua lógica de criar vetor para cá) ...
    return dados

def executar(tamanho, op_metodo, forma_vetor=False):
    # 1. Cria os dados
    dados = criar_vetor(tamanho=tamanho, formato=forma_vetor)

    # 2. Converte para C
    ArrayC = ctypes.c_int * tamanho
    vetor_c = ArrayC(*dados)

    # 3. Executa
    # Nota: Aqui você precisa mapear qual função do C chamar baseado no 'op_metodo'
    # Se for QuickSort, usa inicia_quick_sort. Se for Bubble, usa test_bubble_sort, etc.
    
    # Exemplo simplificado (você terá que melhorar essa lógica de seleção):
    if isinstance(op_metodo, int) or (isinstance(op_metodo, str) and len(op_metodo) > 1): 
        # É Quick Sort (tem código tipo 11, 23, etc)
        tempo_segundos = lib.inicia_quick_sort(vetor_c, tamanho, int(op_metodo))
    else:
        # É outro algoritmo (ex: Bubble Sort)
        # Você precisará mapear o nome do algoritmo para a função correta
        # Exemplo temporário:
        tempo_segundos = lib.test_intro_sort(vetor_c, tamanho) 
    
    return tempo_segundos * 1000.0





#=================================================== dic-opções =====================================================

# bubble sort
bubble_sort = {
    "Padrão": "standard",
    "Otimizado (Stop early)": "optimized",
    "Cocktail Shaker (Bidirecional)": "cocktail" # <--- NOVO
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















































































































# ======================== ADD & UPDATES ========================

# bubble sort (Adicionado Cocktail)
bubble_sort = {
    "Padrão": "standard",
    "Otimizado (Stop early)": "optimized",
    "Cocktail Shaker (Bidirecional)": "cocktail" # <--- NOVO
}

# counting sort (Preenchido)
counting_sort = {
    "Padrão (Apenas Positivos)": "standard",
    "Com Shift (Aceita Negativos)": "shift"     # <--- Sugestão de implementação futura
}

# heap sort (Mantido)
heap_sort = {
    "Heapify (Floyd)": "heapify",
    "Sift-Up (Simples)": "siftup"
}

# insertion sort (Mantido)
insert_sort = {
    "Linear (Padrão)": "linear",
    "Binária": "binary"
}

# intro sort (Preenchido)
intro_sort = {
    "Padrão (Quick+Heap+Insert)": "standard"
}

# merge sort (Mantido)
merge_sort = {
    "Recursivo (Top-Down)": "recursivo",
    "Iterativo (Bottom-Up)": "iterativo"
}

# quick sort (Adicionado Dual-Pivot)
algoritmo = {
    "Lomuto (1 Pivô)": "1",
    "Hoare (1 Pivô)": "2",
    "3-Vias (Dutch Flag)": "3",
    "Dual-Pivot (Yaroslavskiy)": "4" # <--- NOVO (Desafio: Implementar Dual Pivot)
}

metodos = {
    "Último":"1",
    "Primeiro":"2",
    "Mediana de 3":"3",
    "Meio":"4",
    "Aleatório":"5"
}

# radix sort (Mantido)
radix_sort = {
    "LSD (Menos Signif.)": "LSD",
    "MSD (Mais Signif.)": "MSD"
}

# selection sort (Adicionado Bidirecional)
selection_sort = {
    "Padrão (Min)": "standard",
    "Bidirecional (Min/Max)": "double" # <--- NOVO
}

# shell sort (Mantido)
shell_sort = {
    "Shell (N/2)":"1",
    "Knuth (3k-1)/2":"2",
    "Ciura (Exp. Melhor)":"3",
    "Hibbard":"4"
}

# Novos Algoritmos Extras (Sugestão)
comb_sort = {
    "Padrão (Fator 1.3)": "standard"
}

gnome_sort = {
    "Padrão": "standard"
}

# ====================================================== OPÇÕES ======================================================

chaves = {
    "Bubble Sort": [bubble_sort],
    "Comb Sort": [comb_sort],          # <--- NOVO
    "Counting Sort": [counting_sort],  # <--- AGORA TEM OPÇÃO
    "Gnome Sort": [gnome_sort],        # <--- NOVO
    "Heap Sort": [heap_sort],
    "Insertion Sort": [insert_sort],
    "Intro Sort": [intro_sort],        # <--- AGORA TEM OPÇÃO
    "Merge Sort": [merge_sort],
    "Quick Sort": [algoritmo, metodos], 
    "Radix Sort": [radix_sort],
    "Selection Sort": [selection_sort],# <--- AGORA TEM OPÇÃO
    "Shell Sort": [shell_sort]
}




















































# bucket sort
bucket_sort = {
    "Padrão (Inteiros)": "standard"
}

# tim sort
tim_sort = {
    "Padrão (Run=32)": "standard"
}

# bogo sort (Cuidado: Trava com n > 12)
bogo_sort = {
    "Aleatório": "standard"
}

# --- Adicione na lista 'chaves' ---
chaves = {
    # ... os que você já tem ...
    "Bucket Sort": [bucket_sort], # <--- NOVO
    "Tim Sort": [tim_sort],       # <--- NOVO
    "Bogo Sort": [bogo_sort]      # <--- NOVO (Se quiser a piada)
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

