#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    double start_time = MPI_Wtime();

    // Build array
    int array_length = atoi(argv[1]);

    int *arr = malloc(array_length * sizeof(*arr));
    int *aux = malloc(array_length * sizeof(*aux));

    srand(time(NULL));
    int i;
    for (i = 0; i < array_length; ++i)
    {
        arr[i] = rand() % array_length;
    }

    // Start merge
    mergeSort(arr, 0, array_length - 1, aux);

    double end_time = MPI_Wtime();

    printf("La ejecucion secuencial tomó: %f s (MPI_TIME)\n", (end_time - start_time));
    MPI_Finalize();

    return 0;
}

void mergeSort(int arr[], int s, int e, int aux[])
{
    if (e <= s)
        return;

    int m = (s + e) / 2;

    mergeSort(arr, s, m, aux);
    mergeSort(arr, m + 1, e, aux);

    int pointer_left = s;      // pointer_left points to the beginning of the left sub-array
    int pointer_right = m + 1; // pointer_right points to the beginning of the right sub-array
    int k;                     // k is the loop counter

    // we loop from i to j to fill each element of the final merged array
    for (k = s; k <= e; k++)
    {
        if (pointer_left == m + 1)
        { // left pointer has reached the limit
            aux[k] = arr[pointer_right];
            pointer_right++;
        }
        else if (pointer_right == e + 1)
        { // right pointer has reached the limit
            aux[k] = arr[pointer_left];
            pointer_left++;
        }
        else if (arr[pointer_left] < arr[pointer_right])
        { // pointer left points to smaller element
            aux[k] = arr[pointer_left];
            pointer_left++;
        }
        else
        { // pointer right points to smaller element
            aux[k] = arr[pointer_right];
            pointer_right++;
        }
    }

    int h;
    for (h = s; h <= e; h++)
    { // copy the elements from aux[] to a[]
        arr[h] = aux[h];
    }
}

void printArray(char str[], int arr[], int arr_size)
{

    printf("Printing the %s array:\n", str);

    printf("{");
    int i;
    for (i = 0; i < arr_size; i++)
        printf(" %d", arr[i]);
    printf("} \n");
}
