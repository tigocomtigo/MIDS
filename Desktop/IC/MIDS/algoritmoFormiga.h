#include <time.h>
#include "comandossimplificados.h"
#define ferInicial 1
#define ferEntrada 1
#define ferSaida 1
#define ferMax 3000000

int totalFeromonios;

// Como fazer isso funcionar?
// Colocando valores em um vetor e dependendo do valor total temos maiores probabilidades
// Posicoes precisam estar ordenadas

void colocarFeromonios(int* tabela, int pos){
    tabela[pos] += ferEntrada;
    totalFeromonios += ferEntrada;
    //imprima(totalFeromonios);
}

int encontrarCaminhoRandomico(int* tabela, int tamTabela, int* marcado){
    //rand(time(NULL));
    int aux = rand() % (totalFeromonios);
    int i = 0;
    int j = 0;
    while(j < aux){
        //printf("j:");
        j += tabela[i];
        //imprima(j);
        ++i;
    }
    if(marcado[i] != 0){
        for(int k = i; k < tamTabela; ++k){
            if(marcado[k] == 0){
                return k;
            }
        }
        for(int k = i; k >= 0; --k){
            if(marcado[k] == 0){
                return k;
            }
        }
    }
    return i;
}

/*void zerarEntradas(int* marcado, int tam){
    for(int i = 0; i < tam; ++i){
        marcado[i] = 0;
    }
}*/

void ajustarEntradas(int* tabela, int tamTabela){
    for(int i = 0; i < tamTabela; ++i){
        tabela[i] = ferInicial;
    }
}

int removerAdjascentesFormigas(SparseMatrix* mat, int* marcado, int pos, int tam2){
    Node* aux = mat->data[pos];
    int retorno = tam2 - 1;
    while(aux != NULL){
        if(marcado[aux->col] == 0){
            marcado[aux->col] = 2;
            --retorno;
        }
        aux = aux->next;
    }
    return retorno;
}

int testarResultado(SparseMatrix* mat, int entrada[], int tamanho){
    int* marcado = malloc(sizeof(int*) * (tamanho - 1));
    zerarEntradas(marcado, tamanho);
    for(int i = 0; i < tamanho; ++i){
        //marcado[i] == 1;
        if(entrada[i] == 0){
            break;
        }
        //imprima(entrada[i]);
        marcado[entrada[i]] = 1;
        removerAdjacentes(mat, marcado, entrada[i]);
    }
    for(int i = 0; i < tamanho; ++i){
        if(marcado[i] == 0){
            //imprima(i);
            return 0;
        }
    }
    return 1;
    
}

void zerarSimples(int* vetor, int tamanho){
    for(int i = 0; i < tamanho; ++i){
        if(vetor[i] == 0){
            break;
        }else{
            vetor[i] = 0;
        }
    }
}

void inserirSeNaoPertence(int* vetorFeromonio, int valor, int tamanho){
    for(int i = 0; i < tamanho; ++i){
        if(vetorFeromonio[i] == valor){
            break;
        }else if(vetorFeromonio[i] == 0){
            vetorFeromonio[i] = valor;
            break;
        }
    }
}

int ajustarFormigasGulosas(int* index, int* tabela, int tamanho){
    for(int i = 0; i < tamanho; ++i){
        tabela[index[i]] = i + 1;
    }
}

void algoritmoFurmigona(SparseMatrix* mat, int tamanho, int* index){
    int* marcado = malloc(sizeof(int*) * (tamanho - 1));
    int* tabela = malloc(sizeof(int*) * (tamanho - 1));
    ajustarEntradas(tabela, tamanho);
    //ajustarFormigasGulosas(index, tabela, tamanho);
    totalFeromonios = ferInicial * tamanho;
    int* vetorResposta = malloc(sizeof(int*) * (tamanho - 1));
    int* vetorFinal = malloc(sizeof(int*) * (tamanho - 1));
    int* vetorFeromonio = malloc(sizeof(int*) * (tamanho - 1));
    zerarEntradas(vetorFinal, tamanho);
    zerarEntradas(vetorFeromonio, tamanho);
    //printf("%i ", tamanho);
    int menor = tamanho;
    int atual;
    int aux;
    int tam2;
    int pos;
    //zerarEntradas(vetorResposta,tamanho);
    //printf("%i ", totalFeromonios);
    while(totalFeromonios < ferMax){
        //imprima(totalFeromonios);
        tam2 = tamanho;
        aux = 0;
        atual = 0;
        zerarSimples(vetorResposta, tamanho);
        zerarEntradas(marcado, tamanho);
        //printf("%i ", tam2);
        while(tam2 > 0){
            pos = encontrarCaminhoRandomico(tabela, tamanho, marcado);
            marcado[pos] = 1;
            tam2 = removerAdjascentesFormigas(mat, marcado, pos, tam2);
            vetorResposta[aux] = pos + 1;
            //marcado[pos] = 1;
            //imprima(pos);
            //printf("x:");
            //imprima(tam2);
            //pausar();
            //imprima(totalFeromonios);
            //colocarFeromonios(tabela,pos);
            //imprima(vetorResposta[aux]);
            ++atual;
            ++aux;
            //printf("%i ", totalFeromonios);
            //printf("%i ", atual);
        }
        //imprima(-1);
        //imprima(menor);
        //printf("\n");
        //imprima(testarResultado(mat, vetorResposta, tamanho));
        //printf("\n");
        if(atual <= menor){
            zerarSimples(vetorFinal, tamanho);
            zerarEntradas(vetorFeromonio, tamanho);
            for(int i = 0; i < tamanho; ++i){
                vetorFinal[i] = vetorResposta[i];
                vetorFeromonio[i] = vetorResposta[i];
                if(vetorFinal[i] == 0){
                    break;
                }
                colocarFeromonios(tabela,vetorFinal[i]);
            }
            //printf("%i", menor);
            menor = atual;
        }else if(atual == menor){
            //imprima(totalFeromonios);
            for(int i = 0; i < tamanho; ++i){
                //imprima(vetorFinal[i]);
                if(vetorFeromonio[i] != 0){
                    inserirSeNaoPertence(vetorFeromonio, vetorResposta[i], tamanho);
                    colocarFeromonios(tabela,vetorFeromonio[i]);
                }else{
                    break;
                }
            }
            //imprima(-1);
        }else{
            for(int i = 0; i < tamanho; ++i){
                //imprima(vetorFinal[i]);
                if(vetorFeromonio[i] != 0){
                    //imprima(vetorFinal[i]);
                    colocarFeromonios(tabela,vetorFeromonio[i]);
                }else{
                    break;
                }
            }
        }
        //printf("%i", menor);
    }
    //zerarEntradas(marcado, tamanho);
    //imprima(testarResultado(mat, vetorFinal, tamanho));
    
    for(int i = 0; i < tamanho; ++i){
        
        if(vetorFinal[i] == 0){
            imprima(i);
            break;
        }
        //printf("%i ", vetorFinal[i]);
    }
    
}




