#ifndef MATMUL_H
#define MATMUL_H

#include <cstddef>
#include <vector>

bool can_multiply(size_t m1, size_t n1, size_t m2, size_t n2);

std::vector<std::vector<double>>
matmul(const std::vector<std::vector<double>> &matrix1,
       const std::vector<std::vector<double>> &matrix2);

void print_matrix(const std::vector<std::vector<double>> &matrix);

#endif
