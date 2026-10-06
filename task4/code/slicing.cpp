#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  size_t rows, cols, row_start, row_end, col_start, col_end;

  std::ifstream input("input.txt");
  std::string line;
  std::getline(input, line);
  std::sscanf(line.c_str(), "%lu %lu", &rows, &cols);

  std::vector<std::vector<int>> img(rows);
  for (size_t i = 0; i < rows; i++) {
    img[i].resize(cols);
    std::getline(input, line);
    std::istringstream iss(line);
    for (auto &item : img[i])
      iss >> item;
  }

  std::cout << "Please input the slicing parameters (format: \"row_start "
               "row_end col_start col_end\"): ";
  std::cin >> row_start >> row_end >> col_start >> col_end;

  if (row_start > rows) {
    std::cout << "row_start is out of bounds\n";
    return 1;
  }
  if (row_end > rows) {
    std::cout << "row_end is out of bounds\n";
    return 1;
  }
  if (col_start > cols) {
    std::cout << "col_start is out of bounds\n";
    return 1;
  }
  if (col_end > rows) {
    std::cout << "col_end is out of bounds\n";
    return 1;
  }
  if (row_start > row_end) {
    std::cout << "row_start must be smaller than row_end\n";
    return 1;
  }
  if (col_start > col_end) {
    std::cout << "col_start must be smaller than col_end\n";
    return 1;
  }

  std::ofstream output("output_cpp.txt");
  for (size_t i = row_start; i < row_end; i++) {
    std::string row = "";
    for (size_t j = col_start; j < col_end; j++)
      row += std::to_string(img[i][j]) + ' ';
    row += '\n';
    output << row;
  }
}
