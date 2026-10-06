#include "matrix.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main(int argc, char** argv) {
    const std::size_t n = argc > 1 ? std::stoul(argv[1]) : 500;
    const int repeats = argc > 2 ? std::stoi(argv[2]) : 5;
    std::mt19937_64 rng(42); std::uniform_real_distribution<double> d(0.0,1.0);
    Matrix a(n,n), b(n,n);
    for (std::size_t i=0;i<n;++i) for (std::size_t j=0;j<n;++j) { a(i,j)=d(rng); b(i,j)=d(rng); }
    volatile double sink = 0;
    multiply(a,b); // warm-up
    std::vector<double> times;
    for (int r=0;r<repeats;++r) {
        auto start=std::chrono::steady_clock::now(); Matrix c=multiply(a,b);
        auto end=std::chrono::steady_clock::now();
        times.push_back(std::chrono::duration<double>(end-start).count()); sink += c(0,0);
    }
    double sum=0, mn=times[0], mx=times[0];
    for(double t:times){sum+=t; if(t<mn)mn=t; if(t>mx)mx=t;}
    std::cout << "cpp," << n << ',' << repeats << ',' << mn << ',' << sum/repeats << ',' << mx << ',' << sink << "\n";
}
