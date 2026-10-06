#include <iostream>
#include <vector>

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

void print_matrix(const std::vector<std::vector<double>> &matrix) {
  for (auto &row : matrix) {
    for (auto &item : row)
      std::cout << item << ' ';
    std::cout << '\n';
  }
}
