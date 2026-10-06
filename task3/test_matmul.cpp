#include "matmul.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

bool check_matrix(const std::vector<std::vector<double>> &expected,
                  const std::vector<std::vector<double>> &actual) {
  if (expected.size() != actual.size())
    return false;
  for (size_t i = 0; i < expected.size(); i++) {
    if (expected[i].size() != actual[i].size())
      return false;
    for (size_t j = 0; j < expected[i].size(); j++) {
      if (expected[i][j] != actual[i][j])
        return false;
    }
  }
  return true;
}

void print_success(const std::string &test_name) {
  std::cout << "======\n" << test_name << ": SUCCESS\n" << "======\n";
}

void print_failed(const std::string &test_name,
                  const std::vector<std::vector<double>> &expected,
                  const std::vector<std::vector<double>> &actual) {
  std::cout << "======\n" << test_name << ": FAILED\n";
  std::cout << "Expected:\n";
  print_matrix(expected);
  std::cout << "Actual:\n";
  print_matrix(actual);
  std::cout << "======\n";
}

void test_matmul_identity() {
  std::vector<std::vector<double>> matrix1 = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
  };
  std::vector<std::vector<double>> matrix2 = {
      {1, 0, 0},
      {0, 1, 0},
      {0, 0, 1},
  };
  std::vector<std::vector<double>> actual = matmul(matrix1, matrix2);
  if (check_matrix(matrix1, actual))
    print_success("test_matmul_identity");
  else
    print_failed("test_matmul_identity", matrix1, actual);
}

void test_matmul_zero() {
  std::vector<std::vector<double>> matrix1 = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
  };
  std::vector<std::vector<double>> matrix2 = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
  };
  std::vector<std::vector<double>> actual = matmul(matrix1, matrix2);
  if (check_matrix(matrix2, actual))
    print_success("test_matmul_zero");
  else
    print_failed("test_matmul_zero", matrix2, actual);
}

int main() {
  test_matmul_identity();
  test_matmul_zero();
}
