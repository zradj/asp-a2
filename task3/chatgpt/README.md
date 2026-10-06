# Matrix Multiplication: NumPy vs C++

This project implements dense matrix multiplication in two ways:

- **Python/NumPy** using NumPy arrays and the `@` matrix-multiplication operator.
- **C++** using a small row-major `Matrix` class and a cache-friendlier `i-k-j` triple loop.

The C++ implementation includes unit tests for correctness and invalid dimensions.

## Requirements

- Python 3
- NumPy
- A C++17 compiler (tested with GCC)

## Implementation

### NumPy

```python
import numpy as np

def multiply(a: np.ndarray, b: np.ndarray) -> np.ndarray:
    return a @ b
```

The `@` operator performs matrix multiplication and uses NumPy's optimized native linear-algebra implementation.

### C++

The C++ implementation stores elements in a contiguous row-major `std::vector<double>`. Multiplication uses the loop ordering `i-k-j`:

```cpp
for (std::size_t i = 0; i < a.rows(); ++i)
    for (std::size_t k = 0; k < a.cols(); ++k) {
        const double aik = a(i, k);
        for (std::size_t j = 0; j < b.cols(); ++j)
            c(i, j) += aik * b(k, j);
    }
```

For matrices of dimensions `m × n` and `n × p`, both implementations have the mathematical complexity **O(mnp)** and require **O(mp)** additional space for the result.

## C++ unit tests

The test suite checks:

1. A known 2×3 by 3×2 multiplication.
2. Multiplication by the identity matrix.
3. Multiplication involving zero matrices.
4. Rejection of incompatible dimensions.

Build and run the tests:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic \
    code/matrix.cpp code/test_matrix.cpp -o code/test_matrix
./code/test_matrix
```

Expected output:

```text
All tests passed.
```

## Benchmark methodology

Both implementations were warmed up once and then executed **5 times** for each square matrix size. The reported values are the minimum, mean, and maximum execution times across those five multiplication runs.

The C++ program was compiled with:

```text
g++ -std=c++17 -O2 -Wall -Wextra -pedantic
```

The Python environment used **NumPy 2.3.5**.

Benchmark command:

```bash
# C++
./code/benchmark 500 5

# NumPy
PYTHONPATH=python python3 code/benchmark.py --size 500 --repeats 5
```

### Results

Times below are in seconds and were measured in the same execution environment. Exact timings will vary with CPU load, compiler, BLAS backend, and NumPy configuration.

| Matrix size |  C++ min | C++ mean |  C++ max | NumPy min | NumPy mean | NumPy max | C++/NumPy mean |
| ----------: | -------: | -------: | -------: | --------: | ---------: | --------: | -------------: |
|         100 | 0.000905 | 0.001628 | 0.002546 |  0.000036 |   0.000043 |  0.000067 |          37.7× |
|         250 | 0.009063 | 0.010701 | 0.016488 |  0.000392 |   0.000576 |  0.000749 |          18.6× |
|         500 | 0.078411 | 0.088033 | 0.110472 |  0.019897 |   0.027977 |  0.053665 |          3.15× |
|         750 | 0.280837 | 0.297836 | 0.314375 |  0.011930 |   0.024207 |  0.056897 |          12.3× |

The relative timings are not universal: NumPy may be linked against a highly optimized BLAS implementation and may use multiple CPU threads, whereas the C++ implementation here is a straightforward single-threaded implementation. Therefore, these measurements compare the supplied implementations rather than proving that “Python is faster than C++.”

The non-monotonic NumPy timings also demonstrate why a single benchmark run should not be treated as a definitive performance measurement; system scheduling and BLAS behavior can have a noticeable effect. For a rigorous performance study, repeat the experiment several times, pin CPU/thread settings, and report distributions rather than only one run.

## Code-size analysis

The implementation source contains:

| File                   |   Lines |     Bytes |
| ---------------------- | ------: | --------: |
| `code/matrix.hpp`      |      21 |       634 |
| `code/matrix.cpp`      |      25 |     1,019 |
| `code/test_matrix.cpp` |      39 |     1,133 |
| `code/benchmark.cpp`   |      24 |     1,035 |
| `code/multiply.py`     |       4 |        95 |
| `code/benchmark.py`    |      12 |       557 |
| **Total**              | **125** | **4,473** |

The core multiplication itself is particularly small in both versions. NumPy expresses the operation in one line because the array storage, dimension handling, optimized kernels, and numerical operations are provided by the library. The C++ version requires substantially more source code because it explicitly defines matrix storage, indexing, dimension validation, multiplication, tests, and benchmarking.

## Analysis

### Correctness

The C++ implementation passed all four unit-test groups. The tests cover both ordinary multiplication and important edge/error cases, although they are not a formal proof of correctness for every possible matrix.

### Execution time

For the tested environment, NumPy was faster at every matrix size. This is expected for a NumPy operation such as `@`: the Python layer mainly dispatches the operation, while the actual numerical work is performed by optimized compiled code. The C++ implementation is also compiled and optimized, but it is still a basic scalar triple-loop implementation and does not use a specialized matrix-multiplication library.

The C++ `i-k-j` ordering is preferable to a naive `i-j-k` ordering for this row-major representation because it reuses `a(i,k)` and accesses a row of `b` contiguously in the innermost loop. Nevertheless, optimized BLAS implementations can use blocking/tiling, SIMD instructions, cache-aware algorithms, and multiple threads, so they can outperform this simple implementation by a large margin.

### Code size

The NumPy core is much smaller: the actual multiplication is a single expression. The C++ implementation is more verbose because it exposes lower-level details. This illustrates an important trade-off: high-level numerical libraries provide concise APIs while moving implementation complexity into optimized native libraries.

## Conclusion

- **NumPy:** smallest implementation and fastest in this benchmark environment.
- **C++:** more implementation code but full control over memory layout and the multiplication algorithm.
- **Correctness:** verified through dedicated C++ unit tests.
- **Performance:** the C++ implementation could be substantially improved with SIMD, cache blocking, parallelism, or a tuned BLAS library.

The benchmark should be considered an empirical comparison of these particular implementations and environment settings, not a general claim about Python versus C++ performance.
