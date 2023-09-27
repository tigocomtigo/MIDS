void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int values[], int indices[], int low, int high) {
    int pivot = values[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (values[j] < pivot) {
            i++;
            swap(&values[i], &values[j]);
            swap(&indices[i], &indices[j]);
        }
    }
    swap(&values[i + 1], &values[high]);
    swap(&indices[i + 1], &indices[high]);
    return (i + 1);
}

void quickSort(int values[], int indices[], int low, int high) {
    if(values != NULL && indices != NULL){
        if (low < high) {
            int pi = partition(values, indices, low, high);
    
            quickSort(values, indices, low, pi - 1);
            quickSort(values, indices, pi + 1, high);
        }
    }else{
        printf("Erro: vetor de valores nulos");
    }
}

