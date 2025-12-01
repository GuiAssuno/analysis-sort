import random
import ctypes
import dicionarios as dic 

class Gerenciador:
    def __init__(self):
        self.vetor_salvo = []

    def obter_vetor(self, tamanho, formato, novo_vetor=True):

        if not novo_vetor and self.vetor_salvo and len(self.vetor_salvo) == tamanho:
            return self.vetor_salvo.copy()
        
        dados = []
        match(formato):
            case "aleatorio":
                dados = [random.randint(0, int(tamanho)) for _ in range(tamanho)]

            case "fixo":
                lista_base = [3, 7, 9, 2, 9, 6, 4, 1, 0, 8, 5]
                if tamanho > len(lista_base):
                    dados = (lista_base * (tamanho // len(lista_base) + 1))[:tamanho]
                else:
                    dados = lista_base[:tamanho]
            
            case "repetido":
                dados = [random.randint(0, int(tamanho * 0.2)) for n in range(tamanho)]
            
            case "ordenado":
                dados = [random.randint(0, tamanho) for _ in range(tamanho)]
                dados.sort()
            
            case "ordenado_inverso":
                dados = [random.randint(0, tamanho) for _ in range(tamanho)]
                dados.sort(reverse=True)
            
            case "quase_ordenado":
                dados = list(range(tamanho))
                qtd_trocas = int(tamanho * 0.05) 
                if qtd_trocas < 1: qtd_trocas = 1
                for _ in range(qtd_trocas):
                    i1 = random.randint(0, tamanho-1)
                    i2 = random.randint(0, tamanho-1)
                    dados[i1], dados[i2] = dados[i2], dados[i1]
            
            case "semi_ordenado_começo":
                meio = tamanho // 2 
                dados = []
                for n in range(tamanho):
                    if n >= meio:
                        dados.append(random.randint(0, tamanho * 2))  
                    else:
                        dados.append(n)  
            
            case "semi_ordenado_alternado":
                dados = []
                for n in range(tamanho):
                    if n % 2 == 0:
                        dados.append(random.randint(0, tamanho))  
                    else:
                        dados.append(n) 
            
            case "semi_ordenado_começo_depois_alterna":
                meio = tamanho // 2
                dados = []
                for n in range(tamanho):
                    if n > meio:
                        if n % 2 == 0:
                            dados.append(random.randint(0, tamanho * 2))
                        else:
                            dados.append(n)  
                    else:
                        dados.append(n)
            
        # salva o novo vetor
        self.vetor_salvo = dados.copy()
        return dados

    def executar(self, tamanho, op_metodo, forma_vetor=False, op_sort='', novo=True):
        # Chama o método para pegar os dados
        dados = self.obter_vetor(tamanho=tamanho, formato=forma_vetor, novo_vetor=novo)

        # trasforma a lista em um array C
        ArrayC = ctypes.c_int * tamanho
        vetor_c = ArrayC(*dados)
        
        # Executa algoritmo escolhido
        tempo_segundos = dic.inicia_algortmo[op_sort](vetor_c, tamanho, int(op_metodo))

        # Converte para milisegundos
        tempo_ms = tempo_segundos * 1000
        print(f"C retornou: {tempo_ms:.4f} ms")

        return tempo_ms
