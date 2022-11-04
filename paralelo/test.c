#include <stdio.h>
#include <stdlib.h>
#include "util.c"
#include <ctype.h>
int main(int argc, char **argv)
{

    int *array = malloc((argc - 2) * sizeof(*array));
    int arr_len = argc - 2;

    for (int i = 0; i < argc - 2; ++i)
        array[i] = atoi(argv[i + 2]);

    printArray(array, argc - 2, 1);

    free(array);
    return 0;
}