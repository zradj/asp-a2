#include "matmul.h"
#include <chrono>
#include <iostream>
#include <vector>

int main() {
  std::vector<std::vector<double>> matrix1 = {
      {1337, 42, 11, 22, 1000, -555, 817, 123123},
      {1231, 77676, 43, 67, 0, 575, 1231, -887},
      {999, -99, 32, 1313, 888, 15151, 7, 1},
      {1, -1, 1, 1, -1, 1, -1, -1},
      {565, 6, 0, -1, 0, 12, 5, 8888},
      {5645, -9898, 9000, 8000, -7000, 6000, -5050, 5000},
      {1, 2, 3, -4, 5, 6, 7, 8},
      {9, 10, -11, 12, 13, 14, 15, 17},
  };
  std::vector<std::vector<double>> matrix2 = {
      {8, 9, 10, 11, 0, -555, 817, -123123},
      {1231, 77676, 43, 67, 0, 575, 1231, 887},
      {441, 666, 6686, 998, 8888, -7, 7, 1},
      {11, 1, 122, 1, 1, 0, 23, 1},
      {565, 6, 0, 0, 0, 12, 5, 8888},
      {5645, 9898, 9000, 8000, 7000, 6000, 5050, 5000},
      {1, 2, 3, 4, 5, 6, 7, 8},
      {9, 10, 11, 12, 13, 14, 15, 17},
  };

  auto start = std::chrono::high_resolution_clock::now();

  std::vector<std::vector<double>> res = matmul(matrix1, matrix2);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  std::cout << "Result:\n";
  print_matrix(res);
  std::cout << "Execution time: " << duration.count() << " microseconds\n";
}
