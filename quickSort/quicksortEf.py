import numpy as np
import random
import time

ARRAYRANGE = 101  # note that this is the number of values, not the max number
ARRAYSIZE = int(1e5)  # size of the array

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
    start_time = time.time()

    if False:
        write_to_file("intArray.txt")

    my_array = read_from_file("intArray.txt")
    size = len(my_array)
    print(f"allocated {size * 4} bytes in total for {size} ints")

    if False:
        print("Original array:", my_array)

    my_array = np.array(my_array)  # Convert to NumPy array
    my_array = np.sort(my_array)   # Use NumPy's sorting function

    end_time = time.time()
    total_time = end_time - start_time
    print(f"Time taken for sorting {size} elements with NumPy: {total_time:.10f} seconds")

    if False:
        print("\nSorted array (NumPy):", my_array)

if __name__ == "__main__": # only run main when not imported
    main()
