#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Standard Merge Sort Logic here...
void merge(int arr[], int l, int m, int r) { /* ... */ }
void mergeSort(int arr[], int l, int r) { /* ... */ }

int main() {
    int n = 1000;
    int arr[n];
    for(int i=0; i<n; i++) arr[i] = rand() % 100;
    clock_t start = clock();
    mergeSort(arr, 0, n-1);
    clock_t end = clock();
    printf("Sequential Time: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
