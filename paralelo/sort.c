

void merge(int *arr, int *aux_arr, int start, int mid, int end)
{

    int h, i, j, k;
    h = start;
    i = start;
    j = mid + 1;

    while ((h <= mid) && (j <= end))
    {

        if (arr[h] <= arr[j])
        {

            aux_arr[i] = arr[h];
            h++;
        }

        else
        {

            aux_arr[i] = arr[j];
            j++;
        }

        i++;
    }

    if (mid < h)
    {

        for (k = j; k <= end; k++)
        {

            aux_arr[i] = arr[k];
            i++;
        }
    }

    else
    {

        for (k = h; k <= mid; k++)
        {

            aux_arr[i] = arr[k];
            i++;
        }
    }

    for (k = start; k <= end; k++)
    {

        arr[k] = aux_arr[k];
    }
}

void mergeSort(int *arr, int *aux_arr, int start, int end)
{

    int mid;

    if (start < end)
    {

        mid = (start + end) / 2;

        mergeSort(arr, aux_arr, start, mid);
        mergeSort(arr, aux_arr, (mid + 1), end);
        merge(arr, aux_arr, start, mid, end);
    }
}
