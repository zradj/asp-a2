#include "matmul.h"
#include <cstdio>
#include <iostream>
#include <vector>

void read_matrix(std::vector<std::vector<double>> &matrix, size_t m, size_t n) {
  matrix.resize(m);
  for (auto &row : matrix) {
    row.resize(n);
    for (auto &item : row)
      std::cin >> item;
  }
}

int main() {
  std::vector<std::vector<double>> matrix1, matrix2;
  size_t m1, n1, m2, n2;

  std::cout << "Please enter the dimensions of the first matrix (rows, "
               "columns). Example: 2 3\n";
  if (!(std::cin >> m1 >> n1)) {
    std::cout << "Invalid input.\n";
    return 1;
  };
  if (m1 < 0 || n1 < 0) {
    std::cout << "The dimensions must be non-negative.\n";
    return 1;
  }
  std::cout << "Please enter the dimensions of the second matrix (rows, "
               "columns). Example: 3 2\n";
  if (!(std::cin >> m2 >> n2)) {
    std::cout << "Invalid input.\n";
    return 1;
  };
  if (m2 < 0 || n2 < 0) {
    std::cout << "The dimensions must be non-negative.\n";
    return 1;
  }

  if (!can_multiply(m1, n1, m2, n2)) {
    std::cout
        << "Cannot multiply the matrices. The number of columns of the first "
           "matrix must match the number of rows of the second.\n";
    return 1;
  }

  std::cout << "Please enter the first matrix.\n";
  read_matrix(matrix1, m1, n1);
  std::cout << "Please enter the second matrix.\n";
  read_matrix(matrix2, m2, n2);

  std::vector<std::vector<double>> res = matmul(matrix1, matrix2);
  printf("Result (%lux%lu):\n", m1, n2);
  print_matrix(res);
}
