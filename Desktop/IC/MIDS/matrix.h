// Estrutura de nó para representar elementos não nulos
typedef struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
} Node;

// Estrutura de matriz esparsa
typedef struct SparseMatrix {
    int rows;
    int cols;
    Node** data; // Array de ponteiros para nós
} SparseMatrix;

// Função para criar uma matriz esparsa vazia
SparseMatrix* createSparseMatrix(int rows, int cols) {
    SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if (!matrix) {
        fprintf(stderr, "Erro: Falha na alocação de memória.\n");
        exit(1);
    }
    matrix->rows = rows;
    matrix->cols = cols;
    
    // Inicializar a matriz com NULLs
    matrix->data = (Node**)malloc(rows * sizeof(Node*));
    if (!matrix->data) {
        fprintf(stderr, "Erro: Falha na alocação de memória.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = NULL;
    }
    
    return matrix;
}

// Função para inserir um elemento não nulo na matriz
void insertElement(SparseMatrix* matrix, int row, int col, int value) {
    if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols) {
        fprintf(stderr, "Erro: Índices de linha ou coluna fora do intervalo.\n");
        return;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Erro: Falha na alocação de memória.\n");
        exit(1);
    }
    
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    
    // Inserir na lista de nós da linha
    if (matrix->data[row] == NULL) {
        matrix->data[row] = newNode;
    } else {
        Node* current = matrix->data[row];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


// Função para imprimir a matriz esparsa
void printSparseMatrix(SparseMatrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        Node* current = matrix->data[i];
        for (int j = 0; j < matrix->cols; j++) {
            if (current && current->col == j) {
                printf("%d ", current->value);
                current = current->next;
            } else {
                //printf("0 ");
            }
        }
        printf("\n");
    }
}

void printSparseMatrixTeste(SparseMatrix* matrix, int teste) {
    Node* current = matrix->data[teste];
    for (int j = 0; j < matrix->cols; j++) {
        if (current && current->col == j) {
            printf("%d ", current->value);
            current = current->next;
        } else {
            //printf("0 ");
        }
    }
    printf("\n");
        
    
}

// Função para inserir os valores do arquivo texto e retornar o numero de arestas de cada elemento
int* insertFileValues(SparseMatrix* matrix, FILE* file, int size, int tipo){
    int valor1, valor2;
    int* retorno = (int*) malloc(sizeof(int*) * size);
    if(retorno == NULL){
        printf("Erro: Falha na alocação de memória.");
        exit(1);
    }else{
        for(int i = 0; i < size; ++i){
            retorno[i] = 0;
        }
    }
    if(tipo == 1){
        while(!feof(file)){
            fscanf(file,"%i %i\n", &valor1, &valor2);
            //fscanf(file,"%i %i\n", &valor1, &valor2);
            insertElement(matrix, valor1 - 1, valor2 - 1, valor2);
            insertElement(matrix, valor2 - 1, valor1 - 1, valor1);
            ++retorno[valor1 - 1];
            ++retorno[valor2 - 1];
        }
    }else if(tipo == 2){
        while(!feof(file)){
            fscanf(file,"e %i %i\n", &valor1, &valor2);
            //fscanf(file,"%i %i\n", &valor1, &valor2);
            insertElement(matrix, valor1 - 1, valor2 - 1, valor2);
            insertElement(matrix, valor2 - 1, valor1 - 1, valor1);
            ++retorno[valor1 - 1];
            ++retorno[valor2 - 1];
        }
    }
    
    return retorno;
}