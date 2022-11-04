#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.c"
#include "sort.c"

int array[10] = {3, 5, 1, 2, 7, 6, 8, 9, 0, 4};

// En los parametros asumo que paso
// argv[0] => Cantidad de nodos
// argv[1] => El array
int main(int argc, char **argv)
{
    printf("%s", argv[1]);
    /***** Inicializo MPI *****/
    int my_id,
        comm_size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,
                  &my_id);

    MPI_Comm_size(MPI_COMM_WORLD,
                  &comm_size);

    /***** Parseo el array *****/

    /*****Defino variables necesarias *****/
    int array_length = sizeof(array) / sizeof(array[0]);

    // Todo: Cambiar por comm_size para que se pueda usar en distintos tamaños
    int sub_array_length = array_length / 8;
    int partition_size = array_length / sub_array_length;

    // Todo: Si el tamaño del array es dinamico, entonces cambiar la definicion
    // int *sub_array = malloc(partition_size * sizeof(int));
    int sub_array[sub_array_length];

    /***** Reparto subarrays *****/
    MPI_Scatter(array,
                sub_array_length,
                MPI_INT,
                sub_array,
                sub_array_length,
                MPI_INT,
                0,
                MPI_COMM_WORLD);

    // Todo: Si el tamaño del array es dinamico, entonces cambiar la definicion
    // int *aux_array = malloc(partition_size * sizeof(int));
    int aux_array[sub_array_length];
    mergeSort(sub_array, aux_array, 0, sub_array_length - 1);

    /***** Concateno todos los subarray en 1 *****/
    int *merged_array = NULL;
    if (my_id == 0)
    {
        merged_array = malloc(array_length * sizeof(int));
    }

    MPI_Gather(sub_array,
               sub_array_length,
               MPI_INT,
               merged_array,
               sub_array_length,
               MPI_INT,
               0,
               MPI_COMM_WORLD);

    /***** Armo el ultimo ordenamiento desde el master *****/

    if (my_id == 0)
    {
        // Todo: Si el tamaño del array es dinamico, entonces cambiar la definicion
        int temp_array[25];

        printArray(merged_array, array_length, 1);
        mergeSort(merged_array, temp_array, 0, array_length - 1);
        printArray(merged_array, array_length, 1);

        // free(merged_array);
    }

    // free(sub_array);
    // free(aux_array);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}
