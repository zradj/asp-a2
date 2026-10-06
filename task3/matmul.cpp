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

// takes all dimensions for convenience and readability
bool can_multiply(size_t m1, size_t n1, size_t m2, size_t n2) {
  return n1 == m2;
}

std::vector<std::vector<double>>
matmul(const std::vector<std::vector<double>> &matrix1,
       const std::vector<std::vector<double>> &matrix2) {
  size_t i, j, k, mat2_cols = matrix2.size() > 0 ? matrix2[0].size() : 0;
  std::vector<std::vector<double>> res(matrix1.size());
  for (auto &row : res)
    row.resize(mat2_cols, 0);

  for (i = 0; i < matrix1.size(); i++)
    for (j = 0; j < mat2_cols; j++)
      for (k = 0; k < matrix2.size(); k++)
        res[i][j] += matrix1[i][k] * matrix2[k][j];

  return res;
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
  for (auto &row : res) {
    for (auto &item : row)
      std::cout << item << ' ';
    std::cout << '\n';
  }
}
