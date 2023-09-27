#include <time.h>
#include "comandossimplificados.h"
#define ferInicial 10
#define ferEntrada 10
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

int verificarAdjascentes(SparseMatrix* mat, int* marcado, int pos){
    Node* aux = mat->data[pos];
    while(aux != NULL){
        if(marcado[aux->col] == 2 || marcado[aux->col] == 1){
            return 0;
        }
        //marcado[aux->col] = 2;
        aux = aux->next;
    }
    return 1;
}

int encontrarCaminhoRandomico(SparseMatrix* mat, int* tabela, int tamTabela, int* marcado){
    //srand(time(NULL));
    int aux = rand() % (totalFeromonios);
    int i = 0;
    int j = 0;
    while(j < aux){
        //printf("j:");
        j += tabela[i];
        //imprima(j);
        ++i;
    }
    if(verificarAdjascentes(mat, marcado, i) == 0){
        for(int k = i; k < tamTabela; ++k){
            if(verificarAdjascentes(mat, marcado, k) == 1){
                return k;
            }
            if(verificarAdjascentes(mat, marcado, (2*i) - k) == 1 && k <= (2*i)){
                return ((2*i) - k);
            }
        }
        return -1;
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

int removerAdjascentesDoAdjascenteFormigas(SparseMatrix* mat, int* marcado, int pos, int tam2){
    Node* aux = mat->data[pos];
    int retorno = tam2 - 1;
    while(aux != NULL){
        if(marcado[aux->col] == 0){
            //imprima(aux->col);
            marcado[aux->col] = 3;
            //--retorno;
        }
        aux = aux->next;
    }
    return retorno;
}

int removerAdjascentesFormigas(SparseMatrix* mat, int* marcado, int pos, int tam2){
    Node* aux = mat->data[pos];
    int retorno = tam2 - 1;
    while(aux != NULL){
        if(marcado[aux->col] == 0 || marcado[aux->col] == 3){
            //imprima(aux->col);
            marcado[aux->col] = 2;
            retorno = removerAdjascentesDoAdjascenteFormigas(mat, marcado, aux->col, retorno);
            //marcado[aux->col] = 2;
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

int existeTres(int* marcado, int tamanho){
    for(int i = 0; i < tamanho; ++i){
        if(marcado[i] == 3){
            return 1;
        }
    }
    return 0;
}

void algoritmoFurmigona(SparseMatrix* mat, int tamanho){
    int* marcado = malloc(sizeof(int*) * (tamanho - 1));
    int* tabela = malloc(sizeof(int*) * (tamanho - 1));
    ajustarEntradas(tabela, tamanho);
    totalFeromonios = ferInicial * tamanho;
    int* vetorResposta = malloc(sizeof(int*) * (tamanho - 1));
    int* vetorFinal = malloc(sizeof(int*) * (tamanho - 1));
    zerarEntradas(vetorFinal, tamanho);
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
        zerarEntradas(vetorResposta, tamanho);
        zerarEntradas(marcado, tamanho);
        //printf("%i ", tam2);
        while(tam2 > 0){
            pos = encontrarCaminhoRandomico(mat, tabela, tamanho, marcado);
            if(pos == -1){
                break;
            }
            marcado[pos] = 1;
            tam2 = removerAdjascentesFormigas(mat, marcado, pos, tam2);
            vetorResposta[aux] = pos;
            //marcado[pos] = 1;
            imprima(pos);
            printf("x:");
            imprima(tam2);
            pausar();
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
        /*
        if(existeTres(marcado, tamanho) == 0){
            imprima(existeTres(marcado, tamanho));
        }*/
        //imprima(existeTres(marcado, tamanho));
        if(existeTres(marcado, tamanho) == 0){
            if(atual < menor){
                zerarEntradas(vetorFinal, tamanho);
                for(int i = 0; i < tamanho; ++i){
                    vetorFinal[i] = vetorResposta[i];
                    if(vetorFinal[i] == 0){
                        break;
                    }
                    colocarFeromonios(tabela,vetorFinal[i]);
                }
                //printf("%i", menor);
                menor = atual;
            }else{
                //imprima(totalFeromonios);
                for(int i = 0; i < tamanho; ++i){
                    //imprima(vetorFinal[i]);
                    if(vetorFinal[i] != 0){
                        //imprima(vetorFinal[i]);
                        colocarFeromonios(tabela,vetorFinal[i]);
                    }else{
                        break;
                    }
                }
                //imprima(-1);
            }
        }
        
        //printf("%i", menor);
    }
    //imprima(testarResultado(mat, vetorFinal, tamanho));
    
    for(int i = 0; i < tamanho; ++i){
        printf("%i ", vetorFinal[i]);
    }
    
}

//arumar outro jeito de fazer a inserção de feromonios



