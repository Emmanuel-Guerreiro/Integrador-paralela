#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.c"
#include "sort.c"

// En los parametros asumo que paso
// argv[0] => Cantidad de nodos
// argv[1] => El array
int main(int argc, char **argv)
{

    /***** Inicializo MPI *****/
    int my_id,
        comm_size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,
                  &my_id);

    MPI_Comm_size(MPI_COMM_WORLD,
                  &comm_size);

    double start_time = MPI_Wtime();

    int array_length = atoi(argv[1]);
    int *array = malloc(array_length * sizeof(*array));

    if (my_id == 0)
    {
        srand(time(NULL));
        int i;
        for (i = 0; i < array_length; ++i)
        {

            array[i] = rand() % array_length;
        }

        MPI_Bcast(array,
                  array_length,
                  MPI_INT,
                  0,
                  MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    /*****Defino variables necesarias *****/

    int sub_array_length = array_length / comm_size;

    int partition_size = array_length / sub_array_length;

    // Todo: Si el tamaño del array es dinamico, entonces cambiar la definicion
    int *sub_array = malloc(sub_array_length * sizeof(int));
    // int  [sub_array_length];

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
    int *aux_array = malloc(sub_array_length * sizeof(int));
    // int aux_array[sub_array_length];
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
        int *temp_array = malloc(array_length * sizeof(int));

        mergeSort(merged_array, temp_array, 0, array_length - 1);
    }

    double end_time = MPI_Wtime();
    if (my_id == 0)
    {
        printf("La ejecucion tomó: %f s (MPI_TIME)\n", (end_time - start_time));
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}
