#include "matrix.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

void expect_close(double a, double b) { assert(std::abs(a - b) < 1e-12); }

void test_known_product() {
    Matrix a(2, 3, {1,2,3,4,5,6});
    Matrix b(3, 2, {7,8,9,10,11,12});
    Matrix c = multiply(a, b);
    expect_close(c(0,0), 58); expect_close(c(0,1), 64);
    expect_close(c(1,0), 139); expect_close(c(1,1), 154);
}

void test_identity() {
    Matrix a(3,3, {1,2,3,4,5,6,7,8,9});
    Matrix i(3,3, {1,0,0,0,1,0,0,0,1});
    Matrix c = multiply(a, i);
    for (std::size_t r=0; r<3; ++r) for (std::size_t col=0; col<3; ++col)
        expect_close(c(r,col), a(r,col));
}

void test_zeros() {
    Matrix a(2,3); Matrix b(3,4); Matrix c = multiply(a,b);
    for (double x : c.data()) expect_close(x, 0);
}

void test_incompatible_dimensions() {
    Matrix a(2,3), b(2,2);
    bool threw = false;
    try { (void)multiply(a,b); } catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
}

int main() {
    test_known_product(); test_identity(); test_zeros(); test_incompatible_dimensions();
    std::cout << "All tests passed.\n";
}
