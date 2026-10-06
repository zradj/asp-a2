# Task 3 - Matrix Multiplication

You can easily run the C++ code if you have the `make` command. Go to the `code` directory and use the following commands:

```bash
# Test C++ execution time
make time

# Run the C++ CLI
make cli

# Run unit tests for C++
make test

# Remove executables
make clean
```

For Python, just run `python3` directly on the files. Make sure you have `numpy` installed.

## Analysis of Code Size

For code size analysis, I will consider only the files `matmul.cpp` and `matmul_cli.py` for C++ and Python, respectively.

Overall, if we exclude the I/O code in both languages, the code size boils down to only eight lines of code:

```python
def read_matrix():
    # ...
    if matrix.ndim != 2:
        print("Invalid matrix")
        sys.exit(1)
    # ...

def main:
    # ...
    cols1 = len(matrix[0]) if len(matrix) > 0 else 0
    if cols1 != len(matrix2):
        print("Cannot multiply the matrices. The number of columns of the first matrix must match the number of rows of the second.")
        sys.exit(1)
    # ...
    print(matrix1 @ matrix2)
```

The `@` operator calls the `__matmul__` dunder method on the NumPy arrays under the hood.

For the C++ code in `matmul.cpp`, there are 19 lines of significant code in total: the `can_multiply` and `matmul` functions.

It is natural that C++ code is lengthier than the Python code, because C++ does not have out-of-the-box functionality for matrix multiplication, unlike a library like NumPy. Also, the code size is almost certainly much larger in Python if we take the NumPy source code into account.

## Analysis of the Execution Times

The C++ and Python codes multiply two 8x8 matrices (same in both codes). The execution time only measures the time it took to multiply the matrices. The I/O and assignment operations are not counted.

Python ran in an average of `0.000026` seconds over five runs (or 26 microseconds). C++ ran in an average of 46 microseconds over five runs.

I am not surprised by these results, because NumPy uses C under the hood and that C code has been extremely optimized by dozens of experts over many years. It is not surprising that my C++ code I wrote in a day cannot outperform NumPy.
