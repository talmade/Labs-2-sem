#include "sort.h"

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void sortDoubles(double *arr, int count) {
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
