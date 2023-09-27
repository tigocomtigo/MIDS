#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "quicksort.h"
#include "algoritmoguloso.h"
#include "algoritmoFormiga.h"

int main()
{
    //Inicializando variáveis
    FILE *file;
    file = fopen("san1000.mtx", "r");
    int tam1,tam2,vertices;
    
    //Lendo os valores iniciais do arquivo
    fscanf(file,"%%%%MatrixMarket matrix coordinate pattern symmetric\n");
    fscanf(file,"%i %i %i\n", &tam1, &tam2, &vertices);
    
    //Iniciando a matriz esparsa
    SparseMatrix *mat = createSparseMatrix(tam1, tam2);
    
    //Inserindo os valores e recebendo um vetor com a quantidade de arestas de cada vertice
    int* arestas = insertFileValues(mat, file, tam1 - 1);
    
    //Criando o índice para encontrar os vertices com maior numero de arestas
    int* index = (int*) malloc(sizeof(int*) * (tam1 - 1));
    for(int i = 0; i < tam1; ++i){
        index[i] = i + 1;
    }
    
    //Utilizando quicksort para ordenar os vertices
    //quickSort(arestas, index, 0, tam1 - 1);
    
    //int* resultado = algoritmoGuloso(mat, arestas, index, tam1);
    srand(time(NULL));
    algoritmoFurmigona(mat, tam1);
    //imprimirMIDS(resultado, tam1);
    
    /*
    for(int i = 0; i < tam1; ++i){
        printf("%i: %i\n", index[i],arestas[i]);
    }*/
    //printSparseMatrixTeste(mat, 7);

    return 0;
}
