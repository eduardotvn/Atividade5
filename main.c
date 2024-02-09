#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int contarSerial(int *vetor, int size, int x) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (vetor[i] == x) {
            count++;
        }
    }
    return count;
}

int contarParalelo(int *vetor, int size, int x) {
    int count = 0;

    #pragma omp parallel for reduction(+:count)
    for (int i = 0; i < size; ++i) {
        if (vetor[i] == x) {
            count++;
        }
    }

    return count;
}

int main() {

    int size = -1;  

    while(size < 0)
    {
        printf("Digite um tamanho (valido) para o vetor: ");
        scanf("%d", &size);
    }
    
    int* vetor = (int*)malloc(size*sizeof(int));

    printf("Digite os valores do vetor:\n");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &vetor[i]);
    }

    printf("Agora, digite o valor a ser buscado: ");
    int x;
    scanf("%d", &x);

    double start_serial = omp_get_wtime();
    int count_serial = contarSerial(vetor, size, x);
    double end_serial = omp_get_wtime();

    double tempo_serial = end_serial - start_serial;

    double start_parallel = omp_get_wtime();
    int count_parallel = contarParalelo(vetor, size, x);
    double end_parallel = omp_get_wtime();

    double tempo_parallel = end_parallel - start_parallel;

    printf("Serial com OpenMP: %d ocorre %d vezes.\n", x, count_serial);
    printf("Tempo de execução serial com OpenMP: %f segundos\n", tempo_serial);
    printf("Paralelo com OpenMP: %d ocorre %d vezes.\n", x, count_parallel);
    printf("Tempo de execução paralelo com OpenMP: %f segundos\n", tempo_parallel);

    return 0;
}
