#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"

int main()
{

    // Build array
    int arr_size;
    printf("Enter number of elements in the array:\n");
    scanf("%d", &arr_size);

    int arr[arr_size], aux[arr_size];
    printf("Enter %d integers\n", arr_size);

    for (int i = 0; i < arr_size; i++)
        scanf("%d", &arr[i]);

    printArray("original", arr, arr_size);

    // Start merge
    mergeSort(arr, 0, arr_size - 1, aux);

    printArray("sorted", arr, arr_size);

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

    for (int k = s; k <= e; k++)
    { // copy the elements from aux[] to a[]
        arr[k] = aux[k];
    }
}

void printArray(char str[], int arr[], int arr_size)
{

    printf("Printing the %s array:\n", str);

    printf("{");
    for (int i = 0; i < arr_size; i++)
        printf(" %d", arr[i]);
    printf("} \n");
}
