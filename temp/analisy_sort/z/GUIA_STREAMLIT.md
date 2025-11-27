# Guia de Uso e Modificação do Streamlit

O Streamlit é uma biblioteca Python que permite criar aplicativos web interativos para ciência de dados e análise de forma rápida e com poucas linhas de código. O arquivo original `Main.py` utilizava o Streamlit para criar uma interface de teste interativa.

Este guia explica como você pode usar e modificar o layout do Streamlit para seus próprios projetos.

## 1. Estrutura Básica do Streamlit

Um aplicativo Streamlit é construído sequencialmente, de cima para baixo. Cada chamada de função (`st.title()`, `st.write()`, `st.sidebar.slider()`) adiciona um elemento à página.

### Componentes Principais de Layout

| Componente | Função | Exemplo de Uso |
| :--- | :--- | :--- |
| `st.title()` | Define o título principal da página. | `st.title("Meu Aplicativo de Análise")` |
| `st.header()` | Define um cabeçalho de seção. | `st.header("Gráfico de Resultados")` |
| `st.write()` | Função genérica para exibir texto, DataFrames, gráficos, etc. | `st.write("Olá, mundo!")` |
| `st.sidebar` | Cria uma barra lateral para controles e configurações. | `st.sidebar.selectbox("Opção", ["A", "B"])` |
| `st.columns()` | Divide a área principal em colunas para layout lado a lado. | `col1, col2 = st.columns(2)` |
| `st.expander()` | Cria uma seção recolhível para esconder conteúdo. | `with st.expander("Ver Detalhes"): st.write("Conteúdo oculto")` |

## 2. Detalhamento de Parâmetros de Objetos Comuns

A seguir, detalhamos os parâmetros dos objetos Streamlit mais utilizados para entrada de dados e visualização.

### A. Widgets de Entrada (Input Widgets)

Os widgets de entrada são usados para coletar informações do usuário. Eles sempre retornam o valor atual do controle.

#### `st.selectbox(label, options, index=0, help=None)`

Usado para selecionar uma única opção em uma lista suspensa.

| Parâmetro | Tipo | Descrição |
| :--- | :--- | :--- |
| `label` | `str` | O texto que aparece acima da caixa de seleção. |
| `options` | `list`, `tuple` | A lista de valores disponíveis para seleção. |
| `index` | `int` | O índice da opção que deve ser selecionada por padrão (começa em 0). |
| `help` | `str` | Uma dica de ferramenta (tooltip) que aparece ao passar o mouse sobre o widget. |

#### `st.slider(label, min_value, max_value, value=None, step=None)`

Usado para selecionar um valor dentro de um intervalo.

| Parâmetro | Tipo | Descrição | |
| :--- | :--- | :--- | :--- |
| `label` | `str` | O texto que aparece acima do slider. |
| `min_value` | `int`, `float` | O valor mínimo que pode ser selecionado. |
| `max_value` | `int`, `float` | O valor máximo que pode ser selecionado. |
| `value` | `int`, `float` | O valor inicial do slider. Se não for fornecido, será `min_value`. |
| `step` | `int`, `float` | O incremento entre os valores. |

#### `st.button(label, help=None)`

Cria um botão. Retorna `True` se o botão foi clicado na última interação do usuário, e `False` caso contrário.

| Parâmetro | Tipo | Descrição |
| :--- | :--- | :--- |
| `label` | `str` | O texto exibido no botão. |
| `help` | `str` | Uma dica de ferramenta (tooltip). |

### B. Elementos de Visualização (Output Elements)

Estes elementos são usados para exibir dados e gráficos.

#### `st.dataframe(data)`

Exibe um DataFrame do Pandas como uma tabela interativa.

| Parâmetro | Tipo | Descrição |
| :--- | :--- | :--- |
| `data` | `pd.DataFrame` | O DataFrame a ser exibido. |

#### `st.line_chart(data, x=None, y=None, color=None)`

Exibe um gráfico de linha. É uma abstração simples do Altair/Vega-Lite.

| Parâmetro | Tipo | Descrição |
| :--- | :--- | :--- |
| `data` | `pd.DataFrame` | O DataFrame contendo os dados do gráfico. |
| `x` | `str` | O nome da coluna a ser usada no eixo X. |
| `y` | `str` | O nome da coluna a ser usada no eixo Y. Pode ser uma lista de nomes. |
| `color` | `str` | O nome da coluna a ser usada para colorir as linhas (útil para separar séries de dados). |

## 3. Como Modificar o Layout do `Main.py` Original

O arquivo original `Main.py` (que foi substituído por `analyze_performance.py` para automação) usava o Streamlit. Se você quiser reverter para uma interface interativa, use a estrutura abaixo como base:

### A. Usando a Barra Lateral (`st.sidebar`)

Tudo o que estiver dentro de `st.sidebar` será colocado na barra lateral, ideal para controles:

```python
# Título da Barra Lateral
st.sidebar.title("Configurações do Teste")

# Widget de seleção de algoritmo na barra lateral
algoritmo = st.sidebar.selectbox(
    "Algoritmo de Partição",
    ("Lomuto", "Hoare", "3-Vias")
)

# Botão de execução na barra lateral
if st.sidebar.button("Executar Teste"):
    # Lógica de execução aqui
    pass
```

### B. Usando Colunas (`st.columns`)

Para colocar elementos lado a lado na área principal:

```python
# Divide a área principal em duas colunas de largura igual
col_dados, col_grafico = st.columns(2)

# Conteúdo da primeira coluna
with col_dados:
    st.header("Dados Brutos")
    st.dataframe(df_resultados)

# Conteúdo da segunda coluna
with col_grafico:
    st.header("Visualização")
    st.line_chart(df_resultados)
```

### C. Gerenciamento de Estado (`st.session_state`)

O Streamlit reexecuta o script inteiro a cada interação. Para manter dados (como os resultados dos testes) entre as interações, use o `st.session_state`:

```python
# Inicializa o estado se ele ainda não existir
if 'resultados' not in st.session_state:
    st.session_state.resultados = pd.DataFrame(columns=['Tamanho', 'Tempo (ms)', 'Metodo'])

# Adiciona um novo resultado
nova_linha = pd.DataFrame(...)
st.session_state.resultados = pd.concat([st.session_state.resultados, nova_linha], ignore_index=True)

# Exibe o gráfico usando o estado
st.line_chart(st.session_state.resultados)
```

Ao dominar esses conceitos, você pode modificar o layout do Streamlit para exibir qualquer tipo de dado ou controle que desejar. Para mais detalhes sobre outros widgets e funcionalidades, consulte a [Documentação Oficial do Streamlit](https://docs.streamlit.io/).
