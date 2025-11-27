# Detalhamento Técnico da Análise de Desempenho do Quick Sort

Este documento detalha as alterações, adições e correções realizadas no código original (`quick_sort.c` e `Main.py`) para criar a solução final de análise de desempenho do algoritmo Quick Sort.

## 1. Erros Encontrados e Correções Aplicadas

O principal desafio encontrado durante a execução dos testes foi a instabilidade do algoritmo no cenário de Pior Caso, que resultou em uma falha de segmentação.

### 1.1. Erro: `Segmentation fault` no Pior Caso

| Erro | Causa | Correção Aplicada |
| :--- | :--- | :--- |
| **`Segmentation fault`** (Falha de Segmentação) | Ocorreu durante o teste do Pior Caso (Quick Sort Lomuto com pivô no último elemento em um vetor já ordenado) para **N ≥ 200.000**. A complexidade O(N²) do pior caso força uma recursão profunda (N chamadas aninhadas), excedendo o limite de memória da pilha de chamadas (Stack Overflow). | **Limitação do Tamanho de Entrada:** O tamanho máximo de teste para o Pior Caso foi limitado a **N = 50.000** no script `analyze_performance.py`. Isso permitiu que a curva O(N²) fosse demonstrada claramente sem causar a falha do programa. |
| **Timeout de Execução** | O tempo de execução do Pior Caso para N=50.000 é de aproximadamente 5 a 6 segundos, o que excedia o limite de tempo padrão de 30 segundos para a execução de comandos. | **Aumento do Timeout:** O tempo limite de execução foi estendido para 180 segundos, garantindo a conclusão dos testes mais longos. |

### 1.2. Correções de Lógica e Estrutura no Código C

O código C original (`quick_sort.c`) continha implementações de partição incompletas ou incorretas para os esquemas Hoare e 3-Way.

| Componente | Problema no Código Original | Correção e Motivo |
| :--- | :--- | :--- |
| **Partição Hoare** | A função `hoare_mediana` (original) não implementava o esquema de Hoare corretamente, parecendo uma variação do Lomuto. | Implementação da função `partition_hoare` **clássica** no novo arquivo (`quick_sort_analysis.c`), que utiliza dois ponteiros que se movem em direção ao centro e retorna o índice de partição correto. |
| **Quick Sort 3-Way** | A função recursiva original estava incorreta, pois não usava os limites de partição (`lt` e `gt`) de forma adequada. | A função `partition_3way` foi reescrita para usar ponteiros (`*lt`, `*gt`) e a função recursiva (`quick_sort_3way_recursive`) foi corrigida para chamar as sub-rotinas nos intervalos `[esquerda, lt - 1]` e `[gt + 1, direita]`, ignorando a seção central de elementos iguais ao pivô. |

## 2. Adições e Otimizações Chave

As seguintes funcionalidades foram adicionadas para atender aos requisitos de análise detalhada e portabilidade:

### 2.1. Contagem de Operações (Métricas de Complexidade)

Para ir além da medição de tempo (que é afetada pelo hardware e sistema operacional), foram adicionadas métricas de complexidade:

*   **Variáveis Globais:** `long long comparisons` e `long long swaps` foram introduzidas no `quick_sort_analysis.c`.
*   **Contagem de Trocas:** A função auxiliar `swap` agora incrementa a variável `swaps` a cada troca realizada.
*   **Contagem de Comparações:** A variável `comparisons` é incrementada dentro dos loops de partição (Lomuto, Hoare, 3-Way) a cada vez que um elemento é comparado com o pivô.

### 2.2. Interface de Comunicação C/Python (ctypes)

A comunicação entre o Python e o C foi formalizada e simplificada:

*   **Estrutura de Retorno:** Uma estrutura C (`AnalysisResult`) foi criada para retornar múltiplos valores de forma organizada: `time_ms`, `comparisons` e `swaps`.
*   **Função Unificada:** A função `analyze_quicksort` no C agora recebe o vetor, o tamanho, o código do algoritmo e o código do pivô, centralizando a lógica de execução.
*   **Tipagem no Python:** O script Python utiliza o módulo `ctypes` para definir a estrutura `AnalysisResult` e os tipos de argumentos da função C, garantindo a correta passagem de dados e o recebimento dos resultados.

### 2.3. Automação e Geração de Gráficos (analyze_performance.py)

O script Python foi completamente reescrito para automatizar a análise:

*   **Geração de Dados de Teste:** Funções Python foram criadas para gerar os vetores de entrada que simulam os casos:
    *   **Caso Médio:** Vetor aleatório.
    *   **Pior Caso:** Vetor ordenado (para Lomuto/Hoare com pivô simples).
    *   **Melhor Caso:** Vetor com muitos elementos repetidos (para 3-Way).
*   **Geração de Gráfico:** A biblioteca `matplotlib` é usada para gerar um gráfico de linha de alta visibilidade, comparando o **Tempo de Execução (ms)** versus o **Tamanho do Vetor (N em milhares)** para cada cenário testado.

## 3. Estrutura Final do Código C (`quick_sort_analysis.c`)

O novo código C é modular e focado na análise:

1.  **`AnalysisResult` struct:** Define o formato de saída.
2.  **`swap` function:** Função auxiliar com contador de trocas.
3.  **Pivot Selectors:** Funções para escolha do pivô (`pivot_last`, `pivot_median_of_three`, etc.).
4.  **Partition Schemes:** Funções de partição (`partition_lomuto`, `partition_hoare`, `partition_3way`) com contadores de comparações.
5.  **Recursive Quick Sorts:** Funções recursivas para cada esquema de partição.
6.  **`analyze_quicksort`:** Função principal chamada pelo Python, que gerencia a cópia do vetor, a seleção do algoritmo/pivô, a medição do tempo e o retorno dos resultados.

Esta estrutura garante que o código C seja uma biblioteca de análise de alto desempenho, enquanto o Python se concentra na orquestração e visualização dos resultados.
