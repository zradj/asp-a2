#include "matrix.hpp"
#include <stdexcept>

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}

Matrix::Matrix(std::size_t rows, std::size_t cols, const std::vector<double>& data)
    : rows_(rows), cols_(cols), data_(data) {
    if (data.size() != rows * cols) throw std::invalid_argument("data size mismatch");
}

double& Matrix::operator()(std::size_t row, std::size_t col) { return data_[row * cols_ + col]; }
double Matrix::operator()(std::size_t row, std::size_t col) const { return data_[row * cols_ + col]; }

Matrix multiply(const Matrix& a, const Matrix& b) {
    if (a.cols() != b.rows()) throw std::invalid_argument("incompatible matrix dimensions");
    Matrix c(a.rows(), b.cols());
    for (std::size_t i = 0; i < a.rows(); ++i)
        for (std::size_t k = 0; k < a.cols(); ++k) {
            const double aik = a(i, k);
            for (std::size_t j = 0; j < b.cols(); ++j)
                c(i, j) += aik * b(k, j);
        }
    return c;
}
