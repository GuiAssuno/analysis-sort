# Análise de Desempenho do Algoritmo Quick Sort

Este projeto fornece uma solução otimizada e multiplataforma para analisar o desempenho do algoritmo Quick Sort, comparando diferentes esquemas de partição (Lomuto, Hoare, 3-Way) e estratégias de escolha de pivô em cenários de melhor, médio e pior caso.

A solução utiliza a velocidade do **C** para a execução do algoritmo de ordenação e a flexibilidade do **Python** para a automação dos testes, coleta de dados e geração de gráficos.

## Estrutura do Projeto

*   `quick_sort_analysis.c`: Código-fonte em C com a implementação do Quick Sort, contadores de operações (comparações e trocas) e a função de análise.
*   `libquicksort.so`: Biblioteca compartilhada compilada a partir do código C (necessária para Linux).
*   `analyze_performance.py`: Script em Python que orquestra os testes, chama a função C via `ctypes`, coleta os resultados e gera o gráfico de desempenho.
*   `quick_sort_performance_analysis.png`: Gráfico gerado com os resultados da análise.
*   `quick_sort_performance_data.csv`: Dados brutos de tempo e contagem de operações.

## Como Executar

A execução é dividida em duas etapas: compilação do código C e execução do script Python.

### 1. Compilação da Biblioteca C

**Pré-requisito:** Você precisa ter um compilador C (como GCC) instalado no seu sistema.

#### No Linux (ou WSL):

1.  Navegue até o diretório `quicksort_analysis`.
2.  Execute o comando de compilação:
    ```bash
    gcc -shared -o libquicksort.so quick_sort_analysis.c -fPIC
    ```

#### No Windows (usando MinGW/GCC):

1.  Navegue até o diretório `quicksort_analysis`.
2.  Execute o comando de compilação (o nome do arquivo de saída deve ser `.dll`):
    ```bash
    gcc -shared -o libquicksort.dll quick_sort_analysis.c
    ```
    *Nota: Você precisará ajustar o nome do arquivo da biblioteca no script Python de `libquicksort.so` para `libquicksort.dll` se usar este nome.*

### 2. Execução da Análise (Python)

**Pré-requisitos:** Python 3, e as bibliotecas `pandas` e `matplotlib`.

1.  Instale as dependências:
    ```bash
    pip install pandas matplotlib
    ```
2.  Execute o script de análise:
    ```bash
    python analyze_performance.py
    ```

O script irá:
1.  Executar o Quick Sort para os cenários pré-definidos (Médio, Pior e Melhor Caso) em diferentes tamanhos de entrada.
2.  Coletar o tempo de execução, o número de comparações e o número de trocas.
3.  Gerar o gráfico de desempenho (`quick_sort_performance_analysis.png`).
4.  Salvar os dados brutos em CSV (`quick_sort_performance_data.csv`).

## Cenários de Teste Incluídos

O script `analyze_performance.py` testa os seguintes cenários para demonstrar o desempenho em diferentes casos:

| Algoritmo | Pivô | Cenário | Tipo de Dados | Complexidade Esperada |
| :--- | :--- | :--- | :--- | :--- |
| **Lomuto** | Mediana de Três | Caso Médio | Aleatório | O(N log N) |
| **Lomuto** | Último Elemento | Pior Caso | Ordenado | O(N²) |
| **Hoare** | Aleatório | Caso Médio | Aleatório | O(N log N) |
| **3-Way** | Último Elemento | Melhor Caso | Repetido | O(N log N) (melhor que O(N²) em dados repetidos) |
| **3-Way** | Mediana de Três | Caso Médio | Aleatório | O(N log N) |

O gráfico gerado ilustra claramente a diferença entre o desempenho quadrático (Pior Caso) e o desempenho log-linear (Caso Médio/Melhor Caso).

## Análise dos Resultados

O gráfico de desempenho (Tempo de Execução vs. Tamanho do Vetor) permite a **Análise Empírica** solicitada:

*   **Curvas O(N log N):** As linhas para os casos Médio e Melhor Caso (Lomuto Mediana de 3, Hoare Aleatório, 3-Way) devem crescer de forma suave e controlada, refletindo a eficiência esperada do Quick Sort.
*   **Curva O(N²):** A linha para o Pior Caso (Lomuto Último em dados ordenados) deve crescer muito mais rapidamente, demonstrando o colapso de desempenho quando a escolha do pivô é ruim.
*   **3-Way Partition:** O caso de dados repetidos deve ser o mais rápido, pois a partição de 3 vias lida de forma eficiente com elementos iguais ao pivô.

Os dados brutos no arquivo CSV também permitem a **Contagem de Operações** (Comparações e Trocas), que é uma métrica mais precisa do que apenas o tempo, pois não é afetada por outros processos do sistema.
