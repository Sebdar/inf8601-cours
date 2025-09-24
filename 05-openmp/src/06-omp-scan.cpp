#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>
#include <vector>

#include "utils.h"

constexpr size_t n = 33554432UL;  // large number
int main() {
    std::vector<float> a, b;

    a.resize(n); random_fill(a);
    b.resize(n); 

    // Serial scan
    auto t0 = now();
    float scan_sum = 0.f;
    for(auto i = 0; i < n; ++i) {
        scan_sum += a[i];
        b[i] = scan_sum;
    }
    auto t1 = now();
    std::cout << "Serial : " << count_ms(t1 - t0) << " ms\n";

    // Parallel add
    t0 = now();

    scan_sum = 0.f;
    #pragma omp parallel for reduction(inscan,+: scan_sum)
    for(auto i = 0; i < n; ++i) {
        scan_sum += a[i];
        #pragma omp scan inclusive(scan_sum)
        b[i] = scan_sum;
    }
    
    t1 = now();
    std::cout << "Parallel : " << count_ms(t1 - t0) << " ms\n";
}
