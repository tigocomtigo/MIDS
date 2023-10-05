void zerarEntradas(int* marcado, int tam){
    for(int i = 0; i < tam; ++i){
        marcado[i] = 0;
    }
}

void removerAdjacentes(SparseMatrix* mat, int* marcado, int pos){
    Node* aux = mat->data[pos];
    while(aux != NULL){
        if(marcado[aux->col] != 1){
            marcado[aux->col] = 2;
        }
        //marcado[aux->col] = 2;
        aux = aux->next;
    }
}

void removerLista(SparseMatrix* mat, int* marcado, int pos,int* arestas, int* index, int tamanho){
    Node* aux = mat->data[pos];
    while(aux != NULL){
        for(int i = 0; i < tamanho; ++i){
            if(index[i] == aux->col){
                --arestas[i];
                break;
            }
        }
        aux = aux->next;
    }
}

void removerAdjacentesTeste(SparseMatrix* mat, int* marcado, int pos,int* arestas, int* index, int tamanho){
    Node* aux = mat->data[pos];
    while(aux != NULL){
        if(marcado[aux->col] != 1){
            marcado[aux->col] = 2;
            removerLista(mat, marcado, aux->col, arestas, index, tamanho);
        }
        //marcado[aux->col] = 2;
        aux = aux->next;
    }
}


int* algoritmoGuloso(SparseMatrix* mat, int* arestas, int* index, int tamanho){
    int* marcado = malloc(sizeof(int*) * (tamanho - 1));
    zerarEntradas(marcado, tamanho);
    
    for(int i = tamanho - 1; i > 0; --i){
        if(marcado[index[i]] == 0){
            marcado[index[i]] = 1;
            removerAdjacentesTeste(mat, marcado, i, arestas, index, tamanho);
            quickSort(arestas, index, 0, tamanho - 1);
        }
    }
    
    return marcado;
}

void imprimirMIDS(int* marcado, int tam){
    int contador = 0;
    for(int i = 0; i < tam; ++i){
        if(marcado[i] == 1){
            ++contador;
            //printf("%i ", i);
        }
    }
    printf("%i", contador);
}