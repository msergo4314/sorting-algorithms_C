#include <stdio.h>

void bubbleSort(int arr[], int size) {
    int temp;
    int swapped;

    for (int i = 0; i < size - 1; i++) {
        swapped = 0;  // Initialize a flag to check if any swapping occurs

        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;  // Set the flag to indicate a swap occurred
            }
        }

        // If no two elements were swapped in the inner loop, the array is already sorted
        if (swapped == 0) {
            break;
        }
    }
}

int main() {
    int myArray[12] = {64, 34, 25, 12, 22, 11, 90, 1, 3, 7, 0, 8};
    int size = 12;

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", myArray[i]);
    }

    // Sort the array using bubble sort
    bubbleSort(myArray, size);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", myArray[i]);
    }

    return 0;
}
