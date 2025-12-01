# Analysis Sort
"Um framework de benchmarking de alta performance para análise comparativa de algoritmos, utilizando arquitetura híbrida Python/C para medir eficiência de CPU, memória e estabilidade em cenários reais."


## 📊 Tabela Comparativa

* **Estabilidade**: Se existem dois elementos com o mesmo valor, eles mantêm a ordem original relativa após a ordenação?
    * **Sim**: Estável.
    * **Não**: Instável.
      
* **Adaptabilidade**: O algoritmo consegue tirar vantagem se o vetor já estiver parcialmente ordenado (rodando mais rápido)?
    * **Sim**: Torna-se $O(n)$ ou próximo disso.
    * **Não**: Roda sempre no mesmo tempo $O(n^2)$ ou $O(n \log n)$.
      
* **Localidade de Cache**: O algoritmo acessa a memória de forma sequencial (amigável à CPU) ou faz saltos aleatórios (lento)?
    * **Excelente**: Acesso linear contínuo.
    * **Boa**: Acesso linear na maior parte, com alguns saltos.
    * **Ruim**: Muitos saltos de memória ou uso excessivo de ponteiros/listas auxiliares.
      
  
| Algoritmo | Variações Implementadas | Estabilidade | Adaptabilidade | Localidade de Cache |
| :--- | :--- | :---: | :---: | :---: |
| **Quick Sort** | • Lomuto (1 Pivô)<br>• Hoare (1 Pivô)<br>• 3-Vias (Dutch Flag)<br>• Dual-Pivot (Yaroslavskiy) | **Não** | **Não** | **Excelente** |

---

## 📝 Notas

1.  **Quick Sort**: Apesar de instável e não adaptativo, sua excelente localidade de cache o torna o mais rápido na prática para dados aleatórios.
