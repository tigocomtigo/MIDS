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
    file = fopen("hamming8-2.mis", "r");
    int tam1,tam2;
    
    //Lendo os valores iniciais do arquivo
    //fscanf(file,"%%%%MatrixMarket matrix coordinate pattern symmetric\n");
    //fscanf(file,"%i %i %i\n", &tam1, &tam2, &vertices);
    //fscanf(file,"%%%%MatrixMarket matrix coordinate pattern symmetric\n");
    fscanf(file,"%i %i\n", &tam2, &tam2);

    //Iniciando a matriz esparsa
    SparseMatrix *mat = createSparseMatrix(tam2, tam2);
    
    //Inserindo os valores e recebendo um vetor com a quantidade de arestas de cada vertice
    int* arestas = insertFileValues(mat, file, tam2 - 1);
    
    //Criando o índice para encontrar os vertices com maior numero de arestas
    /*
    int* index = (int*) malloc(sizeof(int*) * (tam2 - 1));
    for(int i = 0; i < tam2; ++i){
        index[i] = i;
    }*/
    
    //Utilizando quicksort para ordenar os vertices
    //quickSort(arestas, index, 0, tam2 - 1);
    //imprima(index[0]);


    //int* resultado = algoritmoGuloso(mat, arestas, index, tam1);
    srand(time(NULL));
    algoritmoFurmigona(mat, tam2, index);
    //imprimirMIDS(resultado, tam1);
    
    /*
    for(int i = 0; i < tam1; ++i){
        printf("%i: %i\n", index[i],arestas[i]);
    }*/
    //printSparseMatrix(mat);

    return 0;
}
