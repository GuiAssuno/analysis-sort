# Analysis Sort
"Um framework de benchmarking de alta performance para análise comparativa de algoritmos, utilizando arquitetura híbrida Python/C para medir eficiência de CPU, memória e estabilidade em cenários reais."


## 📊 Tabela Comparativa

| Algoritmo | Variações Implementadas | Estabilidade | Adaptabilidade | Localidade de Cache |
| :--- | :--- | :---: | :---: | :---: |

| **Quick Sort** | • Lomuto (1 Pivô)<br>• Hoare (1 Pivô)<br>• 3-Vias (Dutch Flag)<br>• Dual-Pivot (Yaroslavskiy) | ❌ | ❌ | ⭐⭐⭐ |

---

## 📝 Notas

1.  **Quick Sort**: Apesar de instável e não adaptativo, sua excelente localidade de cache o torna o mais rápido na prática para dados aleatórios.
2.  **Tim Sort**: É o algoritmo padrão do Python e Java. Sua "Adaptabilidade" é extrema; ele detecta *runs* naturais nos dados, tornando-o imbatível em dados reais (não-aleatórios).
3.  **Cycle Sort**: Tem performance de tempo ruim ($O(n^2)$), mas é o campeão absoluto em **menor número de escritas** na memória, útil para memórias Flash/EEPROM.
4.  **Tree Sort**: O desempenho depende do balanceamento. Nesta implementação (não-balanceada), ele degrada para $O(n^2)$ se o vetor já estiver ordenado (pior caso), mas é ótimo para dados aleatórios.
