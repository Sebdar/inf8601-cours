#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>
#include <vector>

#include "utils.h"

constexpr size_t n = 33554432UL;  // large number
int main() {
    float *a, *b, *c;

    a = new float[n]; random_fill(a, n);
    b = new float[n]; random_fill(b, n);
    c = new float[n];

    // Serial add
    auto t0 = now();
    for(auto i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
    auto t1 = now();
    std::cout << "Serial : " << count_ms(t1 - t0) << " ms\n";

    // Parallel add
    t0 = now();
    #pragma omp parallel for simd
    for(auto i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
    t1 = now();
    std::cout << "Parallel : " << count_ms(t1 - t0) << " ms\n";

    delete a;
    delete b;
    delete c;
}
