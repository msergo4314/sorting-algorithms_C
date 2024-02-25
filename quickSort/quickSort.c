#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// max number is ARRAYRANGE + 1
#define ARRAYRANGE 101 // note that this is the number of values, not the max number
#define ARRAYSIZE 1e6 // size of the array

void swapInts(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int* arr, int start, int end) {
    int pivot = arr[end];
    int i = start-1;
    int j = start;
    while (j < end) {
        if(arr[j] <= pivot) {
            i += 1;
            swapInts(&arr[j], &arr[i]);
        }
        j++;
    }
    i++; // increment i
    swapInts(&arr[j], &arr[i]);
    return i; // location of pivot (middle of array)
}

void quickSort(int* arr, int start, int end) {
    if (end <= start) {
        return;
    }

    int pivotIndex = partition(arr, start, end);
    // for(int i = start; i < end+1; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");
    
    quickSort(arr, start, pivotIndex-1);
    quickSort(arr, pivotIndex + 1, end);
 
}

void bubblesort(int* array, int size) {
    int swapped = 0;

    for (int i = 0; i < size-1; i++) {
        swapped = 0;  // Initialize a flag to check if any swapping occurs

        for (int j = 0; j < size -1- i; j++) {
            if (array[j] > array[j + 1]) {
                swapInts(&array[j], &array[j+1]);
                swapped = 1;  // Set the flag to indicate a swap occurred
            }
        }

        // If no two elements were swapped in the inner loop, the array is already sorted
        if (swapped == 0) {
            break;
        }
    }

}

int writeToFile(char* fileName) {
    
    FILE *fptr;
    char filePath[100]; // Adjust the size as needed
    snprintf(filePath, sizeof(filePath), "../%s", fileName);
    fptr = fopen(filePath, "w");
    if (fptr == NULL) {
        perror("Could not open file for writing!\n");
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
    char filePath[104]; // Adjust the size as needed
    snprintf(filePath, sizeof(filePath) - 4, "../%s", fileName);
    // in this case sizeof() returns size of the whole array
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

int main() {

    srand(time(0)); // seed
    struct timespec begin, end;
    //clock_t start_time, end_time;
    //double cpu_time_used;

    int *myArray = NULL;
    int size = 0;
    int bytesAlloced = 0;
    if (1) {
        if (writeToFile("intArray.txt")) {
            printf("error with printing to the file\n");
        }
    }

    myArray = readFromFile("intArray.txt", &bytesAlloced);

    if (myArray == NULL) {
        printf("could not scan file contents properly\n");
        return 1;
    }
    size = (int)(bytesAlloced / sizeof(int));
    printf("allocated %d bytes in total for %d ints\n", bytesAlloced, size);

    if (0) {
        printf("Original array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", myArray[i]);
        }
        printf("\n");
    }

    //start_time = clock(); // Record the start time
    
    timespec_get(&begin, TIME_UTC);

    //Sort the array using quick sort
    quickSort(myArray, 0, size-1);
    
    // bubblesort(myArray, size);

    timespec_get(&end, TIME_UTC);
    // end_time = clock(); // Record the end time
    // cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // printf("time A: %ld\n", (long int)begin.tv_nsec);
    // printf("time B: %ld\n", (long int)end.tv_nsec);

    // printf("time A sec: %d\n", (int)begin.tv_sec);
    // printf("time B sec: %d\n", (int)end.tv_sec);

    // Get difference, then print
    double timeSeconds = (double)(end.tv_sec - begin.tv_sec);
    double timeNanoSeconds = (double)(end.tv_nsec - begin.tv_nsec);
    double totalTime = timeSeconds + timeNanoSeconds / 1.0e9;

    printf("Time taken for sorting %d elements with quicksort (in C): %012.10lf seconds\n", size, totalTime);

    if (0) {
        printf("\nSorted array (quick sort): ");
        for (int i = 0; i < size; i++) {
            printf("%d ", myArray[i]);
        }
    }
    free(myArray);
    
    //printf("\nTime taken for sorting %d elements with quicksort: %.8f seconds\n", size, cpu_time_used);

    return 0;
}
