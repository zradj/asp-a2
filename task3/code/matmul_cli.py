import sys
import numpy as np

def read_matrix():
    matrix = []
    while True:
        line = input()
        if line.strip() == "":
            break
        try:
            nums = [float(x) for x in line.strip().split()]
            matrix.append(nums)
        except ValueError:
            print("One of the inputs was not a valid number")
            sys.exit(1)

    try:
        matrix = np.asanyarray(matrix)
    except ValueError:
        print("Invalid matrix")
        sys.exit(1)

    if matrix.ndim != 2:
        print("Invalid matrix")
        sys.exit(1)

    return matrix


def main():
    print("Please enter the first matrix:")
    matrix1 = read_matrix()
    print("Please enter the second matrix:")
    matrix2 = read_matrix()

    cols1 = len(matrix[0]) if len(matrix) > 0 else 0
    if cols1 != len(matrix2):
        print("Cannot multiply the matrices. The number of columns of the first matrix must match the number of rows of the second.")
        sys.exit(1)

    print(matrix1 @ matrix2)

if __name__ == "__main__":
    main()
