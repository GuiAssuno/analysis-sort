

# Analysis Sort

O Analysis Sort é um projeto focado em analisar o comportamento, o tempo de execução e a eficiência de diversos algoritmos de ordenação. O grande diferencial do projeto é a sua arquitetura híbrida. A interface e a geração de gráficos são feitas em Python para facilitar a visualização, enquanto a execução dos algoritmos ocorre em C, garantindo resultados rápidos e precisos.

## Como Funciona

1. **Configuração via UI:** O usuário escolhe o algoritmo, as variações (ex: tipo de pivô), o tamanho do array (100 a 10.000) e o estado inicial dos dados (aleatório, ordenado, invertido, todos iguais, etc.).
2. **Ponte Python-C:** O Python utiliza a biblioteca `ctypes` para enviar esses parâmetros para uma biblioteca compilada em C (`.dll` Windows ou `.so` Linux).
3. **Processamento:** O código em C aloca o array, executa a ordenação nativamente, calcula o tempo de execução e devolve os resultados.
4. **Visualização:** O Streamlit exibe os resultados em um gráfico de `Tamanho` X `Tempo`, mantendo um histórico das execuções anteriores para comparações diretas.

##  Funcionalidades Atuais
*    **Gráficos e Histórico:** Visualização interativa de tempo de execução com histórico de execuções anteriores, permitindo comparar o desempenho de diferentes métodos na mesma sessão.
*    **Configuração de Arrays:** Teste a resiliência dos algoritmos gerando vetores de tamanho entre 100 e 10.000 elementos em diversos estados:
    *   Aleatório
    *   Totalmente Ordenado
    *   Inversamente Ordenado
    *   Todos os elementos iguais
*    **Variações Estratégicas:** Suporte a diferentes abordagens dentro de um mesmo método para testes profundos (ex: métodos de particionamento e escolha de pivô).

### Algoritmos e Variações Suportadas (23 Métodos)

O projeto conta atualmente com 23 métodos de ordenação implementados em C. Abaixo estão os algoritmos disponíveis e suas respectivas variações configuráveis:

**Lista Completa de Algoritmos Clássicos e Híbridos:**
*   **Troca:** Bubble Sort, Comb Sort, OOdd-Even Sort, Bogo Sort, Gnome Sort.
*   **Inserção / Seleção:** Insertion Sort, Selection Sort, Shell Sort, Cycle Sort.
*   **Eficientes / Divisão e Conquista:** Merge Sort, Heap Sort, Intro Sort, Tim Sort, Quick Sort.
*   **Não-comparativos:** Counting Sort, Radix Sort, Bucket Sort, Pigeonhole Sort, Flash Sort.
*   **Exóticos / Específicos:** Bitonic Sort, Pancake Sort, Stooge Sort, Tree Sort.

## Roadmap e Futuras Implementações

O projeto está em constante evolução. As próximas etapas de desenvolvimento incluem:

*   **Métricas de Hardware :** Adicionar rastreamento de uso de **Memória (RAM)** e **Processador (CPU)** durante a ordenação.
*   **Sistema de Pontuação:** Geração de uma "nota" de performance baseada na eficiência do algoritmo contra a condição inicial do vetor, criando um histórico de desempenho detalhado.
*   **API para Algoritmos Customizados:** Permitir que os usuários escrevam e injetem seus próprios algoritmos de ordenação em C ou Python para testar a performance contra os 23 algoritmos nativos.
*   **Construtor de Algoritmos Híbridos:** Uma interface para misturar algoritmos criando regras dinâmicas (ex: "Use *Quick Sort* até o subarray ter tamanho 10, depois mude para *Insertion Sort*").

## Tecnologias Utilizadas

*   **Frontend & Análise de Dados:** Python, Streamlit.
*   **Motor de Ordenação:** C.
*   **Integração:** `ctypes` (Ponte C-Python).
