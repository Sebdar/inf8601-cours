#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>
#include <vector>

#include "utils.h"

constexpr size_t n = 33554432UL;  // large number
int main() {
    std::vector<float> a, b, c;

    a.resize(n); random_fill(a);
    b.resize(n); random_fill(b);
    c.resize(n);

    // Serial add
    auto t0 = now();
    for(auto i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
    auto t1 = now();
    std::cout << "Serial : " << count_ms(t1 - t0) << " ms\n";

    // Parallel add
    t0 = now();
    #pragma omp parallel for
    for(auto i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
    t1 = now();
    std::cout << "Parallel : " << count_ms(t1 - t0) << " ms\n";
}
