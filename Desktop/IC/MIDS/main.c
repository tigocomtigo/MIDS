#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "quicksort.h"
#include "algoritmoguloso.h"
#include "algoritmoFormiga.h"
#define leitura 1
//1 = Dimacs, 2 = bshlib

int main()
{
    //Inicializando variáveis
    FILE *file;
    file = fopen("san200_0.7_1.mis", "r");
    int tam2,vertices;
    
    if(leitura == 1){
        fscanf(file,"%i %i\n", &tam2, &tam2);
        fscanf(file,"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ");
    }else if(leitura == 2){
        fscanf(file, "p edge %i %i    ", &tam2, &vertices);
    }

    //Lendo os valores iniciais do arquivo
    //fscanf(file,"%%%%MatrixMarket matrix coordinate pattern symmetric\n");
    //fscanf(file,"%i %i %i\n", &tam1, &tam2, &vertices);
    //fscanf(file,"p edge %i %i \n", &tam2, &tam1);
    //fscanf(file,"%i %i\n", &tam2, &tam2);

    //Iniciando a matriz esparsa
    SparseMatrix *mat = createSparseMatrix(tam2, tam2);
    
    //Inserindo os valores e recebendo um vetor com a quantidade de arestas de cada vertice
    int* arestas = insertFileValues(mat, file, tam2 - 1, leitura);
    
    //Criando o índice para encontrar os vertices com maior numero de arestas
    /*
    int* index = (int*) malloc(sizeof(int*) * (tam2 - 1));
    for(int i = 0; i < tam2; ++i){
        index[i] = i;
    }*/
    
    //Utilizando quicksort para ordenar os vertices
    //quickSort(arestas, index, 0, tam2 - 1);
    //imprima(index[0]);


    //int* resultado = algoritmoGuloso(mat, arestas, index, tam2);
    //imprimirMIDS(resultado, tam2);
    
    srand(time(NULL));
    double elapsed = 0;
    clock_t begin = clock();
    
    for(int i = 2; i < 200; ++i){
        printf("%i: ", i);
        algoritmoFurmigona(mat, tam2, i);
        printf("\n");
    }

    //algoritmoFurmigona(mat, tam2, 18);

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    elapsed = time_spent;
    printf("\nExecuted in : %f s\n", elapsed);
    //imprimirMIDS(resultado, tam1);

    /*
    for(int i = 0; i < tam1; ++i){
        printf("%i: %i\n", index[i],arestas[i]);
    }*/
    //printSparseMatrix(mat);

    return 0;
}
