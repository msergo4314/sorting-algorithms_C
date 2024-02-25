import random
import time
import sys

sys.setrecursionlimit(10**6)  # Adjust the limit as needed


ARRAYRANGE = 101  # note that this is the number of values, not the max number
ARRAYSIZE = int(1e5)  # size of the array


def swap_ints(a, b):
    temp = a
    a = b
    b = temp


def partition(arr, start, end):
    pivot = arr[end]
    i = start - 1
    j = start
    while j < end:
        if arr[j] <= pivot:
            i += 1
            arr[j], arr[i] = arr[i], arr[j]
        j += 1
    i += 1
    arr[j], arr[i] = arr[i], arr[j]
    return i


def quick_sort(arr, start, end):
    if end <= start:
        return
    pivot_index = partition(arr, start, end)
    quick_sort(arr, start, pivot_index - 1)
    quick_sort(arr, pivot_index + 1, end)


def bubble_sort(array):
    size = len(array)
    swapped = False
    for i in range(size - 1):
        swapped = False
        for j in range(size - 1 - i):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]
                swapped = True
        if not swapped:
            break


def write_to_file(file_name):
    file_path = f"../{file_name}"
    with open(file_path, "w") as fptr:
        for _ in range(ARRAYSIZE):
            fptr.write(f"{random.randint(0, ARRAYRANGE - 1)} ")


def read_from_file(file_name):
    file_path = f"../{file_name}"
    array = []
    with open(file_path, "r") as fptr:
        for num in fptr.read().split():
            array.append(int(num))
    return array


def main():
    random.seed(time.time())

    if False:
        write_to_file("intArray.txt")

    my_array = read_from_file("intArray.txt")
    size = len(my_array)
    print(f"allocated {size * 4} bytes in total for {size} ints")

    if False:
        print("Original array:", my_array)
    
    start_time = time.time()
    quick_sort(my_array, 0, size - 1)
    # bubble_sort(my_array)
    end_time = time.time()

    total_time = end_time - start_time
    print(f"Time taken for sorting {size} elements with quicksort: {total_time:.10f} seconds")

    if False:
        print("\nSorted array (quick sort):", my_array)

if __name__ == "__main__":
    main()