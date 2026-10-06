#include "matmul.h"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

bool check_matrix(const std::vector<std::vector<double>> &expected,
                  const std::vector<std::vector<double>> &actual) {
  double epsilon = 1e-9;
  if (expected.size() != actual.size())
    return false;
  for (size_t i = 0; i < expected.size(); i++) {
    if (expected[i].size() != actual[i].size())
      return false;
    for (size_t j = 0; j < expected[i].size(); j++) {
      if (std::abs(expected[i][j] - actual[i][j]) > epsilon)
        return false;
    }
  }
  return true;
}

void print_success(const std::string &test_name) {
  std::cout << "======\n" << test_name << ": SUCCESS\n" << "======\n";
}

void print_failed_mul(const std::string &test_name,
                      const std::vector<std::vector<double>> &expected,
                      const std::vector<std::vector<double>> &actual) {
  std::cout << "======\n" << test_name << ": FAILED\n";
  std::cout << "Expected:\n";
  print_matrix(expected);
  std::cout << "Actual:\n";
  print_matrix(actual);
  std::cout << "======\n";
}

void print_failed_check(const std::string &test_name, bool expected) {
  std::string msg =
      expected == true ? "succeed, but it failed." : "fail, but it succeeded.";
  std::cout << "======\n"
            << test_name
            << ": FAILED\nExpected the multiplication possibility check to "
            << msg << "\n======\n";
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

  if (!can_multiply(matrix1.size(), matrix1[0].size(), matrix2.size(),
                    matrix2[0].size())) {
    print_failed_check("test_matmul_identity", true);
    return;
  }

  if (check_matrix(matrix1, actual))
    print_success("test_matmul_identity");
  else
    print_failed_mul("test_matmul_identity", matrix1, actual);
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

  if (!can_multiply(matrix1.size(), matrix1[0].size(), matrix2.size(),
                    matrix2[0].size())) {
    print_failed_check("test_matmul_zero", true);
    return;
  }

  if (check_matrix(matrix2, actual))
    print_success("test_matmul_zero");
  else
    print_failed_mul("test_matmul_zero", matrix2, actual);
}

void test_matmul_same_dims() {
  std::vector<std::vector<double>> matrix1 = {
      {1, -2, 3, -4},
      {5, -6, 7, -8},
      {9, -10, 11, -12},
      {13, -14, 15, -16},
  };
  std::vector<std::vector<double>> matrix2 = {
      {100.1, 100.2, 100.3, 100.4},
      {100.5, 100.6, 100.7, 100.8},
      {100.9, 101, 101.1, 101.2},
      {101.3, 101.4, 101.5, 101.6},
  };
  std::vector<std::vector<double>> expected = {
      {-203.4, -203.6, -203.8, -204},
      {-206.6, -206.8, -207, -207.2},
      {-209.8, -210, -210.2, -210.4},
      {-213, -213.2, -213.4, -213.6},
  };

  std::vector<std::vector<double>> actual = matmul(matrix1, matrix2);

  if (!can_multiply(matrix1.size(), matrix1[0].size(), matrix2.size(),
                    matrix2[0].size())) {
    print_failed_check("test_matmul_same_dims", true);
    return;
  }

  if (check_matrix(expected, actual))
    print_success("test_matmul_same_dims");
  else
    print_failed_mul("test_matmul_same_dims", expected, actual);
}

void test_matmul_different_dims() {
  std::vector<std::vector<double>> matrix1 = {
      {10, 100},
      {1000, 10000},
      {100000, 1000000},
  };
  std::vector<std::vector<double>> matrix2 = {
      {1, 2, 3},
      {4, 5, 6},
  };
  std::vector<std::vector<double>> expected = {
      {410, 520, 630},
      {41000, 52000, 63000},
      {4100000, 5200000, 6300000},
  };

  std::vector<std::vector<double>> actual = matmul(matrix1, matrix2);

  if (!can_multiply(matrix1.size(), matrix1[0].size(), matrix2.size(),
                    matrix2[0].size())) {
    print_failed_check("test_matmul_different_dims", true);
    return;
  }

  if (check_matrix(expected, actual))
    print_success("test_matmul_different_dims");
  else
    print_failed_mul("test_matmul_different_dims", expected, actual);
}

void test_matmul_incorrect_dims() {
  std::vector<std::vector<double>> matrix1 = {
      {10, 100},
      {1000, 10000},
      {100000, 1000000},
  };
  std::vector<std::vector<double>> matrix2 = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
  };

  if (!can_multiply(matrix1.size(), matrix1[0].size(), matrix2.size(),
                    matrix2[0].size()))
    print_success("test_matmul_incorrect_dims");
  else
    print_failed_check("test_matmul_incorrect_dims", false);
}

void test_matmul_empty_matrices() {
  std::vector<std::vector<double>> matrix1 = {};
  std::vector<std::vector<double>> matrix2 = {};
  std::vector<std::vector<double>> expected = {};
  std::vector<std::vector<double>> actual = matmul(matrix1, matrix2);

  if (!can_multiply(0, 0, 0, 0)) {
    print_failed_check("test_matmul_different_dims", true);
    return;
  }

  if (check_matrix(expected, actual))
    print_success("test_matmul_empty_matrices");
  else
    print_failed_mul("test_matmul_empty_matrices", expected, actual);
}

int main() {
  test_matmul_identity();
  test_matmul_zero();
  test_matmul_same_dims();
  test_matmul_different_dims();
  test_matmul_incorrect_dims();
  test_matmul_empty_matrices();
}
