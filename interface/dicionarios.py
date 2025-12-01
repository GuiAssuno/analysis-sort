from config_c import lib









# =============================================================================================================================================
# ====================================================================== dic-sort =============================================================
# =============================================================================================================================================

# 3. bubble sort
bubble_sort = {
    "Padrão": "1",
    "Otimizado (Stop Early)": "2",
    "Cocktail Shaker (Bidirecional)": "3"
}

# 17. quick sort
# escolha do algoritmo
alg = {
    "Lomuto": "1",
    "Hoare": "2",
    "3-Vias (Dutch Flag)": "3",
    "Dual-Pivot (Yaroslavskiy)": "4" # O dual-pivot geralmente ignora o seletor de pivô secundário
}
# escolha do pivô
met = {
    "Último": "1",
    "Primeiro": "2",
    "Mediana de 3": "3",
    "Aleatório": "5",
    "Meio (Simples)": "4"
}


# =============================================================================================================================================
# ===================================================================== OPÇÕES ================================================================
# =============================================================================================================================================

inicia_algortmo = {
    "Bubble Sort": lib.inicia_bubble_sort,
    "Quick Sort": lib.inicia_quick_sort
}

chaves = {
    "Bubble Sort":     [bubble_sort],       # 3 jeitos: Padrão, Otimizado e Cocktail Shaker (Bidirecional)
    "Quick Sort":      [alg, met],          # 4 Algoritmos (Lomuto, Hoare, 3-Way, Dual-Pivot) + 5 Pivôs
}

tipo_vetor ={
    "Aleatórios": "aleatorio",
    "Fixo": "fixo", 
    "Duplicados": "repetido", 
    "Ordenado": "ordenado" 
}

tipo_ordenar = {
    "Completo": "ordenado",
    "Quase": "quase_ordenado", 
    "Inverso": "ordenado_inverso", 
    "Alternando": "semi_ordenado_alternado", 
    "1° Metade Ord. / Alterna": "semi_ordenado_começo_depois_alterna", 
    "1° Metade Ord. / Aleatorio": "semi_ordenado_começo"
}

# =============================================================================================================================================
# ============================================================== Big O: dic-casos =============================================================
# =============================================================================================================================================

info_algoritmos = {
    "Bitonic Sort": {
        "best": "O(log² n) paralelo",
        "avg": "O(n log² n)",
        "worst": "O(n log² n)",
        "space": "O(n log² n)",
        "desc": "Projetado para computação paralela (GPUs). Em CPU (serial) é mais lento que Merge Sort."
    },
    "Bogo Sort": {
        "best": "O(n)",
        "avg": "O(n × n!)",
        "worst": "Infinito",
        "space": "O(1)",
        "desc": "Algoritmo de piada. Embaralha aleatoriamente até ordenar. Não use com N > 12."
    },
    "Bubble Sort": {
        "best": "O(n)",
        "avg": "O(n²)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Simples e didático. A versão Cocktail é bidirecional. Bom apenas para listas quase ordenadas."
    },
    "Bucket Sort": {
        "best": "O(n + k)",
        "avg": "O(n + k)",
        "worst": "O(n²)",
        "space": "O(n)",
        "desc": "Distribui em baldes. Ótimo para distribuição uniforme (0.0 a 1.0). Pior caso ocorre se tudo cai num balde só."
    },
    "Comb Sort": {
        "best": "O(n log n)",
        "avg": "O(n² / 2^p)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Melhoria do Bubble Sort. Usa um 'gap' (fator 1.3) para eliminar 'tartarugas' (números pequenos no fim)."
    },
    "Counting Sort": {
        "best": "O(n + k)",
        "avg": "O(n + k)",
        "worst": "O(n + k)",
        "space": "O(k)",
        "desc": "Não comparativo. Conta a frequência. Imbatível se o range (k) for pequeno. Gasta muita RAM se k for grande."
    },
    "Cycle Sort": {
        "best": "O(n²)",
        "avg": "O(n²)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Lento, mas faz o mínimo teórico de escritas na memória. Ideal para memórias EEPROM/Flash desgastáveis."
    },
    "Flash Sort": {
        "best": "O(n)",
        "avg": "O(n + m)",
        "worst": "O(n²)",
        "space": "O(n)",
        "desc": "Probabilístico in-place. Classifica dados por distribuição (similar ao Bucket) sem gastar muita memória extra."
    },
    "Gnome Sort": {
        "best": "O(n)",
        "avg": "O(n²)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Similar ao Insertion Sort, mas move elementos como um 'Gnomo de Jardim' (troca e volta). Código muito simples."
    },
    "Heap Sort": {
        "best": "O(n log n)",
        "avg": "O(n log n)",
        "worst": "O(n log n)",
        "space": "O(1)",
        "desc": "Garante O(n log n) sem memória extra, mas é lento na prática devido à má localidade de cache (saltos na memória)."
    },
    "Insertion Sort": {
        "best": "O(n)",
        "avg": "O(n²)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Excelente para vetores pequenos (N < 50) ou quase ordenados. Usado internamente pelo TimSort e IntroSort."
    },
    "Intro Sort": {
        "best": "O(n log n)",
        "avg": "O(n log n)",
        "worst": "O(n log n)",
        "space": "O(log n)",
        "desc": "Híbrido (Quick + Heap + Insertion). Começa com Quick, muda para Heap se a recursão ficar profunda. Padrão do C++."
    },
    "Merge Sort": {
        "best": "O(n log n)",
        "avg": "O(n log n)",
        "worst": "O(n log n)",
        "space": "O(n)",
        "desc": "Estável e previsível. Divide e conquista. Gasta memória extra O(n), o que é ruim para grandes volumes de dados."
    },
    "Odd-Even Sort": {
        "best": "O(n)",
        "avg": "O(n²)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Variação paralela do Bubble Sort. Compara pares Ímpares/Pares independentemente. Útil em hardware paralelo."
    },
    "Pancake Sort": {
        "best": "O(n)",
        "avg": "O(n²)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Problema matemático: ordenar apenas 'virando' o topo da pilha (flip). Curiosidade teórica."
    },
    "Pigeonhole Sort": {
        "best": "O(n + range)",
        "avg": "O(n + range)",
        "worst": "O(n + range)",
        "space": "O(range)",
        "desc": "Pai do Counting Sort. Move itens para 'buracos' correspondentes. Rápido se a variação de valores for pequena."
    },
    "Quick Sort": {
        "best": "O(n log n)",
        "avg": "O(n log n)",
        "worst": "O(n²)",
        "space": "O(log n)",
        "desc": "Rei da performance geral. Instável. Cache-friendly. O Dual-Pivot (Java) é a versão mais moderna e rápida."
    },
    "Radix Sort": {
        "best": "O(nk)",
        "avg": "O(nk)",
        "worst": "O(nk)",
        "space": "O(n + k)",
        "desc": "Ordena dígito por dígito. Linear para inteiros, mas tem overhead alto. LSD é estável, MSD não."
    },
    "Selection Sort": {
        "best": "O(n²)",
        "avg": "O(n²)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Lento. Faz o mínimo de trocas (N) entre os algoritmos quadráticos, mas faz muitas comparações."
    },
    "Shell Sort": {
        "best": "O(n log n)",
        "avg": "O(n log n) a O(n^1.5)",
        "worst": "O(n²)",
        "space": "O(1)",
        "desc": "Generalização do Insertion Sort usando 'gaps'. A sequência de Ciura ou Knuth torna ele surpreendentemente rápido."
    },
    "Stooge Sort": {
        "best": "O(n^2.7)",
        "avg": "O(n^2.7)",
        "worst": "O(n^2.7)",
        "space": "O(1)",
        "desc": "Propositalmente ruim. Ordena recursivamente o início (2/3) e o fim (2/3). Apenas para fins educacionais."
    },
    "Tim Sort": {
        "best": "O(n)",
        "avg": "O(n log n)",
        "worst": "O(n log n)",
        "space": "O(n)",
        "desc": "O 'Estado da Arte'. Híbrido (Merge + Insertion). Detecta padrões nos dados. Padrão do Python e Java."
    },
    "Tree Sort": {
        "best": "O(n log n)",
        "avg": "O(n log n)",
        "worst": "O(n²)",
        "space": "O(n)",
        "desc": "Constrói uma Árvore Binária de Busca (BST). Degrada para O(n²) se a árvore ficar desbalanceada (vetor já ordenado)."
    }
}




# =============================================================================================================================================
# ==================================================== DICIONÁRIOS DE CONFIGURAÇÃO ============================================================
# =============================================================================================================================================


# 1. bitonic sort
Tag_bitonic_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": False}
}

# 2. bogo sort
Tag_bogo_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": False}
}

# 3. bubble sort
Tag_bubble_sort = {
    "Padrão": {"id": "standard", "estavel": True, "adaptativo": True},
    "Otimizado": {"id": "optimized", "estavel": True, "adaptativo": True},
    "Cocktail Shaker": {"id": "cocktail", "estavel": True, "adaptativo": True}
}

# 4. bucket sort
Tag_bucket_sort = {
    "Padrão": {"id": "standard", "estavel": True, "adaptativo": False}
}

# 5. comb sort
Tag_comb_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": True}
}

# 6. counting sort
Tag_counting_sort = {
    "Padrão (Positivos)": {"id": "standard", "estavel": True, "adaptativo": False},
    "Com Shift (Negativos)": {"id": "shift", "estavel": True, "adaptativo": False}
}

# 7. cycle sort
Tag_cycle_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": False}
}

# 8. flash sort
Tag_flash_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": True}
}

# 9. gnome sort
Tag_gnome_sort = {
    "Padrão": {"id": "standard", "estavel": True, "adaptativo": True}
}

# 10. heap sort
Tag_heap_sort = {
    "Heapify (Floyd)": {"id": "heapify", "estavel": False, "adaptativo": False},
    "Sift-Up": {"id": "siftup", "estavel": False, "adaptativo": False}
}

# 11. insertion sort
Tag_insert_sort = {
    "Linear": {"id": "linear", "estavel": True, "adaptativo": True},
    "Binária": {"id": "binary", "estavel": True, "adaptativo": True}
}

# 12. intro sort
Tag_intro_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": True}
}

# 13. merge sort
Tag_merge_sort = {
    "Recursivo": {"id": "recursivo", "estavel": True, "adaptativo": False},
    "Iterativo": {"id": "iterativo", "estavel": True, "adaptativo": False}
}

# 14. odd-even sort
Tag_odd_even_sort = {
    "Padrão": {"id": "standard", "estavel": True, "adaptativo": True}
}

# 15. pancake sort
Tag_pancake_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": False}
}

# 16. pigeonhole sort
Tag_pigeonhole_sort = {
    "Padrão": {"id": "standard", "estavel": True, "adaptativo": False}
}

# 17. quick sort
Tag_alg = {
    "Lomuto": {"id": "1", "estavel": False, "adaptativo": False},
    "Hoare": {"id": "2", "estavel": False, "adaptativo": False},
    "3-Vias": {"id": "3", "estavel": False, "adaptativo": False}, # Melhora com repetidos, mas não ordenados
    "Dual-Pivot": {"id": "4", "estavel": False, "adaptativo": False}
}
Tag_met = {
    "Último": "1",
    "Primeiro": "2",
    "Mediana de 3": "3",
    "Aleatório": "5",
    "Meio": "4"
}

# 18. radix sort
Tag_radix_sort = {
    "LSD": {"id": "LSD", "estavel": True, "adaptativo": False},
    "MSD": {"id": "MSD", "estavel": False, "adaptativo": False} # MSD in-place geralmente é instável
}

# 19. selection sort
Tag_selection_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": False},
    "Bidirecional": {"id": "double", "estavel": False, "adaptativo": False}
}

# 20. shell sort
Tag_shell_sort = {
    "Shell": {"id": "1", "estavel": False, "adaptativo": True},
    "Knuth": {"id": "2", "estavel": False, "adaptativo": True},
    "Ciura": {"id": "3", "estavel": False, "adaptativo": True},
    "Hibbard": {"id": "4", "estavel": False, "adaptativo": True}
}

# 21. stooge sort
Tag_stooge_sort = {
    "Padrão": {"id": "standard", "estavel": False, "adaptativo": False}
}

# 22. tim sort
Tag_tim_sort = {
    "Padrão": {"id": "1", "estavel": True, "adaptativo": True},
    "Completo": {"id": "2", "estavel": True, "adaptativo": True}
}

# 23. tree sort
Tag_tree_sort = {
    "Padrão": {"id": "standard", "estavel": True, "adaptativo": True} 
    # Tree sort In-Order é estável dependendo da implementação da árvore, 
    # e adaptativo porque montagem da árvore muda com dados ordenados (pior caso).
}