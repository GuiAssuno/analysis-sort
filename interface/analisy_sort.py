import streamlit as slit
import pandas as pd
from func import Gerenciador
import dicionarios as dic

def run():
    # --- para guardar os dados do gráfico ---
    if 'resultados' not in slit.session_state:
        slit.session_state.resultados = pd.DataFrame(columns=['Algoritmo','Metodo','Array','Tamanho', 'Tempo (ms)'])

    if 'gerenciador' not in slit.session_state:
        slit.session_state.gerenciador = Gerenciador()

#======================================================= front-end =====================================================
#===================================================== coluna-lateral ==================================================

    slit.sidebar.title("Configurações")

    op_sort = slit.sidebar.selectbox("Escolha o Sort", list(dic.chaves.keys()), index=None)

    match (op_sort):
        case "Bubble Sort":
            op_algoritmo = slit.sidebar.selectbox("Tipo de Variavel", list(dic.chaves[op_sort][0].keys()))
            op_code = dic.chaves[op_sort][0][op_algoritmo]
        
        case "Heap Sort": 
            op_algoritmo = slit.sidebar.selectbox("Tipo de Construção", list(dic.chaves[op_sort][0].keys()))
            op_code = dic.chaves[op_sort][0][op_algoritmo]
                                            
        case "Insertion Sort": 
            op_algoritmo = slit.sidebar.selectbox("Tipo de Busca", list(dic.chaves[op_sort][0].keys()))
            op_code = dic.chaves[op_sort][0][op_algoritmo] 
        
        case "Merge Sort": 
            op_algoritmo = slit.sidebar.selectbox("Qual tipo", list(dic.chaves[op_sort][0].keys()))
            op_code = dic.chaves[op_sort][0][op_algoritmo]

        case "Quick Sort": 
            op_algoritmo = slit.sidebar.selectbox("Algoritmo de Partição",  list(dic.chaves[op_sort][0].keys()))
            op_code = dic.chaves[op_sort][0][op_algoritmo]

            pivot = slit.sidebar.selectbox("Método de Escolha do Pivô", list(dic.chaves[op_sort][1].keys()))
            op_code += dic.chaves[op_sort][1][pivot]
            op_algoritmo += " + " + pivot

        case "Radix Sort": 
            op_algoritmo = slit.sidebar.selectbox("Tipo de Ordem", list(dic.chaves[op_sort][0].keys()))
            op_code = dic.chaves[op_sort][0][op_algoritmo]

        case "Shell Sort":
            op_algoritmo = slit.sidebar.selectbox("Tipo de Gaps", list(dic.chaves[op_sort][0].keys()))
            op_code = dic.chaves[op_sort][0][op_algoritmo]

    # Slider para o tamanho
    tam = slit.sidebar.slider("Tamanho do Vetor", 
                            min_value=1000, 
                            max_value=100000, 
                            value=1000, 
                            step=1000)

# ==================================================== Escolha de dados =======================================================
    on = slit.sidebar.toggle("Mesmo vetor", help="Escolha manter o mesmo vetor para todas as execuções (on = mesmo vetor, off = novo vetor a cada execução)")
    
    tipo_dados = slit.sidebar.radio("Tipo de Dados", list(dic.tipo_vetor.keys()))
    tipo_dados = dic.tipo_vetor[tipo_dados]

    if tipo_dados == "ordenado":
        tipo_dados = slit.sidebar.radio("Forma de Ordenação", list(dic.tipo_ordenar.keys()))
        tipo_dados = dic.tipo_ordenar[tipo_dados]

# ==================================================== botão de Executar ==================================================
    coluna1, coluna2 = slit.sidebar.columns([2,2],vertical_alignment='center')

    with coluna1:
        if slit.button("Executar"): 

            with slit.spinner(f"Executanto...............", show_time=True):
                # tam => Tamanho do vetor | op_code => o algoritmo ultilizado | tipo_dados => forma que os dados do vetor estaram
                tempo_ms = slit.session_state.gerenciador.executar(
                    tamanho= tam, 
                    op_metodo= op_code, 
                    forma_vetor= tipo_dados, 
                    op_sort= op_sort, 
                    novo= not on
                )
            
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
    with coluna2:
        if slit.button("Limpar", type="primary"):
            slit.session_state.resultados = pd.DataFrame(columns=['Algoritmo','Metodo','Array','Tamanho', 'Tempo (ms)'])


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

