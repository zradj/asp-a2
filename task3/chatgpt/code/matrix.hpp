#pragma once
#include <cstddef>
#include <vector>

class Matrix {
public:
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(std::size_t rows, std::size_t cols, const std::vector<double>& data);

    double& operator()(std::size_t row, std::size_t col);
    double operator()(std::size_t row, std::size_t col) const;
    std::size_t rows() const noexcept { return rows_; }
    std::size_t cols() const noexcept { return cols_; }
    const std::vector<double>& data() const noexcept { return data_; }

private:
    std::size_t rows_, cols_;
    std::vector<double> data_;
};

Matrix multiply(const Matrix& a, const Matrix& b);
