# Demonstração de Estruturas de Dados: Python (GUI) + C (Operações)

Este projeto demonstra como integrar uma interface gráfica em **Python (usando Tkinter)** com operações de estruturas de dados implementadas em **C**, utilizando a biblioteca `ctypes` do Python.

O objetivo é ilustrar o conceito de operações unificadas **"U" (Unificar)** em estruturas de dados Lineares (Lista) e Não Lineares (Árvore Binária de Busca), separando a lógica de negócios (C) da apresentação (Python).

## Estrutura do Projeto

O projeto é organizado nos seguintes arquivos:

1.  `app_gui.py`: O script principal em Python que cria a interface gráfica (GUI) com Tkinter e usa `ctypes` para chamar as funções da biblioteca C.
2.  `estruturas_c/`: Diretório contendo os arquivos C.
    *   `estruturas_c/estruturas.h`: Arquivo de cabeçalho com as definições das estruturas (`NoLista`, `NoArvore`) e as assinaturas das funções.
    *   `estruturas_c/estruturas.c`: Arquivo de implementação das funções de estruturas de dados em C.
    *   `estruturas_c/libestruturas.so`: A biblioteca compartilhada compilada a partir do código C.
3.  `test_integration.py`: Script de teste em Python (sem GUI) para validar a comunicação entre Python e C.

## Conceito "U" (Unificar)

As operações em C foram nomeadas de forma unificada para demonstrar que as ações fundamentais são as mesmas, independentemente da estrutura:

| Operação | Estrutura Linear (Lista) | Estrutura Não Linear (Árvore) |
| :--- | :--- | :--- |
| **U_Inserir** | `U_Lista_Inserir(dado)` | `U_Arvore_Inserir(dado)` |
| **U_Remover** | `U_Lista_Remover(dado)` | `U_Arvore_Remover(dado)` |
| **U_Acessar** | (Simulado na GUI) | `U_Arvore_Acessar(dado)` |
| **U_Visualizar** | `U_Lista_Visualizar()` | `U_Arvore_Visualizar()` |

## Como Executar

### Pré-requisitos

Para executar este projeto, você precisará ter instalado:

*   Python 3
*   Tkinter (Geralmente instalado com o Python, mas pode precisar ser instalado separadamente em alguns sistemas Linux: `sudo apt-get install python3-tk`)
*   GCC (Compilador C)

### Passos

1.  **Compilar a Biblioteca C (Se necessário):**
    A biblioteca `libestruturas.so` já foi compilada. Caso precise recompilar (após modificações no código C), use o seguinte comando no terminal, a partir do diretório raiz do projeto:
    ```bash
    gcc -shared -o estruturas_c/libestruturas.so estruturas_c/estruturas.c -fPIC
    ```

2.  **Executar o Teste de Integração (Opcional):**
    Para verificar se a comunicação Python-C está funcionando corretamente no seu ambiente:
    ```bash
    python3 test_integration.py
    ```
    A saída deve mostrar as operações de Lista e Árvore sendo executadas com sucesso.

3.  **Executar a Aplicação com Interface Gráfica:**
    ```bash
    python3 app_gui.py
    ```
    **Nota:** Se você estiver em um ambiente sem servidor gráfico (como este sandbox), a execução da GUI pode falhar. O objetivo principal aqui é fornecer o código funcional para ser executado em um ambiente de desktop.

## Detalhes da Implementação

### Integração Python-C (`ctypes`)

O arquivo `app_gui.py` usa `ctypes` para:

1.  **Carregar a Biblioteca:** `lib = cdll.LoadLibrary(LIB_PATH)`
2.  **Definir Tipos de Argumentos e Retorno:** Isso é crucial para garantir que o Python e o C interpretem corretamente os dados (ex: `lib.U_Lista_Inserir.argtypes = [c_int]`, `lib.U_Lista_Visualizar.restype = c_char_p`).
3.  **Gerenciamento de Memória:** A função `liberar_tudo()` em C é chamada quando a aplicação Python é fechada (`master.protocol("WM_DELETE_WINDOW", self.on_closing)`), garantindo que a memória alocada dinamicamente em C (para os nós da Lista e da Árvore) seja liberada corretamente.

### Estruturas em C

*   **Lista (Linear):** Implementada como uma Lista Encadeada Simples.
*   **Árvore (Não Linear):** Implementada como uma Árvore Binária de Busca (BST).
*   **Visualização:** As funções `U_Lista_Visualizar` e `U_Arvore_Visualizar` em C retornam uma string formatada (`char*`) que é então decodificada e exibida na GUI do Python.

Este projeto é um excelente ponto de partida para entender como linguagens de alto nível (Python) podem aproveitar a performance de linguagens de baixo nível (C) para tarefas intensivas, como manipulação de estruturas de dados complexas.
