# Analysis Sort
"Um framework de benchmarking de alta performance para análise comparativa de algoritmos, utilizando arquitetura híbrida Python/C para medir eficiência de CPU, memória e estabilidade em cenários reais."


## 📊 Tabela Comparativa

| Algoritmo | Variações Implementadas | Estabilidade | Adaptabilidade | Localidade de Cache |
| :--- | :--- | :---: | :---: | :---: |
| **Quick Sort** | • Lomuto (1 Pivô)<br>• Hoare (1 Pivô)<br>• 3-Vias (Dutch Flag)<br>• Dual-Pivot (Yaroslavskiy) | ❌ | ❌ | ⭐⭐⭐ |

---

## 📝 Notas

1.  **Quick Sort**: Apesar de instável e não adaptativo, sua excelente localidade de cache o torna o mais rápido na prática para dados aleatórios.
