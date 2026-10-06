import sys
import numpy as np

def read_matrix():
    matrix = []
    while True:
        line = input()
        if line.strip() == "":
            break
        nums = [float(x) for x in line.strip().split()]
        matrix.append(nums)
    matrix = np.asanyarray(matrix)
    if matrix.ndim != 2 or matrix.dtype != np.float64:
        print("Invalid matrix")
        sys.exit(1)
    return matrix


def main():
    print("Please enter the first matrix:")
    matrix1 = read_matrix()
    print("Please enter the second matrix:")
    matrix2 = read_matrix()
    print(matrix1 @ matrix2)

if __name__ == "__main__":
    main()
