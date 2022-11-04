#include <stdio.h>
#include <ctype.h>
void printArray(int arr[], int arr_size, int node_id)
{

    printf("Printing from %d array: \t", node_id);

    printf("{");
    int i;
    for (i = 0; i < arr_size; i++)
    {
        printf(" %d", arr[i]);
    }
    printf("} \n");
}

long int *processArray(char *input, int *lng)
{
    int length = 0, i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == ',')
            length++;
        i++;
    }
    if (length > 0)
        length++;

    input++;

    int j = 0;
    long int *out = malloc(length * sizeof(long int));
    while (*input != '}')
    {
        while (*input != '\0' && !isdigit(*input))
            input++;
        if (!isdigit(*input))
            break;
        out[j++] = strtol(input, &input, 10);
    }
    *lng = j;

    return out;
}
