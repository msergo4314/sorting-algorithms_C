#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// max number is ARRAYRANGE + 1
#define ARRAYRANGE 101 // note that this is the number of possible values, not the max number
#define ARRAYSIZE 1e2 // size of the array

void swapInts(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int writeToFile(char* fileName) {
    
    FILE *fptr;
    char filePath[104]; // Adjust the size as needed
    // cd up to parent once
    snprintf(filePath, sizeof(filePath) - 4, "../%s", fileName);
    fptr = fopen(filePath, "w");
    if (fptr == NULL) {
        return 1;
    }
    for (int i = 0; i < ARRAYSIZE; i++) {
        fprintf(fptr, "%d ", rand() % ARRAYRANGE);
    }
    fclose(fptr);
    return 0;
}

int* readFromFile(char* fileName, int *bytesAllocated) {
    FILE *fptr;
    char filePath[100]; // Adjust the size as needed
    snprintf(filePath, sizeof(filePath), "../%s", fileName);
    fptr = fopen(filePath, "r");
    int num; // current number scanned
    int scanned = 0;
    int* array = malloc(sizeof(int)); // one int
    if (fptr == NULL) {
        fprintf(stdout, "Error reading file!\n");
        return NULL;
    }
    while (fscanf(fptr, "%d ", &num) != EOF) {
        //printf("scanned: %d\n",num);
        scanned += 1;
        array = realloc(array, sizeof(int) * (scanned));
        array[scanned-1] = num;
        if (array == NULL) {
            fprintf(stderr, "ERROR WITH REALLOC\n");
        }

    }
    fclose(fptr);
    *bytesAllocated = scanned * sizeof(int);
    return array;
}

void merge(int* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}



int main() {

    srand(time(0)); // seed
    clock_t start_time, end_time;
    double cpu_time_used;


    int *myArray = NULL;
    int size = 0;
    int bytesAlloced = 0;
    
    // if (writeToFile("intArray.txt")) {
    //     printf("error with printing to the file\n");
    // }

    myArray = readFromFile("intArray.txt", &bytesAlloced);

    if (myArray == NULL) {
        printf("could not scan file contents properly\n");
        return 1;
    }
    size = (int)(bytesAlloced / sizeof(int));
    printf("allocated %'d bytes in total for %d ints\n", bytesAlloced, size);

    // printf("Original array: ");
    // for (int i = 0; i < size; i++) {
    //     printf("%d ", myArray[i]);
    // }
    printf("\n");

    start_time = clock(); // Record the start time
    
    //Sort the array using quick sort
    mergeSort(myArray, 0, size-1);
    

    end_time = clock(); // Record the end time
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    if (1) {
        printf("\nSorted array (merge sort): ");
        for (int i = 0; i < size; i++) {
            printf("%d ", myArray[i]);
        }
    }
    free(myArray);
    
    printf("\nTime taken for sorting %-5d elements with mergesort: %.8f seconds\n", size, cpu_time_used);
    return 0;
}
