#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix slice_2d(const Matrix& matrix,
                std::size_t row_start, std::size_t row_end, std::size_t row_step,
                std::size_t col_start, std::size_t col_end, std::size_t col_step) {
    if (row_step == 0 || col_step == 0) {
        throw std::invalid_argument("slice steps must be non-zero");
    }
    if (row_start > row_end || col_start > col_end) {
        throw std::invalid_argument("this example expects non-decreasing slice bounds");
    }

    Matrix result;
    for (std::size_t r = row_start; r < row_end && r < matrix.size(); r += row_step) {
        std::vector<int> row;
        for (std::size_t c = col_start; c < col_end && c < matrix[r].size(); c += col_step) {
            row.push_back(matrix[r][c]);
        }
        result.push_back(row);
    }
    return result;
}

void write_csv(const Matrix& matrix, const std::string& path) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("cannot open output file: " + path);
    for (const auto& row : matrix) {
        for (std::size_t c = 0; c < row.size(); ++c) {
            if (c) out << ',';
            out << row[c];
        }
        out << '\n';
    }
}

void print_matrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto value : row) std::cout << std::setw(4) << value;
        std::cout << '\n';
    }
}

int main(int argc, char** argv) {
    const std::string output = argc > 1 ? argv[1] : "cpp_slice.csv";

    // 6 x 8 matrix with values 1..48.
    Matrix matrix(6, std::vector<int>(8));
    int value = 1;
    for (auto& row : matrix) {
        for (auto& cell : row) cell = value++;
    }

    // Equivalent to NumPy: matrix[1:5:2, 2:7:2]
    const Matrix sliced = slice_2d(matrix, 1, 5, 2, 2, 7, 2);

    std::cout << "Original matrix:\n";
    print_matrix(matrix);
    std::cout << "\nC++ slice [rows 1:5:2, cols 2:7:2]:\n";
    print_matrix(sliced);

    write_csv(sliced, output);
    return 0;
}
